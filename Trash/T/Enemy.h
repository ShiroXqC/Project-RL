#include "Entity.h"
#include <string>

class Enemy : public Entity {
private:
    std::string type;
    int gold_dropped;
    char symbol;  // Symbol used for map display (e.g. 'G', 'S', etc.)

public:
    Enemy(int x, int y, std::string type, int gold_dropped);
    Enemy();

    void attack(Entity& target) override;
    void takeDamage(int amount) override;
    char getSymbol() const override;

    int getExperience() const { return experience; }
    int getGoldDropped() const { return gold_dropped; }
    std::string getType() const { return type; }
};
