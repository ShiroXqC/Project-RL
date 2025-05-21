#pragma once
#include "Player.h"
#include "Item.h"
#include <iostream>
#include <memory>
#include <conio.h>

class Shop {
private:
    Player* player;

    const int HEALTH_POTION_PRICE = 15;
    const int SWORD_PRICE = 30;
    const int GREAT_SWORD_PRICE = 60;
    const int EXCALIBUR_PRICE = 120;
    const int SHIELD_PRICE = 25;
    const int KNIGHTS_SHIELD_PRICE = 50;
    const int HEROS_SHIELD_PRICE = 100;

public:
    // Constructor
    Shop(Player* p) : player(p) {}

    // Display shop interface
    void DisplayShop();

    // Choices for purchasing
    void Choices();

    // Purchase options
    void buyHealthPotion();
    void buySword();
    void buyGreatSword();
    void buyExcalibur();
    void buyShield();
    void buyKnightsShield(); // Fixed spelling
    void buyHerosShield();

    // Item prices
    int getHealthPotionPrice() const;
    int getSwordPrice() const;
    int getGreatSwordPrice() const;
    int getExcaliburPrice() const;
    int getShieldPrice() const;
    int getKnightsShieldPrice() const;
    int getHerosShieldPrice() const;
};
