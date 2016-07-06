/* -*- c++ -*- */

#define MESSAGEUTILS_API
#define BLOCKS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "messageutils_swig_doc.i"

%{
#include "messageutils/pdu_debug.h"
#include "messageutils/message_thresh_switch.h"
#include "messageutils/add_const_msg.h"
#include "messageutils/vector_pdu_source_f.h"
#include "messageutils/vector_pdu_source_b.h"
#include "messageutils/mult_const_msg.h"
#include "messageutils/vector_pdu_source_c.h"
#include "messageutils/socket_pdu_repack.h"
#include "messageutils/vector_pdu_source_i.h"
#include "messageutils/pdu_splitter.h"
%}

%include "gnuradio/blocks/pdu.h"

%include "messageutils/pdu_debug.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, pdu_debug);
%include "messageutils/message_thresh_switch.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, message_thresh_switch);
%include "messageutils/add_const_msg.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, add_const_msg);


%include "messageutils/vector_pdu_source_f.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, vector_pdu_source_f);
%include "messageutils/vector_pdu_source_b.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, vector_pdu_source_b);
%include "messageutils/mult_const_msg.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, mult_const_msg);
%include "messageutils/vector_pdu_source_c.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, vector_pdu_source_c);

%include "messageutils/socket_pdu_repack.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, socket_pdu_repack);
%include "messageutils/vector_pdu_source_i.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, vector_pdu_source_i);

%include "messageutils/pdu_splitter.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, pdu_splitter);
