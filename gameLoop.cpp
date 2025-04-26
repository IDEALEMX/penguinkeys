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

string emptyString(int size) {
    string newString = "";
    for (int i = 0; i < size; i++) {
        newString.append("  ");
    }
    return newString;
}

int startGame (gameSettings* settings) {
    GameLogic gameLogic;

    fillDeck(settings, &gameLogic);

    // Current game loop
    while (!settings->endCondition(&gameLogic)) {

        // Process game logic
        if (IsWindowResized())
            gameLogic.reorderDeck();

        // process key input
        if (IsKeyPressed(KEY_N)) {
            gameLogic.currentCharacter += 1;
        }

        // Drawing
        BeginDrawing();
        ClearBackground(PURPLE);
        gameLogic.drawText();
        EndDrawing();
    }

    return 0;
}

