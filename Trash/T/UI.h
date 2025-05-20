#pragma once
#include "Map.h"

class UI {
public:
    static void drawMainUI(const Map& map);
    static void drawCombatUI(const Player& player, const std::vector<std::string>& combatLog);
};
