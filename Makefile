#!/bin/bash
CC=g++
CFLAGS= -lm -std=c++0x
DEPS = /home/john/Desktop/cpp/heatflow/headers/systemheader.hpp /home/john/Desktop/cpp/heatflow/headers/systemheader.hpp /usr/include/tnt/tnt_array1d.h /usr/include/tnt/tnt_array2d.h /usr/include/jama/jama_lu.h /home/j_p124/boost/boost_1_58_0/boost/multiprecision/cpp_dec_float.hpp /home/j_p124/boost/boost_1_58_0/boost/multiprecision/number.hpp 


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: parser.o system.o system_loop.o integrate.o TEG.o system2.o system_loop2.o TEG2.o throughput.o main.o
	g++ -o design *.o 
