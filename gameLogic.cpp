#include <raylib.h>
#include <iostream>
using namespace std;
#include <deque>

#include "styleSettings.cpp"

#pragma once

class GameLogic {
public:

    // Game counters
    int typedWords;
    int mistakes;

    // Loaded words
    deque<string> line1 = {"hello!", "this", "is", "a", "little", "test",":)"};
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
        if (!IsWindowResized())
           return;

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

    string dequeToPrintableText() {
        string result = "";
        for (int lineIndex = 0; lineIndex < numberOfVisibleLines; lineIndex ++) {
            deque<string> currentLine = text[lineIndex];
            result = result + lineToString(&currentLine) + "\n";
        }
        return result;
    }

    string lineToString (deque<string>* line) {

        if (line->empty())
            return "";

        string resultString;
        for (int i = 0; i < line->size() ;i++) {
            resultString = resultString + (*line)[i] + " ";
        }
        return resultString;
    }

    // Screen related functions

    float getHorizontalBlankSpaceStart() {
        return horizontalBlankSpacePercent * GetScreenWidth();
    }

    float getHorizontalBlankSpaceEnd() {
        int width = GetScreenWidth();
        return width - horizontalBlankSpacePercent * width;
    }

    bool stringFitsOnScreen(const string inputString) {
        int textWidth = MeasureText(inputString.c_str(), fontSize);
        return textWidth < GetScreenWidth() - getHorizontalBlankSpaceStart() * 2;
    }
    
};
