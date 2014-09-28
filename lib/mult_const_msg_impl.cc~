/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
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
#include "mult_const_msg_impl.h"
#include <volk/volk.h>

namespace gr {
  namespace messageutils {

    mult_const_msg::sptr
    mult_const_msg::make(float constant, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new mult_const_msg_impl(constant, debug));
    }


    mult_const_msg_impl::mult_const_msg_impl(float constant, bool debug)
      : gr::sync_block("mult_const_msg",
              gr::io_signature::make(1,1, sizeof(gr_complex)),
              gr::io_signature::make(1,1, sizeof(gr_complex))),
            d_debug(debug), d_const(constant)
    {
      const int alignment_multiple =
	      volk_get_alignment() / sizeof(gr_complex);
        set_alignment(std::max(1,alignment_multiple));

        message_port_register_in(pmt::mp("msg"));
        set_msg_handler(pmt::mp("msg"),
        boost::bind(&mult_const_msg_impl::handle_msg, this, _1));
    }


    mult_const_msg_impl::~mult_const_msg_impl()
    {

    }


    void
    mult_const_msg_impl::handle_msg(pmt::pmt_t msg)
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
            const float* d = (float*) pmt::uniform_vector_elements(d_vect, offset);

            float d_temp = d[0];

            if (len != 1)
            {
              if (d_debug){
                std::cout<<"Got a PDU with more than one value. Skipping"<<std::endl;
              }
              return;
            }



            if (d_const != d_temp)
            {
              if (d_debug)
              {
                std::cout<<"Got a new value of "<<d_temp<<". Updating..."<<std::endl;
              }
              d_const = d_temp;
            }

        }
    }

    int
    mult_const_msg_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

        int noi = noutput_items;

        volk_32fc_s32fc_multiply_32fc(out, in, d_const, noi);

        return noutput_items;
    }

  } /* namespace messageutils */
} /* namespace gr */

