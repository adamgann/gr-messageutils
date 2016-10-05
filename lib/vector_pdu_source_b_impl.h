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

#ifndef INCLUDED_MESSAGEUTILS_VECTOR_PDU_SOURCE_B_IMPL_H
#define INCLUDED_MESSAGEUTILS_VECTOR_PDU_SOURCE_B_IMPL_H

#include <messageutils/vector_pdu_source_b.h>

namespace gr {
  namespace messageutils {

    class vector_pdu_source_b_impl : public vector_pdu_source_b
    {
     private:
      std::vector<uint8_t> d_data;    
      bool d_debug;
      int d_type;
      bool d_finished;
      float d_period_ms;
			float d_period_delay;
      boost::shared_ptr<boost::thread> d_thread;
      
      long d_packet;
      bool d_tag_output;
      unsigned int d_packet_lim;
      bool limit_packets;

     public:
      vector_pdu_source_b_impl(const std::vector<uint8_t> &data, float period_ms, 
                                bool tag_output, bool debug, unsigned int packet_lim, float initial_delay);
      ~vector_pdu_source_b_impl();
      void set_period(float period_ms);
      void send_pdu(void);
      void set_vec(const std::vector<uint8_t> &data);
      void set_limit(unsigned int packet_lim);
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_VECTOR_PDU_SOURCE_B_IMPL_H */

