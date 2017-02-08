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
#include "messageutils/mult_const_msg.h"
#include "messageutils/socket_pdu_repack.h"
#include "messageutils/pdu_splitter.h"

#include "messageutils/vector_source_pdu_b.h"
#include "messageutils/vector_source_pdu_f.h"
#include "messageutils/vector_source_pdu_c.h"
#include "messageutils/pdu_to_file.h"
%}

%include "gnuradio/blocks/pdu.h"

%include "messageutils/vector_source_pdu_b.h"
%include "messageutils/vector_source_pdu_f.h"
%include "messageutils/vector_source_pdu_c.h"

GR_SWIG_BLOCK_MAGIC2(messageutils, vector_source_pdu_b);
GR_SWIG_BLOCK_MAGIC2(messageutils, vector_source_pdu_f);
GR_SWIG_BLOCK_MAGIC2(messageutils, vector_source_pdu_c);

%include "messageutils/pdu_debug.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, pdu_debug);
%include "messageutils/message_thresh_switch.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, message_thresh_switch);
%include "messageutils/add_const_msg.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, add_const_msg);


%include "messageutils/mult_const_msg.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, mult_const_msg);


%include "messageutils/socket_pdu_repack.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, socket_pdu_repack);


%include "messageutils/pdu_splitter.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, pdu_splitter);
%include "messageutils/pdu_to_file.h"
GR_SWIG_BLOCK_MAGIC2(messageutils, pdu_to_file);
