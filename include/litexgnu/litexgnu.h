/* -*- c++ -*- */
/*
 * Copyright 2021 gr-litexgnu author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LITEXGNU_LITEXGNU_H
#define INCLUDED_LITEXGNU_LITEXGNU_H

#include <litexgnu/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace litexgnu {

    /*!
     * \brief <+description of block+>
     * \ingroup litexgnu
     *
     */
    class LITEXGNU_API litexgnu : virtual public gr::block
    {
     public:
      typedef std::shared_ptr<litexgnu> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of litexgnu::litexgnu.
       *
       * To avoid accidental use of raw pointers, litexgnu::litexgnu's
       * constructor is in a private implementation
       * class. litexgnu::litexgnu::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace litexgnu
} // namespace gr

#endif /* INCLUDED_LITEXGNU_LITEXGNU_H */

