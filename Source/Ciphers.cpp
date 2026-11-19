#include "Ciphers.h"

void caesarEncrypt(char* text, int shift)
{
    shift = ((shift % 26) + 26) % 26;   // keep the shift between 0 and 25

    for (char* p = text; *p != '\0'; p++)   // pointer walks through the text
    {
        if (*p >= 'A' && *p <= 'Z')
            *p = 'A' + (*p - 'A' + shift) % 26;
        else if (*p >= 'a' && *p <= 'z')
            *p = 'a' + (*p - 'a' + shift) % 26;
        // anything else (spaces, digits, punctuation) stays unchanged
    }
}

void caesarDecrypt(char* text, int shift)
{
    caesarEncrypt(text, 26 - (((shift % 26) + 26) % 26));
}
