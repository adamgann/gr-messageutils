# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.




########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include(GrMiscUtils)
GR_EXPAND_X_CC_H_IMPL(messageutils vector_source_pdu_X 			b f c)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND messageutils_sources
    pdu_debug_impl.cc
    message_thresh_switch_impl.cc
    add_const_msg_impl.cc
    mult_const_msg_impl.cc
    socket_pdu_repack_impl.cc
    pdu_splitter_impl.cc
    ${generated_sources}
    pdu_to_file_impl.cc )

add_library(gnuradio-messageutils SHARED ${messageutils_sources})
add_dependencies(gnuradio-messageutils messageutils_generated_includes messageutils_generated_swigs)
target_link_libraries(gnuradio-messageutils ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-messageutils PROPERTIES DEFINE_SYMBOL "gnuradio_messageutils_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-messageutils
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

