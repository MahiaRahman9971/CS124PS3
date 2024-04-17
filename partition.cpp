#include "partition.hh"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <algorithm_id> <input_file> <max_iterations>\n";
        return 1;
    }

    int algorithm_id = std::stoi(argv[1]);
    const char* input_file = argv[2];
    int max_iterations = std::stoi(argv[3]);

    // Read the input file
    std::vector<long long> numbers = read_input(input_file);
    long long residue;

    switch (algorithm_id) {
        case 0:
            residue = karmarkar_karp(numbers);
            break;
        case 1:
            residue = repeated_random(numbers, max_iterations, false);
            break;
        case 2:
            residue = hill_climbing(numbers, max_iterations, false);
            break;
        case 3:
            residue = simulated_annealing(numbers, max_iterations, false);
            break;
        case 11:
            residue = repeated_random(numbers, max_iterations, true);
            break;
        case 12:
            residue = hill_climbing(numbers, max_iterations, true);
            break;
        case 13:
            residue = simulated_annealing(numbers, max_iterations, true);
            break;
        default:
            std::cerr << "Invalid algorithm ID\n";
            return 2;
    }

    std::cout << "Residue: " << residue << std::endl;
    return 0;
}
