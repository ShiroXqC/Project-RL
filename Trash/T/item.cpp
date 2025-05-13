#include "Item.h"
#include "player.h"
#include <cstdlib>
#include <ctime>

// HealthPotion class
class HealthPotion : public Item {
public:
    HealthPotion(int x, int y) 
        : Item("Health Potion", x, y, true, 'H') {}

    void use(Player& player) override {
        player.heal(20); // Heals 20 HP
        std::cout << "You used a Health Potion and regained health!\n";
    }

    std::unique_ptr<Item> clone() const override {
        return std::make_unique<HealthPotion>(*this);
    }

    char getDisplayChar() const override {
        return symbol;
    }
};

// Random item generator (only HealthPotion for now)
Item* Item::createRandomItem(int x, int y) {
    return new HealthPotion(x, y);
}
