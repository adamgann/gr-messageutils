/* -*- c++ -*- */
/* 
 * Copyright 2017 Adam M. Gannon
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

#ifndef @GUARD_NAME_IMPL@
#define @GUARD_NAME_IMPL@

#include <messageutils/@NAME@.h>

namespace gr {
  namespace messageutils {

    class @NAME_IMPL@ : public @NAME@
    {
     	private:
		    std::vector<@O_TYPE@> d_data;   
		    float d_period_ms; 
		    bool d_tag_output;
		    bool d_debug;
        unsigned int d_packet_lim;
        float d_period_delay;
        
        bool d_finished;
		    int d_offset;
				long d_packet;
				bool limit_packets;
				boost::shared_ptr<boost::thread> d_thread;

     public:
      @NAME_IMPL@(const std::vector<@O_TYPE@> &data, float period_ms, 
                                bool tag_output, bool debug, unsigned int packet_lim, float initial_delay);
      ~@NAME_IMPL@();
      void set_period(float period_ms);
      void send_pdu(void);
      void set_vec(const std::vector<@O_TYPE@> &data);
      void set_limit(unsigned int packet_lim);
      int work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items);

			bool start();
			bool stop();

    };

  } // namespace messageutils
} // namespace gr

#endif /* @GUARD_NAME_IMPL */

