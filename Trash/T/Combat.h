#pragma once 
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
using namespace std;

class Combat : public Map{
public:
    static void startCombat(Player& player, Enemy& enemy);    
};