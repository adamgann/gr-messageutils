/* -*- c++ -*- */

#define MESSAGEUTILS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "messageutils_swig_doc.i"

%{
#include "messageutils/pdu_debug.h"
#include "messageutils/message_thresh_switch.h"
#include "messageutils/add_const_msg.h"
%}

%include "messageutils/pdu_debug.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, pdu_debug);
%include "messageutils/message_thresh_switch.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, message_thresh_switch);
%include "messageutils/add_const_msg.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, add_const_msg);
