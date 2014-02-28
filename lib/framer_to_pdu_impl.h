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

#ifndef INCLUDED_MESSAGEUTILS_FRAMER_TO_PDU_IMPL_H
#define INCLUDED_MESSAGEUTILS_FRAMER_TO_PDU_IMPL_H

#include <messageutils/framer_to_pdu.h>

namespace gr {
  namespace messageutils {

    class framer_to_pdu_impl : public framer_to_pdu
    {
     private:
      enum state_t {STATE_SYNC_SEARCH, STATE_HAVE_SYNC, STATE_HAVE_HEADER};
      static const int MAX_PKT_LEN    = 4096;
      static const int HEADERBITLEN   = 32;

     
      state_t           d_state;
      unsigned int      d_header;	      // header bits
      int	            d_headerbitlen_cnt;    // how many so far

      unsigned char     d_packet[MAX_PKT_LEN]; // assembled payload
      float             d_packet_float[MAX_PKT_LEN];
      unsigned char     d_packet_byte;	      // byte being assembled
      int	            d_packet_byte_index;   // which bit of d_packet_byte we're working on
      int	            d_packetlen;		   // length of packet
      int               d_packet_whitener_offset;   // offset into whitener string to use
      int	            d_packetlen_cnt;	           // how many so far

      bool              d_debug;

        union U8f {
            uint8_t byte[4];
            float f;
        };

        union U8f u8f;

    protected:
      void enter_search();
      void enter_have_sync();
      void enter_have_header(int payload_len, int whitener_offset);
      unsigned int update_crc32(unsigned int crc, const unsigned char *buf, size_t len);
      unsigned int crc32(const unsigned char *buf, size_t len);
      unsigned int crc32(const std::string s);
      bool check_crc (const std::string s);

      bool header_ok()
      {
	    // confirm that two copies of header info are identical
	    return ((d_header >> 16) ^ (d_header & 0xffff)) == 0;
      }

      void header_payload(int *len, int *offset)
      {
	    // header consists of two 16-bit shorts in network byte order
	    // payload length is lower 12 bits
	    // whitener offset is upper 4 bits
	    *len = (d_header >> 16) & 0x0fff;
	    *offset = (d_header >> 28) & 0x000f;
      }

     public:
      framer_to_pdu_impl(bool debug);
      ~framer_to_pdu_impl();
    
      void send_pdu();
      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace messageutils
} // namespace gr

#endif /* INCLUDED_MESSAGEUTILS_FRAMER_TO_PDU_IMPL_H */

