#include "Combat.h"
#include "UI.h"
#include <conio.h> // For _getch()
#include <iostream>

class Map;
void Combat::startCombat(Player& player, Enemy& enemy) {
    vector<string> combatLog;
    vector<string> battleHistory;
    int pDamage = player.getAttackpower();

    while (player.getIsAlive() && enemy.getIsAlive()) {
        combatLog.clear();

        // Round header
        combatLog.push_back("A wild " + enemy.getType() + " appears!");
        combatLog.push_back("Player HP: " + to_string(player.getHp()) + " | Enemy HP: " + to_string(enemy.getHp()));
        combatLog.push_back("Choose an action:");
        combatLog.push_back("1. Attack");
        combatLog.push_back("2. Use Item");
        combatLog.push_back("3. Run");

        // Draw the UI
        UI::drawCombatUI(player, combatLog, battleHistory, &enemy);

        int choice;
        while (true) {
            std::cout << "Enter your choice (1-3): ";
            std::string input;
            std::getline(std::cin, input); // Read full line

            if (input == "1" || input == "2" || input == "3") {
                choice = std::stoi(input); // Safe to convert
                break;
            } else {
                UI::drawCombatUI(player, combatLog, battleHistory, &enemy);
            }
        }

        //Possible choice either to attack , use item or run?
        switch (choice) {
            case 1: 
            {
                int damage = player.getAttackpower();
                enemy.takeDamage(damage);
                break;
            }
            case 2: 
            {
                player.showInventory();
                cout << "Enter item index to use: ";
                int index;
                cin >> index;
                if (!player.useItem(index)) 
                {
                    combatLog.push_back("Failed to use item!");
                }
                break;
            }
            case 3: 
            {
                combatLog.push_back("You ran away!");
                UI::drawCombatUI(player, combatLog, battleHistory);
                return;
            }
            default:
                combatLog.push_back("Invalid choice.");
        }

        // Enemy's turn
        if (enemy.getIsAlive()) 
        {
            int damage = enemy.getAttackpower();
            player.takeDamage(damage);
            combatLog.push_back("Enemy dealt " + to_string(damage) + " damage!");
            battleHistory.push_back("You dealt " + to_string(pDamage) + " damage to " + enemy.getType() + ".");
            battleHistory.push_back(enemy.getType() + " dealt " + to_string(damage) + " damage to you.");

            if (player.getDefense() > 0) {
                battleHistory.push_back("You blocked " + to_string(player.getDefense()) + " damage with your defense.");
            }
        }

        if (!enemy.getIsAlive()) {
            battleHistory.push_back("You have defeated the " + enemy.getType() + "!");
            battleHistory.push_back("You have gained " + to_string(enemy.getExperience()) + " EXP and " + to_string(enemy.getGoldDropped()) + " gold!");
            UI::drawCombatUI(player, combatLog, battleHistory, &enemy);
        }
    }

    if (!player.getIsAlive()) {
        combatLog.push_back("You were defeated.");
    } else {
        player.gainExperience(enemy.getExperience());
        player.gainGold_From_Enemy(enemy.getGoldDropped());
    }
    UI::drawCombatUI(player, combatLog, battleHistory);
    _getch();
    return;   
}
