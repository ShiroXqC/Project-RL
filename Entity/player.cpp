#include "player.h"
#include <iostream>

Player::Player(int startX, int startY)
    : Entity(10, 3, 0, startX, startY) {}

void Player::move(char direction, const std::vector<std::string>& map) {
    int newX = x, newY = y;
    if (direction == 'w') newY--;
    else if (direction == 's') newY++;
    else if (direction == 'a') newX--;
    else if (direction == 'd') newX++;

    if (map[newY][newX] != '#') {
        x = newX;
        y = newY;
    }
}