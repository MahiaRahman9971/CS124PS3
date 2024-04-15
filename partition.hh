#ifndef PARTITION_H
#define PARTITION_H

#include <vector>
#include <string>

// Algorithm functions
// long long karmarkar_karp(const std::vector<long long>& numbers);
// long long repeated_random(const std::vector<long long>& numbers, bool prepartition);
// long long hill_climbing(const std::vector<long long>& numbers, bool prepartition);
// long long simulated_annealing(const std::vector<long long>& numbers, bool prepartition);

// Utility functions
std::vector<long long> read_numbers(const std::string& file_path);
std::vector<int> generate_random_solution(int n);
std::vector<int> generate_prepartition(int n);
long long compute_residue(const std::vector<long long>& numbers, const std::vector<int>& solution);
std::vector<int> get_neighbor(const std::vector<int>& solution);

#endif // PARTITION_H