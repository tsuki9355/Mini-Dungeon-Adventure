#pragma once
#include "Monster.h"
#include "Player.h"

class Game {
public:
    void run();

private:
    Player player;
    bool running = true;

    // Screens and menus
    void showIntro();
    void showHud() const;
    void mainMenu();
    void visitMerchant();
    bool openBag();  // returns true if an item was used

    // Dungeon events
    void exploreRoom();
    void fight(Monster monster);
    void monsterTurn(Monster& monster, bool playerDefending);
    void winFight(const Monster& monster);

    void endGame();
};
