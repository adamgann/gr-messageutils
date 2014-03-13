/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_MESSAGEUTILS_VECTOR_PDU_INT_H
#define INCLUDED_MESSAGEUTILS_VECTOR_PDU_INT_H

#include <messageutils/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace messageutils {

    /*!
     * \brief <+description of block+>
     * \ingroup messageutils
     *
     */
    class MESSAGEUTILS_API vector_pdu_int : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<vector_pdu_int> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of messageutils::vector_pdu_int.
       *
       * To avoid accidental use of raw pointers, messageutils::vector_pdu_int's
       * constructor is in a private implementation
       * class. messageutils::vector_pdu_int::make is the public interface for
       * creating new instances.
       */
      virtual void set_period(float period_ms) = 0;
      virtual void set_vec(const std::vector<uint8_t> &data) = 0;
      static sptr make(const std::vector<uint8_t> &data, float period_ms, bool debug);;
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_VECTOR_PDU_INT_H */

