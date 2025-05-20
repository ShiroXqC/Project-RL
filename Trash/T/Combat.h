#pragma once 
#include "Player.h"
#include "Enemy.h"

class Map;
class Combat {
    public:
        static void startCombat(Player& player, Enemy& enemy);
};