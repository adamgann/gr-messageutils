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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "pdu_splitter_impl.h"

#define dout if (d_debug) std::cout

namespace gr {
  namespace messageutils {

    pdu_splitter::sptr
    pdu_splitter::make(blocks::pdu::vector_type type, const std::vector<int> &lengths, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new pdu_splitter_impl(type, lengths, debug));
    }


    pdu_splitter_impl::pdu_splitter_impl(blocks::pdu::vector_type type, const std::vector<int> &lengths, bool debug)
      : gr::block("pdu_splitter",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
				d_itemsize(blocks::pdu::itemsize(type)), d_type(type), d_lengths(lengths), d_debug(debug)
    {

      message_port_register_in(pmt::intern("in"));
			set_msg_handler(pmt::intern("in"), boost::bind(&pdu_splitter_impl::handle_msg, this, _1));


			d_pdu_sum = 0;
			for (unsigned int ii=0; ii<lengths.size(); ii++)
			{
				message_port_register_out(format_port(ii));
				d_pdu_sum += lengths[ii];
			}

		}


    pdu_splitter_impl::~pdu_splitter_impl()
    {
    }

		pmt::pmt_t 
		pdu_splitter_impl::format_port(int port)
		{
			std::ostringstream ss;
			ss << "out" << port;		

			pmt::pmt_t port_label = pmt::mp(ss.str());
			return port_label;
		}

		void
		pdu_splitter_impl::send_pdu(pmt::pmt_t output_vec, int port)
		{
      pmt::pmt_t pdu_meta = pmt::make_dict();
      pmt::pmt_t msg = pmt::cons(pdu_meta, output_vec);
      message_port_pub(format_port(port),msg);  			
		}

		void 
		pdu_splitter_impl::handle_msg(pmt::pmt_t msg)
		{

			// Check that this is a PDU, then grab the data vector 
      if (!pmt::is_pair(msg))
      {
        throw std::runtime_error("received a malformed pdu message");
      }
			pmt::pmt_t input_pdu_vec = pmt::cdr(msg);
			size_t pdu_len = pmt::length(input_pdu_vec);

			if (pdu_len != d_pdu_sum)
			{
				throw std::runtime_error("I can't split this vector into the required lengths. Check Lengths param\n");
			}

			// Unpack RX pdu into a std vector 
			size_t io(0);
			std::vector<uint8_t> data_buffer(pdu_len*d_itemsize);
			const uint8_t* ptr = (const uint8_t*) uniform_vector_elements(input_pdu_vec, io);
			memcpy(&data_buffer[0], ptr, pdu_len*d_itemsize);

			// Split the buffer into PDUs and send out starting with Port 0 
			int buf_offset = 0;
			for (unsigned int ii=0; ii<d_lengths.size(); ii++)
			{
				pmt::pmt_t output_pdu_vec =  blocks::pdu::make_pdu_vector(d_type, &data_buffer[buf_offset], d_lengths[ii]);
				buf_offset+=d_lengths[ii]*d_itemsize;
				send_pdu(output_pdu_vec,ii);

				dout<<"Copied a vector of size "<<d_lengths[ii]<<" itemsize "<<d_itemsize<<" to buffer of size "<<data_buffer.size()<<std::endl;
			}	
		}

		
  } /* namespace messageutils */
} /* namespace gr */

