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


#ifndef INCLUDED_MESSAGEUTILS_MESSAGE_THRESH_SWITCH_H
#define INCLUDED_MESSAGEUTILS_MESSAGE_THRESH_SWITCH_H

#include <messageutils/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace messageutils {

    /*!
     * \brief <+description of block+>
     * \ingroup messageutils
     *
     */
    class MESSAGEUTILS_API message_thresh_switch : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<message_thresh_switch> sptr;

      enum value_thresh_comp_type
      {
            VAL_ABOVE,
            VAL_BELOW,
            VAL_EQUAL
      };

      /*!
       * \brief Return a shared_ptr to a new instance of messageutils::message_thresh_switch.
       *
       * To avoid accidental use of raw pointers, messageutils::message_thresh_switch's
       * constructor is in a private implementation
       * class. messageutils::message_thresh_switch::make is the public interface for
       * creating new instances.
       */
      static sptr make(size_t itemsize, std::string key, double thresh, bool debug);
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_MESSAGE_THRESH_SWITCH_H */
