#include <iostream>
#include <fstream>
#include <random>
#include <cstdint>

int main() {
    // File to write the integers
    std::ofstream file("random_integers.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    // Random number generator setup
    std::random_device rd;  // Seed for the random number engine
    std::mt19937_64 rng(rd());  // Use Mersenne Twister engine for 64-bit integers
    std::uniform_int_distribution<std::uint64_t> dist(1, 1000000000000); // Uniform distribution between 1 and 10^12

    // Generate and write 100 random integers
    for (int i = 0; i < 100; ++i) {
        std::uint64_t number = dist(rng);
        file << number << std::endl;
    }

    file.close();
    std::cout << "Generated file with 100 random integers." << std::endl;

    return 0;
}
