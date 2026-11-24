#include <fstream>
#include <cstdlib>
#include <cstring>
#include "FileIO.h"
using namespace std;

const char* const FILE_HEADER = "CIPHERLAB_SESSION";

void resetSession(CipherSession* session)
{
    session->text[0] = '\0';
    session->key[0] = '\0';
    session->cipherType = 0;
}

bool saveSession(const char* filename, const CipherSession* session)
{
    ofstream out(filename);
    if (!out)
        return false;

    out << FILE_HEADER << endl;
    out << session->cipherType << endl;
    out << session->key << endl;
    out << session->text << endl;

    return static_cast<bool>(out);
}

bool loadSession(const char* filename, CipherSession* session)
{
    ifstream in(filename);
    if (!in)
        return false;

    CipherSession temp;      // read into a temporary copy first
    resetSession(&temp);
    char line[100];

    in.getline(line, 100);
    if (!in || strcmp(line, FILE_HEADER) != 0)
        return false;        // not a CipherLab session file

    in.getline(line, 100);
    if (!in)
        return false;
    temp.cipherType = atoi(line);
    if (temp.cipherType < 0 || temp.cipherType > 3)
        return false;

    in.getline(temp.key, MAX_KEY);
    if (!in)
        return false;

    in.getline(temp.text, MAX_TEXT);
    if (!in)
        return false;

    *session = temp;         // only replace the real session if everything worked
    return true;
}