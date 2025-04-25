# pragma once

#define rStringMake(string) {string, sizeof(string)}

typedef struct {
    char* stringPointer;
    int lenght;
} rString;

