#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
    std::string type;
    int expDrop, goldDrop;
public:
    // Constructor with type-based stats
    Enemy(int x, int y, std::string type)
    {
        this->x = x;
        this->y = y;
        this->type = type;
        this->hp = hp;
        this->attackpower = attackpower;
        this->exp = exp;
        // Set stats based on type
        if (type == "Goblin") {
            hp = 14;
            attackpower = 5;
            exp = 10;
        } else if (type == "Slime") {
            hp = 10;
            attackpower = 3;
            exp = 5;
        } else if (type == "Vampire") {
            hp = 20;
            attackpower = 5;
            exp = 20;
        } else if (type == "Death Knight") {
            hp = 30;
            attackpower = 8;
            exp = 30;
        } else if (type == "Zombie") {
            hp = 18;
            attackpower = 6;
            exp = 15;
        } else {
            // Default stats
            hp = 10;
            attackpower = 2;
            exp = 5;
        }
    }
    
    
    // Override attack
    void attack(Entity& target) override;

    // Symbol for rendering
    char getSymbol() const {
        if (type == "Goblin")       return 'G';
        else if (type == "Slime")    return 'S';
        else if (type == "Vampire")  return 'V';
        else if (type == "Death Knight") return 'K';
        else if (type == "Zombie")   return 'Z';
    }
};
