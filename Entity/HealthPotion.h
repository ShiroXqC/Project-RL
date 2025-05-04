// HealthPotion.h
#pragma once
#include "Item.h"

class HealthPotion : public Item {
public:
    HealthPotion(int x, int y) 
        : Item("Health Potion", x, y, true, 'H') {} // 'H' symbol
    
    // Optional: override getDisplayChar if you want different display logic
    char getDisplayChar() const override { return 'H'; }
};