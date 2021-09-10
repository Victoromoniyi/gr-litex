from gnuradio import gr, gr_unittest
from gnuradio import blocks
 
try:
    from howto import square_ff
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from howto import square_ff
 
class qa_square_ff(gr_unittest.TestCase):
 
    def setUp(self):
        self.tb = gr.top_block()
 
    def tearDown(self):
        self.tb = None

    def test_001_square_ff(self):      
        src_data = (3, 4, 5.5, 2, 3)
        expected_result = (9, 16, 30.25, 4, 9)
        src = blocks.vector_source_f(src_data)
        sqr = square_ff()
        dst = blocks.vector_sink_f()
        self.tb.connect(src, sqr)
        self.tb.connect(sqr,dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)
        # check data

 
if __name__ == '__main__':
    gr_unittest.run(qa_square_ff, "qa_square_ff.yaml")