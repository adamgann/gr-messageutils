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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "pdu_debug_impl.h"
#include <cstdio>
#include <iostream>

namespace gr {
  namespace messageutils {

    pdu_debug::sptr
    pdu_debug::make(bool meta_only, bool display)
    {
      return gnuradio::get_initial_sptr
        (new pdu_debug_impl(meta_only, display));
    }


    void
    pdu_debug_impl::print_pdu(pmt::pmt_t pdu)
    {

      if (!d_display)
        return;

      pmt::pmt_t meta = pmt::car(pdu);
      pmt::pmt_t vector = pmt::cdr(pdu);
      
      if (d_meta_only)
      {

          if (!pmt::eq(meta, pmt::PMT_NIL) )
          {

              std::cout << "* MESSAGE DEBUG PRINT PDU METADATA *\n";
              pmt::print(meta);
        
              
              std::cout << "***********************************\n";
        
          }

      }//if meta_only
      else
      {
              std::cout << "* MESSAGE DEBUG PRINT PDU VERBOSE *\n";
              pmt::print(meta);
        
              size_t len = pmt::length(vector);
              std::cout << "pdu_length = " << len << std::endl;
              std::cout << "contents = " << std::endl;
              size_t offset(0);
              const uint8_t* d = (const uint8_t*) pmt::uniform_vector_elements(vector, offset);
              for(size_t i=0; i<len; i+=16){
                printf("%04x: ", ((unsigned int)i));
                for(size_t j=i; j<std::min(i+16,len); j++){
                  printf("%02x ",d[j] );
                }

                std::cout << std::endl;
              }

              std::cout << "***********************************\n";

      }
    }


    int
    pdu_debug_impl::num_messages()
    {
      return (int)d_messages.size();
    }

    pmt::pmt_t
    pdu_debug_impl::get_message(int i)
    {
      gr::thread::scoped_lock guard(d_mutex);

      if((size_t)i >= d_messages.size()) {
        throw std::runtime_error("message_debug: index for message out of bounds.\n");
      }

      return d_messages[i];
    }






    pdu_debug_impl::pdu_debug_impl(bool meta_only, bool display)
      : gr::block("pdu_debug",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
        d_meta_only(meta_only), d_display(display)

    {
    
     
      message_port_register_in(pmt::mp("pdus"));
      set_msg_handler(pmt::mp("pdus"), boost::bind(&pdu_debug_impl::print_pdu, this, _1));

    }


    pdu_debug_impl::~pdu_debug_impl()
    {
    }


  } /* namespace messageutils */
} /* namespace gr */

