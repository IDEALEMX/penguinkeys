#include <raylib.h>
#include "gameLoop.cpp"
#include "endConditions.cpp"
#include "wordGenerators.cpp"
#include "styleSettings.cpp"

int main() {

    // Create the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800, "penguinKeys");
    loadValues();
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
