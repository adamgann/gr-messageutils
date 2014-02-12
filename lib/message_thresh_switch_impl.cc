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
#include "message_thresh_switch_impl.h"

namespace gr {
  namespace messageutils {

    message_thresh_switch::sptr
    message_thresh_switch::make(size_t itemsize, std::string key, double thresh, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new message_thresh_switch_impl(itemsize, key, thresh, debug));
    }


    message_thresh_switch_impl::message_thresh_switch_impl(size_t itemsize, std::string key, double thresh, bool debug)
      : gr::sync_block("message_thresh_switch",
              gr::io_signature::make(1, 1, itemsize),
              gr::io_signature::make2(2, 2, itemsize, itemsize)),
        d_itemsize(itemsize), d_key(key), d_thresh(thresh), d_debug(debug) 
    {
        message_port_register_in(pmt::mp("msg"));
    }


    message_thresh_switch_impl::~message_thresh_switch_impl()
    {

    
    }

    int
    message_thresh_switch_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *signal = (const char *) input_items[0];
        char *out_above = (char *) output_items[0];
        char *out_below = (char *) output_items[1];

        d_decode_msg = false;

        
        //Get possible message data and check if valid      TODO: Move all this shit to a message handler, if possible
        pmt::pmt_t msg(delete_head_nowait(pmt::mp("msg")));
        if (msg.get() != NULL)
            if (pmt::is_pair(msg))      // TODO: implement pdu::is_valid()
            {
                d_meta = pmt::car(msg);
                d_vect = pmt::cdr(msg);
                
                if (!pmt::eq(d_meta, pmt::PMT_NIL) )
                    d_decode_msg = true;
            }
               
        //If valid, decode
        if (d_decode_msg)
        {

            pmt::pmt_t klist(pmt::dict_keys(d_meta));
            for(size_t i=0; i<pmt::length(klist); i++)
            {
                pmt::pmt_t k(pmt::nth(i, klist));
                pmt::pmt_t v(pmt::dict_ref(d_meta, k, pmt::PMT_NIL));

                if (pmt::eq(k,pmt::string_to_symbol(d_key)))
                    std::cout<<"Equal"<<std::endl;                  

                d_value = pmt::to_double(v);
                std::cout<<d_value<<std::endl;


            }           
         }

        

        

        //Copy Output
        memcpy(out_above,signal,noutput_items*d_itemsize);
        

        return noutput_items;
    }

  } /* namespace messageutils */
} /* namespace gr */

