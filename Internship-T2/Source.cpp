#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class CaesarCipher {
private:
    int shift;

    char shiftChar(char c, int shift) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            return (c - base + shift) % 26 + base;
        }
        return c;
    }

public:
    CaesarCipher(int shift) : shift(shift % 26) {}

    void encrypt(const string& inputFilePath, const string& outputFilePath) {
        ifstream inputFile(inputFilePath);
        ofstream outputFile(outputFilePath);

        if (!inputFile.is_open() || !outputFile.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            for (char& c : line) {
                c = shiftChar(c, shift);
            }
            outputFile << line << endl;
        }

        inputFile.close();
        outputFile.close();
    }

    void decrypt(const string& inputFilePath, const string& outputFilePath) {
        ifstream inputFile(inputFilePath);
        ofstream outputFile(outputFilePath);

        if (!inputFile.is_open() || !outputFile.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            for (char& c : line) {
                c = shiftChar(c, 26 - shift);
            }
            outputFile << line << endl;
        }

        inputFile.close();
        outputFile.close();
    }
};

void displayMenu() {
    cout << "\nCaesar Cipher Application\n";
    cout << "1. Encrypt File\n";
    cout << "2. Decrypt File\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int shift, choice;
    string inputFilePath, outputFilePath;

    cout << "Enter the shift value: ";
    cin >> shift;
    CaesarCipher cipher(shift);

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter input file path: ";
            cin >> inputFilePath;
            cout << "Enter output file path: ";
            cin >> outputFilePath;
            cipher.encrypt(inputFilePath, outputFilePath);
            cout << "File encrypted successfully." << endl;
            break;
        }
        case 2: {
            cout << "Enter input file path: ";
            cin >> inputFilePath;
            cout << "Enter output file path: ";
            cin >> outputFilePath;
            cipher.decrypt(inputFilePath, outputFilePath);
            cout << "File decrypted successfully." << endl;
            break;
        }
        case 3:
            cout << "Exiting the application." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
