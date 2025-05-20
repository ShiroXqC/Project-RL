#include "UI.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <sstream>
using namespace std;

// Helper function to determine zone name based on floor
string getFloorZoneName(int floor) {
    if (floor <= 1) return "Astre Depths";
    if (floor == 2) return "Forgotten Crypt";
    if (floor == 3) return "Blazing Catacombs";
    if (floor >= 4) return "Abyss";
    return "Unknown Realm";
}

void UI::drawMainUI(const Map& map) {
    const Player& player = *map.getPlayer();

    int floor = map.getFloor();
    string zoneName = getFloorZoneName(floor);

    // === Header Row ===
    cout << "+-------------------+       +-----------------------+         +-----------------+\n";
    cout << "|      MENU         |       |        INFO           |         |   CHARACTER     |\n";
    cout << "|-------------------|       |-----------------------|         |-----------------|\n";

    // === Content Rows (Aligning 3 panels) ===
    cout << "| Traverse Dungeon  |       |                       |         | NAME: " << player.getSymbol() << "         |\n";
    cout << "| [i]Inventory      |       |                       |         | HP: " << player.getHp() << "/" << player.getMaxHealth() << "       |\n";

    // Floor number centered
    ostringstream floorLine;
    floorLine << "Floor: " << floor << "/4";
    int floorPad = (23 - floorLine.str().length()) / 2;

    cout << "| [c]Character Sheet|       |"
         << string(floorPad, ' ') << floorLine.str()
         << string(23 - floorLine.str().length() - floorPad, ' ') << "|         | LEVEL: " << player.getLevel() << "        |\n";

    // Zone name centered
    int zonePad = (23 - zoneName.length()) / 2;
    cout << "| [p]Shop           |       |"
         << string(zonePad, ' ') << zoneName
         << string(23 - zoneName.length() - zonePad, ' ') << "|         | CURR XP: " << player.getXP() << "      |\n";

    cout << "|-----------------  |       |                       |         | REQ. XP: " << player.getXPToNextLevel() << "    |\n";
    cout << "| Back to Main Menu |       |                       |         | DEF: " << player.getDefense() << "          |\n";
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

    const int combatWidth = 36;
    const int charWidth = 23;
    const std::string gap = "               "; // wider spacing between panels

    std::cout << "+------------------------------------+" << gap << "+-----------------------+\n";
    std::cout << "|           COMBAT LOG               |" << gap << "|       CHARACTER       |\n";
    std::cout << "|------------------------------------|" << gap << "|-----------------------|\n";

    for (int i = 0; i < 8; ++i) {
        // Left: Combat log
        std::cout << "| ";
        if (i < combatLog.size()) {
            std::cout << std::setw(combatWidth - 2) << std::left << combatLog[i];
        } else {
            std::cout << std::setw(combatWidth - 2) << " ";
        }
        std::cout << " |" << gap;

        // Right: Character info
        std::cout << "| ";
        switch (i) {
            case 0: std::cout << std::setw(charWidth) << std::left << ("NAME: " + std::string(1, player.getSymbol())); break;
            case 1: std::cout << std::setw(charWidth) << std::left << ("HP: " + std::to_string(player.getHp()) + "/" + std::to_string(player.getMaxHealth())); break;
            case 2: std::cout << std::setw(charWidth) << std::left << ("LEVEL: " + std::to_string(player.getLevel())); break;
            case 3: std::cout << std::setw(charWidth) << std::left << ("CURR XP: " + std::to_string(player.getXP())); break;
            case 4: std::cout << std::setw(charWidth) << std::left << ("REQ. XP: " + std::to_string(player.getXPToNextLevel())); break;
            case 5: std::cout << std::setw(charWidth) << std::left << ("DEF: " + std::to_string(player.getDefense())); break;
            case 6: std::cout << std::setw(charWidth) << std::left << ("BLK: " + std::to_string(player.getBlock())); break;
            case 7: std::cout << std::setw(charWidth) << std::left << ("GOLD: " + std::to_string(player.getGold())); break;
            default: std::cout << std::setw(charWidth) << " "; break;
        }
        std::cout << " |\n";
    }

    std::cout << "+------------------------------------+" << gap << "+-----------------------+\n";
}