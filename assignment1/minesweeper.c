/************
 * COMP1521 21T3
 * Assignment 1 - Minesweeper
 *
 * Version: 1.5 (18-10-21)
 *
 * To get any new versions of the C file, you will need to re-run 1521 fetch to 
 * get new files. Do this by running these commands:
 * $ rm minesweeper.c
 * $ 1521 fetch minesweeper
 */

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "grid.h"

#define VALUE_MASK      0x0F
#define IS_BOMB_MASK    0x10
#define IS_RVLD_MASK    0x20
#define IS_MRKD_MASK    0x40

#define EMPTY_CELL      0
#define MAX_NAME_LEN    20
#define MAX_SCORES      10

#define FALSE           0
#define TRUE            1

#define MARK            0
#define REVEAL          1

#define PLAYING         0
#define WIN             1
#define LOSE            2

#define NO              0
#define YES             1
#define SCORES          2

// Functions to implement.
void     reveal_grid        (void);                     // Subset 0
void     place_bombs        (int bad_row, int bad_col); // Subset 1
void     mark_cell          (int row, int col);         // Subset 2
void     reveal_cell        (int row, int col);         // Subset 3
void     clear_surroundings (int row, int col);         // Subset 3
int      update_highscore   (int score);                // Subset 4
void     print_scores       (void);                     // Subset 4

// Other provided functions.
void     fill_grid          (int bad_row, int bad_col);
void     count_adj_bombs    (void);
int      is_bad_cell        (int row, int col, int bad_row, int bad_col);

void     control_play       (void);
int      play               (void);
int      check_end_play     (void);
int      prompt_new_game    (void);
int      check_valid_input  (int action, int row, int col);
void     add_user_score     (int score);
void     place_single_bomb  (int bad_row, int bad_col);

void     clear_grid         (void);
void     print_grid         (void);
void     get_args           (void);
void     init_scores        (void);
void     seed_rng           (unsigned int input_seed);
uint32_t rand_value         (uint32_t n);

// Struct used to store a user's score.
typedef struct UserScore {
  int  score;
  char name[MAX_NAME_LEN + 1];
} UserScore;

// Global variables required for the assignment.
int game_state;
int bomb_count;
int cells_left;

int8_t grid[N_ROWS][N_COLS];

// Used as index to store user scores.
int       nth_round = 0;
char      user_name[MAX_NAME_LEN + 1];
UserScore high_score;
UserScore scores[MAX_SCORES];

// Global variables for game configuration.
int debug_mode = FALSE;
int seed;
int total_bombs;

int main(int argc, char **argv) {
  get_args();
  seed_rng((unsigned int)seed);
  init_scores();
  control_play();

  return 0;
}

/*******************************************************************************
 * The following functions will need to be implemented by you in MIPS to
 *compelate the assignment.
 ******************************************************************************/

// Subset 0
/* Used by debug mode to reveal the entire grid. */
void reveal_grid(void) {
  for (int row = 0; row < N_ROWS; row++) {
    for (int col = 0; col < N_COLS; col++) {
      grid[row][col] |= IS_RVLD_MASK;
    }
  }
}

// Subset 1
/* Places bombs onto the grid. */
void place_bombs(int bad_row, int bad_col) {
  for (int i = 0; i < total_bombs; i++) {
    place_single_bomb(bad_row, bad_col);
  }
}

// Subset 2
/* Marks the cell. */
void mark_cell(int row, int col) {
  if (grid[row][col] & IS_RVLD_MASK) {
    if (debug_mode) {
      return;
    }
    printf("Cannot mark a revealed cell.\n");
    return;
  }
  // Unmark a marked cell.
  if (grid[row][col] & IS_MRKD_MASK) {
    grid[row][col] &= ~IS_MRKD_MASK;
    bomb_count++;
    // Mark a cell.
  } else {
    grid[row][col] |= IS_MRKD_MASK;
    bomb_count--;
  }
}

// Subset 3
/* Reveals the cell. */
void reveal_cell(int row, int col) {
  // Cannot reveal a cell that is currently marked.
  if (grid[row][col] & IS_MRKD_MASK) {
    if (debug_mode) {
      return;
    }
    printf("Cannot reveal a marked cell.\n");
    return;
  }
  if (grid[row][col] & IS_RVLD_MASK) {
    if (debug_mode) {
      return;
    }
    printf("Cell is already revealed.\n");
    return;
  }
  // Trigger game over if the cell is a bomb.
  if (grid[row][col] & IS_BOMB_MASK) {
    game_state = LOSE;
  }
  // Reveal the cell.
  if ((grid[row][col] & VALUE_MASK) == 0) {
    clear_surroundings(row, col);
  } else {
    grid[row][col] |= IS_RVLD_MASK;

    if (game_state != LOSE) {
      cells_left--;
    }
  }

  if (cells_left == 0) {
    game_state = WIN;
  }
}

// Subset 3
/* Recursively reveal a section of cells with no neighbouring bombs. */
void clear_surroundings(int row, int col) {
  if (row < 0 || row >= N_ROWS || col < 0 || col >= N_COLS) {
    return;
  }
  if (grid[row][col] & IS_RVLD_MASK) {
    return;
  }
  // Reveal the cell.
  grid[row][col] |= IS_RVLD_MASK;
  cells_left--;

  // Unmark the cell if it was marked.
  grid[row][col] &= ~IS_MRKD_MASK;

  // Stop revealing once a numbered cell is reached.
  if (grid[row][col] & VALUE_MASK) {
    return;
  }

  // Recurse to the surrounding cells in the grid.
  clear_surroundings(row - 1, col);
  clear_surroundings(row - 1, col - 1);
  clear_surroundings(row - 1, col + 1);
  clear_surroundings(row, col - 1);
  clear_surroundings(row, col + 1);
  clear_surroundings(row + 1, col - 1);
  clear_surroundings(row + 1, col);
  clear_surroundings(row + 1, col + 1);
}

// Subset 4
/* Set the highscore if the provided score is higher. */
int update_highscore(int score) {
  if (high_score.score < score) {
    high_score.score = score;

    // Copy over the string.
    int i = 0;
    while (user_name[i] != '\0') {
      high_score.name[i] = user_name[i];
      ++i;
    }
    high_score.name[i] = '\0';

    return TRUE;
  }
  return FALSE;
}

// Subset 4
/* Prints the last 10 scores. */
void print_scores(void) {
  printf("-------------SCORES-----------\n\n");
  for (int i = 0; i < MAX_SCORES; i++) {
    struct UserScore curr = scores[i];
    if (curr.score == -1) {
      break;
    }
    printf("------------------------------\n");
    printf("* USERNAME:\t%s\n", curr.name);
    printf("* SCORE:\t%d\n", curr.score);
  }
  printf("------------------------------\n");
}

/*******************************************************************************
 * The following functions will already be implemented.
 ******************************************************************************/
/*
Main controller for the game.
Handles restarting the game upon losing or winning a round.
*/
void control_play(void) {
  int play_again = NO;
  do {
    if (play_again == SCORES) {
      print_scores();
      play_again = prompt_new_game();
      continue;
    }

    printf("Enter your user name: ");
    scanf(" %20s", user_name); // C has no way to not hard code this

    printf("Reveal Any Cell to Begin...:\n");

    clear_grid();
    if (debug_mode) {
      reveal_grid();
    }

    game_state = PLAYING;
    bomb_count = total_bombs;
    cells_left = N_CELLS - total_bombs;

    print_grid();
    // Gets user first input. We need to do this in order to make sure that
    // the user doesn't die on the first click.
    int action, row, col;
    int valid;
    do {
      printf("What's your first move? (action row col)\n");

      int n_read1 = scanf(" %d", &action);
      if (n_read1 == EOF || action == -1) {
        return;
      }
      int n_read2 = scanf(" %d", &row);
      if (n_read2 == EOF) {
        return;
      }
      int n_read3 = scanf(" %d", &col);
      if (n_read3 == EOF) {
        return;
      }
      valid = check_valid_input(action, row, col);
      if (!valid) {
        fprintf(stderr, "Bad user input, try again.\n");
      }
      if (action == MARK) {
        mark_cell(row, col);
        print_grid();
      }
    } while (!valid || (action != REVEAL));

    fill_grid(row, col);
    reveal_cell(row, col);
    print_grid();
    play_again = play();

  } while (play_again);
}

/* Plays the game */
int play(void) {
  while (game_state == PLAYING) {
    printf("What's your next move? (action row col)\n");
    int action, row, col;
    int n_read1 = scanf(" %d", &action);
    if (n_read1 == EOF || action == -1) {
      return FALSE;
    }
    int n_read2 = scanf(" %d", &row);
    if (n_read2 == EOF) {
      return FALSE;
    }
    int n_read3 = scanf(" %d", &col);
    if (n_read3 == EOF) {
      return FALSE;
    }
    if (!check_valid_input(action, row, col)) {
      printf("Bad user input, try again.\n");
      continue;
    }
    if (action == MARK) {
      mark_cell(row, col);
    } else if (action == REVEAL) {
      reveal_cell(row, col);
    }
    print_grid();
  }
  return check_end_play();
}

/* Checks if the user wants to stop playing once game has ended. */
int check_end_play(void) {
  if (game_state == WIN) {
    printf("Congratulations, you won!\n");
  } else { // game_state == LOSE
    printf("Boom! you lost :(\n");
  }

  int score = N_CELLS - cells_left;
  add_user_score(score);

  printf("Your score was: %d (%d cells remaining)\n", score, cells_left);
  // Subset 3
  if (update_highscore(score)) {
    printf("The highscore is now: %d by you (%s)\n", high_score.score, high_score.name);
  } else {
    printf("The highscore is: %d by %s\n", high_score.score, high_score.name);
  }

  return prompt_new_game();
}

/* Adds user's score to the scores array. */
void add_user_score(int score) {
  struct UserScore *user_score = &scores[nth_round % MAX_SCORES];

  user_score->score = score;
  // Copy over the string.
  int i = 0;
  while (user_name[i] != '\0') {
    user_score->name[i] = user_name[i];
    ++i;
  }
  user_score->name[i] = '\0';

  nth_round++;
}

/* Prompts user for new game.*/
int prompt_new_game(void) {
  printf("New Game? (no: 0, yes: 1, scores: 2)\n");
  // Interprets any input other than 1 or 2 as no.
  int response = NO;
  if (scanf(" %d", &response) != 1) {
    return FALSE;
  }
  if (response != YES && response != SCORES) {
    response = NO;
  }

  return response;
}

/* Check that user input is valid. */
int check_valid_input(int action, int row, int col) {
  if (action != MARK && action != REVEAL) {
    return FALSE;
  }
  if (row < 0 || row > N_ROWS - 1) {
    return FALSE;
  }
  if (col < 0 || col > N_COLS - 1) {
    return FALSE;
  }
  return TRUE;
}

/* Prints the grid. */
void print_grid(void) {
  printf("Total Bomb Count: %d\n", bomb_count);
  for (int i = 0; i < N_ROWS; i++) {
    for (int j = 0; j < N_COLS; j++) {
      if (grid[i][j] & IS_MRKD_MASK) {
        printf("X ");
      } else if (grid[i][j] & IS_RVLD_MASK) {
        if (grid[i][j] & IS_BOMB_MASK) {
          printf("* ");
        } else {
          printf("%d ", grid[i][j] & VALUE_MASK);
        }
      } else {
        printf("- ");
      }
    }
    putchar('\n');
  }
}

/* Create the minesweeper grid. */
void fill_grid(int bad_row, int bad_col) {
  place_bombs(bad_row, bad_col);
  count_adj_bombs();
}

/* Places a single bomb onto the grid. */
void place_single_bomb(int bad_row, int bad_col) {
  int row, col;
  do {
    row = (int)rand_value(N_ROWS);
    col = (int)rand_value(N_COLS);
  } while (is_bad_cell(row, col, bad_row, bad_col));
  grid[row][col] |= IS_BOMB_MASK;
}

/* Clear the minesweeper grid for filling again. */
void clear_grid(void) {
  for (int row = 0; row < N_ROWS; ++row) {
    for (int col = 0; col < N_COLS; ++col) {
      grid[row][col] = EMPTY_CELL;
    }
  }
}

/*
Count the number of bombs that are adjacent to each cell in the grid and
update grid values to match.
*/
void count_adj_bombs(void) {
  for (int i = 0; i < N_ROWS; i++) {
    for (int j = 0; j < N_COLS; j++) {
      int count = 0;
      for (int n = -1; n <= 1; n++) {
        for (int m = -1; m <= 1; m++) {
          if ((int)i + n >= 0 && (int)i + n < N_ROWS && (int)j + m >= 0 && (int)j + m < N_COLS) {
            if (grid[i + n][j + m] & IS_BOMB_MASK) {
              count++;
            }
          }
        }
      }
      grid[i][j] |= count;
    }
  }
}

/*
Check the cell is not adjacent to or equal to the user's first click.
*/
int is_bad_cell(int row, int col, int bad_row, int bad_col) {
  if (grid[row][col] & IS_BOMB_MASK) {
    return TRUE;
  }
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if ((row + i == bad_row) && (col + j == bad_col)) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/* Initialise scores array. */
void init_scores(void) {
  for (int i = 0; i < MAX_SCORES; i++) {
    scores[i].score = -1;
    scores[i].name[0] = '\0';
  }
}

/* Get program args. */
void get_args(void) {
  int tmp, n_read;

  printf("How many bombs on the grid? ");
  n_read = scanf(" %d", &tmp);
  if (n_read == EOF) {
    exit(EXIT_FAILURE);
  }
  if (tmp <= 0 || tmp > MAX_BOMBS) {
    fprintf(stderr, "Bombs must be in the range %d to %d.\n", 1, MAX_BOMBS);
    exit(EXIT_FAILURE);
  }
  total_bombs = tmp;

  printf("Seed: ");
  n_read = scanf(" %d", &tmp);
  if (n_read == EOF) {
    exit(EXIT_FAILURE);
  }
  seed = tmp;
  printf("Debug Mode: ");
  n_read = scanf(" %d", &tmp);
  if (n_read == EOF) {
    exit(EXIT_FAILURE);
  }
  if (tmp != FALSE && tmp != TRUE) {
    fprintf(stderr, "Debug mode must be either 0 or 1.\n");
    exit(EXIT_FAILURE);
  }
  debug_mode = tmp;
}

uint32_t rand_master_seed = 0;

// Randomising from a set of sub seeds increases the period of the repetition.
uint32_t rand_sub_seeds[3] = {123, 456, 789};

void seed_rng(unsigned int input_seed) {
  rand_master_seed = input_seed;
}

uint32_t rand_value(uint32_t n) {
  rand_master_seed  = (rand_master_seed  * 1103515245 + 12345) & 0x7FFFFFFF;
  rand_sub_seeds[0] = (rand_sub_seeds[0] * 1103515245 + 12345) & 0x7FFFFFFF;
  rand_sub_seeds[1] = (rand_sub_seeds[1] * 1103515245 + 12345) & 0x7FFFFFFF;
  rand_sub_seeds[2] = (rand_sub_seeds[2] * 1103515245 + 12345) & 0x7FFFFFFF;
  return rand_sub_seeds[rand_master_seed % 3] % n;
}
