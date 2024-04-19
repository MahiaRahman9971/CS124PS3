#include "partition.hh"

// Global random device and random generator
std::random_device rd;
std::mt19937_64 rng(rd());
std::uniform_int_distribution<long long> dist(0, 1000000000000LL);
int max_iter = 30000;

// Function to read the input file into a vector of integers
std::vector<long long> read_input(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    std::vector<long long> numbers;
    long long number;
    while (file >> number) {
        numbers.push_back(number);
    }
    return numbers;
}

// Function to generate a new random prepartitioning
std::vector<int> prepartitioning(const std::vector<long long>& A) {
    int n = A.size();
    std::vector<int> P(n);

    // Randomly assign each element in A to a partition
    std::uniform_int_distribution<int> partition_dist(1, n);
    for (int i = 0; i < n; ++i) {
        P[i] = partition_dist(rng);
    }

    return P;
}


// Function to calculate residue for a given solution
long long calculate_residue(const std::vector<long long>& A, const std::vector<int>& S) {
    long long residue = 0;
    for (size_t i = 0; i < A.size(); ++i) {
        residue += S[i] * A[i];
    }
    return std::abs(residue);
}

// Generate a random solution
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

// Karmarkar-Karp algorithm
long long karmarkar_karp(const std::vector<long long>& A) {
    if (A.empty()) {
        std::cerr << "Input vector A is empty." << std::endl;
        return 0;
    }

    std::vector<long long> heap = A;
    std::make_heap(heap.begin(), heap.end());
    while (heap.size() > 1) {
        std::pop_heap(heap.begin(), heap.end());
        long long largest = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            std::pop_heap(heap.begin(), heap.end());
            long long second_largest = heap.back();
            heap.pop_back();

            long long new_elem = largest - second_largest;
            heap.push_back(new_elem);
            std::push_heap(heap.begin(), heap.end());
        } else {
            std::cerr << "Heap doesn't have enough elements." << std::endl;
            break;
        }
    }
    return std::abs(heap[0]);
}

// Prepartitioning function for Karmarkar-Karp
long long karmarkar_karp_prepartitioned(const std::vector<long long>& A, const std::vector<int>& P) {
    int n = A.size();
    std::vector<long long> partition_sums(n, 0);

    // Aggregate the sums for each partition
    for (int i = 0; i < n; ++i) {
    if (P[i] <= 0 || P[i] > n) {
        std::cerr << "Error: Invalid value in P: " << P[i] << "\n";
        return -1; // or some other error value
        }
        partition_sums[P[i] - 1] += A[i];
    }

    return karmarkar_karp(partition_sums);
}

// Repeated Random algorithm
long long repeated_random(const std::vector<long long>& A, bool prepartition) {
    std::uniform_int_distribution<int> dist(1, A.size());
    std::vector<int> solution(A.size());

    // Start with a random solution or prepartition
    if (prepartition) {
        solution = prepartitioning(A);
    } else {
        generate_random_solution(solution, dist, prepartition);
    }

    long long best_residue = calculate_residue(A, solution);

    for (int i = 0; i < max_iter; ++i) {
        if (prepartition) {
            solution = prepartitioning(A);
        } else {
            generate_random_solution(solution, dist, prepartition);
        }

        long long residue = calculate_residue(A, solution);

        if (residue < best_residue) {
            best_residue = residue;
        }
    }
    return best_residue;
}


// Generate a neighboring solution
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

// Generate and return a random neighbor of the current solution
std::vector<int> random_neighbor(const std::vector<int>& solution, bool prepartition) {
    std::vector<int> neighbor = solution;
    generate_neighbor_solution(neighbor, prepartition);
    return neighbor;
}


// Hill Climbing algorithm
long long hill_climbing(const std::vector<long long>& A, bool prepartition) {
    std::uniform_int_distribution<int> dist(1, A.size());
    std::vector<int> solution(A.size());


    generate_random_solution(solution, dist, prepartition);

    long long best_residue = calculate_residue(A, solution);

    for (int i = 0; i < max_iter; ++i) {
        if (prepartition) {
            solution = prepartitioning(A);
        } else {
            generate_random_solution(solution, dist, prepartition);
        }

        long long residue = calculate_residue(A, solution);

        if (residue < best_residue) {
            best_residue = residue;
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

    long long current_residue = (prepartition ? simulated_annealing_prepartitioned(A, solution): calculate_residue(A, solution));
    long long best_residue = current_residue;

    std::uniform_real_distribution<double> prob(0.0, 1.0);

    for (int i = 0; i < max_iter; ++i) {
        std::vector<int> new_solution = solution;
        generate_neighbor_solution(new_solution, prepartition);
        long long new_residue = (prepartition ? simulated_annealing_prepartitioned(A, new_solution): calculate_residue(A, new_solution));

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

std::vector<long long> generate_random_instance(int size, long long max_value) {
    std::vector<long long> instance;
    std::uniform_int_distribution<long long> dist(1, max_value);
    for (int i = 0; i < size; ++i) {
        instance.push_back(dist(rng));
    }
    return instance;
}
