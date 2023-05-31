// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <string.h>

// // #define MAX_WORD_LENGTH 51
// // #define MAX_DICTIONARY_WORDS 500000

// // typedef struct dic1{
// //     char word[MAX_WORD_LENGTH];
// // } DictionaryWord;

// // typedef struct dic2{
// //     DictionaryWord words[MAX_DICTIONARY_WORDS];
// //     int count;
// // } Dictionary;

// // int main(int argc, char *argv[]){
// //     Dictionary dictionary;
// //     dictionary.count = 0;
// //     FILE *dictionaryFile = fopen("dictionary.txt", "r");
// //     if (dictionaryFile == NULL) {
// //         printf("Could not open dictionary file.\n");
// //         return 1;
// //     }else{
// //         printf("Opened dictionary file.\n");
// //     }
// //     wait(200);
// //     // printf("How");
// // }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_WORD_LENGTH 51
// #define MAX_DICTIONARY_WORDS 500000

// typedef struct dic1 {
//     char word[MAX_WORD_LENGTH];
// } DictionaryWord;

// typedef struct dic2 {
//     DictionaryWord words[MAX_DICTIONARY_WORDS];
//     int count;
// } Dictionary;

// int main(int argc, char *argv[]) {
//     // Dictionary dictionary;
//     // dictionary.count = 0;
//     FILE *dictionaryFile = fopen("dictionary.txt", "r");
//     if (dictionaryFile == NULL) {
//         printf("Could not open dictionary file.\n");
//         return 1;
//     } else {
//         printf("Opened dictionary file.\n");
//     }

//     char line[MAX_WORD_LENGTH];
//     while (fgets(line, sizeof(line), dictionaryFile) != NULL) {
//         // Remove the newline character at the end
//         line[strcspn(line, "\n")] = '\0';
//         printf("Read word: %s\n", line);
//     }

//     fclose(dictionaryFile);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define MAX_WORD_LENGTH 50
// #define MAX_DICTIONARY_WORDS 500000

// int compare(const void *a, const void *b) {
//     return *(const char *)a - *(const char *)b;
// }

// int isAnagram(const char *word, const char *jumble) {
//     char sortedWord[MAX_WORD_LENGTH];
//     char sortedJumble[MAX_WORD_LENGTH];

//     strcpy(sortedWord, word);
//     strcpy(sortedJumble, jumble);

//     qsort(sortedWord, strlen(sortedWord), sizeof(char), compare);
//     qsort(sortedJumble, strlen(sortedJumble), sizeof(char), compare);

//     return strcmp(sortedWord, sortedJumble) == 0;
// }


void unscrambleWords(FILE *dictionaryFile, FILE *jumbleFile) {
    char dictionary[300001][51];
    char jumble[51];
    int numWords = 0;

    // Read dictionary words
    while (fgets(dictionary[numWords], 51, dictionaryFile) != NULL) {
        // Remove newline character from the end
        dictionary[numWords][strcspn(dictionary[numWords], "\n")] = '\0';
        numWords++;
    }
    printf("in\n");
    // // Read jumbled words
    // while (fgets(jumble, MAX_WORD_LENGTH, jumbleFile) != NULL) {
    //     int i, matchFound = 0;
    //     jumble[strcspn(jumble, "\n")] = '\0';  // Remove newline character

    //     printf("%s: ", jumble);

    //     // Check each word in the dictionary
    //     for (i = 0; i < numWords; i++) {
    //         if (isAnagram(dictionary[i], jumble)) {
    //             printf("%s ", dictionary[i]);
    //             matchFound = 1;
    //         }
    //     }

    //     if (!matchFound) {
    //         printf("NO MATCHES");
    //     }

    //     printf("\n");
    // }
}

int main(int argc, char *argv[]) {
    // FILE *dictionaryFile;
    // FILE *jumbleFile;

    // if (argc < 3) {
    //     printf("Usage: %s <dictionary> <jumbles>\n", argv[0]);
    //     return 1;
    // }

    FILE *dictionaryFile = fopen("dictionary.txt", "r");
    FILE *jumbleFile = fopen("jumbles.txt", "r");
    // dictionaryFile = fopen(argv[1], "r");
    // jumbleFile = fopen(argv[2], "r");

    if (dictionaryFile == NULL || jumbleFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }
    printf("Opened files.\n");

    unscrambleWords(dictionaryFile, jumbleFile);

    fclose(dictionaryFile);
    fclose(jumbleFile);

    return 0;
}
