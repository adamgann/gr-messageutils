/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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
#include "pdu_to_file_impl.h"
#include <stdexcept>


#define dout if (1) std::cout

namespace gr {
  namespace messageutils {

    pdu_to_file::sptr
    pdu_to_file::make(const char *filename, bool append)
    {
      return gnuradio::get_initial_sptr
        (new pdu_to_file_impl(filename, append));
    }

    pdu_to_file_impl::pdu_to_file_impl(const char *filename, bool append)
      : gr::block("pdu_to_file",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
          file_sink_base(filename, true, append)
    {
    
      message_port_register_in(pmt::mp("in"));
			set_msg_handler(pmt::mp("in"), boost::bind(&pdu_to_file_impl::handle_msg, this, _1));
    
    }


    pdu_to_file_impl::~pdu_to_file_impl()
    {
    }
    
    void 
    pdu_to_file_impl::handle_msg(pmt::pmt_t msg)
    {
    	dout<<"Got msg"<<std::endl;
      // Check PMT 
      if (!pmt::is_pair(msg))
      {
        throw std::runtime_error("received a malformed pdu message");
      }
      pmt::pmt_t data_meta = pmt::car(msg);
      pmt::pmt_t data_blob = pmt::cdr(msg);

      size_t offset(0);
      size_t len = pmt::blob_length(data_blob);
      const uint8_t *d = (const uint8_t*) pmt::uniform_vector_elements(data_blob,offset);
      
      
      do_update();                    // update d_fp is reqd
      if(!d_fp) 
      {
      	dout<<"No file pointer!"<<std::endl;
      	return;
      }
      
      int count = fwrite(d, 1, len, d_fp);
      dout<<"Count "<<count<<std::endl;
      
      if (ferror(d_fp))
      {
      	throw std::runtime_error("Uh oh.");
      }
      fflush(d_fp);

      
    }


  } /* namespace messageutils */
} /* namespace gr */

