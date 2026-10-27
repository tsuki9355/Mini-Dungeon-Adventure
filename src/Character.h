#pragma once
#include <algorithm>
#include <string>

// Stats shared by everything that can fight: the player and every monster.
struct Character {
    std::string name;
    int health = 0;
    int maxHealth = 0;
    int attack = 0;
    int defense = 0;

    bool isAlive() const { return health > 0; }

    // Defense blocks part of the hit, but every hit does at least 1 damage.
    // Returns the damage actually taken.
    int takeDamage(int amount) {
        int damage = std::max(1, amount - defense);
        health = std::max(0, health - damage);
        return damage;
    }

    // Health can never go above maxHealth. Returns how much was healed.
    int heal(int amount) {
        int before = health;
        health = std::min(maxHealth, health + amount);
        return health - before;
    }
};
