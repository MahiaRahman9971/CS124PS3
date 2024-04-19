#pragma once
#ifndef PARTITION_H
#define PARTITION_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
#include <random>
#include <cstdlib>
#include <unordered_map>
#include <climits>

long long karmarkar_karp(const std::vector<long long>& nums);
long long karmarkar_karp_prepartitioned(const std::vector<long long>& A, const std::vector<int>& P);
std::vector<int> random_solution(size_t n, bool prepartition);
long long calculate_residue(const std::vector<long long>& A, const std::vector<int>& S);
std::vector<int> neighbor_solution(const std::vector<int>& solution, bool prepartition);
long long repeated_random(const std::vector<long long>& A, bool prepartition);
long long hill_climbing(const std::vector<long long>& A, bool prepartition);
double temperature(int iter);
long long simulated_annealing(const std::vector<long long>& A, bool prepartition);
#endif 