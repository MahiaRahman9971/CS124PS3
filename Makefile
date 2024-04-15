
# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

# Targets and Dependencies
all: generate

main: main.o utilities.o partition.o generate.o
	$(CXX) $(CXXFLAGS) -o main main.o utilities.o partition.o

generate: generate.o utilities.o partition.o
	$(CXX) $(CXXFLAGS) -o generate generate.o utilities.o partition.o

generate.o: generate.cpp 
	$(CXX) $(CXXFLAGS) -c generate.cpp

utilities.o: utilities.cpp
	$(CXX) $(CXXFLAGS) -c utilities.cpp

partition.o: partition.cpp partition.h
	$(CXX) $(CXXFLAGS) -c partition.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f main main.o utilities.o partition.o generate generate.o
