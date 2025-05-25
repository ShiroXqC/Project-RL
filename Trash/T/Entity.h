#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Entity
{
    protected:
    int hp; 
    int attackpower;
    int exp;
    int x, y;
    bool isAlive = true;
    virtual char getSymbol() const = 0;
    

    public:

    Entity(int hp, int attackpower, int exp, int startX, int startY)
    {
        this->hp=hp;
        this->attackpower=attackpower;
        this->exp=exp;
        this->x=startX;
        this->y=startY;
    }
    
    Entity()
    {
        this->hp=0;
        this->attackpower=0;
        this->exp=0;
        this->x=0;
        this->y=0;
    }

    //Getters
    int getHp() const;
    virtual getAttackpower() const;
    int getExp() const;
    int getX() const;
    int getY() const;
    bool getIsAlive() const;
    
    //Setters
    void setHp(int hp);
    void setAttackpower(int attackpower);
    void setExp(int exp);
    void setY(int y);
    void setX(int x);
    void setPosition(int newX, int newY);
    
    virtual void takeDamage(int amount);
    virtual void attack(Entity &target);

    virtual ~Entity() = default; 

};
