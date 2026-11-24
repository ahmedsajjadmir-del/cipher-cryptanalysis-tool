#pragma once
#include "Analysis.h"

const int MAX_KEY = 60;      // maximum key length

// Everything the program needs to remember about one working session
struct CipherSession
{
    char text[MAX_TEXT];     // the current text
    char key[MAX_KEY];       // Caesar: the shift as text (e.g. "3"), others: the keyword/key
    int cipherType;          // 0 = none chosen, 1 = Caesar, 2 = Vigenere, 3 = Substitution
};

void resetSession(CipherSession* session);

// Both return true on success, false on failure
bool saveSession(const char* filename, const CipherSession* session);
bool loadSession(const char* filename, CipherSession* session);
