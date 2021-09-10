/* -*- c++ -*- */
/*
 * Copyright 2021 gr-howto author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_HOWTO_SQUARE_FF_IMPL_H
#define INCLUDED_HOWTO_SQUARE_FF_IMPL_H

#include <howto/square_ff.h>

namespace gr {
  namespace howto {

    class square_ff_impl : public square_ff
    {
     private:
      // Nothing to declare in this block.

     public:
      square_ff_impl();
      ~square_ff_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_SQUARE_FF_IMPL_H */

