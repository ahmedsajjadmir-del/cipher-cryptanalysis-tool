#pragma once

// Caesar cipher: shifts each letter by 'shift' positions
void caesarEncrypt(char* text, int shift);
void caesarDecrypt(char* text, int shift);

// Vigenere cipher: key must be letters only (e.g. "LEMON")
bool isValidVigenereKey(const char* key);
void vigenereEncrypt(char* text, const char* key);
void vigenereDecrypt(char* text, const char* key);

// Substitution cipher: key must be 26 different letters (a scrambled alphabet)
bool isValidSubstitutionKey(const char* key);
void substitutionEncrypt(char* text, const char* key);
void substitutionDecrypt(char* text, const char* key);