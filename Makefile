# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

# Targets and Dependencies
.PHONY: all clean

all: partition generate_input

partition: partition.o algorithms.o
	$(CXX) $(CXXFLAGS) -o $@ $^

generate_input: generate_input.o 
	$(CXX) $(CXXFLAGS) -o $@ $<

generate_input.o: generate_input.cpp 
	$(CXX) $(CXXFLAGS) -c $<

partition.o: partition.cpp partition.hh
	$(CXX) $(CXXFLAGS) -c $<

algorithms.o: algorithms.cpp algorithms.hh
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f partition generate_input *.o
