#include "Combat.h"
#include "UI.h"
#include <conio.h> // For _getch()
#include <iostream>
using namespace std;
class Map;
void Combat::startCombat(Player& player, Enemy& enemy) {
    std::vector<std::string> combatLog;

    while (player.getIsAlive() && enemy.getIsAlive()) {
        combatLog.clear();

        // Round header
        combatLog.push_back("A wild " + enemy.getType() + " appears!");
        combatLog.push_back("Player HP: " + std::to_string(player.getHp()) +
                            " | Enemy HP: " + std::to_string(enemy.getHp()));
        combatLog.push_back("Choose an action:");
        combatLog.push_back("1. Attack");
        combatLog.push_back("2. Use Item");
        combatLog.push_back("3. Run");

        // Draw the UI
        UI::drawCombatUI(player, combatLog);

        int choice;
        std::cin >> choice;
        //Possible choice either to attack , use item or run?
        switch (choice) {
            case 1: {
                int damage = player.getAttackpower();
                enemy.takeDamage(damage);
                combatLog.push_back("You dealt " + std::to_string(damage) + " damage!");
                break;
            }
            case 2: {
                player.showInventory();
                std::cout << "Enter item index to use: ";
                int index;
                std::cin >> index;
                if (!player.useItem(index)) {
                    combatLog.push_back("Failed to use item!");
                }
                break;
            }
            case 3: {
                combatLog.push_back("You ran away!");
                UI::drawCombatUI(player, combatLog);
                return;
            }
            default:
                combatLog.push_back("Invalid choice.");
        }

        // Enemy's turn
        if (enemy.getIsAlive()) {
            int damage = enemy.getAttackpower();
            player.takeDamage(damage);
            combatLog.push_back("Enemy dealt " + std::to_string(damage) + " damage!");
        }
    }

    if (!player.getIsAlive()) {
        combatLog.push_back("You were defeated.");
    } else {
        combatLog.push_back("Enemy defeated!");
        player.gainExperience(enemy.getExperience());
        player.gainGold_From_Enemy(enemy.getGoldDropped());
    }
    UI::drawCombatUI(player, combatLog);
    _getch();
   return;   
}
