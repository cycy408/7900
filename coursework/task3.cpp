#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cctype>
#include <fstream>  // 新增：文件操作头文件
using namespace std;

// 第二种方法的加密（移位密码）
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

// 第二种方法的解密（移位密码）
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

// 输入并校验用户自定义的密文表（你的原始函数）
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

// 第一种方法加密（自定义映射）
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

// 第一种方法解密（自定义映射）
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

// 从txt文件读取内容（支持多行、带空格）
string readFromFile(const string& filename) {
    ifstream inFile(filename);  // 打开文件
    if (!inFile.is_open()) {    // 检查文件是否打开成功
        cout << "Error: Cannot open input file \"" << filename << "\"!" << endl;
        return "";
    }

    string content, line;
    while (getline(inFile, line)) {  // 逐行读取
        content += line + "\n";      // 保留换行符，还原原始格式
    }
    inFile.close();  // 关闭文件

    cout << "Successfully read from \"" << filename << "\"!" << endl;
    cout << "Read content length: " << content.size() << " characters" << endl;
    return content;
}

// 将内容写入txt文件
bool writeToFile(const string& filename, const string& content) {
    ofstream outFile(filename);  // 打开文件（若存在则覆盖，若不存在则创建）
    if (!outFile.is_open()) {    // 检查文件是否打开成功
        cout << "Error: Cannot open output file \"" << filename << "\"!" << endl;
        return false;
    }

    outFile << content;  // 写入内容
    outFile.close();     // 关闭文件

    cout << "Successfully written to \"" << filename << "\"!" << endl;
    return true;
}

int main() {
    int choice = 1;  // 初始化choice，让循环能启动
    const string plainTable = "abcdefghijklmnopqrstuvwxyz";  // 固定明文表（全局复用）
    string savedCipherTable;  // 保存加密时的密文表，用于解密

    // 主循环：选择0才退出
    while (choice != 0) {
        cout << "\n===== Encryption and Decryption Machine =====" << endl;
        cout << "1. Encryption (read from txt, write to txt)" << endl;
        cout << "2. Decryption (read from txt, write to txt)" << endl;
        cout << "0. Quit (exit)" << endl;
        cout << "=============================================================" << endl;
        cout << "Please choose the number: ";
        cin >> choice;
        cout << endl;

        // 加密分支
        if (choice == 1) {
            int choice1;
            cout << "Choose encryption method:" << endl;
            cout << "1. Custom Mapping Cipher (substitution)" << endl;
            cout << "2. Shift Cipher (transposition)" << endl;
            cout << "Please choose the number: ";
            cin >> choice1;
            cout << endl;

            // 读取输入文件
            string inputFilename;
            cout << "Input the path/name of the plaintext file (e.g., plaintext.txt): ";
            cin >> inputFilename;
            string plaintext = readFromFile(inputFilename);
            if (plaintext.empty()) {  // 读取失败则跳过
                continue;
            }
            cout << "----------------------------------------" << endl;

            string ciphertext;
            if (choice1 == 2) {
                // 移位密码加密
                cout << "Input shift parameter n (integer): ";
                int n;
                cin >> n;
                ciphertext = Substitution(plaintext, n);
                cout << "Encryption completed!" << endl;
            } else if (choice1 == 1) {
                // 自定义映射加密
                cout << "Plaintext table (fixed): " << plainTable << endl;
                cout << "----------------------------------------" << endl;
                savedCipherTable = inputCipherTable();  // 输入并保存密文表
                cout << "----------------------------------------" << endl;
                ciphertext = encrypt(plaintext, plainTable, savedCipherTable);
                cout << "Encryption completed!" << endl;
            } else {
                cout << "Error: Invalid choice! Please choose 1 or 2." << endl;
                continue;
            }

            // 写入输出文件
            string outputFilename;
            cout << "Input the path/name of the ciphertext file (e.g., ciphertext.txt): ";
            cin >> outputFilename;
            if (writeToFile(outputFilename, ciphertext)) {
                cout << "Encryption success! Result saved to \"" << outputFilename << "\"" << endl;
            }

        // 解密分支
        } else if (choice == 2) {
            int choice1;
            cout << "Choose decryption method:" << endl;
            cout << "1. Custom Mapping Cipher (substitution)" << endl;
            cout << "2. Shift Cipher (transposition)" << endl;
            cout << "Please choose the number: ";
            cin >> choice1;
            cout << endl;

            // 读取输入文件
            string inputFilename;
            cout << "Input the path/name of the ciphertext file (e.g., ciphertext.txt): ";
            cin >> inputFilename;
            string ciphertext = readFromFile(inputFilename);
            if (ciphertext.empty()) {  // 读取失败则跳过
                continue;
            }
            cout << "----------------------------------------" << endl;

            string decryptedText;
            if (choice1 == 2) {
                // 移位密码解密（尝试所有26种可能，选择一种写入文件）
                cout << "Trying all 26 shift possibilities (n=0~25):" << endl;
                cout << "----------------------------------------" << endl;
                vector<string> allResults;
                for (int n = 0; n < 26; n++) {
                    string res = Decryption1(ciphertext, n);
                    allResults.push_back(res);
                    cout << "n=" << n << ": " << (res.size() > 50 ? res.substr(0, 50) + "..." : res) << endl;
                }
                cout << "----------------------------------------" << endl;

                // 让用户选择正确的n，写入文件
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
                // 自定义映射解密
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

            // 写入输出文件
            string outputFilename;
            cout << "Input the path/name of the plaintext file (e.g., decrypted.txt): ";
            cin >> outputFilename;
            if (writeToFile(outputFilename, decryptedText)) {
                cout << "Decryption success! Result saved to \"" << outputFilename << "\"" << endl;
            }

        // 退出分支
        } else if (choice == 0) {
            cout << "Thanks for using!" << endl;
        } else {
            cout << "Error: Invalid choice! Please choose 0, 1, or 2." << endl;
        }
    }

    return 0;
}