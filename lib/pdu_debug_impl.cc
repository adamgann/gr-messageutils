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
    pdu_debug::make(size_t type,  bool print_ascii,bool meta_only, bool display)
    {
      return gnuradio::get_initial_sptr
        (new pdu_debug_impl(type, print_ascii, meta_only, display));
    }

    uint8_t pdu_debug_impl::reverse(uint8_t b)
    {
       b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
       b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
       b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
       return b;
    }


    void
    pdu_debug_impl::print_pdu(pmt::pmt_t pdu)
    {

      if (!d_display)
        return;


      
      if (d_meta_only)
      {
          pmt::pmt_t meta = pmt::car(pdu);
          pmt::pmt_t vector = pmt::cdr(pdu);
          if (!pmt::eq(meta, pmt::PMT_NIL) )
          {

              std::cout << "***********************************\n";
              std::cout << "**** Meta Data ****\n";
              pmt::print(meta);
        
              
              std::cout << "***********************************\n\n";
        
          }

      }//if meta_only
      else
      {
          pmt::pmt_t meta = pmt::car(pdu);
          pmt::pmt_t vector = pmt::cdr(pdu);
    
          std::cout << "***********************************\n";
          std::cout << "**** Meta Data ****\n";
          pmt::print(meta);
    
          std::cout << "\n**** PDU Data ****\n";
          size_t len = pmt::length(vector);
          std::cout << "PDU Length:  " << len;
          std::cout<<std::setw(20)<<"Vector Type:  ";
          size_t offset(0);

          //Print PDU Blob based on type. TODO: Make this a case/switch.
          if (d_type == sizeof(char))
          {

              (d_print_ascii) ? (std::cout<<"ASCII"<<std::endl) : (std::cout<<"Byte"<<std::endl);
              std::cout<<"Contents: "<<std::endl;
              const uint8_t* d = (const uint8_t*) pmt::uniform_vector_elements(vector, offset);
              for(size_t i=0; i<len; i+=16)
              {
                for(size_t j=i; j<std::min(i+16,len); j++)
                {
                  if (d_print_ascii)
                  {
                    printf("%c", reverse(d[j]));
                  }
                  else
                  {
                     printf("%02x ",d[j] );  //FIXME
                  }

                    
                }
              }
          }

          else if (d_type == sizeof(float))
          {
              std::cout<<"Float"<<std::endl;
              std::cout<<"Contents: "<<std::endl;
              const float* d = (const float*) pmt::uniform_vector_elements(vector, offset);
              for(size_t i=0; i<len; i+=16)
              {
                printf("%04x: ", ((unsigned int)i));
                for(size_t j=i; j<std::min(i+16,len); j++)
                {
                  printf("%02f ",d[j] );
                }
              }
          }
          else if (d_type == sizeof(gr_complex))
          {
                std::cout<<"Complex"<<std::endl;
                std::cout<<"Sorry. Didn't get around to handling complex yet."<<std::endl;
          }

          else
          {
                std::cout<<"Invalid type. How did you get here in the first place?"<<std::endl;
          }

          std::cout << std::endl;
          std::cout << "***********************************\n\n";

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






    pdu_debug_impl::pdu_debug_impl(size_t type,  bool print_ascii, bool meta_only, bool display)
      : gr::block("pdu_debug",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
        d_type(type), d_print_ascii(print_ascii), d_meta_only(meta_only), d_display(display)

    {
    
     
      message_port_register_in(pmt::mp("pdus"));
      set_msg_handler(pmt::mp("pdus"), boost::bind(&pdu_debug_impl::print_pdu, this, _1));

    }


    pdu_debug_impl::~pdu_debug_impl()
    {
    }


  } /* namespace messageutils */
} /* namespace gr */

