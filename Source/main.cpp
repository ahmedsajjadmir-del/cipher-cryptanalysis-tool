#include <iostream>
#include "Ciphers.h"
#include "Analysis.h"
using namespace std;

int main()
{
    char secret[MAX_TEXT] = "The quick brown fox jumps over the lazy dog and runs far away";
    caesarEncrypt(secret, 11);
    cout << "Intercepted: " << secret << endl;

    char cracked[MAX_TEXT];
    int shift = crackCaesar(secret, cracked);
    cout << "Shift found: " << shift << endl;
    cout << "Cracked:     " << cracked << endl;

    return 0;
}