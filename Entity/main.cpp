
#include <string>
#include "item.h"
#include "Entity.h"
#include "player.h"
#include "Map.h"
#include <ctime>   // for time()
#include <cstdlib> // for rand() and srand()

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random generator

    // Create a 15x10 map
    Map gameMap(15, 10);

    // Spawn some items
    gameMap.spawnRandomItems(6); // Alternates Sword (S) and HealthPotion (H)

    // Spawn some enemies
    gameMap.spawnRandomEnemies(8); // Goblins, Slimes, Succubi, etc.

    // Display the map
    gameMap.display();

    // Just end here for now (no gameplay loop)
    return 0;
}
