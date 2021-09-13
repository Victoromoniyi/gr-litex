/* -*- c++ -*- */
/*
 * Copyright 2021 gr-litexgnu author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LITEXGNU_LITEXGNU_IMPL_H
#define INCLUDED_LITEXGNU_LITEXGNU_IMPL_H

#include <litexgnu/litexgnu.h>

namespace gr {
  namespace litexgnu {

    class litexgnu_impl : public litexgnu
    {
     private:
      // Nothing to declare in this block.

     public:
      litexgnu_impl();
      ~litexgnu_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);

    };

  } // namespace litexgnu
} // namespace gr

#endif /* INCLUDED_LITEXGNU_LITEXGNU_IMPL_H */

