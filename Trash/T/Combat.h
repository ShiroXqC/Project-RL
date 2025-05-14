#pragma once 
#include "Player.h"
#include "Enemy.h"

class Combat {
    public:
        static void startCombat(Player& player, Enemy& enemy);
};