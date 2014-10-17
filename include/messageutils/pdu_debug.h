/* -*- c++ -*- */
/* 
 * Copyright 2014 Adam Gannon.
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


#ifndef INCLUDED_MESSAGEUTILS_PDU_DEBUG_H
#define INCLUDED_MESSAGEUTILS_PDU_DEBUG_H

#include <messageutils/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace messageutils {

    /*!
     * \brief Debug block with added functions for PDUs. 
     *
     * \details
     * The message debug block is used to capture and print or store
     * messages as they are received. Any block that generates a
     * message may connect that message port to one or more of the
     * three message input ports of this debug block. The message
     * ports are:
     *
     * \li print: prints the message directly to standard out.
     * \li store: stores the message in an internal vector. May be
     *            access using the get_message function.
     * \li print_pdu: specifically designed to handle formatted PDUs
     *                (see pdu.h).
     */
    class MESSAGEUTILS_API pdu_debug : virtual public gr::block
    {
     public:

      enum vector_type{byte_t, float_t, complex_t};

      typedef boost::shared_ptr<pdu_debug> sptr;


      static sptr make(size_t type, bool print_ascii, bool reverse_ascii, bool meta_only, bool display);


    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_PDU_DEBUG_H */

