# include "readOnlyStrings.c"

# pragma once

typedef struct {
    int typedWords;
    int mistakes;
} gameState ;

typedef struct {
    int (*endCondition) (gameState*);
    rString (*wordGenerator) ();
} gameSettings;

const gameState defaultGameState = {0, 0};

int startGame (gameSettings* settings) {
    gameState state = defaultGameState;
    while (!settings->endCondition) {
    }
    return 0;
}
