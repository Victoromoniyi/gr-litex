/* -*- c++ -*- */
/*
 * Copyright 2021 Victor Omoniyi.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <gnuradio/io_signature.h>
#include "litexgnu_impl.h"
#include <algorithm>
#include <exception>

extern "C" 
{
#include "litepcie.h"
#include "config.h"
#include "csr.h"
#include "flags.h"
#include "soc.h"
#include "liblitepcie.h"
}

static char litepcie_device[1024];
static int litepcie_device_num;
int fd;
char *buf_rd, *buf_wr;
struct pollfd fds;
uint32_t errors;
ssize_t len;



namespace gr {
  namespace litexgnu {
    using input_type = float;
    using output_type = float;
    litexgnu::sptr              
    litexgnu::make()
    {
      return gnuradio::make_block_sptr<litexgnu_impl>(
        );

    }


static void info(void)
{
    int i;
    unsigned char fpga_identification[256];

    fd = open(litepcie_device, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Could not init driver\n");
        exit(1);
    }

    for(i=0; i<256; i++)
        fpga_identification[i] = litepcie_readl(fd, CSR_IDENTIFIER_MEM_BASE + 4*i);
    printf("FPGA identification: %s\n", fpga_identification);
}

static void dma_test(void) //rename to prep_buff
{    
    int ret;
    int i;
    ssize_t len;

    int64_t duration;
    int64_t last_time;

    uint32_t seed_wr;
    uint32_t seed_rd;

    seed_wr = 0;
    seed_rd = 0;

    memset(buf_rd, 0, DMA_BUFFER_TOTAL_SIZE);
    memset(buf_wr, 0, DMA_BUFFER_TOTAL_SIZE);
}
    /*
     * The private constructor
     */
    litexgnu_impl::litexgnu_impl()
      : gr::block("litexgnu",
              gr::io_signature::make(1, 1, sizeof(input_type)),
              gr::io_signature::make(1, 1, sizeof(output_type)))
    {
      
    }

    /*
     * Our virtual destructor.
     */
    litexgnu_impl::~litexgnu_impl()
    {
    }

    void
    litexgnu_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
      
    }
	
    bool 
    litexgnu_impl::start( )
    {
      buf_rd = (char*)malloc(DMA_BUFFER_TOTAL_SIZE);
      buf_wr = (char*)malloc(DMA_BUFFER_TOTAL_SIZE);
      snprintf(litepcie_device, sizeof(litepcie_device), "/dev/litepcie%d", litepcie_device_num);
      info();
      
      int64_t reader_hw_count, reader_sw_count, reader_sw_count_last;
      int64_t writer_hw_count, writer_sw_count;
      errors = 0;


    fds.fd = open(litepcie_device, O_RDWR | O_CLOEXEC);
    fds.events = POLLIN | POLLOUT;
    if (fds.fd < 0) {
        fprintf(stderr, "Could not init driver\n");
        exit(1);
    }

    /* request dma */
    if ((litepcie_request_dma_reader(fds.fd) == 0) |
        (litepcie_request_dma_writer(fds.fd) == 0)) {
        printf("DMA not available, exiting.\n");
        errors += 1;
        exit(1);
    }

    /* enable dma loopback*/
    litepcie_dma(fds.fd, 1);

      signal(SIGINT, intHandler);
      dma_test(); //rename to prep_buff


      return 0; 
    }

    bool 
    litexgnu_impl::stop()
    {
      if (fd >= 1){
        close(fd);
      }

      free(buf_rd);
      free(buf_wr);
      return 0; 
    }

// 256 buffers
// 8192 bytes long
// how many dma buffers worth of data i have

    int
    litexgnu_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      int bytes_written;
      int consumed_items;
      int created_items;

            /* write event */
            if (fds.revents & POLLOUT) {
            int max_items = DMA_BUFFER_TOTAL_SIZE / sizeof(output_type);
            int n_write_items = std::min(max_items,ninput_items[0]);

            bytes_written = write(
                fds.fd,
            (void*)input_items.data(),
            ninput_items[0]*sizeof(input_type));
        if (bytes_written != n_write_items*sizeof(input_type)) {
            std::cout << "Error: "; 
            }
        }


        consumed_items = bytes_written / sizeof(output_type);

            /* read event */
            if (fds.revents & POLLIN) {
                int bytes_read = read(fds.fd,
                       (void*)output_items.data(),
                       noutput_items*sizeof(output_type));
                       
                       created_items = bytes_read / sizeof(output_type);
            }


      const float *in = (const float *)(input_items[0]);
      float *out = (float *)(output_items[0]);

      for(int i = 0; i < noutput_items;  i++) {
        out[i] = in[i] * in[i];
      }

     const char *cmd;
     litepcie_device_num = 0;
     




      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each(consumed_items);
      

      // Tell runtime system how many output items we produced.

      return created_items;
      
    }

  } /* namespace litexgnu */

  
} /* namespace gr */
