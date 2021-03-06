#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Pdu Source
# Generated: Fri Oct 17 15:23:09 2014
##################################################

from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import messageutils
import wx

class pdu_source(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Pdu Source")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.float_data = float_data =  [0.3426 ,3.5784 ,2.7694,  0.5377, 1.8339, -2.2588, 0.8622, 0.3188, -1.3077, -0.4336]
        self.ascii_bytes = ascii_bytes = [84, 104, 105, 115, 32, 105, 115, 32, 97, 32, 116, 101, 115, 116]

        ##################################################
        # Blocks
        ##################################################
        self.messageutils_vector_pdu_xx_0 = messageutils.vector_pdu_source_b(ascii_bytes, 1000, True, False, 0)
        self.messageutils_pdu_debug_0 = messageutils.pdu_debug(gr.sizeof_char, False, False, False, True)

        ##################################################
        # Asynch Message Connections
        ##################################################
        self.msg_connect(self.messageutils_vector_pdu_xx_0, "pdus", self.messageutils_pdu_debug_0, "pdus")

# QT sink close method reimplementation

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_float_data(self):
        return self.float_data

    def set_float_data(self, float_data):
        self.float_data = float_data

    def get_ascii_bytes(self):
        return self.ascii_bytes

    def set_ascii_bytes(self, ascii_bytes):
        self.ascii_bytes = ascii_bytes
        self.messageutils_vector_pdu_xx_0.set_vec(self.ascii_bytes)

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
    tb = pdu_source()
    tb.Start(True)
    tb.Wait()

