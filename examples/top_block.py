#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Thu Feb 13 16:25:57 2014
##################################################

from gnuradio import blocks
from gnuradio import channels
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.wxgui import forms
from gnuradio.wxgui import scopesink2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import messageutils
import numpy
import wx

class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.thresh = thresh = 15
        self.samp_rate = samp_rate = 32000
        self.noise_volt = noise_volt = 0

        ##################################################
        # Blocks
        ##################################################
        _thresh_sizer = wx.BoxSizer(wx.VERTICAL)
        self._thresh_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_thresh_sizer,
        	value=self.thresh,
        	callback=self.set_thresh,
        	label='thresh',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._thresh_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_thresh_sizer,
        	value=self.thresh,
        	callback=self.set_thresh,
        	minimum=0,
        	maximum=50,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_thresh_sizer)
        self.notebook_0 = self.notebook_0 = wx.Notebook(self.GetWin(), style=wx.NB_TOP)
        self.notebook_0.AddPage(grc_wxgui.Panel(self.notebook_0), "above")
        self.notebook_0.AddPage(grc_wxgui.Panel(self.notebook_0), "below")
        self.Add(self.notebook_0)
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
        self.wxgui_scopesink2_0_0 = scopesink2.scope_sink_c(
        	self.notebook_0.GetPage(0).GetWin(),
        	title="Scope Plot",
        	sample_rate=samp_rate,
        	v_scale=0,
        	v_offset=0,
        	t_scale=0,
        	ac_couple=False,
        	xy_mode=False,
        	num_inputs=1,
        	trig_mode=wxgui.TRIG_MODE_AUTO,
        	y_axis_label="Counts",
        )
        self.notebook_0.GetPage(0).Add(self.wxgui_scopesink2_0_0.win)
        self.wxgui_scopesink2_0 = scopesink2.scope_sink_c(
        	self.notebook_0.GetPage(1).GetWin(),
        	title="Scope Plot",
        	sample_rate=samp_rate,
        	v_scale=0,
        	v_offset=0,
        	t_scale=0,
        	ac_couple=False,
        	xy_mode=False,
        	num_inputs=1,
        	trig_mode=wxgui.TRIG_MODE_AUTO,
        	y_axis_label="Counts",
        )
        self.notebook_0.GetPage(1).Add(self.wxgui_scopesink2_0.win)
        self.messageutils_pdu_debug_0 = messageutils.pdu_debug(True, False)
        self.messageutils_message_thresh_switch_0 = messageutils.message_thresh_switch(gr.sizeof_gr_complex, "snr", thresh, True)
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
        self.blocks_throttle_0_0 = blocks.throttle(gr.sizeof_char*1, samp_rate)
        self.blocks_tagged_stream_to_pdu_0 = blocks.tagged_stream_to_pdu(blocks.complex_t, "packet_len")
        self.blocks_stream_to_tagged_stream_0 = blocks.stream_to_tagged_stream(gr.sizeof_gr_complex, 1, 1000, "packet_len")
        self.analog_random_source_x_0 = blocks.vector_source_b(map(int, numpy.random.randint(0, 2, 1000)), True)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.digital_psk_mod_0, 0), (self.channels_channel_model_0, 0))
        self.connect((self.blocks_throttle_0_0, 0), (self.digital_psk_mod_0, 0))
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_throttle_0_0, 0))
        self.connect((self.digital_mpsk_snr_est_cc_0, 0), (self.blocks_stream_to_tagged_stream_0, 0))
        self.connect((self.blocks_stream_to_tagged_stream_0, 0), (self.blocks_tagged_stream_to_pdu_0, 0))
        self.connect((self.digital_mpsk_snr_est_cc_0, 0), (self.messageutils_message_thresh_switch_0, 0))
        self.connect((self.messageutils_message_thresh_switch_0, 1), (self.wxgui_scopesink2_0, 0))
        self.connect((self.messageutils_message_thresh_switch_0, 0), (self.wxgui_scopesink2_0_0, 0))
        self.connect((self.channels_channel_model_0, 0), (self.digital_mpsk_snr_est_cc_0, 0))

        ##################################################
        # Asynch Message Connections
        ##################################################
        self.msg_connect(self.blocks_tagged_stream_to_pdu_0, "pdus", self.messageutils_pdu_debug_0, "pdus")
        self.msg_connect(self.blocks_tagged_stream_to_pdu_0, "pdus", self.messageutils_message_thresh_switch_0, "msg")

# QT sink close method reimplementation

    def get_thresh(self):
        return self.thresh

    def set_thresh(self, thresh):
        self.thresh = thresh
        self._thresh_slider.set_value(self.thresh)
        self._thresh_text_box.set_value(self.thresh)
        self.messageutils_message_thresh_switch_0.set_threshold(self.thresh)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0_0.set_sample_rate(self.samp_rate)
        self.wxgui_scopesink2_0.set_sample_rate(self.samp_rate)
        self.wxgui_scopesink2_0_0.set_sample_rate(self.samp_rate)

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
    tb = top_block()
    tb.Start(True)
    tb.Wait()

