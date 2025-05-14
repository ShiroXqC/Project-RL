#pragma once
#include<iostream>
#include<string>
#include<vector>

class Entity
{
    protected:
    int hp; 
    int attackpower;
    int def;
    int x, y;
    bool isAlive = true;
    
    public:
    //Constructor overload
     Entity(int hp, int attackpower, int def, int startX, int startY)
    
    {
        this->hp=hp;
        this->attackpower=attackpower;
        this->def=def
        this->x=startX;
        this->y=startY;
    }
    
    //Default Constructor 
     Entity()
    {
        this->hp=0;
        this->attackpower=0;
        this->def=0;
        this->x=0;
        this->y=0;
    }

    //Getters
    int getHp() const;
    int getAttackpower() const;
    int getDef() const;
    int getX() const;
    int getY() const;
    bool getIsAlive() const;

    //Setters
    void setHp(int hp);
    void setAttackpower(int attackpower);
    void setDef(int def);
    void setY(int y);
    void setX(int x); // Fixed: Changed parameter name from y to x
    void setPosition(int newX, int newY);
    void takeDamage(int amount);
    
    //Virtual function
    virtual void takeDamage(int amount);
    virtual void attack(Entity &target);
};