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

#ifndef @GUARD_NAME@
#define @GUARD_NAME@

#include <messageutils/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace messageutils {


    class MESSAGEUTILS_API @NAME@ : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<@NAME@> sptr;
      static sptr make(const std::vector<@I_TYPE@> &data, float period_ms, 
                        bool tag_output, bool debug, unsigned int packet_lim = 0, float initial_delay = 0);
      virtual void set_period(float period_ms) = 0;
      virtual void set_vec(const std::vector<@O_TYPE@> &data) = 0;
    };

  } // namespace messageutils
} // namespace gr

#endif /* @GUARD_NAME@ */
