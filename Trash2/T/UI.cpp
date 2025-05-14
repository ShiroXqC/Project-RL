#include "UI.h"
#include <iostream>

void UI::drawMainUI(const Map& map) {
    const Player& player = *map.getPlayer();

    std::cout << "+-----------------+       +-----------------------+\n";
    std::cout << "|      MENU       |       |        INFO          |\n";
    std::cout << "|-----------------|       |-----------------------|\n";
    std::cout << "| Traverse Dungeon|\n";
    std::cout << "| Inventory       |\n";
    std::cout << "| Character Sheet |\n";
    std::cout << "| Shop            |\n";
    std::cout << "|-----------------|\n";
    std::cout << "| Back to Main Menu           Astre Depths\n";
    std::cout << "|                           Floor: 1/4           |\n";
    std::cout << "+-----------------+       +-----------------------+\n";

    std::cout << "\n";

    std::cout << "+-----------------+       +-----------------------+\n";
    std::cout << "|   CHARACTER     |       |         MAP           |\n";
    std::cout << "|-----------------|       |-----------------------|\n";
    std::cout << "| NAME: " << player.getSymbol() << "\n";
    std::cout << "| HP: " << player.getHp() << "/" << player.getMaxHealth() << "\n";
    std::cout << "| LEVEL: " << player.getLevel() << "\n";
    std::cout << "| CURR XP: " << player.getXP() << "\n";
    std::cout << "| REQ. XP: " << player.getXPToNextLevel() << "\n";
    std::cout << "| DEF: " << player.getDefense() << "\n";
    std::cout << "| BLK: " << player.getBlock() << "\n";
    std::cout << "| ATK: " << player.getMinAtk() << "-" << player.getMaxAtk() << "\n";
    std::cout << "| GOLD: " << player.getGold() << "\n";

    std::cout << "|\n+-----------------+       +-----------------------+\n";
    std::cout << "                          |                       |\n";

    // === MAP RENDERING ===
    for (int y = 0; y < map.getHeight(); ++y) {
        std::cout << "                          | ";
        for (int x = 0; x < map.getWidth(); ++x) {
            if (player.getX() == x && player.getY() == y) {
                std::cout << '@';  // Player
            } else {
                std::cout << map.getTile(x, y);  // Enemy (!), item, or space
            }
        }
        std::cout << " |\n";
    }

    std::cout << "                          | @ = You, ! = Enemy    |\n";
    std::cout << "                          +-----------------------+\n";
}
