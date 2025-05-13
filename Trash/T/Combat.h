#pragma once 
#include "player.h"
#include "Enemy.h"
#include <string>

class Combat {
    public:
    static void startCombat(Player& player, Enemy& enemy);
};