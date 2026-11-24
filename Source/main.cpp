#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Ciphers.h"
#include "Analysis.h"
#include "FileIO.h"
using namespace std;

const char* const DEFAULT_SUB_KEY = "QWERTYUIOPASDFGHJKLZXCVBNM";

// ------------------------------------------------------------ input helpers

// Reads one whole line (spaces allowed) into buffer
void readLine(const char* prompt, char* buffer, int size)
{
    cout << prompt;
    cin.getline(buffer, size);
    if (cin.eof())
        return;
    if (cin.fail())              // line was longer than the buffer
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "(Input was too long and has been cut short.)" << endl;
    }
}

// Checks that a string looks like a whole number such as 5 or -3
bool looksLikeInteger(const char* s)
{
    const char* p = s;
    if (*p == '-')
        p++;
    if (*p == '\0')
        return false;
    for (; *p != '\0'; p++)
    {
        if (*p < '0' || *p > '9')
            return false;
    }
    return true;
}

// Reads a whole number. Returns false if the user typed something else.
bool readInt(const char* prompt, int* value)
{
    char line[100];
    readLine(prompt, line, 100);
    if (!looksLikeInteger(line))
        return false;
    *value = atoi(line);
    return true;
}

// ------------------------------------------------------------ menu actions

void showMenu()
{
    cout << "\n========== CipherLab ==========" << endl;
    cout << "1. Enter text" << endl;
    cout << "2. Choose cipher and key" << endl;
    cout << "3. Encrypt current text" << endl;
    cout << "4. Decrypt current text" << endl;
    cout << "5. Frequency analysis (histogram)" << endl;
    cout << "6. Auto-crack Caesar cipher" << endl;
    cout << "7. Save session to file" << endl;
    cout << "8. Load session from file" << endl;
    cout << "9. Show current session" << endl;
    cout << "0. Exit" << endl;
}

const char* cipherName(int type)
{
    if (type == 1) return "Caesar";
    if (type == 2) return "Vigenere";
    if (type == 3) return "Substitution";
    return "None chosen";
}

void showSession(const CipherSession* s)
{
    cout << "\n--- Current session ---" << endl;
    cout << "Cipher: " << cipherName(s->cipherType) << endl;
    cout << "Key:    " << (s->key[0] == '\0' ? "(none)" : s->key) << endl;
    cout << "Text:   " << (s->text[0] == '\0' ? "(none)" : s->text) << endl;
}

void chooseCipher(CipherSession* s)
{
    cout << "\n1. Caesar (key: a number)" << endl;
    cout << "2. Vigenere (key: a word)" << endl;
    cout << "3. Substitution (key: 26 different letters)" << endl;

    int type;
    if (!readInt("Select cipher: ", &type) || type < 1 || type > 3)
    {
        cout << "Invalid cipher choice." << endl;
        return;
    }

    char input[MAX_KEY];

    if (type == 1)
    {
        int shift;
        if (!readInt("Enter shift number (e.g. 3): ", &shift))
        {
            cout << "That is not a valid number." << endl;
            return;
        }
        snprintf(s->key, MAX_KEY, "%d", shift);
    }
    else if (type == 2)
    {
        readLine("Enter keyword (letters only, e.g. LEMON): ", input, MAX_KEY);
        if (!isValidVigenereKey(input))
        {
            cout << "Invalid keyword. Use letters only, no spaces." << endl;
            return;
        }
        copyString(input, s->key, MAX_KEY);
    }
    else
    {
        readLine("Enter 26-letter key, or press Enter for the default: ", input, MAX_KEY);
        if (input[0] == '\0')
            copyString(DEFAULT_SUB_KEY, input, MAX_KEY);
        if (!isValidSubstitutionKey(input))
        {
            cout << "Invalid key. It needs exactly 26 different letters." << endl;
            return;
        }
        copyString(input, s->key, MAX_KEY);
    }

    s->cipherType = type;
    cout << "Cipher set to " << cipherName(type) << " with key " << s->key << endl;
}

void applyCipher(CipherSession* s, bool encrypt)
{
    if (s->text[0] == '\0')
    {
        cout << "No text yet. Use option 1 first." << endl;
        return;
    }
    if (s->cipherType == 0)
    {
        cout << "No cipher chosen yet. Use option 2 first." << endl;
        return;
    }

    if (s->cipherType == 1)
    {
        int shift = atoi(s->key);
        if (encrypt) caesarEncrypt(s->text, shift);
        else         caesarDecrypt(s->text, shift);
    }
    else if (s->cipherType == 2)
    {
        if (encrypt) vigenereEncrypt(s->text, s->key);
        else         vigenereDecrypt(s->text, s->key);
    }
    else
    {
        if (encrypt) substitutionEncrypt(s->text, s->key);
        else         substitutionDecrypt(s->text, s->key);
    }

    cout << (encrypt ? "Encrypted text: " : "Decrypted text: ") << s->text << endl;
}

void showFrequencies(const CipherSession* s)
{
    if (s->text[0] == '\0')
    {
        cout << "No text yet. Use option 1 first." << endl;
        return;
    }

    FreqReport report;
    countFrequencies(s->text, &report);

    if (report.totalLetters == 0)
    {
        cout << "The text contains no letters." << endl;
        return;
    }

    cout << "\nLetter frequencies:" << endl;
    printHistogram(&report);
    cout << "Total letters: " << report.totalLetters << endl;
    cout << "Most common letter: " << report.mostCommon << endl;
}

void autoCrack(CipherSession* s)
{
    if (s->text[0] == '\0')
    {
        cout << "No text yet. Use option 1 first." << endl;
        return;
    }

    FreqReport report;
    countFrequencies(s->text, &report);
    if (report.totalLetters < 20)
        cout << "Warning: the text is short, so the result may be unreliable." << endl;

    char cracked[MAX_TEXT];
    int shift = crackCaesar(s->text, cracked);

    cout << "Most likely Caesar shift: " << shift << endl;
    cout << "Decrypted text: " << cracked << endl;

    int answer;
    if (readInt("Replace the session text with this result? (1 = yes, 0 = no): ", &answer) && answer == 1)
    {
        copyString(cracked, s->text, MAX_TEXT);
        cout << "Session text updated." << endl;
    }
}

void saveToFile(const CipherSession* s)
{
    char filename[100];
    readLine("File name to save to (Enter for session.txt): ", filename, 100);
    if (filename[0] == '\0')
        copyString("session.txt", filename, 100);

    if (saveSession(filename, s))
        cout << "Session saved to " << filename << endl;
    else
        cout << "Could not save the file." << endl;
}

void loadFromFile(CipherSession* s)
{
    char filename[100];
    readLine("File name to load (Enter for session.txt): ", filename, 100);
    if (filename[0] == '\0')
        copyString("session.txt", filename, 100);

    if (loadSession(filename, s))
    {
        cout << "Session loaded from " << filename << endl;
        showSession(s);
    }
    else
        cout << "Could not load that file (missing or not a CipherLab session)." << endl;
}

// -------------------------------------------------------------------- main

int main()
{
    CipherSession session;
    resetSession(&session);

    int choice = -1;
    while (choice != 0)
    {
        showMenu();
        if (!readInt("Choice: ", &choice))
            choice = -1;
        if (cin.eof())
            break;

        switch (choice)
        {
        case 1:
            readLine("Enter text: ", session.text, MAX_TEXT);
            break;
        case 2: chooseCipher(&session);        break;
        case 3: applyCipher(&session, true);   break;
        case 4: applyCipher(&session, false);  break;
        case 5: showFrequencies(&session);     break;
        case 6: autoCrack(&session);           break;
        case 7: saveToFile(&session);          break;
        case 8: loadFromFile(&session);        break;
        case 9: showSession(&session);         break;
        case 0: cout << "Goodbye!" << endl;    break;
        default: cout << "Invalid choice, try again." << endl;
        }
    }
    return 0;
}