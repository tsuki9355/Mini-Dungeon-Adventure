#pragma once
#include <string>
#include <vector>

struct ScoreEntry {
    std::string name;
    int score;
};

// Reads saved scores from highscores.txt (empty list if the file is missing).
std::vector<ScoreEntry> loadHighScores();

// Adds a score, sorts the list from best to worst, keeps the top 5 and saves it.
void saveHighScore(const ScoreEntry& entry);

void showHighScores();
