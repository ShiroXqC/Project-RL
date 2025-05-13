#include"Entity.h"

//Getters
int Entity::getHp() const { return hp;}
int Entity::getAttackpower() const{ return attackpower;}
int Entity::getExp() const{ return exp;}   
int Entity::getX() const{ return x;}
int Entity::getY() const{ return y;}
//Setters           
void Entity::setHp(int hp) { this->hp=hp;}
void Entity::setAttackpower(int attackpower) { this->attackpower=attackpower;}   
void Entity::setExp(int exp) { this->exp=exp;}
void Entity::setX(int x) { this->x=x;}
void Entity::setY(int y) { this->y=y;}
void Entity::setPosition (int newX, int newY){this->x=newX; this->y=newY;}
bool Entity::getIsAlive() const{ return hp>0;}
void Entity::takeDamage(int amount)
{
    this->hp-=amount;
    if (hp < 0) hp = 0;   // Ensure hp doesn't go negative
}
//Virtual function 
void Entity::attack(Entity &target)
{
    target.takeDamage(this->attackpower);
}
