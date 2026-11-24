#pragma once

const int MAX_TEXT = 500;    // maximum text length used across the project

struct FreqReport
{
    int counts[26];      // counts[0] = how many A/a, counts[1] = B/b, ...
    int totalLetters;    // total letters found
    char mostCommon;     // the most frequent letter (uppercase), '-' if none
};

// Copies a string using pointers, never writing more than 'size' characters
void copyString(const char* from, char* to, int size);

void countFrequencies(const char* text, FreqReport* report);
void printHistogram(const FreqReport* report);

// Tries all 26 Caesar shifts, returns the most likely one and writes the
// decrypted text into bestPlain (which must hold MAX_TEXT characters)
int crackCaesar(const char* cipherText, char* bestPlain);