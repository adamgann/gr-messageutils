#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Mon Aug 31 17:51:43 2015
##################################################

from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import messageutils
import wx

class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Blocks
        ##################################################
        self.messageutils_socket_pdu_repack_0 = messageutils.socket_pdu_repack(gr.sizeof_float,True,False)
        self.messageutils_pdu_debug_1 = messageutils.pdu_debug(gr.sizeof_float, False, True, False, True)
        self.messageutils_pdu_debug_0_0 = messageutils.pdu_debug(gr.sizeof_char, False, True, False, True)
        self.blocks_socket_pdu_0_0 = blocks.socket_pdu("UDP_SERVER", "127.0.0.1", "52002", 10000, False)
        self.blocks_socket_pdu_0 = blocks.socket_pdu("UDP_SERVER", "127.0.0.1", "52001", 10000, False)

        ##################################################
        # Asynch Message Connections
        ##################################################
        self.msg_connect(self.messageutils_socket_pdu_repack_0, "out", self.messageutils_pdu_debug_1, "pdus")
        self.msg_connect(self.blocks_socket_pdu_0, "pdus", self.messageutils_socket_pdu_repack_0, "in")
        self.msg_connect(self.blocks_socket_pdu_0_0, "pdus", self.messageutils_pdu_debug_0_0, "pdus")


if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
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
