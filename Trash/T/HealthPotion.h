// HealthPotion.h
#pragma once
#include "Item.h"
#include "Player.h" 

class HealthPotion : public Item {
    public:
        HealthPotion(int x, int y) 
            : Item("Health Potion", x, y, true, 'H') {} // 'H' symbol
        
            std::unique_ptr<Item> clone() const override {
                return std::make_unique<HealthPotion>(*this);
            }
        
            void use(Player& player) override {
                player.heal(10); // Heal the player by 10 HP
            }
            
        
        // Optional: override getDisplayChar if you want different display logic
        char getDisplayChar() const override { return 'H'; }
};