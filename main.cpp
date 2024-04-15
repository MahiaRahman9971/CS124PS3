#include "partition.hh"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./partition flag algorithm inputfile\n";
        return 1;
    }

    int flag = std::atoi(argv[1]);
    int algorithm_code = std::atoi(argv[2]);
    std::string input_file = argv[3];

    if (flag == -1) {
        // Testing standard representation: Generate and print a random solution
        int n = 5;  // assuming we want a solution of size 100
        std::vector<int> solution = generate_random_solution(n);
        std::cout << "Sample standard representation solution:\n";
        for (int i = 0; i < solution.size(); ++i) {
            std::cout << solution[i] << " ";
        }
        std::cout << std::endl;
        return 0;
    }

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
        case 11:
            residue = prepartitioned_repeated_random(numbers);
            break;
        case 12:
            residue = prepartitioned_hill_climbing(numbers);
            break;
        case 13:
            residue = prepartitioned_simulated_annealing(numbers);
            break;
        default:
            std::cerr << "Invalid algorithm code\n";
            return 1;
    }

    // std::cout << "Residue: " << residue << std::endl;
    // std::cout << << std::endl;
    // return 0;
}



