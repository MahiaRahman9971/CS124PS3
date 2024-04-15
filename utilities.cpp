#include "partition.hh"


// Standard Representation of a solution: 
// Choose two random indices from 1 to n and swap their signs with proability 0.5
std::vector<int> standard_representation(const std::vector<int>& solution) {
    std::vector<int> neighbor = solution;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, solution.size() - 1);
    int i = dis(gen);
    int j = dis(gen);
    neighbor[i] = -neighbor[i];
    neighbor[j] = -neighbor[j];
    return neighbor;
}

std::vector<int> generate_prepartition(int n) {
    std::vector<int> prepartition(n); // Initialize a vector of size n
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, n);  // Define a uniform distribution from 1 to n
    std::generate(prepartition.begin(), prepartition.end(), [&]() { return dis(gen); }); 
    return prepartition;
}

std::vector<long long> read_numbers(const std::string& file_path) {
    std::vector<long long> numbers;
    std::ifstream file(file_path);
    long long number;
    while (file >> number) {
        numbers.push_back(number);
    }
    return numbers;
}

// Generate a random solution of size n of 1s and -1s
std::vector<int> generate_random_solution(int n) {
    std::vector<int> solution(n); // Initialize a vector of size n
    std::random_device rd; // Obtain a random seed from the OS entropy device
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> dis(0, 1); // Define a uniform distribution from 0 to 1
    std::generate(solution.begin(), solution.end(), [&]() { return dis(gen) == 0 ? -1 : 1; }); // Generate a random solution
    return solution;
   
}

long long compute_residue(const std::vector<long long>& numbers, const std::vector<int>& solution) {
    // Placeholder for computing the residue
    return 0;
}

std::vector<int> get_neighbor(const std::vector<int>& solution) {
    // Placeholder for getting a neighbor solution
    return solution;
}