#include "partition.hh"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <algorithm_id> <input_file>\n";
        return 1;
    }

    int algorithm_id = std::stoi(argv[2]);
    const char* input_file = argv[3];

    // Read the input file
    std::vector<long long> numbers = read_input(input_file);
    long long residue;

    switch (algorithm_id) {
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
            residue = repeated_random(numbers, true);
            break;
        case 12:
            residue = hill_climbing(numbers, true);
            break;
        case 13:
            residue = simulated_annealing(numbers, true);
            break;
        default:
            std::cerr << "Invalid algorithm ID\n";
            return 2;
    }

    std::cout << residue << std::endl;
    return 0;
}

// #include "partition.hh"
// #include <fstream>

// int main() {
//     const int num_instances = 50;
//     const int instance_size = 100;  // Define the size of each problem instance
//     const long long max_value = 1e6;  // Maximum value for elements in the instance

//     std::ofstream outfile("results.csv");
//     outfile << "Instance,KK,RR Standard,RR Prepartitioned,HC Standard,HC Prepartitioned,SA Standard,SA Prepartitioned\n";

//     for (int i = 0; i < num_instances; ++i) {
//         auto numbers = generate_random_instance(instance_size, max_value);
//         long long kk_result = karmarkar_karp(numbers);
//         long long rr_std = repeated_random(numbers, false);
//         long long rr_prep = repeated_random(numbers, true);
//         long long hc_std = hill_climbing(numbers, false);
//         long long hc_prep = hill_climbing(numbers, true);
//         long long sa_std = simulated_annealing(numbers, false);
//         long long sa_prep = simulated_annealing(numbers, true);

//         outfile << i + 1 << ',' << kk_result << ',' << rr_std << ',' << rr_prep << ','
//                 << hc_std << ',' << hc_prep << ',' << sa_std << ',' << sa_prep << '\n';
//     }

//     outfile.close();
//     return 0;
// }

