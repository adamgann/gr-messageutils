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

#ifndef INCLUDED_MESSAGEUTILS_MESSAGE_THRESH_SWITCH_IMPL_H
#define INCLUDED_MESSAGEUTILS_MESSAGE_THRESH_SWITCH_IMPL_H

#include <messageutils/message_thresh_switch.h>

namespace gr {
  namespace messageutils {

    class message_thresh_switch_impl : public message_thresh_switch
    {
     private:
      size_t d_itemsize;
      bool d_debug;
      bool d_decode_msg;
      double d_thresh;

      pmt::pmt_t d_meta;
	  pmt::pmt_t d_vect;

      double d_value;
      std::string d_key;

      value_thresh_comp_type d_val_thresh_comp;



    

     public:
      message_thresh_switch_impl(size_t itemsize, std::string key, double thresh, bool debug);
      ~message_thresh_switch_impl();
    
      void set_threshold(double thresh);
      void handle_msg(pmt::pmt_t msg);

   

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_MESSAGE_THRESH_SWITCH_IMPL_H */

