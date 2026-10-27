#pragma once
#include <string>

// Small helpers used all over the game: random numbers and keyboard input.
namespace utils {

// Random whole number between min and max (both included).
int randomInt(int min, int max);

// Returns true `percent`% of the time. chance(25) is true about 1 in 4 times.
bool chance(int percent);

// Keeps asking until the player types a number between min and max.
int readChoice(int min, int max);

// Shows a prompt and returns the whole line the player typed.
std::string readLine(const std::string& prompt);

// Text health bar, e.g. [######----]
std::string healthBar(int current, int max, int width = 10);

}  // namespace utils
