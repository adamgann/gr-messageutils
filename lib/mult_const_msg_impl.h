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

#ifndef INCLUDED_MESSAGEUTILS_MULT_CONST_MSG_IMPL_H
#define INCLUDED_MESSAGEUTILS_MULT_CONST_MSG_IMPL_H

#include <messageutils/mult_const_msg.h>

namespace gr {
  namespace messageutils {

    class mult_const_msg_impl : public mult_const_msg
    {
     private:
      bool d_debug; 
      float d_const;

     public:
      mult_const_msg_impl(float constant, bool debug);
      ~mult_const_msg_impl();
      
      void handle_msg(pmt::pmt_t msg);

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_MULT_CONST_MSG_IMPL_H */

