#include "readOnlyStrings.c"

#pragma once

char penguinWord [] = "penguin"; 
rString penguinString = rStringMake(penguinWord);

rString penguin() {
    return penguinString;
}
