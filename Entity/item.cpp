#include "item.h"

item::item(std::string name, int x, int y, bool isConsumedOnUse)
{
    this->name = name;
    this->x = x;
    this->y = y;
    this->isConsumedOnUse = isConsumedOnUse;
    this->symbol = '?';   // Default symbol for items
}
std::string item::getName() const
{
    return name;
}