#include "partition.hh"

int main() {
    // Set up random number generation
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<long long> dist(1, 1000000000000LL); // Range from 1 to 10^12

    // Specify the number of files and numbers per file
    int num_files = 50; // Number of files to generate
    int numbers_per_file = 100; // Numbers per file

    for (int file_num = 1; file_num <= num_files; ++file_num) {
        // Create a filename for each file
        std::string filename = "input" + std::to_string(file_num) + ".txt";
        std::ofstream outfile(filename);

        if (!outfile.is_open()) {
            std::cerr << "Failed to open " << filename << std::endl;
            return -1;
        }

        // Generate and write numbers to the file
        for (int i = 0; i < numbers_per_file; ++i) {
            long long number = dist(rng);
            outfile << number << std::endl;
        }

        outfile.close();
        std::cout << "Generated file: " << filename << std::endl;
    }

    std::cout << "All files have been generated successfully." << std::endl;

    return 0;
}
