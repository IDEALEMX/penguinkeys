#include <iostream>
#include <raylib.h>
#include <deque>

using namespace std;

#include "styleSettings.cpp"
#include "gameLogic.cpp"

#pragma once

typedef struct {
    bool (*endCondition) (GameLogic* );
    // Set to 0 if there is no maximum
    int maxNumberOfWords;
    string (*wordGenerator) ();
} gameSettings;

void fillDeck (gameSettings* settings, GameLogic* game) {
    int fillNumber = 50;

    for (int i = 0; i < fillNumber; i++) {
        game->text[0].push_back(settings->wordGenerator());
    }
    
    game->reorderDeck();
}

int startGame (gameSettings* settings) {
    GameLogic gameLogic;

    fillDeck(settings, &gameLogic);

    // Current game loop
    while (!settings->endCondition(&gameLogic)) {
        // Process game logic
        if (IsWindowResized())
            gameLogic.reorderDeck();

        BeginDrawing();
        string test = "Hello! this is a small test!";
        DrawText(gameLogic.dequeToPrintableText().c_str(),gameLogic.getHorizontalBlankSpaceStart() , gameLogic.getVerticalBlankSpaceStart(), fontSize, WHITE);

        ClearBackground(PURPLE);
        EndDrawing();
    }

    return 0;
}

