#include "partition.hh"
#include "functions.hh"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./partition flag algorithm inputfile\n";
        return 1;
    }

    int flag = std::atoi(argv[1]);
    int algorithm_code = std::atoi(argv[2]);
    std::string input_file = argv[3];

    std::vector<long long> numbers = read_numbers(input_file);
    long long residue = 0;

    switch (algorithm_code) {
        case 0:
            residue = karmarkar_karp(numbers);
            break;
        case 1:
            residue = repeated_random(numbers, false);
            break;
        case 2:
            residue = hill_climbing(numbers, false);
            break;
        case 3:
            residue = simulated_annealing(numbers, false);
            break;
        default:
            std::cerr << "Invalid algorithm code\n";
            return 1;


    }

    std::cout << "Residue: " << residue << std::endl;
    return 0;
}



