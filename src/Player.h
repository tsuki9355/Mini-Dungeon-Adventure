#pragma once
#include <map>
#include <string>
#include <vector>

#include "Character.h"
#include "Item.h"

struct Player : Character {
    int level = 1;
    int xp = 0;
    int gold = 20;
    int monstersDefeated = 0;
    int roomsExplored = 0;
    std::vector<Item> inventory;

    Player();

    int xpToNextLevel() const { return level * 50; }

    // Adds XP and levels up as many times as the XP allows.
    void gainXp(int amount);

    void addItem(const Item& item);

    // Uses one item with this name. Returns false if the player has none.
    bool useItem(const std::string& itemName);

    // Item name -> how many the player carries, sorted A to Z.
    std::map<std::string, int> inventoryCounts() const;

    int score() const;
    void showStats() const;

private:
    void levelUp();
};
