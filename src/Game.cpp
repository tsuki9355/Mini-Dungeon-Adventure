#include "Game.h"

#include <iostream>
#include <string>
#include <vector>

#include "HighScores.h"
#include "Utils.h"

using std::cout;

void Game::run() {
    showIntro();

    std::string name = utils::readLine("What is your name, adventurer? ");
    if (!name.empty()) {
        player.name = name;
    }
    cout << "\nGood luck, " << player.name << ". The Hollow Crypt awaits.\n";

    while (running && player.isAlive()) {
        mainMenu();
    }
    endGame();
}

void Game::showIntro() {
    cout << "=====================================\n"
         << "          MINI DUNGEON\n"
         << "    Descent into the Hollow Crypt\n"
         << "=====================================\n\n"
         << "Beneath the village of Emberfall lies the Hollow Crypt, a maze\n"
         << "of tombs that grows deeper every night. Monsters crawl out of it\n"
         << "and gold glitters in its halls. Many have gone down. Few return.\n\n";
}

void Game::showHud() const {
    cout << "\nHealth: " << player.health << "/" << player.maxHealth << " "
         << utils::healthBar(player.health, player.maxHealth)
         << " | Gold: " << player.gold
         << " | Level: " << player.level
         << " | Room: " << player.roomsExplored << "\n";
}

void Game::mainMenu() {
    showHud();
    cout << "What will you do?\n"
         << "1. Explore deeper\n"
         << "2. Open bag\n"
         << "3. Visit the merchant\n"
         << "4. View stats\n"
         << "5. Leave the dungeon (end run)\n";

    switch (utils::readChoice(1, 5)) {
        case 1: exploreRoom();       break;
        case 2: openBag();           break;
        case 3: visitMerchant();     break;
        case 4: player.showStats();  break;
        case 5: running = false;     break;
    }
}

// Exploring: each room rolls a random event. Add new events here.
void Game::exploreRoom() {
    player.roomsExplored++;
    cout << "\nYou enter room " << player.roomsExplored << " of the crypt...\n";

    int roll = utils::randomInt(1, 100);
    if (roll <= 65) {
        fight(spawnMonster(player.level));
    } else if (roll <= 85) {
        int gold = utils::randomInt(5, 15) * player.level;
        player.gold += gold;
        cout << "You find a dusty chest with " << gold << " gold inside!\n";
    } else if (roll <= 95) {
        player.addItem(ITEM_CATALOG[0]);
        cout << "You find a Small Potion tucked behind a coffin.\n";
    } else {
        int healed = player.heal(30);
        cout << "A quiet shrine glows softly. You rest and recover " << healed << " HP.\n";
    }
}

// Combat
void Game::fight(Monster monster) {
    cout << "A wild " << monster.name << " appears!\n";

    while (player.isAlive() && monster.isAlive()) {
        cout << "\n" << player.name << ": " << player.health << "/" << player.maxHealth << " "
             << utils::healthBar(player.health, player.maxHealth) << "\n"
             << monster.name << ": " << monster.health << "/" << monster.maxHealth << " "
             << utils::healthBar(monster.health, monster.maxHealth) << "\n\n"
             << "1. Attack\n"
             << "2. Defend\n"
             << "3. Use Item\n"
             << "4. Run Away\n";

        bool defending = false;

        switch (utils::readChoice(1, 4)) {
            case 1: {
                int roll = utils::randomInt(player.attack - 2, player.attack + 2);
                int damage = monster.takeDamage(roll);
                cout << "You hit the " << monster.name << " for " << damage << " damage.\n";
                break;
            }
            case 2:
                defending = true;
                cout << "You raise your guard.\n";
                break;
            case 3:
                if (!openBag()) {
                    continue;
                }
                break;
            case 4:
                if (utils::chance(50)) {
                    cout << "You escape back into the shadows!\n";
                    return;
                }
                cout << "You try to flee, but the " << monster.name << " blocks your path!\n";
                break;
        }

        if (monster.isAlive()) {
            monsterTurn(monster, defending);
        }
    }

    if (player.isAlive()) {
        winFight(monster);
    }
}

void Game::monsterTurn(Monster& monster, bool playerDefending) {
    int roll = utils::randomInt(monster.attack - 2, monster.attack + 2);
    if (playerDefending) {
        roll /= 2;
    }
    int damage = player.takeDamage(roll);
    cout << "The " << monster.name << " strikes you for " << damage << " damage.\n";
}

void Game::winFight(const Monster& monster) {
    player.monstersDefeated++;
    player.gold += monster.goldReward;
    cout << "\nYou defeated the " << monster.name << "!\n"
         << "You loot " << monster.goldReward << " gold.\n";
    player.gainXp(monster.xpReward);
}

// Bag and merchant
bool Game::openBag() {
    auto counts = player.inventoryCounts();
    if (counts.empty()) {
        cout << "Your bag is empty.\n";
        return false;
    }

    // Number each item type so the player can pick one.
    cout << "\n--- Bag ---\n";
    std::vector<std::string> names;
    for (const auto& [name, count] : counts) {
        names.push_back(name);
        cout << names.size() << ". " << name << " x" << count << "\n";
    }
    int back = static_cast<int>(names.size()) + 1;
    cout << back << ". Close bag\n";

    int choice = utils::readChoice(1, back);
    if (choice == back) {
        return false;
    }
    return player.useItem(names[choice - 1]);
}

void Game::visitMerchant() {
    cout << "\nMira, a ghostly merchant, drifts out of the wall.\n"
         << "\"Coins for comfort, traveler?\"\n";

    while (true) {
        cout << "\nYour gold: " << player.gold << "\n";
        for (size_t i = 0; i < ITEM_CATALOG.size(); ++i) {
            const Item& item = ITEM_CATALOG[i];
            cout << i + 1 << ". " << item.name << " (" << describeItem(item) << ") - "
                 << item.price << " gold\n";
        }
        int back = static_cast<int>(ITEM_CATALOG.size()) + 1;
        cout << back << ". Leave\n";

        int choice = utils::readChoice(1, back);
        if (choice == back) {
            cout << "Mira fades back into the stone.\n";
            return;
        }

        const Item& item = ITEM_CATALOG[choice - 1];
        if (player.gold < item.price) {
            cout << "\"You cannot afford that, traveler.\"\n";
        } else {
            player.gold -= item.price;
            player.addItem(item);
            cout << "You bought a " << item.name << ".\n";
        }
    }
}

// Ending
void Game::endGame() {
    if (player.isAlive()) {
        cout << "\nYou climb back into the moonlight with your treasure.\n";
    } else {
        cout << "\nYour vision fades... The Hollow Crypt claims another soul.\n";
    }

    player.showStats();
    saveHighScore({player.name, player.score()});
    showHighScores();

    utils::readLine("\nPress Enter to exit...");
}
