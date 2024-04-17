# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

# Targets and Dependencies
all: partition

partition: partition.o algorithms.o
	$(CXX) $(CXXFLAGS) -o partition partition.o algorithms.o

generate_input: generate_input.o 
	$(CXX) $(CXXFLAGS) -o generate_input generate_input.o

generate_input.o: generate_input.cpp 
	$(CXX) $(CXXFLAGS) -c generate_input.cpp

partition.o: partition.cpp
	$(CXX) $(CXXFLAGS) -c partition.cpp

algorithms.o: algorithms.cpp
	$(CXX) $(CXXFLAGS) -c algorithms.cpp

clean:
	rm -f partition generate_input *.o
