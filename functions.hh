#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iterator>
#include <queue>
#include "partition.hh"


#ifndef PARTITION_HPP
#define PARTITION_HPP

#include <vector>

// Karmarkar-Karp algorithm declaration using a maximum heap
long long karmarkar_karp(const std::vector<long long>& numbers);

// Repeated random algorithm
long long repeated_random(const std::vector<long long>& numbers, bool prepartition);

// Hill climbing algorithm
long long hill_climbing(const std::vector<long long>& numbers, bool prepartition);

// Simulated annealing algorithm
long long simulated_annealing(const std::vector<long long>& numbers, bool prepartition);

// Utility to read numbers from a file
std::vector<long long> read_numbers(const char* file_path);

#endif // PARTITION_HH
