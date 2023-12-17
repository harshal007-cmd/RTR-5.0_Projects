#include <stdio.h>
#include <string.h>

void reverseWord(char word[], int start, int end) {
    while (start < end) {
        char temp = word[start];
        word[start] = word[end];
        word[end] = temp;
        start++;
        end--;
    }
}

void reverseWords(char str[]) {
    int length = strlen(str);

    // Reverse each individual word
    int start = 0;
    for (int i = 0; i <= length; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            // Found a word boundary, reverse the word
            int end = i - 1;
            reverseWord(str, start, end);
            start = i + 1; // Move to the next word
        }
    }
}

int main() {
    // Example usage
    char inputStr[] = "Hardcoded string reversal";
    printf("Original String: %s\n", inputStr);

    // Reverse each word in the string
    reverseWords(inputStr);

    printf("Reversed Words: %s\n", inputStr);

    return 0;
}
