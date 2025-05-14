#pragma once
#include "Item.h"

class Sword : public Item {
public:
    Sword(int x, int y)
        : Item("Sword", x, y, false, 'S') {} // 'S' symbol
        
    std::unique_ptr<Item> clone() const override {
        return std::make_unique<Sword>(*this);
    }
    char getDisplayChar() const override { return 'S'; }
void use(Player& player) override {
    // Implementation of using the sword
}
};

