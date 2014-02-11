#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Strobe
# Generated: Tue Feb 11 18:46:54 2014
##################################################

from gnuradio import blocks
from gnuradio import channels
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.wxgui import forms
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import messageutils
import numpy
import tagutils
import wx

class strobe(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Strobe")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.noise_volt = noise_volt = 0

        ##################################################
        # Blocks
        ##################################################
        _noise_volt_sizer = wx.BoxSizer(wx.VERTICAL)
        self._noise_volt_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_noise_volt_sizer,
        	value=self.noise_volt,
        	callback=self.set_noise_volt,
        	label='noise_volt',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._noise_volt_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_noise_volt_sizer,
        	value=self.noise_volt,
        	callback=self.set_noise_volt,
        	minimum=0,
        	maximum=3,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_noise_volt_sizer)
        self.tagutils_stream_to_tagged_stream_sourced_0 = tagutils.stream_to_tagged_stream_sourced(gr.sizeof_gr_complex, 1, 96*2, "packet_len", "s2ts")
        self.messageutils_pdu_debug_0 = messageutils.pdu_debug(True)
        self.digital_psk_mod_0 = digital.psk.psk_mod(
          constellation_points=8,
          mod_code="gray",
          differential=True,
          samples_per_symbol=2,
          excess_bw=0.35,
          verbose=False,
          log=False,
          )
        self.digital_mpsk_snr_est_cc_0 = digital.mpsk_snr_est_cc(2, 10000, 0.001)
        self.channels_channel_model_0 = channels.channel_model(
        	noise_voltage=noise_volt,
        	frequency_offset=0.0,
        	epsilon=1.0,
        	taps=(1.0 + 1.0j, ),
        	noise_seed=0,
        	block_tags=False
        )
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate)
        self.blocks_tagged_stream_to_pdu_0 = blocks.tagged_stream_to_pdu(blocks.complex_t, "packet_len")
        self.analog_random_source_x_0 = blocks.vector_source_b(map(int, numpy.random.randint(0, 2, 1000)), True)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.tagutils_stream_to_tagged_stream_sourced_0, 0), (self.blocks_tagged_stream_to_pdu_0, 0))
        self.connect((self.digital_mpsk_snr_est_cc_0, 0), (self.tagutils_stream_to_tagged_stream_sourced_0, 0))
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.digital_psk_mod_0, 0))
        self.connect((self.digital_psk_mod_0, 0), (self.channels_channel_model_0, 0))
        self.connect((self.channels_channel_model_0, 0), (self.digital_mpsk_snr_est_cc_0, 0))

        ##################################################
        # Asynch Message Connections
        ##################################################
        self.msg_connect(self.blocks_tagged_stream_to_pdu_0, "pdus", self.messageutils_pdu_debug_0, "pdus")

# QT sink close method reimplementation

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

    def get_noise_volt(self):
        return self.noise_volt

    def set_noise_volt(self, noise_volt):
        self.noise_volt = noise_volt
        self._noise_volt_slider.set_value(self.noise_volt)
        self._noise_volt_text_box.set_value(self.noise_volt)
        self.channels_channel_model_0.set_noise_voltage(self.noise_volt)

if __name__ == '__main__':
    import ctypes
    import os
    if os.name == 'posix':
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = strobe()
    tb.Start(True)
    tb.Wait()

