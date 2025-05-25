// HealthPotion.h
#pragma once
#include "Item.h"
#include "Player.h" 
using namespace std;

class HealthPotion : public Item {
    public:
        HealthPotion()
            : Item("Health Potion", true, 'H') {} // 'H' symbol
        
            unique_ptr<Item> clone() const override {
                return make_unique<HealthPotion>(*this);
            }
        
            void use(Player& player) override {
                player.heal(10); // Heal the player by 10 HP
            }
            
        
        // Optional: override getDisplayChar if you want different display logic
        char getDisplayChar() const override { return 'H'; }
};