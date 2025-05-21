#include "Shop.h"
#include "Player.h"
#include <iostream>
#include <conio.h> // For _getch()
#include <memory>
#include <iomanip>
#include "HealthPotion.h" 
#include "Map.h"

// Getters
int Shop::getHealthPotionPrice() const { return HEALTH_POTION_PRICE; }
int Shop::getSwordPrice() const { return SWORD_PRICE; }
int Shop::getGreatSwordPrice() const { return GREAT_SWORD_PRICE; }
int Shop::getExcaliburPrice() const { return EXCALIBUR_PRICE; }
int Shop::getShieldPrice() const { return SHIELD_PRICE; }
int Shop::getKnightsShieldPrice() const { return KNIGHTS_SHIELD_PRICE; }
int Shop::getHerosShieldPrice() const { return HEROS_SHIELD_PRICE; }


void Shop::DisplayShop() {
    system("cls");
    cout << "\t   ======================================SHOP================================\t\n";
    cout << "\t    Item Available:\t" << "Current gold: " << player.getGold << '\n';
    cout << "\tName===================== Price ================================Effect\t\n";
    cout << "\t1. Health potion         " << getHealthPotionPrice() << "  gold" << setw(39) << "+10 hp\t\n";
    cout << "\t2. Sword                 " << getSwordPrice() << "  gold" << setw(39) << "+3 atk\t\n";
    cout << "\t3. Greatsword            " << getGreatSwordPrice() <<  "  gold" << setw(39) << "+6 atk\t\n";
    cout << "\t4. Excalibur             " << getExcaliburPrice() << " gold" << setw(39) << "+9 atk\t\n";
    cout << "\t5. Shield                " << getShieldPrice() << "  gold" << setw(39) << "+2 def\t\n";
    cout << "\t6. Knight's shield       " << getKnightsShieldPrice() << "  gold" << setw(39) << "+4 def\t\n";
    cout << "\t7. Hero's shield         " << getHerosShieldPrice() << " gold" << setw(39) << "+6 def\t\n";
    cout << "\t0. Exit shop\n";
}

void Shop::Choices() {
    int choice;
    bool exitShop = false;

    while (!exitShop) {
        DisplayShop();
        cout << "What do you want to buy? (Enter the number): ";
        cin >> choice;

        switch (choice) {
            case 1:
                buyHealthPotion();
                break;
            case 2:
                buySword();
                break;
            case 3:
                buyGreatSword();
                break;
            case 4:
                buyExcalibur();
                break;
            case 5:
                buyShield();
                break;
            case 6:
                buyKnightsShield();
                break;
            case 7:
                buyHerosShield();
                break;
            case 0:
                cout << "Thank you for visiting the shop!\n";
                exitShop = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                cout << "Press any key to continue...\n";
                _getch();
                break;
        }
    }
}

void Shop::buyHealthPotion() {
    if (PLAYER->spendGold(HEALTH_POTION_PRICE)) {
        auto potion = make_unique<HealthPotion>(-1, -1);  // Use HealthPotion class
        PLAYER->addToInventory(move(potion));
        cout << "Bought a Health Potion!\n";
        cout << "Press any key to continue...\n";
        _getch();
    }
}

void Shop::buySword() {
    if (PLAYER->spendGold(SWORD_PRICE)) {
        PLAYER->addAttackDamage(3);
        cout << "Bought a Sword! Attack power increased.\n";
        cout << "Press any key to continue...\n";
        _getch();
    }
}

void Shop::buyGreatSword() {
    if (PLAYER->spendGold(GREAT_SWORD_PRICE)) {
        PLAYER->addAttackDamage(6);
        cout << "Bought a Great Sword! Attack power increased significantly.\n";
        cout << "Press any key to continue...\n";
        _getch();
    }
}

void Shop::buyExcalibur() {
    if (PLAYER->spendGold(EXCALIBUR_PRICE)) {
        PLAYER->addAttackDamage(9);
        cout << "Bought Excalibur! Attack power greatly increased.\n";
        cout << "Press any key to continue...\n";
        _getch();
    }
}

void Shop::buyShield() {
    if (PLAYER->spendGold(SHIELD_PRICE)) {
        PLAYER->addDefense(2);
        cout << "Bought a Shield! Defense increased.\n";
        cout << "Press any key to continue...\n";
        _getch();
    }
}

void Shop::buyKnightsShield() {
    if (PLAYER->spendGold(KNIGHTS_SHIELD_PRICE)) {
        PLAYER->addDefense(4);
        cout << "Bought a Knight's Shield! Defense increased significantly.\n";
        cout << "Press any key to continue...\n";
        _getch();
    }
}

void Shop::buyHerosShield() {
    if (PLAYER->spendGold(HEROS_SHIELD_PRICE)) {
        PLAYER->addDefense(6);
        cout << "Bought a Hero's Shield! Defense greatly increased.\n";
        cout << "Press any key to continue...\n";
        _getch();
    }
}


