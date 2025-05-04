int main() {
    Map gameMap(20, 15);
    gameMap.startNewTurn();
    
    while (true) {
        // Display map
        gameMap.display();
        
        // Show turn info
        std::cout << "Turn: " << gameMap.getCurrentTurn() << "\n";
        std::cout << "Move with WASD, Space to wait, Q to quit\n";
        
        // Get input
        char input;
        std::cin >> input;
        
        if (tolower(input) == 'q') {
            break;
        }
        
        // Process movement
        if (!gameMap.handlePlayerMove(input)) {
            std::cout << "Invalid move!\n";
        }
    }
    
    return 0;
}



















void Map::spawnRandomEnemies (int count) {
    std::vector<std::string> enemyTypes = {"Goblin", "Slime", "Succubus", "Incubus", "Outcubus", "Binhcubus"};
    
    for (int i = 0; i < count; ++i) {
        auto [x, y] = getRandomEmptyPosition();
        if (x == -1) break; // No space left

        // Choose a random enemy type
        std::string type = enemyTypes[rand() % enemyTypes.size()];
        Enemy* enemy = new Enemy(x, y, type);
        enemies.push_back(enemy);
        grid[y][x] = enemy->getSymbol();
    }
}















#include"Item.h"
#include"Enemy.h"
#include"Entity.h"
#include"player.h"
#include <iostream>
#include <string>
#include <vector>

class Map
{
    private:
    //Map variable
    std::vector<std::vector<char>> grid; //Vector of vector or in other words a 2d matrix of vector of type char
    std::vector<Enemy*> enemies; //Vector containing Enemy pointer
    std::vector<Item*> items; //Vector containing Item pointer 
    int width;
    int height;
    Player *player;

    //Check if coordinates are within map boundaries
    bool isInBounds(int x, int y) const
    {
        return (x >= 0 && x<width && y >=0 && y<height);
    }
    
    //For Player turn based movement
    int currentTurn;
    bool PlayerTurn; 

        
    // Helper method to find empty positions
    std::pair<int, int> getRandomEmptyPosition() const {
        std::vector<std::pair<int, int>> emptyPositions;
        
        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                if (grid[y][x] == '.' && 
                    !(x == player->getX() && y == player->getY())) {
                    emptyPositions.emplace_back(x, y);
                }
            }
        }
        
        if (!emptyPositions.empty()) {
            int index = rand() % emptyPositions.size();
            return emptyPositions[index];
        }
        return {-1, -1}; // No empty positions
    }



    public:
    //Default Constructor
     // Default constructor - creates a small empty map
     Map() : width(10), height(10) 
     {
        // Initialize grid with '.' (empty spaces) by setting the number of rows and column and filling them with _
        grid.resize(height, std::vector<char>(width, '.'));
        
        // Add some basic walls around the edges
        for (int i = 0; i < height; i++) {
            grid[i][0] = '#';       // Left wall
            grid[i][width-1] = '#'; // Right wall
        }
        for (int j = 0; j < width; j++) {
            grid[0][j] = '#';        // Top wall
            grid[height-1][j] = '#'; // Bottom wall
        }
    }
     // Parameterized constructor - creates map with specified dimensions
     Map(int x, int y) : width(x), height(y) {
        // Basic validation (minimum size 3x3)
        if (x < 3) width = 3;
        if (y < 3) height = 3;
        
        // Initialize grid with '.' (empty spaces)
        grid.resize(height, std::vector<char>(width, '.'));
        
        // Add some basic walls around the edges
        for (int i = 0; i < height; i++) {
            grid[i][0] = '#';       // Left wall
            grid[i][width-1] = '#'; // Right wall
        }
        for (int j = 0; j < width; j++) {
            grid[0][j] = '#';        // Top wall
            grid[height-1][j] = '#'; // Bottom wall
        }

        //Generate player in the middle of the map 
        int CenterX = width / 2;
        int CenterY = height / 2;
        player = new Player(CenterX, CenterY);
        grid[CenterY][CenterX] = player -> getSymbol();
        
        //Clean up player
        delete player;
    }

     // Add method to get player
     Player* getPlayer() const { return player; }

    // Add method to update player position on grid
    void updatePlayerPosition(int oldX, int oldY, int newX, int newY); 

    //Turn base movement method
    bool handlePlayerMove(char input);

    //Turn management
    void startNewTurn();
    int getCurrentTurn() const;

    //Enemy turn handling (placeholder)
    void processEnemyTurns();


    //Handle item spawning
    void spawnRandomItems(int count);
    void display() const;

    //To spawn random enemies
    void spawnRandomEnemies(int count);


    //Destructor
    ~Map() {
        for (Enemy* e : enemies)
            delete e;
        for (Item* i : items)
            delete i;
        delete player;
    }
};