/* -*- c++ -*- */
/* 
 * Copyright 2014 Adam Gannon
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
#include "add_const_msg_impl.h"
#include <cstdio>
#include <iostream>


namespace gr {
  namespace messageutils {

    add_const_msg::sptr
    add_const_msg::make(size_t itemsize, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new add_const_msg_impl(itemsize, debug));
    }


    add_const_msg_impl::add_const_msg_impl(size_t itemsize, bool debug)
      : gr::sync_block("add_const_msg",
              gr::io_signature::make(1,2,itemsize),
              gr::io_signature::make(1,1,itemsize)),
        d_itemsize(itemsize), d_debug(debug)
    {
        message_port_register_in(pmt::mp("msg"));
        set_msg_handler(pmt::mp("msg"),
        boost::bind(&add_const_msg_impl::handle_msg, this, _1));
    }

    
    add_const_msg_impl::~add_const_msg_impl()
    {
    }


    void
    add_const_msg_impl::handle_msg(pmt::pmt_t msg)
    {
        pmt::pmt_t d_meta,k,v;
        pmt::pmt_t d_vect;

        if (pmt::is_pair(msg))      
        {
            d_meta = pmt::car(msg);
            d_vect = pmt::cdr(msg);

            //Grab the vector and store it
            size_t len = pmt::length(d_vect);
            size_t offset(0);
            const uint8_t* d = (const uint8_t*) pmt::uniform_vector_elements(d_vect, offset);

            d_val = float((d[0])-'0');

            std::cout<<d_val<<std::endl;
        }

      
                

    }

    int
    add_const_msg_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *iptr = (const float *) input_items[0];
        float *optr = (float*) output_items[0];

        int size = noutput_items;
        const float d_k = 1;
      
      while (size >= 8)
      {
	    *optr++ = *iptr++ + d_val;
	    *optr++ = *iptr++ + d_val;
	    *optr++ = *iptr++ + d_val;
	    *optr++ = *iptr++ + d_val;
	    *optr++ = *iptr++ + d_val;
	    *optr++ = *iptr++ + d_val;
	    *optr++ = *iptr++ + d_val;
	    *optr++ = *iptr++ + d_val;
	    size -= 8;
      }

      while (size-- > 0)
	    *optr++ = *iptr++ + d_val;
      
      
        return noutput_items;
    }

  } /* namespace messageutils */
} /* namespace gr */

