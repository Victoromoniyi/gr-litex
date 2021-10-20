# CMake generated Testfile for 
# Source directory: /home/cardiff/Desktop/gr-litexgnu/python
# Build directory: /home/cardiff/Desktop/gr-litexgnu/build/python
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(qa_litexgnu "/usr/bin/sh" "/home/cardiff/Desktop/gr-litexgnu/build/python/qa_litexgnu_test.sh")
set_tests_properties(qa_litexgnu PROPERTIES  _BACKTRACE_TRIPLES "/home/cardiff/local/lib/cmake/gnuradio/GrTest.cmake;110;add_test;/home/cardiff/Desktop/gr-litexgnu/python/CMakeLists.txt;34;GR_ADD_TEST;/home/cardiff/Desktop/gr-litexgnu/python/CMakeLists.txt;0;")
subdirs("bindings")
