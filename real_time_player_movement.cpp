
#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

using namespace std;

const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;
char map[MAP_HEIGHT][MAP_WIDTH];

// Player position
int playerX = 1;
int playerY = 1;

void generateMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1)
                map[y][x] = '#';
            else
                map[y][x] = '.';
        }
    }
}

void drawInitialMap() {
    cout << "\033[H"; // Move cursor to top-left
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == playerX && y == playerY)
                cout << "@";
            else
                cout << map[y][x];
        }
        cout << endl;
    }
}

void drawTile(int x, int y, char symbol) {
    cout << "\033[" << y + 1 << ";" << x + 1 << "H" << symbol;
}

void movePlayer(char input) {
    int newX = playerX;
    int newY = playerY;

    switch (input) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        default: return;
    }

    if (map[newY][newX] == '#') return;

    drawTile(playerX, playerY, map[playerY][playerX]);
    playerX = newX;
    playerY = newY;
    drawTile(playerX, playerY, '@');
}

#ifdef _WIN32
char getInput() {
    if (_kbhit())
        return _getch();
    return '\0';
}
#else
char getInput() {
    struct termios oldt, newt;
    char ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
        return ch;
    return '\0';
}
#endif

int main() {
    generateMap();
    cout << "\033[2J\033[H"; // Clear screen and move cursor to top
    cout << "\033[?25l"; // Hide cursor
    drawInitialMap();

    while (true) {
        char input = getInput();
        if (input != '\0') {
            movePlayer(input);
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    cout << "\033[?25h"; // Show cursor again (not reached in current loop)
    return 0;
}
