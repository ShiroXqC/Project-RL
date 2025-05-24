#include "UI.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <sstream>


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
    cout << "|      MENU         |       |         INFO          |         |   CHARACTER     |\n";
    cout << "|-------------------|       |-----------------------|         |-----------------|\n";

    // === Content Rows (Aligning 3 panels) ===
    cout << "| Traverse Dungeon  |       |                       |         | NAME: " << player.getSymbol() << "         |\n";
    cout << "| [i]Inventory      |       |                       |         | HP: " << player.getHp() << "/" << player.getMaxHealth() << "       |\n";

    // Floor number centered
    ostringstream floorLine;
    floorLine << "Floor: " << floor << "/4";
    int floorPad = (23 - floorLine.str().length()) / 2;

    cout << "| [p]Shop           |       |"
         << string(floorPad, ' ') << floorLine.str()
         << string(23 - floorLine.str().length() - floorPad, ' ')
         << "|         | LEVEL: " << player.getLevel() << "        |\n";

    // Zone name centered
    int zonePad = (23 - zoneName.length()) / 2;
    cout << "|------------------ |       |"
         << string(zonePad, ' ') << zoneName
         << string(23 - zoneName.length() - zonePad, ' ') << "|         | ATK: " << player.getAttackpower() << "          |\n";

    cout << "| Back to Main Menu |       |                       |         | DEF: " << player.getDefense() << "          |\n";
    cout << "|                   |       |                       |         | GOLD: " << player.getGold() << "        |\n";
    cout << "+-------------------+       +-----------------------+         | XP: " << player.getXP() << " | " << player.getXPToNextLevel() << "     |\n";
    cout << "                                                              +-----------------+\n";

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

    cout << "| @ = You              |\n";
    cout << "+----------------------+\n";
    cout << "Controls: [w]Up [a]Left [s]Down [d]Right [q]Quit\n";
}

void UI::drawCombatUI(const Player& player, const vector<string>& combatLog,  const vector<string>& battleHistory) {
    system("cls"); // Clear screen

    const int combatWidth = 36;
    const int charWidth = 21;
    const int histWidth = 38;
    const string gap = "               "; // wider spacing between panels

    cout << "+------------------------------------+" << gap << "+-----------------------+\n";
    cout << "|           COMBAT LOG               |" << gap << "|       CHARACTER       |\n";
    cout << "|------------------------------------|" << gap << "|-----------------------|\n";

    for (int i = 0; i < 8; ++i) {
        // Left: Combat log
        cout << "| ";
        if (i < combatLog.size()) {
            cout << setw(combatWidth - 2) << left << combatLog[i];
        } else {
            cout << setw(combatWidth - 2) << " ";
        }
        cout << " |" << gap;

        // Right: Character info
        cout << "| ";
        switch (i) {
            case 0: cout << setw(charWidth) << left << ("NAME: " + string(1, player.getSymbol())); 
                    break;
            case 1: cout << setw(charWidth) << left << ("HP: " + to_string(player.getHp()) + "/" + to_string(player.getMaxHealth())); 
                    break;
            case 2: cout << setw(charWidth) << left << ("ATK: " + to_string(player.getAttackpower())); 
                    break;
            case 3: cout << setw(charWidth) << left << ("DEF: " + to_string(player.getDefense())); 
                    break;
            case 4: cout << setw(charWidth) << left << ("GOLD: " + to_string(player.getGold())); 
                    break;
            case 5: cout << setw(charWidth) << left << ("LEVEL: " + to_string(player.getLevel())); 
                    break;
            case 6: cout << setw(charWidth) << left << ("XP: " + to_string(player.getXP()) + "/" + to_string(player.getXPToNextLevel())); 
                    break;
            default:cout << setw(charWidth) << " "; 
                    break;
        }
        cout << " |\n";
    }
    cout << "+------------------------------------+" << gap << "+-----------------------+\n";
         // Battle History section
    cout << "+----------------------- BATTLE HISTORY ------------------------+\n";
    int linesToShow = min(static_cast<int>(battleHistory.size()), 20);
    for (int i = static_cast<int>(battleHistory.size()) - linesToShow; i < battleHistory.size(); ++i) {
        cout << "-----------------------------#"<<i<<"---------------------------------\n";
        cout << "| " << setw(histWidth - 2) << left << battleHistory[i] << " |\n";
    }
    cout << "+---------------------------------------------------------------+\n";
    cout<<"\n";
}
