#include "HighScores.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace {
const std::string SCORE_FILE = "highscores.txt";
const size_t MAX_SCORES = 5;
}  // namespace

std::vector<ScoreEntry> loadHighScores() {
    std::vector<ScoreEntry> scores;
    std::ifstream file(SCORE_FILE);

    // Each line looks like: "<score> <name>"
    ScoreEntry entry;
    while (file >> entry.score) {
        file.ignore();  // skip the space between score and name
        std::getline(file, entry.name);
        scores.push_back(entry);
    }
    return scores;
}

void saveHighScore(const ScoreEntry& entry) {
    std::vector<ScoreEntry> scores = loadHighScores();
    scores.push_back(entry);

    // Sort from highest to lowest score.
    std::sort(scores.begin(), scores.end(),
              [](const ScoreEntry& a, const ScoreEntry& b) { return a.score > b.score; });

    if (scores.size() > MAX_SCORES) {
        scores.resize(MAX_SCORES);
    }

    std::ofstream file(SCORE_FILE);
    for (const ScoreEntry& s : scores) {
        file << s.score << ' ' << s.name << '\n';
    }
}

void showHighScores() {
    std::vector<ScoreEntry> scores = loadHighScores();

    std::cout << "\n=== HALL OF HEROES ===\n";
    if (scores.empty()) {
        std::cout << "No heroes yet. Be the first!\n";
        return;
    }
    for (size_t i = 0; i < scores.size(); ++i) {
        std::cout << i + 1 << ". " << scores[i].name << " - " << scores[i].score << "\n";
    }
}
