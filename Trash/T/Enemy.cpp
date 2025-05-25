#include "Enemy.h"

int Enemy::getExperience() const
{
    return experience;
}

int Enemy::getGoldDropped() const
{
    return gold_dropped;
}

string Enemy::getType() const
{
    return type;
}

Enemy::Enemy(int x, int y, string type, int gold_dropped){
    this->x = x;
    this->y = y;
    this->type = type;
    this->gold_dropped = gold_dropped;

    if (type == "Goblin") {
        hp = 15; attackpower = 6; experience = 10; symbol = 'G'; this->gold_dropped = 20;
    } else if (type == "Slime") {
        hp = 14; attackpower = 5; experience =10; symbol = 'S'; this->gold_dropped = 15;
    } else if (type == "Vampire") {
        hp = 20; attackpower = 5; experience = 20; symbol = 'V'; this->gold_dropped = 25;
    } else if (type == "Death Knight") {
        hp = 30; attackpower = 8; experience = 30; symbol = 'K'; this->gold_dropped = 40;
    } else if (type == "Zombie") {
        hp = 18; attackpower = 6; experience = 15; symbol = 'Z'; this->gold_dropped = 30;
    } else if (type == "Dragon"){
        hp = 100; attackpower = 20; experience = 50; symbol = 'D'; this->gold_dropped = 10000;   
    } else {
        symbol = '!';  // default
    }
}
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
