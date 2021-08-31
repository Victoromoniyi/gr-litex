#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2021 gr-integrator author.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#


import numpy
import litex
import litepcie
import litedram
import mmap

from gnuradio import gr

class integrator(gr.sync_block):
    """
    docstring for block integrator
    """
    def __init__(self):
        gr.sync_block.__init__(self,
            name="integrator",
            in_sig=[numpy.float32],
            out_sig=[numpy.float32],)

        connected = False
        
        fd = open(litepcie_device)
        if (fd < 0):
            print ("Could not open device")
            fd.close()
        else:
            print ("Device connected")
            connected = True
            

    def work(self, input_items, output_items):
        if connected == True:
            output_items[0][:] = input_items[0] * input_items[0]
            return len(output_items[0])
        else:
            return None
            print ("Device not connected")