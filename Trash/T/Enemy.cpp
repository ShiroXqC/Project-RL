#include "Enemy.h"
#include <iostream>
using namespace std;

// Implementation of the virtual attack function
void Enemy::attack(Entity& target) {
    // We can customize enemy attack behavior here
    cout << "Enemy attacks!" << endl;
    
    // For now, just use the base class implementation
    Entity::attack(target);
    
    // Could add special effects based on enemy type
    if (type == "Slime") {
        cout << "The slime's acid deals extra damage!" << endl;
        target.takeDamage(1); // Extra 1 damage
    } else if (type == "Goblin") {
        cout << "The goblin cackles maniacally!" << endl;
    }
}