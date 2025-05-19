#include "UI.h"
#include <iostream>
#include <iomanip>
using namespace std;

void UI::drawMainUI(const Map& map) {
    const Player& player = *map.getPlayer();

    // === Header Row ===
    cout << "+-------------------+       +-----------------------+         +-----------------+\n";
    cout << "|      MENU         |       |        INFO           |         |   CHARACTER     |\n";
    cout << "|-------------------|       |-----------------------|         |-----------------|\n";

    // === Content Rows (Aligning 3 panels) ===
    cout << "| Traverse Dungeon  |       |                       |         | NAME: " << player.getSymbol() << "         |\n";
    cout << "| [i]Inventory      |       |                       |         | HP: " << player.getHp() << "/" << player.getMaxHealth() << "       |\n";
    cout << "| [c]Character Sheet|       |      Floor: 1/4       |         | LEVEL: " << player.getLevel() << "        |\n";
    cout << "| [p]Shop           |       |     Astre Depths      |         | CURR XP: " << player.getXP() << "      |\n";
    cout << "|-----------------  |       |                       |         | REQ. XP: " << player.getXPToNextLevel() << "    |\n";
    cout << "| Back to Main Menu |       |                       |         | DEF: " << player.getDefense() << "          |\n";
    cout << "|                   |       |                       |         | BLK: " << player.getBlock() << "          |\n";
    cout << "|                   |       |                       |         | GOLD: " << player.getGold() << "         |\n";
    cout << "+-------------------+       +-----------------------+         +-----------------+\n";

    // === MAP Header and Rendering ===
    cout << "+----------------------+\n";
    cout << "|         MAP          |\n";
    cout << "|----------------------|\n";

    for (int y = 0; y < map.getHeight(); ++y) {
        cout << "| ";
        for (int x = 0; x < map.getWidth(); ++x) {
            if (player.getX() == x && player.getY() == y) {
                cout << '@';  // Player
            } else {
                cout << map.getTile(x, y);  // Enemy (!), item, or space
            }
        }
        cout << " |\n";
    }

    cout << "| @ = You, ! = Enemy   |\n";
    cout << "+----------------------+\n";
    cout << "Controls: [W]Up [A]Left [S]Down [D]Right [Space]Wait [I]Inventory [Q]Quit\n";
}

void UI::drawCombatUI(const Player& player, const std::vector<std::string>& combatLog) {
    system("cls"); // Clear screen

    cout << "+------------------------+       +-----------------+\n";
    cout << "|      COMBAT LOG        |       |   CHARACTER     |\n";
    cout << "|------------------------|       |-----------------+\n";

    for (size_t i = 0; i < std::max(combatLog.size(), size_t(8)); ++i) {
        // Left: Combat log line
        cout << "| ";
        if (i < combatLog.size()) {
            cout << std::setw(22) << std::left << combatLog[i];
        } else {
            cout << std::setw(22) << "";
        }
        cout << " |       ";

        // Right: Character info line
        switch (i) {
            case 0: cout << "| NAME: " << player.getSymbol(); break;
            case 1: cout << "| HP: " << player.getHp() << "/" << player.getMaxHealth(); break;
            case 2: cout << "| LEVEL: " << player.getLevel(); break;
            case 3: cout << "| CURR XP: " << player.getXP(); break;
            case 4: cout << "| REQ. XP: " << player.getXPToNextLevel(); break;
            case 5: cout << "| DEF: " << player.getDefense(); break;
            case 6: cout << "| BLK: " << player.getBlock(); break;
            case 7: cout << "| GOLD: " << player.getGold(); break;
            default: cout << "|"; break;
        }
        cout << "\n";
    }

    cout << "+------------------------+       +-----------------+\n";
}
