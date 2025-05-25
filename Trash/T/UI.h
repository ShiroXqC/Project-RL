#pragma once
#include "Map.h"
using namespace std;

class UI {
public:
    static void drawMainUI(const Map& map);
    static void drawCombatUI(const Player& player, const vector<string>& combatLog, const vector<string>& battleHistory, const Enemy* enemy = nullptr);
};
