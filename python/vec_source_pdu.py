#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2017 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr
from gnuradio import blocks
import messageutils

class vec_source_pdu(gr.hier_block2):
		"""
		docstring for block vec_source_pdu
		"""
		def __init__(self, item_size, vector, period_ms, tag_output, debug, pkt_limit, initial_delay):
			gr.hier_block2.__init__(self,
				"vec_source_pdu",
				gr.io_signature(0,0,0),  # Input signature
				gr.io_signature(0,0,0)) # Output signature
				
			self.message_port_register_hier_out("out")

			if (item_size == gr.sizeof_char):
				self.vec_source = messageutils.vector_source_pdu_b(vector, period_ms, tag_output, debug, pkt_limit, initial_delay)
			elif (item_size == gr.sizeof_float):
				self.vec_source = messageutils.vector_source_pdu_f(vector, period_ms, tag_output, debug, pkt_limit, initial_delay)
			elif (item_size == gr.sizeof_gr_complex):
				self.vec_source = messageutils.vector_source_pdu_c(vector, period_ms, tag_output, debug, pkt_limit, initial_delay)
			else:
				print "Invalid Data Type."

			self.null_sink = blocks.null_sink(item_size)

			# Define blocks and connect them
			self.msg_connect((self.vec_source, 'pdus'), (self, 'out'))    
			self.connect((self.vec_source, 0), (self.null_sink, 0))   
			
		def set_period(self,period_ms):
			self.vec_source.set_period(period_ms)
			
		def set_vec(self,vector):
			self.vec_source.set_vec(vector)
			 
