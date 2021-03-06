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
#include "framer_to_pdu_impl.h"
#include <cstdio>
#include <string>
#include <stdint.h>
#include <sstream>


namespace gr {
  namespace messageutils {


    inline void
    framer_to_pdu_impl::enter_search()
    {
      
	    fprintf(stderr, "@ enter_search\n");

      d_state = STATE_SYNC_SEARCH;
    }

    inline void
    framer_to_pdu_impl::enter_have_sync()
    {

	  fprintf(stderr, "@ enter_have_sync\n");
      
      d_state = STATE_HAVE_SYNC;
      d_header = 0;
      d_headerbitlen_cnt = 0;
    }

    inline void
    framer_to_pdu_impl::enter_have_header(int payload_len,
					  int whitener_offset)
    {

	        fprintf(stderr, "@ enter_have_header (payload_len = %d) (offset = %d)\n",
		payload_len, whitener_offset);

      d_state = STATE_HAVE_HEADER;
      d_packetlen = payload_len;
      d_packet_whitener_offset = whitener_offset;
      d_packetlen_cnt = 0;
      d_packet_byte = 0;
      d_packet_byte_index = 0;
    }



    framer_to_pdu::sptr
    framer_to_pdu::make(bool debug)
    {
      return gnuradio::get_initial_sptr
        (new framer_to_pdu_impl(debug));
    }


    framer_to_pdu_impl::framer_to_pdu_impl(bool debug)
      : gr::sync_block("framer_to_pdu",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(0,0,0)),
        d_debug(debug)
    {
        enter_search();
        message_port_register_out(pmt::mp("pdus"));
    }


    framer_to_pdu_impl::~framer_to_pdu_impl()
    {
    }

unsigned int
    framer_to_pdu_impl::crc32(const unsigned char *buf, size_t len)
    {
      return update_crc32(0xffffffff, buf, len) ^ 0xffffffff;
    }




	
	unsigned int
    framer_to_pdu_impl::crc32(const std::string s)
    {
      return crc32((const unsigned char *) s.data(), s.size());
    }


    bool 
    framer_to_pdu_impl::check_crc (const std::string s)
    {
	    int len=s.size();	
	    if (len < 4)
	            return false;
	    unsigned char* buf=(unsigned char *)s.data();
	    //for (int i=0;i<len;i++){                          //Dewhiten
	    //	buf[i] = buf[i] ^ random_mask_tuple[i];
	    //}
       	unsigned int actual = crc32((const unsigned char *) buf,len-4);


	    unsigned int temp=0;
	    unsigned int expected=0;
	    for(int i=4;i>0;i--)
        {
		    temp=0;
		    temp=(*(buf+(len-i)))&0xff;			
		    temp=temp<<(i-1)*8;
		    expected=expected | (temp);
	    }
	    //printf("AAAACRC %ud %ud",actual, expected);
        //	unsigned int expected = (int) buf+(len-4)
      	if(actual!=expected) 
		    return false;
	    return true;
    }



    void 
    framer_to_pdu_impl::send_pdu()
    {


        //Convert the 4 byte char representation into its equivalent float value
        //TODO: There must be a faster/easier way to do this
        int d_float_ind = 0;
        for (int ii=0;ii<d_packetlen;ii+=4)
        {

        u8f.byte[0] = d_packet[0+ii];
        u8f.byte[1] = d_packet[1+ii];
        u8f.byte[2] = d_packet[2+ii];
        u8f.byte[3] = d_packet[3+ii];

        d_packet_float[d_float_ind] = u8f.f;
        d_float_ind++;

        }

        //Format the data into a PDU blob
        pmt::pmt_t d_pdu_vector = pmt::init_f32vector(d_float_ind,d_packet_float);

        //Check that the data was properly formatted in PDU
        size_t offset(0);
        const uint8_t* d_vec_check = (const uint8_t*) pmt::uniform_vector_elements(d_pdu_vector, offset);  //Check vector
        
        //Make a PDU Metadata Dictionary to hold Packet Number and Length

        pmt::pmt_t d_pdu_meta = pmt::make_dict();
        //d_pdu_meta = dict_add(d_pdu_meta, pmt::intern("Packet"), pmt::from_long(d_packet));
        d_pdu_meta = dict_add(d_pdu_meta, pmt::intern("Length"), pmt::from_long(d_packetlen)); 
        

        //Create PDU 
        pmt::pmt_t msg = pmt::cons(d_pdu_meta, d_pdu_vector);
        message_port_pub(pmt::mp("pdus"),msg);
        
        fprintf(stderr,"Sent A PDU of length %d\n",d_packetlen);

    }


    int
    framer_to_pdu_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const unsigned char *in = (const unsigned char *) input_items[0];
        int count=0;

        while(count < noutput_items)
        {
	        switch(d_state)
            {

                case STATE_SYNC_SEARCH:    // Look for flag indicating beginning of pkt
	                fprintf(stderr,"SYNC Search, noutput=%d\n", noutput_items);

	                while(count < noutput_items) 
                    {
	                    if(in[count] & 0x2)
                        {  // Found it, set up for header decode
	                        enter_have_sync();
	                        break;
	                    }
	                    count++;
	                }
	                break;


                case STATE_HAVE_SYNC:
                    fprintf(stderr,"Header Search bitcnt=%d, header=0x%08x\n",
		              d_headerbitlen_cnt, d_header);

	                while(count < noutput_items) 
                    {	// Shift bits one at a time into header
	                    d_header = (d_header << 1) | (in[count++] & 0x1);
	                    if(++d_headerbitlen_cnt == HEADERBITLEN)
                        {
                            fprintf(stderr, "got header: 0x%08x\n", d_header);
            
                            
	                        // we have a full header, check to see if it has been received properly

	                        if(header_ok()) 
                            {
                                
		                        int payload_len;
		                        int whitener_offset;
		                        header_payload(&payload_len, &whitener_offset);
		                        enter_have_header(payload_len, whitener_offset);

		                        if(d_packetlen == 0) 
                                {	    // check for zero-length payload
		                               // build a zero-length message

		                          enter_search();
		                        }
	                        }
	                        else
		                        enter_search();				// bad header
	                            break;					// we're in a new state
                            
	                    }
	                }
	                break;
                
        
                case STATE_HAVE_HEADER:
	                fprintf(stderr,"Packet Build\n");

	                while(count < noutput_items) 
                    {   // shift bits into bytes of packet one at a time
	                    d_packet_byte = (d_packet_byte << 1) | (in[count++] & 0x1);
	                    if(d_packet_byte_index++ == 7) 
                        {	  	// byte is full so move to next byte
	                        d_packet[d_packetlen_cnt++] = d_packet_byte;
	                        d_packet_byte_index = 0;
            

	                        if(d_packetlen_cnt == d_packetlen) 
                            {	// packet is filled
		                        // build a message
                                fprintf(stderr,"Got a full packet of length %d, wo %d. Building PDU\n",d_packetlen_cnt,
                                    d_packet_whitener_offset);

                                message::sptr msg =
			                    message::make(0, d_packet_whitener_offset, 0, d_packetlen);
			                    memcpy(msg->msg(), d_packet, d_packetlen_cnt);
			                    
                                bool d_crc_result = check_crc(msg->to_string());
			                    fprintf(stderr,"CRC32 Result: %d",d_crc_result);


                                //std::cout << (msg->to_string());

                                if (d_crc_result)
                                {
                                  
                                    d_packetlen = d_packetlen - 4;
                                    framer_to_pdu_impl::send_pdu();  
                                }

                                

		                    enter_search();
		                    break;
	                        }
	                    }
	                }
                    fprintf(stderr,"Reached noutput items max. Count was %d\n",count);
	                break;

                default:
                    assert(0);

            }//switch 
        }//while

        return noutput_items;
    }


unsigned int
    framer_to_pdu_impl::update_crc32(unsigned int crc, const unsigned char *data, size_t len)
    {
      static const unsigned int table[256] = {
	    0x00000000U,0x04C11DB7U,0x09823B6EU,0x0D4326D9U,
	    0x130476DCU,0x17C56B6BU,0x1A864DB2U,0x1E475005U,
	    0x2608EDB8U,0x22C9F00FU,0x2F8AD6D6U,0x2B4BCB61U,
	    0x350C9B64U,0x31CD86D3U,0x3C8EA00AU,0x384FBDBDU,
	    0x4C11DB70U,0x48D0C6C7U,0x4593E01EU,0x4152FDA9U,
	    0x5F15ADACU,0x5BD4B01BU,0x569796C2U,0x52568B75U,
	    0x6A1936C8U,0x6ED82B7FU,0x639B0DA6U,0x675A1011U,
	    0x791D4014U,0x7DDC5DA3U,0x709F7B7AU,0x745E66CDU,
	    0x9823B6E0U,0x9CE2AB57U,0x91A18D8EU,0x95609039U,
	    0x8B27C03CU,0x8FE6DD8BU,0x82A5FB52U,0x8664E6E5U,
	    0xBE2B5B58U,0xBAEA46EFU,0xB7A96036U,0xB3687D81U,
	    0xAD2F2D84U,0xA9EE3033U,0xA4AD16EAU,0xA06C0B5DU,
	    0xD4326D90U,0xD0F37027U,0xDDB056FEU,0xD9714B49U,
	    0xC7361B4CU,0xC3F706FBU,0xCEB42022U,0xCA753D95U,
	    0xF23A8028U,0xF6FB9D9FU,0xFBB8BB46U,0xFF79A6F1U,
	    0xE13EF6F4U,0xE5FFEB43U,0xE8BCCD9AU,0xEC7DD02DU,
	    0x34867077U,0x30476DC0U,0x3D044B19U,0x39C556AEU,
	    0x278206ABU,0x23431B1CU,0x2E003DC5U,0x2AC12072U,
	    0x128E9DCFU,0x164F8078U,0x1B0CA6A1U,0x1FCDBB16U,
	    0x018AEB13U,0x054BF6A4U,0x0808D07DU,0x0CC9CDCAU,
	    0x7897AB07U,0x7C56B6B0U,0x71159069U,0x75D48DDEU,
	    0x6B93DDDBU,0x6F52C06CU,0x6211E6B5U,0x66D0FB02U,
	    0x5E9F46BFU,0x5A5E5B08U,0x571D7DD1U,0x53DC6066U,
	    0x4D9B3063U,0x495A2DD4U,0x44190B0DU,0x40D816BAU,
	    0xACA5C697U,0xA864DB20U,0xA527FDF9U,0xA1E6E04EU,
	    0xBFA1B04BU,0xBB60ADFCU,0xB6238B25U,0xB2E29692U,
	    0x8AAD2B2FU,0x8E6C3698U,0x832F1041U,0x87EE0DF6U,
	    0x99A95DF3U,0x9D684044U,0x902B669DU,0x94EA7B2AU,
	    0xE0B41DE7U,0xE4750050U,0xE9362689U,0xEDF73B3EU,
	    0xF3B06B3BU,0xF771768CU,0xFA325055U,0xFEF34DE2U,
	    0xC6BCF05FU,0xC27DEDE8U,0xCF3ECB31U,0xCBFFD686U,
	    0xD5B88683U,0xD1799B34U,0xDC3ABDEDU,0xD8FBA05AU,
	    0x690CE0EEU,0x6DCDFD59U,0x608EDB80U,0x644FC637U,
	    0x7A089632U,0x7EC98B85U,0x738AAD5CU,0x774BB0EBU,
	    0x4F040D56U,0x4BC510E1U,0x46863638U,0x42472B8FU,
	    0x5C007B8AU,0x58C1663DU,0x558240E4U,0x51435D53U,
	    0x251D3B9EU,0x21DC2629U,0x2C9F00F0U,0x285E1D47U,
	    0x36194D42U,0x32D850F5U,0x3F9B762CU,0x3B5A6B9BU,
	    0x0315D626U,0x07D4CB91U,0x0A97ED48U,0x0E56F0FFU,
	    0x1011A0FAU,0x14D0BD4DU,0x19939B94U,0x1D528623U,
	    0xF12F560EU,0xF5EE4BB9U,0xF8AD6D60U,0xFC6C70D7U,
	    0xE22B20D2U,0xE6EA3D65U,0xEBA91BBCU,0xEF68060BU,
	    0xD727BBB6U,0xD3E6A601U,0xDEA580D8U,0xDA649D6FU,
	    0xC423CD6AU,0xC0E2D0DDU,0xCDA1F604U,0xC960EBB3U,
	    0xBD3E8D7EU,0xB9FF90C9U,0xB4BCB610U,0xB07DABA7U,
	    0xAE3AFBA2U,0xAAFBE615U,0xA7B8C0CCU,0xA379DD7BU,
	    0x9B3660C6U,0x9FF77D71U,0x92B45BA8U,0x9675461FU,
	    0x8832161AU,0x8CF30BADU,0x81B02D74U,0x857130C3U,
	    0x5D8A9099U,0x594B8D2EU,0x5408ABF7U,0x50C9B640U,
	    0x4E8EE645U,0x4A4FFBF2U,0x470CDD2BU,0x43CDC09CU,
	    0x7B827D21U,0x7F436096U,0x7200464FU,0x76C15BF8U,
	    0x68860BFDU,0x6C47164AU,0x61043093U,0x65C52D24U,
	    0x119B4BE9U,0x155A565EU,0x18197087U,0x1CD86D30U,
	    0x029F3D35U,0x065E2082U,0x0B1D065BU,0x0FDC1BECU,
	    0x3793A651U,0x3352BBE6U,0x3E119D3FU,0x3AD08088U,
	    0x2497D08DU,0x2056CD3AU,0x2D15EBE3U,0x29D4F654U,
	    0xC5A92679U,0xC1683BCEU,0xCC2B1D17U,0xC8EA00A0U,
	    0xD6AD50A5U,0xD26C4D12U,0xDF2F6BCBU,0xDBEE767CU,
	    0xE3A1CBC1U,0xE760D676U,0xEA23F0AFU,0xEEE2ED18U,
	    0xF0A5BD1DU,0xF464A0AAU,0xF9278673U,0xFDE69BC4U,
	    0x89B8FD09U,0x8D79E0BEU,0x803AC667U,0x84FBDBD0U,
	    0x9ABC8BD5U,0x9E7D9662U,0x933EB0BBU,0x97FFAD0CU,
	    0xAFB010B1U,0xAB710D06U,0xA6322BDFU,0xA2F33668U,
	    0xBCB4666DU,0xB8757BDAU,0xB5365D03U,0xB1F740B4U,
      };
  
      while(len > 0)
	  {
	      crc = table[*data ^ ((crc >> 24) & 0xff)] ^ (crc << 8);
	      data++;
	      len--;
	  }
      return crc;
    }

  } /* namespace messageutils */
} /* namespace gr */

