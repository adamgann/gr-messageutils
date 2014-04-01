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

#ifndef INCLUDED_MESSAGEUTILS_VECTOR_PDU_SOURCE_F_IMPL_H
#define INCLUDED_MESSAGEUTILS_VECTOR_PDU_SOURCE_F_IMPL_H

#include <messageutils/vector_pdu_source_f.h>

namespace gr {
  namespace messageutils {

    class vector_pdu_source_f_impl : public vector_pdu_source_f
    {
     private:
      std::vector<float> d_data;    
      bool d_debug;
      int d_type;
      bool d_finished;
      float d_period_ms;
      boost::shared_ptr<boost::thread> d_thread;
      
      long d_packet;

      unsigned int d_packet_cntr;


     public:
      vector_pdu_source_f_impl(const std::vector<float> &data, float period_ms, bool debug);
      ~vector_pdu_source_f_impl();
      void set_period(float period_ms);
      void send_pdu(void);
      void set_vec(const std::vector<float> &data);
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_VECTOR_PDU_SOURCE_F_IMPL_H */

