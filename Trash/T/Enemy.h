#pragma once
#include"Entity.h"

class Enemy : public Entity
{
private:
    std::string type;
    Enemy* currentEnemy;
    int experience;
    int gold_dropped;

public:
    //Constructor
    Enemy(int x, int y, std::string type = "Goblin",int gold_dropped)
    {
        this->x = x;
        this->y = y;
        this->type = type;
        if      (type == "Goblin")       { hp = 14; attackpower = 5; experience = 10; gold_dropped = 2}
        else if (type == "Slime")        { hp = 10; attackpower = 3; experience=5; gold dropped = 5}
        else if (type == "Vampire")      { hp = 20; attackpower = 5; experience = 20; gold dropped = 10}
        else if (type == "Death Knight") { hp = 30; attackpower = 8; experience = 30; gold dropped = 15}
        else if (type == "Zombie")       { hp = 18; attackpower = 6; experience = 15; gold dropped = 20}
    }
    Enemy() : Enemy(0,0,"Goblin") {}

    int getExperience() const  { return experience; } //getter for experience
    int getGold_dropped() const { return gold_dropped; } //getter for gold dropped
    std::string getType() const { return type; }
    
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