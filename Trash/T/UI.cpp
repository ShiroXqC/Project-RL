#include "UI.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <sstream>

// Zone's name
string getFloorZoneName(int floor) {
    if (floor <= 1) 
        return "Astre Depths";
    else if (floor == 2) 
        return "Forgotten Crypt";
    else if (floor == 3) 
        return "Blazing Catacombs";
    else if (floor >= 4) 
        return "Abyss";
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

    cout << "| [p]Shop           |       |" << string(floorPad, ' ') << floorLine.str()
         << string(23 - floorLine.str().length() - floorPad, ' ') << "|         | LEVEL: " << player.getLevel() << "        |\n";

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

void UI::drawCombatUI(const Player& player, const vector<string>& combatLog, const vector<string>& battleHistory, const Enemy* enemy) {
    system("cls");

    const int combatWidth = 36;
    const int charWidth = 21;
    const int histWidth = 38;
    const int asciiWidth = 40;
    const string gap = "               ";

    vector<string> dragonArt = {
        "                 \\||/",
        "                 |  @___oo",
        "      /\\  /\\   / (__,,,,|",
        "     ) /^\\) ^\\/  _)",
        "     )   /^\\/    _)",
        "     )   _ /  /  _)",
        " /\\  ) /\\/ ||  | )_)",
        "<  >      |(,,) )__)",
        " ||      /    \\)___)\\",
        " | \\____(      )___) )___",
        "  \\______(_______;;; __;;;"
    };

    bool isFinalBoss = enemy && (enemy->getType() == "Dragon" || enemy->getType() == "Final Boss");

    cout << "+------------------------------------+" << gap << "+-----------------------+";
    if (isFinalBoss) cout << gap << "+----------------------------------------+";
    cout << "\n";

    cout << "|           COMBAT LOG               |" << gap << "|       CHARACTER       |";
    if (isFinalBoss) cout << gap << "|                FINAL BOSS              |";
    cout << "\n";

    cout << "|------------------------------------|" << gap << "|-----------------------|";
    if (isFinalBoss) cout << gap << "|----------------------------------------|";
    cout << "\n";

    for (int i = 0; i < 11; ++i) {
        cout << "| ";
        if (i < combatLog.size()) cout << setw(combatWidth - 2) << left << combatLog[i];
        else cout << setw(combatWidth - 2) << " ";
        cout << " |" << gap;

        cout << "| ";
        switch (i) {
            case 0: cout << setw(charWidth) << ("NAME: " + string(1, player.getSymbol())); break;
            case 1: cout << setw(charWidth) << ("HP: " + to_string(player.getHp()) + "/" + to_string(player.getMaxHealth())); break;
            case 2: cout << setw(charWidth) << ("ATK: " + to_string(player.getAttackpower())); break;
            case 3: cout << setw(charWidth) << ("DEF: " + to_string(player.getDefense())); break;
            case 4: cout << setw(charWidth) << ("GOLD: " + to_string(player.getGold())); break;
            case 5: cout << setw(charWidth) << ("LEVEL: " + to_string(player.getLevel())); break;
            case 6: cout << setw(charWidth) << ("XP: " + to_string(player.getXP()) + "/" + to_string(player.getXPToNextLevel())); break;
            default: cout << setw(charWidth) << " "; break;
        }
        cout << " |";

        if (isFinalBoss) {
            cout << gap << "| ";
            if (i < dragonArt.size()) cout << setw(asciiWidth - 2) << left << dragonArt[i];
            else cout << setw(asciiWidth - 2) << " ";
            cout << " |";
        }
        cout << "\n";
    }

    cout << "+------------------------------------+" << gap << "+-----------------------+";
    if (isFinalBoss) cout << gap << "+----------------------------------------+";
    cout << "\n";

    cout << "+----------------------- BATTLE HISTORY ------------------------+\n";
    int linesToShow = min(static_cast<int>(battleHistory.size()), 20);
    for (int i = static_cast<int>(battleHistory.size()) - linesToShow; i < battleHistory.size(); ++i) {
        cout << "| " << setw(60) << left << battleHistory[i] << " |\n";
    }
    cout << "+---------------------------------------------------------------+\n\n";
}
