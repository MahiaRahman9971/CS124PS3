// #include <fstream>

// int main() {
//     const int num_instances = 50;
//     const int instance_size = 100;  // Adjust size as needed
//     const long long max_value = 1e6;  // Adjust maximum value as needed
//     std::ofstream outfile("results.csv");

//     // Write headers for CSV output
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

//         // Output results to CSV
//         outfile << i + 1 << ',' << kk_result << ',' << rr_std << ',' << rr_prep << ','
//                 << hc_std << ',' << hc_prep << ',' << sa_std << ',' << sa_prep << '\n';
//     }

//     outfile.close();
//     return 0;
// }
