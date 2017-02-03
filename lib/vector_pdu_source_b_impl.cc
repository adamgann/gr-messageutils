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

#define dout if (d_debug) std::cout

namespace gr {
  namespace messageutils {

    vector_pdu_source_b::sptr
    vector_pdu_source_b::make(const std::vector<uint8_t> &data, float period_ms, 
                                bool tag_output, bool debug, unsigned int packet_lim, float initial_delay)
    {
      return gnuradio::get_initial_sptr
        (new vector_pdu_source_b_impl(data, period_ms, tag_output, debug, packet_lim, initial_delay));
    }

    vector_pdu_source_b_impl::vector_pdu_source_b_impl(const std::vector<uint8_t> &data, float period_ms, 
                                                      bool tag_output, bool debug, unsigned int packet_lim, float initial_delay)
      : gr::sync_block("vector_pdu_source_b",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(1,1,sizeof(char))),
        d_data(data), d_period_ms(period_ms), d_tag_output(tag_output), d_debug(debug), d_packet_lim(packet_lim), d_period_delay(initial_delay)
    {
    	d_offset = 0;
    	d_packet = 0;
    	limit_packets = (packet_lim) ? true : false;
    	dout<<"Limit Packets? "<<limit_packets<<std::endl;
    	
    	message_port_register_out(pmt::mp("pdus"));
		}

    vector_pdu_source_b_impl::~vector_pdu_source_b_impl()
    {
    }

    bool
    vector_pdu_source_b_impl::start()
    {
      d_finished = false;
      d_thread = boost::shared_ptr<gr::thread::thread>
        (new gr::thread::thread(boost::bind(&vector_pdu_source_b_impl::send_pdu, this)));

      return block::start();
    }

    bool
    vector_pdu_source_b_impl::stop()
    {
      // Shut down the thread
      d_finished = true;
      d_thread->interrupt();
      d_thread->join();

      return block::stop();
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
      else 
      {
        limit_packets = true;
        d_packet_lim = packet_lim;
      }

      if (d_debug) {
        std::cout<<"Limit Packets: ";
        (limit_packets) ? std::cout<<"True. Limit: "<<packet_lim : std::cout<<"False";
        std::cout<<std::endl;
      }

    }
    
    int
    vector_pdu_source_b_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {

			if ((limit_packets) && (d_packet > d_packet_lim))
			{
				dout<<d_packet<<"\t"<<d_packet_lim<<"\t"<<limit_packets<<std::endl;
				dout<<"Finished output. Exiting"<<std::endl;
				dout<<"Sent shutdown msg"<<std::endl;
				return -1;
			}
			return 0;
			
    }


    void 
    vector_pdu_source_b_impl::send_pdu()
    {
      
      while(!d_finished) 
      {
        boost::this_thread::sleep(boost::posix_time::milliseconds(d_period_delay));
				d_period_delay = d_period_ms; 
        if(d_finished) 
        {
          return;
        }

        d_packet++;
        if ((limit_packets) && (d_packet > d_packet_lim))
        {
          // Do nothing
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
          if (d_packet == d_packet_lim)
          {
          	d_pdu_meta = dict_add(d_pdu_meta, pmt::intern("Last"), pmt::PMT_T);
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

