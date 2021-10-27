/* -*- c++ -*- */
/*
 * Copyright 2021 Victor Omoniyi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "litexgnu_impl.h"
#include <gnuradio/io_signature.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <algorithm>
#include <exception>

extern "C" {
#include "config.h"
#include "csr.h"
#include "flags.h"
#include "liblitepcie.h"
#include "litepcie.h"
#include "soc.h"
}

struct pollfd fds;
int64_t reader_hw_count, reader_sw_count;
int64_t writer_hw_count, writer_sw_count;


sig_atomic_t keep_running = 1;

void intHandler(int dummy) { keep_running = 0; }

namespace gr {
namespace litexgnu {
using input_type = float;
using output_type = float;
litexgnu::sptr litexgnu::make() { return gnuradio::make_block_sptr<litexgnu_impl>(); }

/*
 * The private constructor
 */
litexgnu_impl::litexgnu_impl()
    : gr::block("litexgnu",
                gr::io_signature::make(1, 1, sizeof(input_type)),
                gr::io_signature::make(1, 1, sizeof(output_type)))
{
    set_output_multiple(DMA_BUFFER_SIZE / sizeof(output_type));
}

/*
 * Our virtual destructor.
 */
litexgnu_impl::~litexgnu_impl() {}

void litexgnu_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    ninput_items_required[0] = noutput_items;
}

bool litexgnu_impl::start()
{
    static char litepcie_device[1024];
    static int litepcie_device_num;

    snprintf(
        litepcie_device, sizeof(litepcie_device), "/dev/litepcie%d", litepcie_device_num);


    fds.fd = open(litepcie_device, O_RDWR | O_CLOEXEC);
    fds.events = POLLIN | POLLOUT;
    if (fds.fd < 0) {
        fprintf(stderr, "Could not init driver\n");
        exit(1);
    }

    unsigned char fpga_identification[256];

    for (int i = 0; i < 256; i++)
        fpga_identification[i] = litepcie_readl(fds.fd, CSR_IDENTIFIER_MEM_BASE + 4 * i);
    printf("FPGA identification: %s\n", fpga_identification);

    /* request dma */
    if ((litepcie_request_dma_reader(fds.fd) == 0) |
        (litepcie_request_dma_writer(fds.fd) == 0)) {
        printf("DMA not available, exiting.\n");
        exit(1);
    }

    /* enable dma loopback*/
    litepcie_dma(fds.fd, 1);

    signal(SIGINT, intHandler);

    return 0;
}

bool litexgnu_impl::stop()
{
    litepcie_dma_reader(fds.fd, 0, &reader_hw_count, &reader_sw_count);
    litepcie_dma_writer(fds.fd, 0, &writer_hw_count, &writer_sw_count);
    litepcie_release_dma_reader(fds.fd);
    litepcie_release_dma_writer(fds.fd);

    if (fds.fd >= 1) {
        close(fds.fd);
    }
    return 0;
}

int litexgnu_impl::general_work(int noutput_items,
                                gr_vector_int& ninput_items,
                                gr_vector_const_void_star& input_items,
                                gr_vector_void_star& output_items)
{
    int bytes_written = 0;
    int bytes_read = 0;
    int consumed_items = 0;
    int created_items = 0;
    int i = 0;
    int errors;
    int64_t reader_sw_count_last = 0;

    int64_t duration;
    int64_t last_time;


    const float** in = (const float**)&input_items[0];
    float** out = (float**)&output_items[0];
    int ret = 0;

    /* set / get dma */
    litepcie_dma_writer(fds.fd, 1, &writer_hw_count, &writer_sw_count);
    litepcie_dma_reader(fds.fd, 1, &reader_hw_count, &reader_sw_count);

    /* polling */
    ret = poll(&fds, 1, 100);
    if (ret <= 0) {
        return 0;
    }

    /* write event */
    if (fds.revents & POLLOUT) {
        int max_items_write = DMA_BUFFER_TOTAL_SIZE / sizeof(input_type);
        int n_dma_blocks = (ninput_items[0] * sizeof(input_type)) / DMA_BUFFER_SIZE;
        int n_dma_items = n_dma_blocks * DMA_BUFFER_SIZE / sizeof(input_type);
        int n_write_items = std::min(max_items_write, n_dma_items);


        bytes_written = write(fds.fd, (void*)in[0], n_write_items * sizeof(input_type));

        if (bytes_written != n_write_items * sizeof(input_type)) {
            std::cout << "Error: Max bytes already written" << '\n';
        }
        consumed_items = bytes_written / sizeof(input_type);

        // std::cout << "Bytes written: " << bytes_written << '\n';
    }


    /* read event */
    if (fds.revents & POLLIN) {
        int max_items_read = DMA_BUFFER_TOTAL_SIZE / sizeof(output_type);
        int n_read_items = std::min(max_items_read, noutput_items);

        // std::cout << "Reading items: " << n_read_items << '\n';
        bytes_read = read(fds.fd, (void*)out[0], n_read_items * sizeof(output_type));

        if (bytes_read != n_read_items * sizeof(output_type)) {
            std::cout << "Error: Max bytes already read" << '\n';
        }
        created_items = bytes_read / sizeof(output_type);
        // std::cout << "Items read: " << created_items << '\n';
    }

    /* statistics */
    duration = get_time_ms() - last_time;
    if (duration > 200) {
        if (i % 10 == 0)
            printf("\e[1mDMA_SPEED(Gbps) TX_BUFFERS RX_BUFFERS  DIFF  ERRORS\e[0m\n");
        i++;
        printf("%14.2lf" "%14.2f %10" PRIu64 " %10" PRIu64 " %6" PRIu64 " %7u\n",
               (double)(reader_sw_count - reader_sw_count_last) * DMA_BUFFER_SIZE * 8 / ((double)duration * 1e6),
               reader_sw_count,
               writer_sw_count,
               reader_sw_count - writer_sw_count,
               errors);
        errors = 0;
        last_time = get_time_ms();
        reader_sw_count_last = reader_sw_count;
    }

    // Tell runtime system how many input items we consumed on
    // each input stream.
    consume_each(consumed_items);


    // Tell runtime system how many output items we produced.

    return created_items;
}


} /* namespace litexgnu */


} /* namespace gr */