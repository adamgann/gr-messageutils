/* -*- c++ -*- */
/* 
 * Copyright 2017 Adam Gannon
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


#ifndef INCLUDED_MESSAGEUTILS_PDU_TO_FILE_H
#define INCLUDED_MESSAGEUTILS_PDU_TO_FILE_H

#include <messageutils/api.h>
#include <gnuradio/block.h>
#include <gnuradio/blocks/file_sink_base.h>

namespace gr {
  namespace messageutils {

    /*!
     * \brief <+description of block+>
     * \ingroup messageutils
     *
     */
    class MESSAGEUTILS_API pdu_to_file : virtual public gr::block,
    																		 virtual public gr::blocks::file_sink_base
    {
     public:
      typedef boost::shared_ptr<pdu_to_file> sptr;

      static sptr make(const char *filename, bool append, bool debug);
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_PDU_TO_FILE_H */

