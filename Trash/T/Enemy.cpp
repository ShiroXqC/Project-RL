#include "Enemy.h"

Enemy::Enemy(int x, int y, std::string type, int gold_dropped)
    : type(type), gold_dropped(gold_dropped) {
    this->x = x;
    this->y = y;

    if (type == "Goblin") {
        hp = 14; attackpower = 5; experience = 10; symbol = 'G';
    } else if (type == "Slime") {
        hp = 10; attackpower = 3; experience = 5; symbol = 'S';
    } else if (type == "Vampire") {
        hp = 20; attackpower = 5; experience = 20; symbol = 'V';
    } else if (type == "Death Knight") {
        hp = 30; attackpower = 8; experience = 30; symbol = 'K';
    } else if (type == "Zombie") {
        hp = 18; attackpower = 6; experience = 15; symbol = 'Z';
    } else {
        symbol = '!';  // default
    }
}

Enemy::Enemy() : Enemy(0, 0, "Goblin", 2) {}

void Enemy::attack(Entity& target) {
    target.takeDamage(attackpower);
}

void Enemy::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
    if (hp == 0) isAlive = false;
}

char Enemy::getSymbol() const {
    return symbol;
}
