
#pragma once

const int MAX_TEXT = 500;    // maximum text length used across the project

struct FreqReport
{
    int counts[26];
    int totalLetters;
    char mostCommon;
};

void countFrequencies(const char* text, FreqReport* report);
void printHistogram(const FreqReport* report);
int crackCaesar(const char* cipherText, char* bestPlain);