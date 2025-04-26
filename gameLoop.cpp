#include <iostream>
#include <raylib.h>
#include <deque>

using namespace std;

#include "styleSettings.cpp"
#include "gameLogic.cpp"

#pragma once


typedef struct {
    bool (*endCondition) (GameLogic* );
    string (*wordGenerator) ();
} gameSettings;

int startGame (gameSettings* settings) {
    GameLogic gameLogic;

    // Current game loop
    while (!settings->endCondition(&gameLogic)) {
        // Process game logic
        gameLogic.reorderDeck();

        BeginDrawing();
        string test = "Hello! this is a small test!";
        DrawText(gameLogic.dequeToPrintableText().c_str(),gameLogic.getHorizontalBlankSpaceStart() , GetScreenHeight() / 2, fontSize, WHITE);

        /*
        if (!gameLogic.stringFitsOnScreen(test)) {
            cout << "ouch I dont fit!" << "\n";
        } else {
            cout << "I fit!" << "\n";
        }
        */

        ClearBackground(PURPLE);
        EndDrawing();
    }

    return 0;
}

