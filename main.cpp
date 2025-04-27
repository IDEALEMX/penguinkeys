#include <raylib.h>

#include "gameLoop.cpp"
#include "endConditions.cpp"
#include "wordGenerators.cpp"
#include "styleSettings.cpp"

int main() {

    // Create the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800, "penguinKeys");
    SetWindowMinSize(350, 350);
    SetTargetFPS(60);

    // General game setup
    loadValues();

    // Gameloop
    while (!WindowShouldClose()) {
        SetRandomSeed(23);
        gameSettings testSettings = {&neverEnd, 0, &randomWords};
        startGame(&testSettings);
    }

    // Close window
    CloseWindow();


    return 0;
}
