# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

# Targets and Dependencies
all: main

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cc

clean:
	rm -f main main.o