#include "partition.hh"

// Global random device and random generator
std::random_device rd;
std::mt19937_64 rng(rd());
int max_iter = 25000;

// Karmarkar-Karp algorithm 
long long karmarkar_karp(const std::vector<long long>& nums) {
    std::vector<long long> heap(nums);
    std::make_heap(heap.begin(), heap.end());

    while (heap.size() > 1) {
        std::pop_heap(heap.begin(), heap.end());
        long long largest = heap.back();
        heap.pop_back();

        std::pop_heap(heap.begin(), heap.end());
        long long second_largest = heap.back();
        heap.pop_back();

        long long difference = largest - second_largest;
        heap.push_back(difference);
        std::push_heap(heap.begin(), heap.end());
    }
    return std::abs(heap.front());
}

long long karmarkar_karp_prepartitioned(const std::vector<long long>& A, const std::vector<int>& P) {
    std::unordered_map<int, long long> partition_sums;
    for (size_t i = 0; i < A.size(); ++i) {
        partition_sums[P[i]] += A[i];
    }

    std::vector<long long> partition_values;
    for (const auto& pair : partition_sums) {
        partition_values.push_back(pair.second);
    }
    return karmarkar_karp(partition_values);
}

std::vector<int> random_solution(size_t n, bool prepartition) {
    std::vector<int> solution(n);
    if (prepartition) {
        std::uniform_int_distribution<int> part_dist(0, n - 1);
        for (size_t i = 0; i < n; ++i) {
            solution[i] = part_dist(rng);
        }
    } else {
        std::uniform_int_distribution<int> sign_dist(0, 1);
        for (size_t i = 0; i < n; ++i) {
            solution[i] = sign_dist(rng) * 2 - 1; // generates -1 or 1
        }
    } 
    return solution;
}

long long calculate_residue(const std::vector<long long>& A, const std::vector<int>& S) {
    long long residue = 0;
    for (size_t i = 0; i < A.size(); ++i) {
        residue += S[i] * A[i];
    }
    return std::abs(residue);
}

std::vector<int> neighbor_solution(const std::vector<int>& solution, bool prepartition) {
    std::vector<int> neighbor = solution;
    std::uniform_int_distribution<size_t> index_dist(0, solution.size() - 1);
    size_t i = index_dist(rng);
    size_t j = index_dist(rng);
    while (j == i) {
        j = index_dist(rng);
    }

    if (prepartition) {
        std::uniform_int_distribution<int> part_dist(0, solution.size() - 1);
        neighbor[i] = part_dist(rng);
    } else {
        neighbor[i] = -neighbor[i];
        if (std::bernoulli_distribution(0.5)(rng)) {
            neighbor[j] = -neighbor[j];
        }
    }
    return neighbor;
}

long long repeated_random(const std::vector<long long>& A, bool prepartition) {
    std::vector<int> solution = random_solution(A.size(), prepartition);
    long long best_residue = (prepartition ? karmarkar_karp_prepartitioned(A, solution) : calculate_residue(A, solution));

    for (int i = 0; i < max_iter; ++i) {
        std::vector<int> new_solution = random_solution(A.size(), prepartition);
        long long new_residue = (prepartition ? karmarkar_karp_prepartitioned(A, new_solution) : calculate_residue(A, new_solution));
        if (new_residue < best_residue) {
            best_residue = new_residue;
        }
    }
    return best_residue;
}

long long hill_climbing(const std::vector<long long>& A, bool prepartition) {
    std::vector<int> solution = random_solution(A.size(), prepartition);
    long long current_residue = (prepartition ? karmarkar_karp_prepartitioned(A, solution) : calculate_residue(A, solution));
    long long best_residue = current_residue;

    for (int i = 0; i < max_iter; ++i) {
        std::vector<int> new_solution = neighbor_solution(solution, prepartition);
        long long new_residue = (prepartition ? karmarkar_karp_prepartitioned(A, new_solution) : calculate_residue(A, new_solution));
        if (new_residue < current_residue) {
            current_residue = new_residue;
            solution = new_solution;
        }
        if (current_residue < best_residue) {
            best_residue = current_residue;
        }
    }
    return best_residue;
}

double temperature(int iter) {
    return 1e10 * pow(0.8, iter / 300);
}

long long simulated_annealing(const std::vector<long long>& A, bool prepartition) {
    std::vector<int> solution = random_solution(A.size(), prepartition);
    long long current_residue = (prepartition ? karmarkar_karp_prepartitioned(A, solution) : calculate_residue(A, solution));
    long long best_residue = current_residue;

    for (int i = 0; i < max_iter; ++i) {
        std::vector<int> new_solution = neighbor_solution(solution, prepartition);
        long long new_residue = (prepartition ? karmarkar_karp_prepartitioned(A, new_solution) : calculate_residue(A, new_solution));

        if (new_residue < current_residue) {
            current_residue = new_residue;
            solution = new_solution;
        } else {
            double T = temperature(i);
            double prob = exp(-(new_residue - current_residue) / T);
            if ((double)rand() / RAND_MAX < prob) {
                current_residue = new_residue;
                solution = new_solution;
            }
        }

        if (current_residue < best_residue) {
            best_residue = current_residue;
        }
    }
    return best_residue;
}
