#include <raylib.h>
#include "gameLoop.c"
#include "endConditions.c"
#include "wordGenerators.c"

int main() {

    // Create the window
    InitWindow(800, 800, "penguinKeys");

    // Gameloop
    while (!WindowShouldClose()) {
        gameSettings testSettings = {&neverEnd, &penguin};
        startGame(&testSettings);
    }

    // Close window
    CloseWindow();

    return 0;
}
