# Makefile for Randomized Algorithms
CXXFLAGS = -Wall -g -O2
CXX=g++

analyse: analyse.o BloomFilter.o SkipList.o RBST.o
	$(CXX) analyse.o BloomFilter.o SkipList.o RBST.o -o analyse -lm -lstdc++

analyse.o: analyse.cpp

BloomFilter.o: BloomFilter.cpp BloomFilter.hpp

SkipList.o: SkipList.cpp SkipList.hpp

RBST.o: RBST.cpp RBST.hpp

clean:
	rm -f *.o *.dat *.ps core analyse
