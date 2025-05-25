// HealthPotion.h
#pragma once
#include "Item.h"
#include "Player.h" 
using namespace std;

class HealthPotion : public Item {
    public:
        HealthPotion(): Item("Health Potion") {}
        
            unique_ptr<Item> clone() const override {
                return make_unique<HealthPotion>(*this);
            }
            
            // Heal the player by 10 HP
            void use(Player& player) override {
                player.heal(10); // Heal the player by 10 HP
            }
};