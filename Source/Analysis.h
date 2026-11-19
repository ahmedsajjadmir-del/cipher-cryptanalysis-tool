

#pragma once

struct FreqReport
{
    int counts[26];      // counts[0] = how many A/a, counts[1] = B/b, ...
    int totalLetters;    // total letters found
    char mostCommon;     // the most frequent letter (uppercase), '-' if none
};

void countFrequencies(const char* text, FreqReport* report);
void printHistogram(const FreqReport* report);
