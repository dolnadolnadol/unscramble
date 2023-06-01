#include "life_engine.h"

/* A game-of-life configuration is stored as a life_board structure.
 * See life_engine.h for more explanation.
 */

/********************************************************************
 * read_board_from_file - reads a given file for the board
 ********************************************************************/
void read_board_from_file(char *filename, life_board *board)
{
  FILE *fp = fopen(filename, "r");
  char lines[MAX_ROWS][MAX_COLS];
  if (NULL==fp) {
    fprintf(stderr, "Cannot open file %s\n, killing self.", filename);
    exit(-1);
  }
  // Guarded against fopen failures
  int row_count = 0;
  int col_count = -1;
  while (!feof(fp) && fgets(lines[row_count], MAX_COLS, fp)) {
    // poor man's trim
    char *line = lines[row_count];
    while (line[strlen(line)-1]=='\n' || line[strlen(line)-1]==' ')
      line[strlen(line)-1]=0;

    int this_col_count = strlen(line);
    if (col_count>0 && this_col_count!=col_count) {
      fprintf(stderr, "Uneven number of columns!\n killing self.");
      exit(-2);
    }
    col_count = this_col_count;
    row_count++;
  }
  DEBUG("num_rows=%d, num_cols=%d\n", row_count,col_count);
  board->num_rows = row_count;
  board->num_cols = col_count;

  size_t nbytes = row_count*col_count*sizeof(unsigned char);
  board->cells = (unsigned char *) malloc(nbytes);

  for (int row=0;row<board->num_rows;++row) {
    for (int col=0;col<board->num_cols;++col) {
      if (lines[row][col]=='*')
        set_alive(*board, row, col);
      else
        set_dead(*board, row, col);
    }
  }
}

/********************************************************************
 * get_index - returns the index into the 1d array
 *    corresponding to the cell location (row, col).
 ********************************************************************/
int get_index(life_board board, int row, int col)
{
  return row * board.num_cols + col;
}
/********************************************************************
 * set_alive - set the given cell to alive
 ********************************************************************/
void set_alive(life_board board, int row, int col)
{
  board.cells[get_index(board, row, col)] = 1;
}

/********************************************************************
* set_dead - set the given cell to dead
********************************************************************/
void set_dead(life_board board, int row, int col)
{
  board.cells[get_index(board, row, col)] = 0;
}


/********************************************************************
 * print_board - prints the board to stdout.
 *    a . indicates an empty square; a * indicates a "live" cell.
 *******************************************************************/
 void print_board(life_board board)
 {
   for (int row=0;row<board.num_rows;++row) {
     for (int col=0;col<board.num_cols;++col) {
       char cell_marker = (board.cells[get_index(board,row,col)]==0)?'.':'*';
       printf("%c", cell_marker);
     }
     printf("\n");
   }
 }

/***********************************************************************
 * is_in_range - returns 0 or 1 indicating whether the given location is
 *    a valid location on this board, assuming 0-indexing.
 ***********************************************************************/
int is_in_range(life_board board, int row, int col)
{
  return (row >= 0 && row < board.num_rows && col >= 0 && col < board.num_cols);
}


/***********************************************************************
 * is_alive - returns 1 if whether a given cell is alive and 0 otherwise.
 *    moreover, it will return 0 if the given location is out of range.
 ***********************************************************************/
int is_alive(life_board board, int row, int col)
{
  if (is_in_range(board, row, col))
    return board.cells[get_index(board, row, col)] == 1;
  else
    return 0;
}


/***********************************************************************
 * count_live_nbrs - returns the number of alive neighbors that a cell
 *    has by adding together the result of is_alive for all 8 directions.
 ***********************************************************************/
int count_live_nbrs(life_board board, int row, int col)
{
  int count = 0;
  int offsets[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},           {0, 1},
    {1, -1},  {1, 0},  {1, 1}
  };

  for (int i = 0; i < 8; i++) {
    int neighbor_row = row + offsets[i][0];
    int neighbor_col = col + offsets[i][1];
    count += is_alive(board, neighbor_row, neighbor_col);
  }

  return count;
}


/***********************************************************************
 * make_next_board - takes the current board and produces (by calling
 *    set_alive, set_dead) the next-generation board according to the
 *    rules of the game of life.
 ***********************************************************************/
void make_next_board(life_board current, life_board next)
{
  for (int row = 0; row < current.num_rows; row++) {
    for (int col = 0; col < current.num_cols; col++) {
      int live_neighbors = count_live_nbrs(current, row, col);
      int current_cell = is_alive(current, row, col);

      if (current_cell == 1 && (live_neighbors < 2 || live_neighbors > 3))
        set_dead(next, row, col);
      else if (current_cell == 0 && live_neighbors == 3)
        set_alive(next, row, col);
      else if (current_cell == 1 && (live_neighbors == 2 || live_neighbors == 3))
        set_alive(next, row, col);
      else
        set_dead(next, row, col);
    }
  }
}

