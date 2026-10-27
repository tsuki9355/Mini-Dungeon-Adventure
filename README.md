# Mini Dungeon: Descent into the Hollow Crypt

A small text-based dungeon adventure written in C++. Explore rooms, fight monsters,
collect gold, level up, and see how deep you can go before the crypt takes you.

Sample Gameplay Screenshots:

<img width="565" height="1012" alt="Sample" src="https://github.com/user-attachments/assets/4fb42cb9-dca0-46e2-a349-6665ada1e662" />

## The Story

Beneath the quiet village of **Emberfall** lies the **Hollow Crypt**, an ancient
maze of tombs that grows a little deeper every night. Nobody knows who built it.
The villagers only know that monsters crawl out of it after dark, and that the
gold of forgotten kings still glitters in its halls.

You are a young adventurer who has volunteered to go down. Your goal is simple:
go as deep as you dare, bring back as much treasure as you can, and come out
alive.

You are not completely alone. **Mira**, a ghostly merchant who died in the crypt
long ago, still drifts through its walls. She will happily trade potions for your
gold. Nobody knows what a ghost wants with gold.

## How to Play

You start with **100 HP**, **20 gold**, and **one Small Potion**.

Each time you explore, you enter a new room. Something random happens:

| Event        | Chance | What happens                       |
|--------------|--------|------------------------------------|
| Monster      | 65%    | A fight begins                     |
| Treasure     | 20%    | You find gold                      |
| Lost potion  | 10%    | You find a Small Potion            |
| Shrine       | 5%     | You recover some health            |

Defeating monsters gives you **gold** and **XP**. Earn enough XP and you **level up**:
more health, attack and defense, plus a full heal. Deeper levels bring tougher
monsters, so spend your gold wisely.

The run ends when your health reaches **0**, or when you choose to leave the
dungeon. Your score is saved to the **Hall of Heroes** (top 5).

**Score** = gold + 20 per monster defeated + 5 per room explored + 50 per level gained

## Controls

Type a number and press **Enter**.

**In the dungeon**

```
1. Explore deeper      - enter the next room
2. Open bag            - use a potion or item
3. Visit the merchant  - buy items from Mira
4. View stats          - see your level, attack, score, etc.
5. Leave the dungeon   - end the run and save your score
```

**In battle**

```
1. Attack     - deal damage to the monster
2. Defend     - take half damage this turn
3. Use Item   - use something from your bag (backing out does not cost a turn)
4. Run Away   - 50% chance to escape
```

## Monsters

| Monster        | Appears from level |
|----------------|--------------------|
| Giant Rat      | 1                  |
| Skeleton       | 1                  |
| Goblin Thief   | 2                  |
| Cave Troll     | 3                  |
| Shadow Wraith  | 4                  |

## Building and Running

You need a C++17 compiler. On Windows, install Visual Studio with the
**"Desktop development with C++"** workload.

**VS Code (easiest):** press **F5**, or open the Run and Debug panel and pick
**"Play Mini Dungeon"**. It builds all the files and starts the game in the
terminal at the bottom of VS Code. You can set breakpoints too.

> Don't use "C/C++: cl.exe build and debug active file". That only compiles the
> one file you have open, and this game is split across several files.

**From a terminal (Windows):**

```bash
build.bat
```

```bash
build\dungeon.exe
```

**With g++ instead (MinGW / Linux / macOS):**

```bash
g++ -std=c++17 -Wall src/*.cpp -o build/dungeon
```

## Project Structure

```
src/
  main.cpp         Starts the game
  Game.h/.cpp      Game loop, menus, exploring, combat, merchant
  Character.h      Shared stats for anything that fights (health, attack, defense)
  Player.h/.cpp    The player: leveling, inventory, score
  Monster.h/.cpp   Monster list and random monster spawning
  Item.h           Item list (potions, tonics) and what they do
  HighScores.h/.cpp Saving and loading the top 5 scores
  Utils.h/.cpp     Random numbers and safe keyboard input
```

### C++ concepts used

| Concept               | Where                                                        |
|-----------------------|--------------------------------------------------------------|
| struct / class        | `Character`, `Player`, `Monster`, `Item`, `Game`             |
| Inheritance           | `Player` and `Monster` both extend `Character`               |
| enum class + switch   | `ItemType` in `Player::useItem()`, menu choices              |
| while loops           | Main game loop, battle loop, input validation                |
| std::vector           | Inventory, monster list, item list, high scores              |
| std::map              | Grouping the bag into "Small Potion x2" (sorted by name)     |
| Searching             | `std::find_if` to find an item in the inventory              |
| Sorting               | `std::sort` to rank high scores                              |
| Weighted random       | `spawnMonster()` picks common monsters more often            |
| File I/O              | `highscores.txt` with `std::ifstream` / `std::ofstream`      |
| Lambdas               | Sort comparison, item search, stat scaling                   |

## Adding Your Own Features

The game is built so most new content is **one line of data**:

- **New monster:** add a line to `MONSTER_TYPES` in `src/Monster.h`.
- **New shop item:** add a line to `ITEM_CATALOG` in `src/Item.h`.
- **New kind of item** (e.g. a defense potion): add a value to `ItemType` in `src/Item.h`,
  then add a `case` for it in `Player::useItem()` and `describeItem()`.
- **New room event** (e.g. a trap): add another `else if` in `Game::exploreRoom()`.
- **New battle action** (e.g. a special attack): add a menu line and a `case` in `Game::fight()`.

Ideas to try next: a boss every 10 rooms, critical hits, armor you can equip,
or saving and loading your run.



