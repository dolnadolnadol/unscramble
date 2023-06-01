#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 51
#define MAX_DICTIONARY_WORDS 500001

typedef struct {
    char word[MAX_WORD_LENGTH];
} DictionaryWord;

typedef struct {
    DictionaryWord words[MAX_DICTIONARY_WORDS];
    int count;
} Dictionary;

void readDictionary(const char* dictionaryFile, Dictionary* dictionary) {
    FILE* file = fopen(dictionaryFile, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open dictionary file: %s\n", dictionaryFile);
        exit(1);
    }

    char buffer[MAX_WORD_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        strcpy(dictionary->words[dictionary->count].word, buffer);
        dictionary->count++;
    }
    printf("its read %d words\n", dictionary->count);

    fclose(file);
}
void countCharacters(const char* word, int* counts) {
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        counts[i] = 0;
    }

    for (int i = 0; word[i] != '\0'; i++) {
        counts[word[i] - 'a']++;
    }
}
int compareWords(const char* word1, const char* word2) {
    int counts1[MAX_WORD_LENGTH] = { 0 };
    int counts2[MAX_WORD_LENGTH] = { 0 };

    countCharacters(word1, counts1);
    countCharacters(word2, counts2);

    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        if (counts1[i] != counts2[i]) {
            return counts1[i] - counts2[i];
        }
    }

    return 0;
}

// void unscrambleWords(const Dictionary* dictionary, const char* jumblesFile) {
//     FILE* file = fopen(jumblesFile, "r");
//     if (file == NULL) {
//         fprintf(stderr, "Failed to open jumbles file: %s\n", jumblesFile);
//         exit(1);
//     }
//     char buffer[MAX_WORD_LENGTH];
//     while (fgets(buffer, sizeof(buffer), file) != NULL) {
//         buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
//         char sortedWord[MAX_WORD_LENGTH];
//         strcpy(sortedWord, buffer);
//         qsort(sortedWord, strlen(sortedWord), sizeof(char), compareWords);
//         printf("%s: ", buffer);
//         int matchCount = 0;
//         for (int i = 0; i < dictionary->count; i++) {
//             char sortedDictionaryWord[MAX_WORD_LENGTH];
//             strcpy(sortedDictionaryWord, dictionary->words[i].word);
//             qsort(sortedDictionaryWord, strlen(sortedDictionaryWord), sizeof(char), compareWords);
//             if (strcmp(sortedWord, sortedDictionaryWord) == 0) {
//                 if (matchCount > 0) {
//                     printf(" ");
//                 }
//                 printf("%s", dictionary->words[i].word);
//                 matchCount++;
//             }
//         }
//         if (matchCount == 0) {
//             printf("NO MATCHES");
//         }
//         printf("\n");
//     }
//     fclose(file);
// }
void unscrambleWords(const Dictionary* dictionary, const char* jumblesFile) {
    FILE* file = fopen(jumblesFile, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open jumbles file: %s\n", jumblesFile);
        exit(1);
    }

    char buffer[MAX_WORD_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        int counts[MAX_WORD_LENGTH] = { 0 };
        countCharacters(buffer, counts);

        printf("%s: ", buffer);

        int matchCount = 0;
        for (int i = 0; i < dictionary->count; i++) {
            if (compareWords(buffer, dictionary->words[i].word) == 0) {
                if (matchCount > 0) {
                    printf(" ");
                }
                printf("%s", dictionary->words[i].word);
                matchCount++;
            }
        }
        if (matchCount == 0) {
            printf("NO MATCHES");
        }

        printf("\n");
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: unscramble <dictionary> <jumbles>\n");
        printf("Note that");
        return 1;
    }

    const char* dictionaryFile = argv[1];
    const char* jumblesFile = argv[2];

    Dictionary dictionary;
    dictionary.count = 0;
    printf("Loading\n");
    fflush(stdout);

    readDictionary(dictionaryFile, &dictionary);
    printf("Dictionary loaded with %d words\n", dictionary.count);
    fflush(stdout);

    // unscrambleWords(&dictionary, jumblesFile);

    return 0;
}

