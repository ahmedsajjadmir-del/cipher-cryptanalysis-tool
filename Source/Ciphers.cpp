#include "Ciphers.h"

// Returns 0-25 for a letter (A/a = 0), or -1 if the character is not a letter
static int letterIndex(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    return -1;
}

// Builds a letter from an index 0-25, keeping the case of the original character
static char makeLetter(char original, int index)
{
    if (original >= 'a' && original <= 'z')
        return static_cast<char>('a' + index);
    return static_cast<char>('A' + index);
}

// ---------------------------------------------------------------- Caesar

void caesarEncrypt(char* text, int shift)
{
    shift = ((shift % 26) + 26) % 26;   // keep the shift between 0 and 25

    for (char* p = text; *p != '\0'; p++)   // pointer walks through the text
    {
        int idx = letterIndex(*p);
        if (idx != -1)
            *p = makeLetter(*p, (idx + shift) % 26);
        // spaces, digits and punctuation stay unchanged
    }
}

void caesarDecrypt(char* text, int shift)
{
    shift = ((shift % 26) + 26) % 26;
    caesarEncrypt(text, 26 - shift);
}

// -------------------------------------------------------------- Vigenere

bool isValidVigenereKey(const char* key)
{
    if (*key == '\0')
        return false;                    // empty key is not allowed

    for (const char* p = key; *p != '\0'; p++)
    {
        if (letterIndex(*p) == -1)
            return false;                // only letters allowed
    }
    return true;
}

// direction = +1 to encrypt, -1 to decrypt
static void vigenere(char* text, const char* key, int direction)
{
    if (!isValidVigenereKey(key))
        return;

    const char* k = key;                 // pointer into the key
    for (char* p = text; *p != '\0'; p++)
    {
        int idx = letterIndex(*p);
        if (idx == -1)
            continue;                    // non-letters do not use up a key letter

        int shift = letterIndex(*k) * direction;
        int newIdx = ((idx + shift) % 26 + 26) % 26;
        *p = makeLetter(*p, newIdx);

        k++;
        if (*k == '\0')
            k = key;                     // go back to the start of the key
    }
}

void vigenereEncrypt(char* text, const char* key)
{
    vigenere(text, key, 1);
}

void vigenereDecrypt(char* text, const char* key)
{
    vigenere(text, key, -1);
}

// ---------------------------------------------------------- Substitution

bool isValidSubstitutionKey(const char* key)
{
    bool seen[26] = { false };
    int count = 0;

    for (const char* p = key; *p != '\0'; p++)
    {
        int idx = letterIndex(*p);
        if (idx == -1)
            return false;                // only letters allowed
        if (seen[idx])
            return false;                // each letter may appear only once
        seen[idx] = true;
        count++;
    }
    return count == 26;
}

void substitutionEncrypt(char* text, const char* key)
{
    if (!isValidSubstitutionKey(key))
        return;

    for (char* p = text; *p != '\0'; p++)
    {
        int idx = letterIndex(*p);
        if (idx != -1)
            *p = makeLetter(*p, letterIndex(key[idx]));   // A -> key[0], B -> key[1], ...
    }
}

void substitutionDecrypt(char* text, const char* key)
{
    if (!isValidSubstitutionKey(key))
        return;

    // Build the reverse mapping: inverse[cipherLetter] = plainLetter
    int inverse[26];
    for (int i = 0; i < 26; i++)
        inverse[letterIndex(key[i])] = i;

    for (char* p = text; *p != '\0'; p++)
    {
        int idx = letterIndex(*p);
        if (idx != -1)
            *p = makeLetter(*p, inverse[idx]);
    }
}