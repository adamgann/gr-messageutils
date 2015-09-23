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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "socket_pdu_repack_impl.h"

namespace gr {
  namespace messageutils {

    socket_pdu_repack::sptr
    socket_pdu_repack::make(size_t type, bool input, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new socket_pdu_repack_impl(type, input, debug));
    }

    socket_pdu_repack_impl::socket_pdu_repack_impl(size_t type, bool input, bool debug)
      : gr::block("socket_pdu_repack",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
      d_type(type), d_input(input), d_debug(debug)
    {
      //Set up Message Handling        
      message_port_register_in(pmt::mp("in"));
      message_port_register_out(pmt::mp("out"));
      set_msg_handler(pmt::mp("in"),
      boost::bind(&socket_pdu_repack_impl::handle_msg, this, _1));
    }

    socket_pdu_repack_impl::~socket_pdu_repack_impl()
    {
    }


    void
    socket_pdu_repack_impl::handle_msg(pmt::pmt_t msg)
    {
      // Get message, check that it's a PDU
      dout<<"Got msg"<<std::endl;
      if (!pmt::is_pair(msg)) 
      {
        return;
      }

      // Grab the data blob and metadata 
      pmt::pmt_t d_meta = pmt::car(msg);
      pmt::pmt_t d_vect = pmt::cdr(msg);


      if (d_type == sizeof(float))
      {
        if (d_input)
        {
          //Get sizes
          size_t pdu_len = pmt::length(d_vect)/d_type; //Socket sends bytes, we want to divide by number of bytes per sample (4 for floats, 8 for complex)
          size_t offset(0);

          // Grab float vector
          const float* d = (float*) pmt::uniform_vector_elements(d_vect, offset); 
          std::vector<float> msg_data;
          msg_data.assign(d,d+pdu_len);

          dout<<"Repacker received vector  ";
          for (int jj=0;jj<pdu_len;jj++) dout<<msg_data[jj]<<", ";
          dout<<std::endl;

          // Pack the new vector into PDU and send
          pmt::pmt_t send_vect = pmt::init_f32vector(pdu_len,msg_data); 
          pmt::pmt_t msg = pmt::cons(d_meta , send_vect);
          message_port_pub(pmt::mp("out"),msg);
        }
        else
        {
          dout<<"Output chosen"<<std::endl;
          size_t pdu_len = pmt::length(d_vect)*d_type;
          size_t offset(0);
          
          const uint8_t* d = (uint8_t*) pmt::uniform_vector_elements(d_vect, offset); 
          std::vector<uint8_t> msg_data;
          msg_data.assign(d,d+pdu_len);
    
          dout<<"Assigned "<<pdu_len<<" elements"<<std::endl;// starting with "<<msg_data[0]<<std::endl;
         
          // Pack the new vector into PDU and send
          pmt::pmt_t send_vect = pmt::init_u8vector(pdu_len,msg_data); 
          pmt::pmt_t msg = pmt::cons(d_meta , send_vect);
          message_port_pub(pmt::mp("out"),msg);
          

        }

      }
      else
      {
        throw std::runtime_error("Data types other than float not yet implimented.\n");
      }


    }




  } /* namespace messageutils */
} /* namespace gr */

