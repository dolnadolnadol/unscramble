// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define max_length 50
// #define max_dic 500000

// int compare(const void *a, const void *b) {
//     return strcmp((const char *)a, (const char *)b);
// }

// int isAnagram(const char *word, const char *jumble) {
//     char sortedWord[max_length];
//     char sortedJumble[max_length];

//     strcpy(sortedWord, word);
//     strcpy(sortedJumble, jumble);

//     qsort(sortedWord, strlen(sortedWord), sizeof(char), compare);
//     qsort(sortedJumble, strlen(sortedJumble), sizeof(char), compare);

//     return strcmp(sortedWord, sortedJumble) == 0;
// }

// void unscrambleWords(FILE *dictionaryFile, FILE *jumbleFile) {
//     char **dictionary = malloc(max_dic * sizeof(char *));
//     char jumble[max_length];
//     int numW = 0;

//     // Read dictionary words
//     char word[max_length];
//     while (fgets(word, max_length, dictionaryFile) != NULL) {
//         word[strcspn(word, "\n")] = '\0';  // Remove newline character
//         dictionary[numW] = strdup(word);
//         numW++;

//         if (numW >= max_dic) {
//             break;
//         }
//     }

//     // Sort the dictionary words
//     qsort(dictionary, numW, sizeof(char *), compare);

//     // Read jumbled words
//     while (fgets(jumble, max_length, jumbleFile) != NULL) {
//         jumble[strcspn(jumble, "\n")] = '\0';  // Remove newline character

//         printf("%s: ", jumble);

//         int i, match = 0;
//         for (i = 0; i < numW; i++) {
//             if (isAnagram(dictionary[i], jumble)) {
//                 printf("%s ", dictionary[i]);
//                 match = 1;
//             }
//         }

//         if (!match) {
//             printf("NO MATCHES");
//         }

//         printf("\n");
//     }

//     // Free memory
//     for (int i = 0; i < numW; i++) {
//         free(dictionary[i]);
//     }
//     free(dictionary);
// }

// int main(int argc, char *argv[]) {
//     FILE *dictionaryFile;
//     FILE *jumbleFile;

//     if (argc < 3) {
//         printf("Usage: %s <dictionary> <jumbles>\n", argv[0]);
//         return 1;
//     }

//     dictionaryFile = fopen(argv[1], "r");
//     jumbleFile = fopen(argv[2], "r");

//     if (dictionaryFile == NULL || jumbleFile == NULL) {
//         printf("Error opening files.\n");
//         return 1;
//     }

//     unscrambleWords(dictionaryFile, jumbleFile);

//     fclose(dictionaryFile);
//     fclose(jumbleFile);

//     return 0;
// }

#include "life_engine.h"

void print_board(life_board board) {
    for (int i = 0; i < board.num_rows; i++) {
        for (int j = 0; j < board.num_cols; j++) {
            unsigned char cell = board.cells[get_index(board, i, j)];
            printf("%c ", cell ? '*' : '.');
        }
        printf("\n");
    }
}

void read_board_from_file(char *filename, life_board *board) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    // Read the number of rows and columns from the file
    fscanf(file, "%d %d", &(board->num_rows), &(board->num_cols));

    // Validate the number of rows and columns
    assert(board->num_rows <= MAX_ROWS);
    assert(board->num_cols <= MAX_COLS);

    // Calculate the total number of cells
    int num_cells = board->num_rows * board->num_cols;

    // Allocate memory for the cells array
    board->cells = (unsigned char *)malloc(num_cells * sizeof(unsigned char));
    if (board->cells == NULL) {
        fprintf(stderr, "Error allocating memory for cells\n");
        exit(1);
    }

    // Read the cell values from the file
    for (int i = 0; i < num_cells; i++) {
        int cell_value;
        fscanf(file, "%d", &cell_value);
        board->cells[i] = (unsigned char)cell_value;
    }

    fclose(file);
}

int get_index(life_board board, int row, int col) {
    // Calculate the index based on row-major order
    return row * board.num_cols + col;
}

void set_alive(life_board board, int row, int col) {
    // Set the cell at the given coordinates as alive (non-empty)
    int index = get_index(board, row, col);
    board.cells[index] = 1;
}

void set_dead(life_board board, int row, int col) {
    // Set the cell at the given coordinates as dead (empty)
    int index = get_index(board, row, col);
    board.cells[index] = 0;
}

int is_in_range(life_board board, int row, int col) {
    // Check if the given coordinates are within the valid range of the board
    return (row >= 0 && row < board.num_rows && col >= 0 && col < board.num_cols);
}

int is_alive(life_board board, int row, int col) {
    // Check if the cell at the given coordinates is alive (non-empty)
    if (is_in_range(board, row, col)) {
        int index = get_index(board, row, col);
        return (board.cells[index] != 0);
    }
    return 0;
}

int count_live_nbrs(life_board board, int row, int col) {
    int count = 0;

    // Define the eight possible neighbors' offsets
    int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (int i = 0; i < 8; i++) {
        int neighbor_row = row + offsets[i][0];
        int neighbor_col = col + offsets[i][1];
        if (is_alive(board, neighbor_row, neighbor_col)) {
            count++;
        }
    }

    return count;
}

void make_next_board(life_board current, life_board next) {
    // Copy the size information to the next board
    next.num_rows = current.num_rows;
    next.num_cols = current.num_cols;

    // Allocate memory for the cells array of the next board
    int num_cells = current.num_rows * current.num_cols;
    next.cells = (unsigned char *)malloc(num_cells * sizeof(unsigned char));
    if (next.cells == NULL) {
        fprintf(stderr, "Error allocating memory for next cells\n");
        exit(1);
    }

    // Compute the next generation based on the current board
    for (int i = 0; i < current.num_rows; i++) {
        for (int j = 0; j < current.num_cols; j++) {
            int live_neighbors = count_live_nbrs(current, i, j);
            int index = get_index(current, i, j);
            unsigned char cell = current.cells[index];

            if (cell != 0) {
                // Cell is alive
                if (live_neighbors == 2 || live_neighbors == 3) {
                    // Cell remains alive in the next generation
                    next.cells[index] = 1;
                } else {
                    // Cell dies of loneliness or suffocation
                    next.cells[index] = 0;
                }
            } else {
                // Cell is dead
                if (live_neighbors == 3) {
                    // Cell becomes alive in the next generation
                    next.cells[index] = 1;
                } else {
                    // Cell remains dead in the next generation
                    next.cells[index] = 0;
                }
            }
        }
    }
}
