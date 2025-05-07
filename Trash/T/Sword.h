#pragma once
#include "Item.h"

class Sword : public Item {
public:
    Sword(int x, int y)
        : Item("Sword", x, y, false, 'S') {} // 'S' symbol
    
    char getDisplayChar() const override { return 'S'; }
};

