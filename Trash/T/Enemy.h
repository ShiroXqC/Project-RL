#pragma once
#include "Entity.h"
#include <string>
using namespace std;

class Enemy : public Entity {
private:
    string type;
    int gold_dropped;
    int experience = 0;
    char symbol;

public:
    Enemy(int x, int y, string type, int gold_dropped);

    void attack(Entity& target) override;
    void takeDamage(int amount) override;
    char getSymbol() const override;

    int getExperience() const;
    int getGoldDropped() const;
    string getType() const;
};
