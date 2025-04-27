#include <raylib.h>
#include <deque>
#include <array>
#include <iostream>
using namespace std;

#include "styleSettings.cpp"

#pragma once

class GameLogic {
public:
    
    // Game counters
    int typedWords = 0;
    int mistakes = 0;
    int currentCharacter = 0;

    // Loaded words
    deque<string> line1;
    deque<string> line2;
    deque<string> line3;
    deque<string> overflow;
    
    const int numberOfVisibleLines = 3;

    // contains the text that will be printed on screen
    deque<deque<string>> text = {line1, line2, line3, overflow};

    /*
     * If the window size changed since the last frame it re orders
     * the text so it now fits into the screen
     * the text on screen only has 3 lines, everything that doesn't
     * fit will be stored on the "overflow" line
     */

    void reorderDeck () {
        for (int lineIndex = 0; lineIndex < numberOfVisibleLines;lineIndex ++) {
            deque<string>* currentLine = &(text[lineIndex]);
            deque<string>* nextLine = &(text[lineIndex + 1]);
            string currentLineAsString = lineToString(currentLine);
            
            // Checks if the current line has too many characters
            while (!stringFitsOnScreen(currentLineAsString) && !currentLine->empty()) {
                string lastWord = (*currentLine)[(*currentLine).size() - 1];
                currentLine->pop_back();
                nextLine->push_front(lastWord);
                // updates the state of the current line as a string
                currentLineAsString = lineToString(currentLine);
            }

            // Checks if the current line has too few characters
            string currentLineAsStringPlusOne;

            // If the next line is empty it will ignore everything
            if (!nextLine->empty()) {
                currentLineAsStringPlusOne = lineToString(currentLine) + (*nextLine)[0];
            } else {
                continue;
            }

            while(stringFitsOnScreen(currentLineAsStringPlusOne)) {
                string newWord = (*nextLine)[0];
                nextLine->pop_front();
                currentLine->push_back(newWord);

                // updates the state of the current line as a string
                if (!nextLine->empty()) {
                    currentLineAsStringPlusOne = lineToString(currentLine) + (*nextLine)[0];
                } else {
                    break;
                }
            }
        }
    }
    
    array<string, 3>preGenerated;

    /*
     * Returns the text deque as a string
     * if there is no window resizing it will
     * return the previously pre-generated text
     * to avoid unnecesary computations
     */
        
    string lineToString (deque<string>* line) {
        if (line->empty())
            return "";

        string resultString;
        for (int i = 0 ; i < line->size() ;i++) {
            if (i == line->size() - 1) {
                resultString += (*line)[i];
                break;
            }
            resultString += (*line)[i] + " ";
        }
        return resultString;
    }

    // Screen related functions

    float getHorizontalBlankSpaceStart() {
        return horizontalBlankSpacePercent * GetScreenWidth();
    }

    float getVerticalBlankSpaceStart() {
        return verticalBlankSpacePercent * GetScreenHeight();
    }

    float getHorizontalBlankSpaceEnd() {
        int width = GetScreenWidth();
        return width - horizontalBlankSpacePercent * width;
    }

    float getVerticalBlankSpaceEnd() {
        int height = GetScreenHeight();
        return height - verticalBlankSpacePercent * height;
    }

    bool stringFitsOnScreen(const string inputString) {
        int textWidth = MeasureText(inputString.c_str(), fontSize);
        return textWidth < GetScreenWidth() - getHorizontalBlankSpaceStart() * 2;
    }

    void checkIfNeedsLineSkip() {
        deque<string>* firstLine = &text[0];
        int firstLineSize = lineToString(firstLine).size();
        if (currentCharacter > firstLineSize) {
            firstLine->clear();
            reorderDeck();
            currentCharacter -= firstLineSize + 1;
        }
    }

    void drawText() {
        for (int i = 0; i < numberOfVisibleLines; i++) {
            deque<string>* line = &text[i];
            string fullText = lineToString(line);
            Vector2 position = {getHorizontalBlankSpaceStart(), getVerticalBlankSpaceStart() + verticalSpacing * i};

            if (i == 0) {
                string typed = fullText.substr(0, currentCharacter);
                string unTyped = fullText.substr(currentCharacter);
                Vector2 sizeOfTyped = MeasureTextEx(font, typed.c_str(), fontSize, 1);
                Vector2 unTypedStart = {position.x + sizeOfTyped.x, position.y};
                DrawTextEx(font, typed.c_str(), position , fontSize, 1, BLUE);
                DrawTextEx(font, unTyped.c_str(), unTypedStart, fontSize, 1, WHITE);
                continue;
            }

            DrawTextEx(font, fullText.c_str(), position , fontSize, 1, WHITE);
        }
    }

    void drawHUD() {
        string wordCountText = "Words: " + to_string(typedWords);
        string mistakeCountText = "Mistakes: " + to_string(mistakes);
        int mistakePositionX = getHorizontalBlankSpaceEnd() - MeasureText(mistakeCountText.c_str(), fontSize) - getHorizontalBlankSpaceStart();
        
        // Branching to prevent overlap
        
        const int maxStringOverlap = 20;
        if (getHorizontalBlankSpaceStart() + MeasureText(wordCountText.c_str(), fontSize) + maxStringOverlap >= mistakePositionX) {
            DrawText(wordCountText.c_str(), getHorizontalBlankSpaceStart(), getVerticalBlankSpaceEnd() - verticalSpacing, fontSize, WHITE);
            DrawText(mistakeCountText.c_str(), getHorizontalBlankSpaceStart(), getVerticalBlankSpaceEnd(), fontSize, WHITE);
            return;
        }

        DrawText(wordCountText.c_str(), getHorizontalBlankSpaceStart(), getVerticalBlankSpaceEnd(), fontSize, WHITE);
        DrawText(mistakeCountText.c_str(), mistakePositionX, getVerticalBlankSpaceEnd(), fontSize, WHITE);
    }
};
