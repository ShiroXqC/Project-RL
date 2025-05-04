#pragma once
#include "entity.h"
#include <vector>
#include <string>
class Player
{
    private:
    int x; //Position X
    int y; //Postition Y
    char player_symbol= '@';

    public:
    Player(int startX, int startY) : x(startX), y(startY){}
    
    //Getters
    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return player_symbol; }

    //Setters(for movement)
    void SetPosition(int newX, int newY) {x = newX; y = newY;}
    void SetPlayerX(int startX) { x = startX; }
    void SetPlayerY(int startY) { y = startY; }
     

};