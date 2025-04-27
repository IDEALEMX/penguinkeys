#include <iostream>
#include <random>
#include <raylib.h>
#include <vector>

using namespace std;

#pragma once

string penguinString = "penguin";

string penguin() {
    return penguinString;
}

const vector<string> wordBank = {"penguin", "hello", "you", "if", "tutsi", "don", "naranjo", "says", "is", "there"};

string randomWords() {
    int r = GetRandomValue(0, wordBank.size() - 1);
    return wordBank[r];
}
