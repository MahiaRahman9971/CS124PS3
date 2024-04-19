#include "partition.hh"

// Global random device and random generator
std::random_device rd;
std::mt19937_64 rng(rd());
int max_iter = 30000;

// Function to read the input file into a vector of integers
std::vector<long long> read_input(const char* filename) {
    std::vector<long long> numbers;
    std::ifstream file(filename);
    long long number;
    while (file >> number) {
        numbers.push_back(number);
    }
    return numbers;
}

// Apply the transformation based on prepartitioning P to get a new array A'
// Input: A - original array, P - prepartitioning
// Output: A' - transformed array
// Example: A = [1, 2, 3, 4, 5], P = [1, 1, 2, 2, 3]
std::vector<long long> transform_prepartition(const std::vector<long long>& A, const std::vector<int>& P) {
    int num_partitions = *max_element(P.begin(), P.end()) + 1; 
    std::vector<long long> partition_sums(num_partitions, 0);
    for (size_t i = 0; i < A.size(); ++i) {
        partition_sums[P[i]] += A[i];
    }
    std::vector<long long> A_prime;
    for (long long sum : partition_sums) {
        if (sum != 0) { 
            A_prime.push_back(sum);
        }
    }
    return A_prime;
}

// Function to calculate residue for a given solution
// Input: A - array of integers, S - solution
// Output: residue of the solution
// Example: A = [1, 2, 3, 4, 5], S = [1, -1, 1, -1, 1] -> residue = 0
long long calculate_residue(const std::vector<long long>& A, const std::vector<int>& S) {
    long long residue = 0;
    for (size_t i = 0; i < A.size(); ++i) {
        residue += S[i] * A[i];
    }
    return std::abs(residue);
}

// Generate a random solution
// Input: solution - vector to store the solution, dist - uniform distribution, prepartition - flag for prepartitioning
// Output: solution vector with random values
// Example: solution = [0, 0, 0, 0, 0], prepartition = true -> solution = [1, 2, 3, 4, 5]
void generate_random_solution(std::vector<int>& solution, std::uniform_int_distribution<int>& dist, bool prepartition) {
    if (prepartition) {
        for (auto& elem : solution) {
            elem = dist(rng);
        }
    } else {
        std::uniform_int_distribution<int> sign_dist(-1, 1);
        for (auto& elem : solution) {
            elem = sign_dist(rng);
        }
    }
}

// Generate a neighboring solution
// Input: solution - vector to store the solution, prepartition - flag for prepartitioning
// Output: solution vector with a neighbor solution
// Example: solution = [1, 2, 3, 4, 5], prepartition = true -> solution = [1, 2, 3, 4, 5]
void generate_neighbor_solution(std::vector<int>& solution, bool prepartition) {
    std::uniform_int_distribution<int> dist_index(0, solution.size() - 1);
    int changes = 1 + (rand() % 3); 
    for (int change = 0; change < changes; ++change) {
        int i = dist_index(rng);
        if (prepartition) {
            int new_partition = dist_index(rng) + 1;
            while (solution[i] == new_partition) { 
                new_partition = dist_index(rng) + 1;
            }
            solution[i] = new_partition;
        } else {
            solution[i] = -solution[i]; 
        }
    }
}

// Karmarkar-Karp algorithm
// Input: A - array of integers
// Output: residue of the Karmarkar-Karp algorithm
// Example: A = [1, 2, 3, 4, 5] -> residue = 1
long long karmarkar_karp(const std::vector<long long>& A) {
    std::vector<long long> heap = A;
    std::make_heap(heap.begin(), heap.end());
    while (heap.size() > 1) {
        std::pop_heap(heap.begin(), heap.end());
        long long largest = heap.back();
        heap.pop_back();

        std::pop_heap(heap.begin(), heap.end());
        long long second_largest = heap.back();
        heap.pop_back();

        long long new_elem = largest - second_largest;
        heap.push_back(new_elem);
        std::push_heap(heap.begin(), heap.end());
    }
    return std::abs(heap[0]);
}

// Karmarkar-Karp algorithm using prepartitioning
// Input: A - array of integers, P - prepartitioning
// Output: residue of the Karmarkar-Karp algorithm
// Example: A = [1, 2, 3, 4, 5], P = [1, 1, 2, 2, 3] -> residue = 1
long long karmarkar_karp_prepartitioned(const std::vector<long long>& A, const std::vector<int>& P) {
    std::vector<long long> A_prime = transform_prepartition(A, P);
    return karmarkar_karp(A_prime);
}

// Repeated Random algorithm
// Input: A - array of integers, prepartition - flag for prepartitioning
// Output: residue of the Repeated Random algorithm
// Example: A = [1, 2, 3, 4, 5], prepartition = false -> residue = 0
long long repeated_random(const std::vector<long long>& A, bool prepartition) {
    std::uniform_int_distribution<int> dist(1, A.size());
    std::vector<int> solution(A.size());
    long long best_residue = LLONG_MAX;

    // Generate a random solution
    generate_random_solution(solution, dist, prepartition);
    for (int i = 0; i < max_iter; ++i) {
        std::vector s_prime = solution;

        long long res = (prepartition ? karmarkar_karp_prepartitioned(A, solution) : calculate_residue(A, solution));
        long long current_residue = calculate_residue(A, s_prime);
        long long new_residue = calculate_residue(A, solution);
        if (current_residue < new_residue) {
            best_residue = current_residue;
        }
    }
    return best_residue;
}


// Hill Climbing algorithm
// Input: A - array of integers, prepartition - flag for prepartitioning
// Output: residue of the Hill Climbing algorithm
// Example: A = [1, 2, 3, 4, 5], prepartition = false -> residue = 0
long long hill_climbing(const std::vector<long long>& A, bool prepartition) {
    std::uniform_int_distribution<int> dist(1, A.size());
    std::vector<int> solution(A.size());
    generate_random_solution(solution, dist, prepartition);

    long long current_residue = (prepartition ? karmarkar_karp_prepartitioned(A, solution) : calculate_residue(A, solution));
    long long best_residue = current_residue;

    for (int i = 0; i < max_iter; ++i) {
        std::vector<int> new_solution = solution;
        generate_neighbor_solution(new_solution, prepartition);
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

// Temperature schedule function
double temperature(int iter) {
    return 1e10 * pow(0.8, iter / 300);
}

// Simulated Annealing algorithm
long long simulated_annealing(const std::vector<long long>& A, bool prepartition) {
    std::uniform_int_distribution<int> dist(1, A.size());
    std::vector<int> solution(A.size());
    generate_random_solution(solution, dist, prepartition);

    long long current_residue = (prepartition ? karmarkar_karp_prepartitioned(A, solution) : calculate_residue(A, solution));
    long long best_residue = current_residue;

    std::uniform_real_distribution<double> prob(0.0, 1.0);

    for (int i = 0; i < max_iter; ++i) {
        std::vector<int> new_solution = solution;
        generate_neighbor_solution(new_solution, prepartition);
        long long new_residue = (prepartition ? karmarkar_karp_prepartitioned(A, new_solution) : calculate_residue(A, new_solution));

        if (new_residue < current_residue || std::exp(-(new_residue - current_residue) / temperature(i)) > prob(rng)) {
            current_residue = new_residue;
            solution = new_solution;
        }

        if (current_residue < best_residue) {
            best_residue = current_residue;
        }
    }
    return best_residue;
}

// Generate a random instance of size elements with values up to max_value
std::vector<long long> generate_random_instance(int size, long long max_value) {
    std::vector<long long> instance;
    std::uniform_int_distribution<long long> dist(1, max_value);
    for (int i = 0; i < size; ++i) {
        instance.push_back(dist(rng));
    }
    return instance;
}

// Questions: 
// prepartiition with kk