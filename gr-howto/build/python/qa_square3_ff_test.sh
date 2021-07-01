#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir="/Users/victoromoniyi/Desktop/GNUBlocks/gr-howto/python"
export GR_CONF_CONTROLPORT_ON=False
export PATH="/Users/victoromoniyi/Desktop/GNUBlocks/gr-howto/build/python":$PATH
export DYLD_LIBRARY_PATH="":$DYLD_LIBRARY_PATH
export PYTHONPATH=/Users/victoromoniyi/Desktop/GNUBlocks/gr-howto/build/swig:$PYTHONPATH
/opt/local/Library/Frameworks/Python.framework/Versions/3.7/bin/python3.7 /Users/victoromoniyi/Desktop/GNUBlocks/gr-howto/python/qa_square3_ff.py 
