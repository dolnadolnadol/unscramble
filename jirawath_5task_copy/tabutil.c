#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void replaceToSpaces(int num) {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (int i = 0; i < num; i++) {
                putchar(' ');
            }
        } else {
            putchar(c);
        }
    }
}

void replaceToTabs(int num) {
    int con_spaces = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            con_spaces++;
            if (con_spaces == num) {
                putchar('\t');
                con_spaces = 0;
            }
        } else {
            for (int i = 0; i < con_spaces; i++) {
                putchar(' ');
            }
            con_spaces = 0;
            putchar(c);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: tabutil [-d|-e] <num_spaces>\n");
        return 1;
    }

    int num = atoi(argv[2]);
    if (num <= 0) {
        printf("number of spaces must be a positive integer\n");
        return 1;
    }

    bool option_d = false;
    if (strcmp(argv[1], "-d") == 0) {
        option_d = true;
    } else if (strcmp(argv[1], "-e") != 0) {
        printf("Invalid option: %s\n", argv[1]);
        return 1;
    }

    if (option_d) {
        replaceToSpaces(num);
    } else {
        replaceToTabs(num);
    }

    return 0;
}
