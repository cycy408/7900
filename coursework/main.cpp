#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cctype>
#include <fstream>  
#include "CipherUtils.h"
#include "FileUtils.h"

using namespace std;

int main() {
    int choice = 1;  // Initialize the variable 'choice' to enable loop execution
    const string plainTable = "abcdefghijklmnopqrstuvwxyz";  // Fixed plaintext table (reused globally)
    string savedCipherTable;  // Save the cipher table used for encryption for decryption purposes
   // Main loop: exit only when 0 is selected
    while (choice != 0) {
        cout << "\n===== Encryption and Decryption Machine =====" << endl;
        cout << "1. Encryption (read from txt, write to txt)" << endl;
        cout << "2. Decryption (read from txt, write to txt)" << endl;
        cout << "0. Quit (exit)" << endl;
        cout << "=============================================================" << endl;
        cout << "Please choose the number: ";
        cin >> choice;
        cout << endl;

        //Encryption
        if (choice == 1) {
            int choice1;
            cout << "Choose encryption method:" << endl;
            cout << "1. Custom Mapping Cipher (substitution)" << endl;
            cout << "2. Shift Cipher (transposition)" << endl;
            cout << "Please choose the number: ";
            cin >> choice1;
            cout << endl;

            // read the input txt
            string inputFilename;
            cout << "Input the path/name of the plaintext file (e.g., plaintext.txt): ";
            cin >> inputFilename;
            string plaintext = readFromFile(inputFilename);
            if (plaintext.empty()) {  // skip if could not read
                continue;
            }
            cout << "----------------------------------------" << endl;

            string ciphertext;
            if (choice1 == 2) {
                // Shift Cipher encryption
                cout << "Input shift parameter n (integer): ";
                int n;
                cin >> n;
                ciphertext = Substitution(plaintext, n);
                cout << "Encryption completed!" << endl;
            } else if (choice1 == 1) {
                // Custom mapping encryption
                cout << "Plaintext table (fixed): " << plainTable << endl;
                cout << "----------------------------------------" << endl;
                savedCipherTable = inputCipherTable();  // Input and save the cipher table
                cout << "----------------------------------------" << endl;
                ciphertext = encrypt(plaintext, plainTable, savedCipherTable);
                cout << "Encryption completed!" << endl;
            } else {
                cout << "Error: Invalid choice! Please choose 1 or 2." << endl;
                continue;
            }

            // write in output file
            string outputFilename;
            cout << "Input the path/name of the ciphertext file (e.g., ciphertext.txt): ";
            cin >> outputFilename;
            if (writeToFile(outputFilename, ciphertext)) {
                cout << "Encryption success! Result saved to \"" << outputFilename << "\"" << endl;
            }

       // Decryption branch
        } else if (choice == 2) {
            int choice1;
            cout << "Choose decryption method:" << endl;
            cout << "1. Custom Mapping Cipher (substitution)" << endl;
            cout << "2. Shift Cipher (transposition)" << endl;
            cout << "Please choose the number: ";
            cin >> choice1;
            cout << endl;

            // read the input file
            string inputFilename;
            cout << "Input the path/name of the ciphertext file (e.g., ciphertext.txt): ";
            cin >> inputFilename;
            string ciphertext = readFromFile(inputFilename);
            if (ciphertext.empty()) {  // skip if could not read
            }
            cout << "----------------------------------------" << endl;

            string decryptedText;
            if (choice1 == 2) {
                // Shift Cipher decryption (try all 26 possible shifts and select one to write to the file)
                cout << "Trying all 26 shift possibilities (n=0~25):" << endl;
                cout << "----------------------------------------" << endl;
                vector<string> allResults;
                for (int n = 0; n < 26; n++) {
                    string res = Decryption1(ciphertext, n);
                    allResults.push_back(res);
                    cout << "n=" << n << ": " << (res.size() > 50 ? res.substr(0, 50) + "..." : res) << endl;
                }
                cout << "----------------------------------------" << endl;

                // Let the user select the correct shift value 'n' and write it to the file
                int selectedN;
                while (true) {
                    cout << "Input the correct n (0~25) to save: ";
                    cin >> selectedN;
                    if (selectedN >= 0 && selectedN < 26) {
                        decryptedText = allResults[selectedN];
                        break;
                    }
                    cout << "Error: n must be between 0 and 25! Please re-enter." << endl;
                }
            } else if (choice1 == 1) {
                // Custom mapping decryption
                if (savedCipherTable.empty()) {
                    cout << "Error: No saved cipher table! Please enter the cipher table." << endl;
                    savedCipherTable = inputCipherTable();
                }
                decryptedText = decrypt(ciphertext, plainTable, savedCipherTable);
                cout << "Decryption completed!" << endl;
            } else {
                cout << "Error: Invalid choice! Please choose 1 or 2." << endl;
                continue;
            }

            // write in output file
            string outputFilename;
            cout << "Input the path/name of the plaintext file (e.g., decrypted.txt): ";
            cin >> outputFilename;
            if (writeToFile(outputFilename, decryptedText)) {
                cout << "Decryption success! Result saved to \"" << outputFilename << "\"" << endl;
            }

        // quit
        } else if (choice == 0) {
            cout << "Thanks for using!" << endl;
        } else {
            cout << "Error: Invalid choice! Please choose 0, 1, or 2." << endl;
        }
    }

    return 0;
}