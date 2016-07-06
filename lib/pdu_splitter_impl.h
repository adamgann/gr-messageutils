/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_MESSAGEUTILS_PDU_SPLITTER_IMPL_H
#define INCLUDED_MESSAGEUTILS_PDU_SPLITTER_IMPL_H

#include <messageutils/pdu_splitter.h>

namespace gr {
  namespace messageutils {

    class pdu_splitter_impl : public pdu_splitter
    {
     	private:
      size_t                        d_itemsize;
			blocks::pdu::vector_type      d_type;
			std::vector<int> 							d_lengths;
      bool                          d_debug;
			int 													d_pdu_sum;

     public:
      pdu_splitter_impl(blocks::pdu::vector_type type, const std::vector<int> &lengths, bool debug);
      ~pdu_splitter_impl();

			void handle_msg(pmt::pmt_t msg);
			void send_pdu(pmt::pmt_t output_vec, int port);
			pmt::pmt_t format_port(int port);
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_PDU_SPLITTER_IMPL_H */

