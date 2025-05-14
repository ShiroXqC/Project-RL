#include "Enemy.h"

// Implementation of the virtual attack function
void Enemy::attack(Entity& target) {
    // We can customize enemy attack behavior here
    std::cout << "Enemy attacks!" << std::endl;
    
    // For now, just use the base class implementation
    Entity::attack(target);
    
    // Could add special effects based on enemy type
    if (type == "Slime") {
        std::cout << "The slime's acid deals extra damage!" << std::endl;
        target.takeDamage(1); // Extra 1 damage
    } else if (type == "Goblin") {
        std::cout << "The goblin cackles maniacally!" << std::endl;
    }
}