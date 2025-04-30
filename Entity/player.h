#pragma once
#include entity.h
#include <vector>
#include <string>

class Player : public Entity {
    public:
        Player(int startX, int startY);
    
        void move(char direction, const std::vector<std::string>& map);
    };