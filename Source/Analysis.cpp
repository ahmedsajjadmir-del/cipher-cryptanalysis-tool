#include <iostream>
#include "Analysis.h"
using namespace std;

void countFrequencies(const char* text, FreqReport* report)
{
    for (int i = 0; i < 26; i++)
        report->counts[i] = 0;
    report->totalLetters = 0;

    // pointer walks through the text, counting each letter
    for (const char* p = text; *p != '\0'; p++)
    {
        if (*p >= 'A' && *p <= 'Z')
            report->counts[*p - 'A']++;
        else if (*p >= 'a' && *p <= 'z')
            report->counts[*p - 'a']++;
    }

    int maxIndex = 0;
    for (int i = 0; i < 26; i++)
    {
        report->totalLetters += report->counts[i];
        if (report->counts[i] > report->counts[maxIndex])
            maxIndex = i;
    }

    if (report->totalLetters > 0)
        report->mostCommon = static_cast<char>('A' + maxIndex);
    else
        report->mostCommon = '-';
}

void printHistogram(const FreqReport* report)
{
    for (int i = 0; i < 26; i++)
    {
        if (report->counts[i] == 0)
            continue;   // skip letters that never appear

        cout << static_cast<char>('A' + i) << " | ";
        for (int j = 0; j < report->counts[i]; j++)
            cout << '#';
        cout << " (" << report->counts[i] << ")" << endl;
    }
}