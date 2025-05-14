#include "Entity.h"

// Getters
int Entity::getHp() const { return hp; }
int Entity::getAttackpower() const { return attackpower; }
int Entity::getDef() const { return def; }
int Entity::getX() const { return x; }
int Entity::getY() const { return y; }
bool Entity::getIsAlive() const { return hp > 0; }  // Fixed

// Setters
void Entity::setHp(int hp) { this->hp = hp; }
void Entity::setAttackpower(int attackpower) { this->attackpower = attackpower; }
void Entity::setDef(int exp) { this->def = def }
void Entity::setX(int x) { this->x = x; }
void Entity::setY(int y) { this->y = y; }
void Entity::setPosition(int newX, int newY) { this->x = newX; this->y = newY; }

// Take damage
void Entity::takeDamage(int amount) {
    this->hp -= amount;
    if (hp < 0) {hp = 0; isAlive = false}
}

// Virtual function
void Entity::attack(Entity &target) {
    int amount = attackpower - target.getDef();
    if (amount > 0) target.takeDamage(amount);
}