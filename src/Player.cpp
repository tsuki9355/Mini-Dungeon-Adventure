#include "Player.h"

#include <algorithm>
#include <iostream>

#include "Utils.h"

Player::Player() {
    name = "Adventurer";
    maxHealth = 100;
    health = maxHealth;
    attack = 12;
    defense = 2;
    addItem(ITEM_CATALOG[0]);  // start with one Small Potion
}

void Player::gainXp(int amount) {
    xp += amount;
    std::cout << "You gain " << amount << " XP.\n";

    while (xp >= xpToNextLevel()) {
        xp -= xpToNextLevel();
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    maxHealth += 15;
    attack += 3;
    defense += 1;
    health = maxHealth;  // full heal as a reward

    std::cout << "*** LEVEL UP! You are now level " << level << ". ***\n"
              << "Max HP +15, Attack +3, Defense +1. Your wounds close.\n";
}

void Player::addItem(const Item& item) {
    inventory.push_back(item);
}

bool Player::useItem(const std::string& itemName) {
    // Linear search for the first item with a matching name.
    auto it = std::find_if(inventory.begin(), inventory.end(),
                           [&](const Item& item) { return item.name == itemName; });
    if (it == inventory.end()) {
        return false;
    }

    switch (it->type) {
        case ItemType::Heal: {
            int healed = heal(it->power);
            std::cout << "You drink the " << it->name << " and recover " << healed << " HP.\n";
            break;
        }
        case ItemType::Strength:
            attack += it->power;
            std::cout << "Power surges through you! Attack +" << it->power << ".\n";
            break;
    }

    inventory.erase(it);
    return true;
}

std::map<std::string, int> Player::inventoryCounts() const {
    std::map<std::string, int> counts;  // std::map keeps keys sorted for us
    for (const Item& item : inventory) {
        counts[item.name]++;
    }
    return counts;
}

int Player::score() const {
    return gold + monstersDefeated * 20 + roomsExplored * 5 + (level - 1) * 50;
}

void Player::showStats() const {
    std::cout << "\n--- " << name << " ---\n"
              << "Level:    " << level << "  (XP " << xp << "/" << xpToNextLevel() << ")\n"
              << "Health:   " << health << "/" << maxHealth << " "
              << utils::healthBar(health, maxHealth) << "\n"
              << "Attack:   " << attack << "\n"
              << "Defense:  " << defense << "\n"
              << "Gold:     " << gold << "\n"
              << "Rooms:    " << roomsExplored << "\n"
              << "Monsters: " << monstersDefeated << " defeated\n"
              << "Score:    " << score() << "\n";
}
