#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

extern "C" {
__declspec(dllexport) char* encrypt(char* text, int key, char* result);
__declspec(dllexport) char* decrypt(char* text, int key, char* result);

    char* encrypt(char* text, int key, char* result) {
        key = (key % 26 + 26) % 26; // ensure key is within range of alphabet

        int len = strlen(text);
        for (int i = 0; i < len; i++) {
            char c = text[i];

            if (isalpha(c)) {
                if (isupper(c)) {
                    int x = (c - 'A' + key) % 26;
                    result[i] = (char)('A' + x);
                }
                else if (islower(c)) {
                    int x = (c - 'a' + key) % 26;
                    result[i] = (char)('a' + x);
                }
            }
            else {
                result[i] = c; // copy non-alphabetic characters as is
            }
        }
        result[len] = '\0';
        return result;
    }

    char* decrypt(char* text, int key, char* result) {
        key = (key % 26 + 26) % 26; // ensure key is within range of alphabet

        int len = strlen(text);
        for (int i = 0; i < len; i++) {
            char c = text[i];

            if (isalpha(c)) {
                if (isupper(c)) {
                    int x = (c - 'A' - key + 26) % 26;
                    result[i] = (char)('A' + x);
                }
                else if (islower(c)) {
                    int x = (c - 'a' - key + 26) % 26;
                    result[i] = (char)('a' + x);
                }
            }
            else {
                result[i] = c; // copy non-alphabetic characters as is
            }
        }
        result[len] = '\0';
        return result;
    }
}