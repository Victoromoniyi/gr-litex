/* -*- c++ -*- */
/*
 * Copyright 2021 gr-litexgnu author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include "litexgnu_impl.h"

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


    /*
     * The private constructor
     */
    litexgnu_impl::litexgnu_impl()
      : gr::block("litexgnu",
              gr::io_signature::make(1, 1, sizeof(input_type)),
              gr::io_signature::make(1, 1, sizeof(output_type)))
    {}

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

    int
    litexgnu_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *)(input_items[0]);
      float *out = (float *)(output_items[0]);

      for(int i = 0; i < noutput_items; i++) {
        out[i] = in[i] * in[i];
      }
      

      // Do <+signal processing+>
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace litexgnu */
} /* namespace gr */

