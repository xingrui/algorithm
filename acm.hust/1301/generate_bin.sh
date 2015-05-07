rm -rf c_test
format_code use_cpp.cpp 
g++     -g -Wall use_cpp.cpp   -o test_bin -lm
