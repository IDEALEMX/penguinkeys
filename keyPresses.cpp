#include <raylib.h>

#pragma once

typedef enum {
    noKeyInput = 0,
    correctKeyInput = 1,
    wrongKeyInput = 2,
    correctKeyAndSpace = 3,
} keyInputType;

/*
 * Returns the last pressed key as a char
 * If there was no valid key pressed it will return 0;
 */

char returnPressedKey() {
    int input = GetKeyPressed();

    switch (input) {
        case KEY_A: return 'a';
        case KEY_B: return 'b';
        case KEY_C: return 'c';
        case KEY_D: return 'd';
        case KEY_E: return 'e';
        case KEY_F: return 'f';
        case KEY_G: return 'g';
        case KEY_H: return 'h';
        case KEY_I: return 'i';
        case KEY_J: return 'j';
        case KEY_K: return 'k';
        case KEY_L: return 'l';
        case KEY_M: return 'm';
        case KEY_N: return 'n';
        case KEY_O: return 'o';
        case KEY_P: return 'p';
        case KEY_Q: return 'q';
        case KEY_R: return 'r';
        case KEY_S: return 's';
        case KEY_T: return 't';
        case KEY_U: return 'u';
        case KEY_V: return 'v';
        case KEY_W: return 'w';
        case KEY_X: return 'x';
        case KEY_Y: return 'y';
        case KEY_Z: return 'z';
        case KEY_SPACE: return ' ';
        case KEY_ENTER: return ' ';
    }

    return 0;
}

keyInputType getKeyInput(char expectedCharacter) {
    char input = returnPressedKey();

    if (input == 0)
        return noKeyInput;

    if (expectedCharacter == '\0' && input == ' ')
        return correctKeyAndSpace;

    if (input == ' ' && input == expectedCharacter)
        return correctKeyAndSpace;

    if (input == expectedCharacter)
        return correctKeyInput;

    return wrongKeyInput;

}
