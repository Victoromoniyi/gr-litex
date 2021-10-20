#!/usr/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir="/home/cardiff/Desktop/gr-litexgnu/python"
export GR_CONF_CONTROLPORT_ON=False
export PATH="/home/cardiff/Desktop/gr-litexgnu/build/python":"$PATH"
export LD_LIBRARY_PATH="":$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
/usr/bin/python3 /home/cardiff/Desktop/gr-litexgnu/python/qa_litexgnu.py 
