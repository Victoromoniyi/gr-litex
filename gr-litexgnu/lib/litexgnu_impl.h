/* -*- c++ -*- */
/*
 * Copyright 2021 gr-litexgnu author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LITEXGNU_LITEXGNU_IMPL_H
#define INCLUDED_LITEXGNU_LITEXGNU_IMPL_H
#define BITS_PER_BYTE 8


#include <litexgnu/litexgnu.h>
#include <sys/poll.h>

namespace gr {
  namespace litexgnu {

    class litexgnu_impl : public litexgnu
    {
     private:
     int64_t reader_hw_count = 0;
     int64_t reader_sw_count = 0;
     int64_t reader_sw_count_last = 0;
     int64_t writer_hw_count = 0;
     int64_t writer_sw_count = 0;
     int64_t duration = 0;
     int64_t last_time = 0;
     int64_t work_iteration = 0;
     int _device_index = 0;
     struct pollfd fds;

     public:
      litexgnu_impl();
      ~litexgnu_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

      bool start();
      bool stop();

    };

  } // namespace litexgnu
} // namespace gr

#endif /* INCLUDED_LITEXGNU_LITEXGNU_IMPL_H */

