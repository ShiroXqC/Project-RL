#pragma once
#include"Entity.h"

class Enemy : public Entity
{
private:
    std::string type;
    Enemy* currentEnemy;
    int experience = 0;

public:
    //Constructor
    Enemy(int x, int y, std::string type = "Goblin")
    {
        this->x = x;
        this->y = y;
        this->type = type;
        if      (type == "Goblin")       { hp=14; attackpower=5;  experience=10; }
        else if (type == "Slime")        { hp=10; attackpower=3;   experience=5; }
        else if (type == "Vampire")      { hp=20; attackpower=5;  experience=20; }
        else if (type == "Death Knight") { hp=30; attackpower=8;  experience=30; }
        else if (type == "Zombie")       { hp=18; attackpower=6;  experience=15; }
    }
    Enemy() : Enemy(0,0,"Goblin") {}

    int getExperience() const  { return experience; } //getter for experience
    
    //Attack functions
    void attack(Entity& target) override;

    char getSymbol() const {
        if      (type == "Goblin")       return 'G';
        else if (type == "Slime")        return 'S';
        else if (type == "Vampire")      return 'V';
        else if (type == "Death Knight") return 'K';
        else if (type == "Zombie")       return 'Z';
        else                              return '?';
    }
};