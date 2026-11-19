#include <iostream>
#include "Ciphers.h"
#include "Analysis.h"
using namespace std;

int main()
{
    char message[500] = "Hello, World!";

    cout << "Original:  " << message << endl;

    caesarEncrypt(message, 3);
    cout << "Encrypted: " << message << endl;

    caesarDecrypt(message, 3);
    cout << "Decrypted: " << message << endl;

    FreqReport report;
    countFrequencies(message, &report);
    cout << "\nLetter frequencies:" << endl;
    printHistogram(&report);
    cout << "Most common letter: " << report.mostCommon << endl;

    return 0;
}
