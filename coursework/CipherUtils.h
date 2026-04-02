#ifndef CIPHER_UTILS_H
#define CIPHER_UTILS_H

#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>

using namespace std;

// Encryption of the second method (Shift Cipher)
string Substitution(string s, int n) {
    n = n % 26;
    for (char& c : s) {
        if (isupper(c)) {
            c = (c - 'A' + n) % 26 + 'A';
        } else if (islower(c)) {
            c = (c - 'a' + n) % 26 + 'a';
        }
    }
    return s;
}

// Decryption of the second method (Shift Cipher)
string Decryption1(string s, int n) {
    n = n % 26;
    for (char& c : s) {
        if (isupper(c)) {
            c = (c - 'A' - n + 26) % 26 + 'A';
        } else if (islower(c)) {
            c = (c - 'a' - n + 26) % 26 + 'a';
        }
    }
    return s;
}

// Input and validate the user-defined cipher table
string inputCipherTable() {
    string cipherTable;
    while (true) {
        cout << "please input the mapping (26 lowercase letters, no duplicates):" << endl;
        cin >> cipherTable;

        if (cipherTable.size() != 26) {
            cout << "Error: length is " << cipherTable.size() << ", must be 26" << endl;
            continue;
        }

        bool hasInvalidChar = false;
        for (char c : cipherTable) {
            if (!islower(c)) {
                hasInvalidChar = true;
                break;
            }
        }
        if (hasInvalidChar) {
            cout << "Error: only input lowercase letters" << endl;
            continue;
        }

        cout << "Succeed! Your cipher table is valid." << endl;
        break;
    }
    return cipherTable;
}

// Encryption of the first method (custom mapping)
string encrypt(const string& plaintext, const string& plainTable, const string& cipherTable) {
    string ciphertext;
    for (char c : plaintext) {
        if (islower(c)) {
            size_t idx = plainTable.find(c);
            ciphertext += (idx != string::npos) ? cipherTable[idx] : c;
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

// Decryption of the first method (custom mapping)
string decrypt(const string& ciphertext, const string& plainTable, const string& cipherTable) {
    string plaintext;
    for (char c : ciphertext) {
        if (islower(c)) {
            size_t idx = cipherTable.find(c);
            plaintext += (idx != string::npos) ? plainTable[idx] : c;
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

#endif // CIPHER_UTILS_H