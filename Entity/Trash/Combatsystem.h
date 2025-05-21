#pragma once
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

class CombatSystem {
private:
    bool playerTurn;

public:
    CombatSystem() : playerTurn(true) {}

    void startCombat(Player* player, Enemy* enemy);
    bool processTurn(Player* player, Enemy* enemy);
};