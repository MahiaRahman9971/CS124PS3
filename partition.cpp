#include "partition.hh"

std::vector<long long> read_numbers(const char* file_path) {
    std::vector<long long> numbers;
    std::ifstream file(file_path);
    long long number;
    while (file >> number) {
        numbers.push_back(number);
    }
    return numbers;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./partition flag algorithm inputfile\n";
        return 1;
    }

    int flag = std::atoi(argv[1]);
    int algorithm = std::atoi(argv[2]);
    const char* input_file = argv[3];

    std::vector<long long> numbers = read_numbers(input_file);
    long long residue;

    switch (algorithm) {
        case 0:
            residue = karmarkar_karp(numbers);
            break;
        case 1:
        case 2:
        case 3:
            residue = repeated_random(numbers, algorithm == 11);
            break;
        default:
            std::cerr << "Invalid algorithm code\n";
            return 1;
    }

    std::cout << "Residue: " << residue << std::endl;
    return 0;
}
