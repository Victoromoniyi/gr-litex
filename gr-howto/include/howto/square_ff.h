/* -*- c++ -*- */
/*
 * Copyright 2021 gr-howto author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_HOWTO_SQUARE_FF_H
#define INCLUDED_HOWTO_SQUARE_FF_H

#include <howto/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace howto {

    /*!
     * \brief <+description of block+>
     * \ingroup howto
     *
     */
    class HOWTO_API square_ff : virtual public gr::block
    {
     public:
      typedef std::shared_ptr<square_ff> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of howto::square_ff.
       *
       * To avoid accidental use of raw pointers, howto::square_ff's
       * constructor is in a private implementation
       * class. howto::square_ff::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace howto
} // namespace gr

#endif /* INCLUDED_HOWTO_SQUARE_FF_H */

