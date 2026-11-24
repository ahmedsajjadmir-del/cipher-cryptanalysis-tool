#include <iostream>
#include "Analysis.h"
#include "Ciphers.h"
using namespace std;

void copyString(const char* from, char* to, int size)
{
    int i = 0;
    for (const char* p = from; *p != '\0' && i < size - 1; p++, i++)
        to[i] = *p;
    to[i] = '\0';
}

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

// Typical percentage of each letter in English text (A..Z)
const double ENGLISH_FREQ[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15, 0.77, 4.03, 2.41,
    6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15, 1.97, 0.07
};

// Lower score = letter frequencies closer to normal English
static double chiSquared(const FreqReport* report)
{
    if (report->totalLetters == 0)
        return 0;

    double score = 0;
    for (int i = 0; i < 26; i++)
    {
        double expected = ENGLISH_FREQ[i] / 100.0 * report->totalLetters;
        double diff = report->counts[i] - expected;
        score += diff * diff / expected;
    }
    return score;
}

int crackCaesar(const char* cipherText, char* bestPlain)
{
    double bestScore = -1;
    int bestShift = 0;

    for (int shift = 0; shift < 26; shift++)
    {
        char trial[MAX_TEXT];
        copyString(cipherText, trial, MAX_TEXT);
        caesarDecrypt(trial, shift);

        FreqReport r;
        countFrequencies(trial, &r);
        double score = chiSquared(&r);

        if (bestScore < 0 || score < bestScore)
        {
            bestScore = score;
            bestShift = shift;
        }
    }

    copyString(cipherText, bestPlain, MAX_TEXT);
    caesarDecrypt(bestPlain, bestShift);
    return bestShift;
}