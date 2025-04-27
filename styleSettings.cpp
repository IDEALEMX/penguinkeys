#include <raylib.h>

# pragma once

// What percent of the screen will be clear on the sides 
float horizontalBlankSpacePercent;
float verticalBlankSpacePercent;

// Font info

Font font;
int fontSize;
int verticalSpacing;

void loadValues() {
    // What percent of the screen will be clear on the sides 
    horizontalBlankSpacePercent = 0.10;
    verticalBlankSpacePercent = 0.20;

    // Font info

    font = GetFontDefault();
    fontSize = 40;
    verticalSpacing = 40;
}


