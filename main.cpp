#include <raylib.h>
#include "gameLoop.cpp"
#include "endConditions.cpp"
#include "wordGenerators.cpp"

int main() {

    // Create the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800, "penguinKeys");
    SetTargetFPS(60);

    // Gameloop
    while (!WindowShouldClose()) {
        gameSettings testSettings = {&neverEnd, 0, &penguin};
        startGame(&testSettings);
    }

    // Close window
    CloseWindow();

    return 0;
}
