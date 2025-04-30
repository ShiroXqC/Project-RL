#pragma once
#include<iostream>
#include<string>
#include<vector>

class Entity
{
    private:
    int hp, attackpower;
    int exp;
    int x, y;

    public:
    //Constructor overload
    Entity(int hp, int attackpower, int exp, int x, int y)
    {
        this->hp=hp;
        this->attackpower=attackpower;
        this->exp=exp;
        this->x=x;
        this->y=y;
    }

    //Default Constructor 
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
    int getAttackpower() const;
    int getExp() const;
    int getX() const;
    int getY() const;

    //Setters
    void setHp(int hp);
    void setAttackpower() const;
    void setExp() const;
    void setX() const;
    void setY() const;

};