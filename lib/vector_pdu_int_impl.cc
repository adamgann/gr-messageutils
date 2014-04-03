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
#include "vector_pdu_int_impl.h"
#include <cstdio>
#include <iostream>

namespace gr {
  namespace messageutils {

    vector_pdu_int::sptr
    vector_pdu_int::make(const std::vector<uint8_t> &data, float period_ms, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new vector_pdu_int_impl(data, period_ms, debug));
    }

    /*
     * The private constructor
     */
    vector_pdu_int_impl::vector_pdu_int_impl(const std::vector<uint8_t> &data, float period_ms, bool debug)
      : gr::block("vector_pdu_int",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),

         d_debug(debug)
    {

      set_period(period_ms);
      set_vec(data);

      message_port_register_out(pmt::mp("pdus"));
      d_thread = boost::shared_ptr<boost::thread>
        (new boost::thread(boost::bind(&vector_pdu_int_impl::send_pdu, this)));

      d_finished = false;

    }

    
    vector_pdu_int_impl::~vector_pdu_int_impl()
    {
      d_finished = true;
      d_thread->interrupt();
      d_thread->join();
    }

    void 
    vector_pdu_int_impl::set_period(float period_ms)
    {
        d_period_ms = period_ms;
    }


    void 
    vector_pdu_int_impl::set_vec(const std::vector<uint8_t> &data)
    {
        d_data = data;   
    }


    void 
    vector_pdu_int_impl::send_pdu()
    {
      
      while(!d_finished) 
      {
        boost::this_thread::sleep(boost::posix_time::milliseconds(d_period_ms)); 
        if(d_finished) 
        {
          //std::cout<<"Good Morning"<<std::endl;
          return;
        }


        //Create a PDU blob with data from vector 
        
        

        //Make a PDU Metadata Dictionary to hold Packet Number and Length
        d_packet++;
        pmt::pmt_t d_pdu_meta = pmt::make_dict();
        d_pdu_meta = dict_add(d_pdu_meta, pmt::intern("Packet"), pmt::from_long(d_packet));

        size_t d_pdu_length = d_data.size();
        pmt::pmt_t d_pdu_vector = pmt::init_u8vector(d_pdu_length,d_data); 
        d_pdu_meta = dict_add(d_pdu_meta, pmt::intern("Length"), pmt::from_long(d_data.size())); 
                

        

        //Check that the data was properly formatted in PDU
        //size_t offset(0);
        //const float* d_vec_check = (const float*) pmt::uniform_vector_elements(d_pdu_vector, offset);   //Check vector is valid
        
        
       

        //Create PDU 
        pmt::pmt_t msg = pmt::cons(d_pdu_meta, d_pdu_vector);
        message_port_pub(pmt::mp("pdus"),msg);
       


        if (d_debug)
        {



            std::cout<<"********** Vector Source Debug **********"<<std::endl;
            std::cout<<"Period:  "<<d_period_ms<<std::setw(20);
            std::cout<<"Set Vector:  ";
            //for(int ii=0;ii<(d_data.size()-1);ii++)
            //    std::cout<<d_data[ii]<<", ";
            //std::cout<<d_data[d_data.size()-1];
            
            std::cout<<std::setw(20)<<"Sent Vector: ";
            //for (int ii=0;ii<int(pmt::length(d_pdu_vector))-1;ii++)
            //{
            ///    std::cout<<d_vec_check[ii]<<", ";
            //}
            //std::cout<<d_vec_check[int(pmt::length(d_pdu_vector))-1];
            //std::cout<<std::endl;
          
            std::cout<<"*****************************************"<<std::endl;  
        }

      }

    }
    


  } /* namespace messageutils */
} /* namespace gr */

