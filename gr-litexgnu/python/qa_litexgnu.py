#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2021 gr-litexgnu author.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

from gnuradio import gr, gr_unittest
from gnuradio import blocks
try:
    from litexgnu import litexgnu
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from litexgnu import litexgnu

class qa_litexgnu(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None


    def test_001_descriptive_test_name(self):
        src_data = (1, 1, 1, 1, 1)
        expected_result = (1, 1, 1, 1, 1)
        src = blocks.vector_source_f(src_data)
        sqr = litexgnu()
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr,dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

if __name__ == '__main__':
    gr_unittest.run(qa_litexgnu)
