# CMake generated Testfile for 
# Source directory: /home/cardiff/Desktop/GNULiteX/gr-howto/python
# Build directory: /home/cardiff/Desktop/GNULiteX/gr-howto/build/python
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(qa_square_ff "/usr/bin/sh" "/home/cardiff/Desktop/GNULiteX/gr-howto/build/python/qa_square_ff_test.sh")
set_tests_properties(qa_square_ff PROPERTIES  _BACKTRACE_TRIPLES "/home/cardiff/local/lib/cmake/gnuradio/GrTest.cmake;110;add_test;/home/cardiff/Desktop/GNULiteX/gr-howto/python/CMakeLists.txt;34;GR_ADD_TEST;/home/cardiff/Desktop/GNULiteX/gr-howto/python/CMakeLists.txt;0;")
subdirs("bindings")
