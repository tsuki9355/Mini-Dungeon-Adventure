#include "Utils.h"

#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>

namespace utils {

// One random engine for the whole program, seeded once on first use.
static std::mt19937& rng() {
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}

int randomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng());
}

bool chance(int percent) {
    return randomInt(1, 100) <= percent;
}

int readChoice(int min, int max) {
    while (true) {
        std::cout << "Enter your choice: ";

        std::string line;
        if (!std::getline(std::cin, line)) {
            std::exit(0);  // input was closed, nothing more to read
        }

        // Accept the line only if it is exactly one number in range.
        std::istringstream in(line);
        int choice;
        char extra;
        if (in >> choice && !(in >> extra) && choice >= min && choice <= max) {
            return choice;
        }
        std::cout << "Please enter a number from " << min << " to " << max << ".\n";
    }
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::string healthBar(int current, int max, int width) {
    int filled = (max > 0) ? current * width / max : 0;
    return "[" + std::string(filled, '#') + std::string(width - filled, '-') + "]";
}

}  // namespace utils
