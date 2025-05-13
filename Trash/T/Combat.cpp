#include "Combat.h"
#include <iostream>

void Combat::startCombat(Player& player, Enemy& enemy) {
    std::cout << "Combat started between " << player.getSymbol()
              << " and " << enemy.getSymbol() << "!\n";

    while (player.isAlive() && enemy.isAlive()) {
        // Player attacks
        int playerDamage = player.getAttackpower();
        enemy.takeDamage(playerDamage);
        std::cout << "You dealt " << playerDamage << " damage to the enemy.\n";

        if (!enemy.isAlive()) {
            std::cout << "Enemy defeated!\n";
            player.gainExperience(enemy.getExperience()); // if implemented
            break; // ✅ this is inside the while loop
        }

        // Enemy attacks
        int enemyDamage = enemy.getAttackpower();
        player.takeDamage(enemyDamage);
        std::cout << "Enemy dealt " << enemyDamage << " damage to you.\n";

        std::cout << "Player HP: " << player.getHp()
                  << " | Enemy HP: " << enemy.getHp() << "\n";
    }
}
