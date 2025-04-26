#include <iostream>

#include "raylib.h"
using namespace std;

#pragma once

class GameLogic {
    // Game counters
    int typedWords;
    int mistakes;
};

typedef struct {
    bool (*endCondition) (GameLogic* );
    string (*wordGenerator) ();
} gameSettings;

int startGame (gameSettings* settings) {
    GameLogic gameLogic;

    // Current game loop
    while (!settings->endCondition(&gameLogic)) {
        BeginDrawing();
        ClearBackground(PURPLE);
        EndDrawing();
    }

    return 0;
}

