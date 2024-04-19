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

std::vector<long long> read_input(const char* filename);
std::vector<long long> transform_prepartition(const std::vector<long long>& A, const std::vector<int>& P);
long long karmarkar_karp(const std::vector<long long>& A);
long long karmarkar_karp_prepartitioned(const std::vector<long long>& A, const std::vector<int>& P);
long long calculate_residue(const std::vector<long long>& A, const std::vector<int>& S);
void generate_random_solution(std::vector<int>& solution, std::uniform_int_distribution<int>& dist, bool prepartition);
long long repeated_random(const std::vector<long long>& A, bool prepartition);
void generate_neighbor_solution(std::vector<int>& solution, bool prepartition);
long long hill_climbing(const std::vector<long long>& A, bool prepartition);
double temperature(int iter);
long long simulated_annealing(const std::vector<long long>& A, bool prepartition);
std::vector<long long> generate_random_instance(int size, long long max_value);
std::vector<int> random_neighbor(const std::vector<int>& solution, bool prepartition);

#endif 