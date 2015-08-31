/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_MESSAGEUTILS_SOCKET_PDU_REPACK_IMPL_H
#define INCLUDED_MESSAGEUTILS_SOCKET_PDU_REPACK_IMPL_H

#include <messageutils/socket_pdu_repack.h>

#define dout if (d_debug) std::cout

namespace gr {
  namespace messageutils {

    class socket_pdu_repack_impl : public socket_pdu_repack
    {
     private:
      size_t d_type;
      bool d_input;
      bool d_debug;

     public:
      socket_pdu_repack_impl(size_t type, bool input, bool debug);
      ~socket_pdu_repack_impl();

      void handle_msg(pmt::pmt_t msg);
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_SOCKET_PDU_REPACK_IMPL_H */

