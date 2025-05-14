#pragma once
#include <iostream>
#include <string>
#include <memory> // For std::unique_ptr

class Player;
class Item {
protected:
    std::string name;
    int x, y;
    bool isConsumedOnUse;
    char symbol;
    
public:
    Item(const std::string& n, int xx, int yy, bool c, char s)
        : name(n), x(xx), y(yy), isConsumedOnUse(c), symbol(s) {}
    virtual ~Item() = default;
    const std::string& getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isConsumable() const { return isConsumedOnUse; }
    virtual void use(Player& player) = 0;
    virtual std::unique_ptr<Item> clone() const = 0;
    virtual char getDisplayChar() const = 0;
    
};
