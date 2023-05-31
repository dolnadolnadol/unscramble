#include <stdio.h>
#include <ctype.h>

void count(int letter[]) {
    int c;
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            c = tolower(c);
            letter[c - 'a']++;
        }
    }
}

void print(int letter[]) {
    int max = 0;
    for (int i = 0; i < 26; i++) {
        if (letter[i] > max) {
            max = letter[i];
        }
    }
    
    for (int i = max; i > 0; i--) {
        for (int j = 0; j < 26; j++) {
            if (letter[j] >= i) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    
    for (int i = 0; i < 26; i++) {
        printf("%c ", 'a' + i);
    }
    printf("\n");
}

int main() {
    int letter[26] = {0};
    count(letter);
    print(letter);
    
    return 0;
}
