#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Read content from txt file (supports multi-line and spaces)
string readFromFile(const string& filename) {
    ifstream inFile(filename);  // Open the file
    if (!inFile.is_open()) {    // Check if the file is opened successfully
        cout << "Error: Cannot open input file \"" << filename << "\"!" << endl;
        return "";
    }

    string content, line;
    while (getline(inFile, line)) {  // Read line by line
        content += line + "\n";     // Preserve line breaks and restore the original format
    }
    inFile.close();  // close the file

    cout << "Successfully read from \"" << filename << "\"!" << endl;
    cout << "Read content length: " << content.size() << " characters" << endl;
    return content;
}

// // Write the content to the txt file
bool writeToFile(const string& filename, const string& content) {
    ofstream outFile(filename);  // Open the file (overwrite if it exists, create if it does not exist)
    if (!outFile.is_open()) {    // Check if the file is opened successfully
        cout << "Error: Cannot open output file \"" << filename << "\"!" << endl;
        return false;
    }

    outFile << content;  // input
    outFile.close();     // close the file

    cout << "Successfully written to \"" << filename << "\"!" << endl;
    return true;
}

#endif // FILE_UTILS_H