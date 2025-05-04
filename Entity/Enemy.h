#pragma once
#include"Entity.h"
class Enemy : public Entity
{
private:
    std::string type; // e.g., Goblin, Slime,Succubus,Incubus,Outcubus,Binhcubus
public:
    //Constructor
    Enemy(int x, int y, std::string type = "Goblin")
    {
        this->x = x;
        this->y = y;
        this->type = type;
        // Initialize base class attributes with reasonable defaults
        this->hp = 10;
        this->attackpower = 2;
        this->exp = 5;
    }
    
    //Default Constructor
    Enemy() : Entity(), type("Goblin") {}
    
    //Attack functions
    void attack(Entity& target) override;

    char getSymbol() const {
        if (type == "Goblin") return 'G';
        else if (type == "Slime") return 'S';
        else if (type == "Succubus") return 'U';
        else if (type == "Incubus") return 'I';
        else if (type == "Outcubus") return 'O';
        else if (type == "Binhcubus") return 'B';
        else return 'E'; // Default Enemy
    }
};