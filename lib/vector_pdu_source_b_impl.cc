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
#include "vector_pdu_source_b_impl.h"

namespace gr {
  namespace messageutils {

    vector_pdu_source_b::sptr
    vector_pdu_source_b::make(const std::vector<uint8_t> &data, float period_ms, 
                                bool tag_output, bool debug, unsigned int packet_lim)
    {
      return gnuradio::get_initial_sptr
        (new vector_pdu_source_b_impl(data, period_ms, tag_output, debug, packet_lim));
    }


    vector_pdu_source_b_impl::vector_pdu_source_b_impl(const std::vector<uint8_t> &data, float period_ms, 
                                                      bool tag_output, bool debug, unsigned int packet_lim)
      : gr::block("vector_pdu_source_b",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
         d_tag_output(tag_output), d_debug(debug), d_packet(0)
    {
		  set_period(period_ms);
    	set_vec(data);
      set_limit(packet_lim);

    	message_port_register_out(pmt::mp("pdus"));
    	d_thread = boost::shared_ptr<boost::thread>
      	(new boost::thread(boost::bind(&vector_pdu_source_b_impl::send_pdu, this)));

      d_finished = false;
	}



    vector_pdu_source_b_impl::~vector_pdu_source_b_impl()
    {
      d_finished = true;
      d_thread->interrupt();
      d_thread->join();
    }


    void 
    vector_pdu_source_b_impl::set_period(float period_ms)
    {
        d_period_ms = period_ms;
    }


    void 
    vector_pdu_source_b_impl::set_vec(const std::vector<uint8_t> &data)
    {
        d_data = data;   
    }

    
    void 
    vector_pdu_source_b_impl::set_limit(unsigned int packet_lim)
    {
      /* Check if we wish to limit number of packets output,
       * if so, set the limit */
      if (packet_lim == 0) {
        limit_packets = false;
      }
      else {
        limit_packets = true;
        d_packet_lim = packet_lim;
      }

      if (d_debug) {
        std::cout<<"Limit Packets: ";
        (limit_packets) ? std::cout<<"True. Limit: "<<packet_lim : std::cout<<"False";
        std::cout<<std::endl;
      }

    }


    void 
    vector_pdu_source_b_impl::send_pdu()
    {
      
      while(!d_finished) 
      {
        boost::this_thread::sleep(boost::posix_time::milliseconds(d_period_ms)); 
        if(d_finished) 
        {
          return;
        }

        d_packet++;
        if ((limit_packets) && (d_packet > d_packet_lim))
        {
          //Do nothing
        }
        else
        {

        

          //Make a PDU Metadata Dictionary to hold Packet Number and Length
          pmt::pmt_t d_pdu_meta = pmt::make_dict();

          size_t d_pdu_length = d_data.size();
          pmt::pmt_t d_pdu_vector = pmt::init_u8vector(d_pdu_length,d_data); 

          if (d_tag_output)
          {
            d_pdu_meta = dict_add(d_pdu_meta, pmt::intern("Packet"), pmt::from_long(d_packet));
            d_pdu_meta = dict_add(d_pdu_meta, pmt::intern("Length"), pmt::from_long(d_data.size())); 
          }       

          //Publish the PDU
          pmt::pmt_t msg = pmt::cons(d_pdu_meta, d_pdu_vector);
          message_port_pub(pmt::mp("pdus"),msg);
          

          if (d_debug)
          {
              std::cout<<"********** Vector Source Debug **********"<<std::endl;
              std::cout<<"Period:  "<<d_period_ms<<std::setw(20);
			        std::cout<<"Length:  "<<d_pdu_length<<std::setw(20);
              std::cout<<std::setw(20)<<"Sent Vector: "<<d_packet<<std::endl;
              std::cout<<"*****************************************"<<std::endl;  
          }
        }

      }//while !d_finished

    }

  } /* namespace messageutils */
} /* namespace gr */

