#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_length 50
#define max_dic 500000

int compare(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int isAnagram(const char *word, const char *jumble) {
    char sortedWord[max_length];
    char sortedJumble[max_length];

    strcpy(sortedWord, word);
    strcpy(sortedJumble, jumble);

    qsort(sortedWord, strlen(sortedWord), sizeof(char), compare);
    qsort(sortedJumble, strlen(sortedJumble), sizeof(char), compare);

    return strcmp(sortedWord, sortedJumble) == 0;
}

void unscrambleWords(FILE *dictionaryFile, FILE *jumbleFile) {
    char **dictionary = malloc(max_dic * sizeof(char *));
    char jumble[max_length];
    int numW = 0;

    // Read dictionary words
    char word[max_length];
    while (fgets(word, max_length, dictionaryFile) != NULL) {
        word[strcspn(word, "\n")] = '\0';  // Remove newline character
        dictionary[numW] = strdup(word);
        numW++;

        if (numW >= max_dic) {
            break;
        }
    }

    // Sort the dictionary words
    qsort(dictionary, numW, sizeof(char *), compare);

    // Read jumbled words
    while (fgets(jumble, max_length, jumbleFile) != NULL) {
        jumble[strcspn(jumble, "\n")] = '\0';  // Remove newline character

        printf("%s: ", jumble);

        int i, match = 0;
        for (i = 0; i < numW; i++) {
            if (isAnagram(dictionary[i], jumble)) {
                printf("%s ", dictionary[i]);
                match = 1;
            }
        }

        if (!match) {
            printf("NO MATCHES");
        }

        printf("\n");
    }

    // Free memory
    for (int i = 0; i < numW; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
}

int main(int argc, char *argv[]) {
    FILE *dictionaryFile;
    FILE *jumbleFile;

    if (argc < 3) {
        printf("Usage: %s <dictionary> <jumbles>\n", argv[0]);
        return 1;
    }

    dictionaryFile = fopen(argv[1], "r");
    jumbleFile = fopen(argv[2], "r");

    if (dictionaryFile == NULL || jumbleFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    unscrambleWords(dictionaryFile, jumbleFile);

    fclose(dictionaryFile);
    fclose(jumbleFile);

    return 0;
}
