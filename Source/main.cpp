#include <iostream>
#include "Ciphers.h"
using namespace std;

int main()
{
    char message[500] = "Hello, World!";

    cout << "Original:  " << message << endl;

    caesarEncrypt(message, 3);
    cout << "Encrypted: " << message << endl;

    caesarDecrypt(message, 3);
    cout << "Decrypted: " << message << endl;

    return 0;
}
