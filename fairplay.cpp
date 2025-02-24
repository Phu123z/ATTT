#include <iostream>

using namespace std;

const int SIZE = 5;

// Tạo bảng mã hóa từ khóa
void generateKeySquare(char keySquare[SIZE][SIZE], const char key[]) {
    bool exists[26] = {false}; 
    int index = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I';  
        if (!exists[c - 'A']) {
            keySquare[index / SIZE][index % SIZE] = c;
            exists[c - 'A'] = true;
            index++;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!exists[c - 'A']) {
            keySquare[index / SIZE][index % SIZE] = c;
            exists[c - 'A'] = true;
            index++;
        }
    }
}

// Tìm vị trí của chữ cái trong bảng
void findPosition(const char keySquare[SIZE][SIZE], char c, int &row, int &col) {
    if (c == 'J') c = 'I';  
    for (row = 0; row < SIZE; row++)
        for (col = 0; col < SIZE; col++)
            if (keySquare[row][col] == c)
                return;
}

// Xử lý bản rõ, chia thành từng cặp
void prepareText(const char text[], char pairs[][2], int &pairCount) {
    pairCount = 0;
    char temp[100] = {0};
    int len = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        char c = toupper(text[i]);
        if (c >= 'A' && c <= 'Z') {
            if (c == 'J') c = 'I';
            temp[len++] = c;
        }
    }

    for (int i = 0; i < len; i++) {
        char first = temp[i];
        char second = (i + 1 < len) ? temp[i + 1] : 'X';

        if (first == second) second = 'X';
        else i++;

        pairs[pairCount][0] = first;
        pairs[pairCount][1] = second;
        pairCount++;
    }
}

// Mã hóa
void encrypt(const char keySquare[SIZE][SIZE], char pairs[][2], int pairCount, char cipherText[]) {
    int index = 0;

    for (int i = 0; i < pairCount; i++) {
        int row1, col1, row2, col2;
        findPosition(keySquare, pairs[i][0], row1, col1);
        findPosition(keySquare, pairs[i][1], row2, col2);

        if (row1 == row2) { 
            cipherText[index++] = keySquare[row1][(col1 + 1) % SIZE];
            cipherText[index++] = keySquare[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) { 
            cipherText[index++] = keySquare[(row1 + 1) % SIZE][col1];
            cipherText[index++] = keySquare[(row2 + 1) % SIZE][col2];
        } else { 
            cipherText[index++] = keySquare[row1][col2];
            cipherText[index++] = keySquare[row2][col1];
        }
    }
    cipherText[index] = '\0';
}

int main() {
    char plaintext[100], key[100], keySquare[SIZE][SIZE], pairs[50][2], cipherText[100];
    int pairCount;

    cout << "Nhap ban ro: ";
    cin.getline(plaintext, 100);
    cout << "Nhap khoa: ";
    cin.getline(key, 100);

    generateKeySquare(keySquare, key);
    prepareText(plaintext, pairs, pairCount);
    encrypt(keySquare, pairs, pairCount, cipherText);

    cout << "Ban ma: " << cipherText << endl;
    return 0;
}
