// #include "partition.hh"

// int main(int argc, char** argv) {
//     if (argc != 4) {
//         std::cerr << "Usage: " << argv[0] << " <algorithm_id> <input_file>\n";
//         return 1;
//     }

//     int algorithm_id = std::stoi(argv[2]);
//     const char* input_file = argv[3];

//     // Read the input file
//     std::vector<long long> numbers = read_input(input_file);
//     long long residue;

//     switch (algorithm_id) {
//         case 0:
//             residue = karmarkar_karp(numbers);
//             break;
//         case 1:
//             residue = repeated_random(numbers, false);
//             break;
//         case 2:
//             residue = hill_climbing(numbers, false);
//             break;
//         case 3:
//             residue = simulated_annealing(numbers, false);
//             break;
//         case 11:
//             residue = repeated_random(numbers, true);
//             break;
//         case 12:
//             residue = hill_climbing(numbers, true);
//             break;
//         case 13:
//             residue = simulated_annealing(numbers, true);
//             break;
//         default:
//             std::cerr << "Invalid algorithm ID\n";
//             return 2;
//     }

//     std::cout << residue << std::endl;
//     return 0;
// }

#include "partition.hh"

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    const int num_instances = 50;
    const int instance_size = 100;  // Define the size of each problem instance
    const long long max_value = 10e12;  // Maximum value for elements in the instance

    std::ofstream outfile("times.csv");
    outfile << "Instance,KK,RR Standard,RR Prepartitioned,HC Standard,HC Prepartitioned,SA Standard,SA Prepartitioned\n";

    for (int i = 0; i < num_instances; ++i) {
        auto numbers = generate_random_instance(instance_size, max_value);
        // Timing each algorithm for each instance

        start = std::chrono::system_clock::now();
        karmarkar_karp(numbers);
        end = std::chrono::system_clock::now();
        long long kk_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        start = std::chrono::system_clock::now();
        repeated_random(numbers, false);
        end = std::chrono::system_clock::now();
        long long rr_std_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        start = std::chrono::system_clock::now();
        repeated_random(numbers, true);
        end = std::chrono::system_clock::now();
        long long rr_prep_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::system_clock::now();
        hill_climbing(numbers, false);
        end = std::chrono::system_clock::now();
        long long hc_std_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::system_clock::now();
        hill_climbing(numbers, true);
        end = std::chrono::system_clock::now();
        long long hc_prep_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::system_clock::now();
        simulated_annealing(numbers, false);
        end = std::chrono::system_clock::now();
        long long sa_std_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::system_clock::now();
        simulated_annealing(numbers, true);
        end = std::chrono::system_clock::now();
        long long sa_prep_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // long long kk_result = karmarkar_karp(numbers);
        // long long rr_std = repeated_random(numbers, false);
        // long long rr_prep = repeated_random(numbers, true);
        // long long hc_std = hill_climbing(numbers, false);
        // long long hc_prep = hill_climbing(numbers, true);
        // long long sa_std = simulated_annealing(numbers, false);
        // long long sa_prep = simulated_annealing(numbers, true);

        outfile << i + 1 << ',' << kk_time << ',' << rr_std_time << ',' << rr_prep_time << ','
                << hc_std_time<< ',' << hc_prep_time << ',' << sa_std_time << ',' << sa_prep_time << '\n';
    }

    outfile.close();
    return 0;
}
