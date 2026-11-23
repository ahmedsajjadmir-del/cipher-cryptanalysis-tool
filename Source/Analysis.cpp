// Typical percentage of each letter in English text (A..Z)
const double ENGLISH_FREQ[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15, 0.77, 4.03, 2.41,
    6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15, 1.97, 0.07
};

// Copies text using pointers (stops before the buffer overflows)
static void copyText(const char* from, char* to)
{
    int i = 0;
    for (const char* p = from; *p != '\0' && i < MAX_TEXT - 1; p++, i++)
        to[i] = *p;
    to[i] = '\0';
}

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

// Tries all 26 shifts, returns the best one and writes the decrypted text to bestPlain
int crackCaesar(const char* cipherText, char* bestPlain)
{
    double bestScore = -1;
    int bestShift = 0;

    for (int shift = 0; shift < 26; shift++)
    {
        char trial[MAX_TEXT];
        copyText(cipherText, trial);
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

    copyText(cipherText, bestPlain);
    caesarDecrypt(bestPlain, bestShift);
    return bestShift;
