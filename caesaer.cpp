#include <cstring> // for strlen
#include <cctype> //for upper and lower case
#include <cstdlib>

using namespace std;

extern "C" {
__declspec(dllexport) char* encrypt(char* text, int key, char* result);
__declspec(dllexport) char* decrypt(char* text, int key, char* result);

char* encrypt (char* text, int key, char* result) {
    char* cipher = (char*)calloc(strlen(text) + 1, sizeof(char));
    ;
        key = (key % 26 + 26) % 26; //range of alphabet

        for (int i=0; i < strlen(text); i++ ) {
            char c = text[i];

            if (isupper(c)) {
                //apply Ceaser Cipher formula
                int x = (c - 'A' + key) % 26;
                //handle boundary condition
                x = x % 26;
                //convert to char
                c = (char)(x + 'A');
            }
            else if (islower(c)) {
                int x = (c - 'a' + key) % 26;
                x = x % 26;
                c = (char)(x + 'a');
            }
            //cipher.insert(cipher.end(), 1, c); //insert in the end
            result[i] = c;
        }
        result[strlen(text)] = '\0';
        return cipher;
    }

char* decrypt (char* text, int key, char* result) {
    char* plain = (char*)calloc(strlen(text) + 1, sizeof(char));
        key = (key % 26 + 26) % 26;

        for (int i=0; i < strlen(text); i++ ) {
            char c = text[i];

            if (isupper(c)) {
                int x = (c - 'A' - key + 26) % 26;
                if (x < 0) {
                    x += 26;
                }
                c = (char)(x + 'A');
            }
            else if (islower(c)) {
                int x = (c - 'a' - key + 26) % 26;
                if (x < 0) {
                    x += 26;
                }
                c = (char)(x + 'a');
            }
            //plain.insert(plain.end(), 1, c);
            result[i] = c;
        }
        result[strlen(text)] = '\0';
        return plain;
    }
}