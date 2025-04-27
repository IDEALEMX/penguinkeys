#include <iostream>
#include <raylib.h>
#include <deque>

using namespace std;

#include "styleSettings.cpp"
#include "gameLogic.cpp"
#include "keyPresses.cpp"

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

        if (gameLogic.text[3].size() < 30)
            fillDeck(settings, &gameLogic);

        // process key input
        char upcomingCharacter = gameLogic.lineToString(&gameLogic.text[0])[gameLogic.currentCharacter];
        keyInputType input = getKeyInput(upcomingCharacter);
        
        if (input == correctKeyInput)
            gameLogic.currentCharacter += 1;

        if (input == correctKeyAndSpace) {
            gameLogic.currentCharacter += 1;
            gameLogic.typedWords +=1;
        }

        if (input == wrongKeyInput)
            gameLogic.mistakes += 1;

        // Drawing
        BeginDrawing();
        ClearBackground(PURPLE);
        gameLogic.checkIfNeedsLineSkip();
        gameLogic.drawText();
        gameLogic.drawHUD();
        EndDrawing();
    }

    return 0;
}

