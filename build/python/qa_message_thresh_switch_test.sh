#!/bin/sh
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/adam/src/gr-messageutils/python
export PATH=/home/adam/src/gr-messageutils/build/python:$PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export PYTHONPATH=/home/adam/src/gr-messageutils/build/swig:$PYTHONPATH
/usr/bin/python /home/adam/src/gr-messageutils/python/qa_message_thresh_switch.py 
