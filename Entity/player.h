#pragma once
#include "entity.h"
#include <vector>
#include <string>

// Controls player movement 
class Player : public Entity {
    public:
        Player(int startX, int startY);
// Movement input: WASD, bounded by walls
        void move(char direction, const std::vector<std::string>& map);
    };