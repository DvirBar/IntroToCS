#include <stdio.h>
#include <stdbool.h>

//----------------------- Sizes and Indexes --------------------------//
#define BOARD_MAX_SIDE 9
#define MIN_TOKENS 3
#define NUM_PLAYERS 2
#define	HISTORY_SIZE BOARD_MAX_SIDE*BOARD_MAX_SIDE

#define RED_SLOT_SYMBOL ('R')
#define YELLOW_SLOT_SYMBOL ('Y')
#define EMPTY_SLOT_SYMBOL (' ')

#define FIRST_PLAYER 1
#define SECOND_PLAYER 2


//----------------------- Message Identifiers --------------------------//
#define MSG_GET_BOARD_ROWS   0
#define MSG_GET_BOARD_COLS   1
#define MSG_GET_NUMBER_TOKENS 2


//--------------------------- Board Edges ------------------------------//
#define BOARD_VERT_SEP  '|'
#define BOARD_LEFT_ANG '\\'
#define BOARD_RIGHT_ANG '/'
#define BOARD_BOTTOM  '-'
#define BOARD_BOTTOM_SEP '-'

//--------------------------- Board Scan Indexes ------------------------------//
#define INCREASE_SCAN_INDEX 1
#define DECREASE_SCAN_INDEX -1
#define SKIP_SCAN_INDEX 0

//--------------------------- Commands -----------------------------//
#define UNDO_MOVE -1
#define REDO_MOVE -2

//--------------------------- Miscellaneous ------------------------------//
#define UNDEFINED_VALUE -1
#define TIE 0

//--------------------------- Functions Declarations ------------------------------//

void print_welcome_message();



//--------------------------- Game Initialization ------------------------------//


bool initialize_game(int* rows, int* cols, int* tokens, char* color);
bool read_game_params(int* rows, int* cols, int* tokens);
bool read_single_param(int param_msg_index, int* param);
bool read_tokens_to_win(int* tokens, int rows);
bool read_board_dimensions(int* rows, int* cols);
bool read_dim_param(int param_msg_index, int *dim);
bool read_starting_color(char* color);
void set_players_tokens(char players_tokens[NUM_PLAYERS], char starting_color);


//--------------------------- Game Sequence ------------------------------//

int game_sequence(char players_tokens[NUM_PLAYERS], int cols, int rows, int tokens);
void init_board(char board[][BOARD_MAX_SIDE]);

void print_board(char board[][BOARD_MAX_SIDE], int cols, int rows);

bool make_move(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int player, int cols,
			   int rows, int* used_tokens, char token, int tokens_to_win, int* winner);

bool read_move(int* col);
void print_enter_column_message();

bool commit_move(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int* used_tokens, int cols,
				 int rows, int chosen_col, char token, int tokens_to_win, int player, int* winner);

bool validate_and_place_token(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int* used_tokens, int rows, int cols, int chosen_col, char token, int tokens_to_win, int player, int* winner);

void add_token(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int row, int col,
			   int rows, int* used_tokens, char token);

int flat_array_index(int row, int col, int rows);
void spread_array_index(int* row, int* col, int flat_index, int rows);
int get_bottom_free_row(char board[][BOARD_MAX_SIDE], int rows, int col);
bool undo_move(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE],
			   int* used_tokens, int rows);

void clear_history_undo(int history[HISTORY_SIZE], int used_tokens);
bool redo_move(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE],
			   int* used_tokens, int rows, char token);

void print_unavailable_undo_redo_message();
bool check_winner(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int rows, int cols,
				  int used_tokens, int tokens_to_win);

bool scan_space(int row_step, int col_step, int tokens_to_win,
				char board[][BOARD_MAX_SIDE], int row, int col, int rows, int cols);

bool scan_side(char board[][BOARD_MAX_SIDE], char token_to_scan, char tokens_to_win,
			   int* current_row, int* current_col, int* counter, int rows, int cols, int row_step,
			   int col_step);

bool scan_cell(char board[][BOARD_MAX_SIDE], int* counter, int* current_row, int* current_col,
			   int row_step, int col_step, char token_to_scan);

void switch_player(int* current_player);

//---------------------------------//

void print_winner(int player_id);

//---------------------------------//

//--------------------------- Main Program -----------------------------//

// Function length: 12 lines.
int main() {
	char color = 0;
	int rows = 0, cols = 0, tokens = 0;
	char players_tokens[NUM_PLAYERS] = {0};
	int winner = UNDEFINED_VALUE;
	
	print_welcome_message();
	
	if(!initialize_game(&rows, &cols, &tokens, &color)) {
		return 0;
	}
	
	set_players_tokens(players_tokens, color);
	
	winner = game_sequence(players_tokens, cols, rows, tokens);
	
	// If winner is still undefined, it means that some error has occured and the program stops
	if(winner != UNDEFINED_VALUE) {
		print_winner(winner);
	}
	
    return 0;
}


//---------------------- Function Implementations ----------------------------//

void print_welcome_message() {
    printf("Welcome to 4-in-a-row game! \n");
}


//---------------------- Game Initialization ----------------------------//

/**
 * Function length: 5 lines.
 *
 * Entrypoint for game initialization phase.
 * Returns true if inserted values were properly typed, otherwise false.
 */
bool initialize_game(int* rows, int* cols, int* tokens, char* color) {
	if(!read_starting_color(color)) {
		return false;
	}
	
	if(!read_game_params(rows, cols, tokens)) {
		return false;
	}

	return true;
}

/**
 * Function length: 5 lines.
 *
 * Reads and validates the chosen rows, columns and tokens required to win from user input.
 * Returns true if inserted values were properly typed, otherwise false.
 */
bool read_game_params(int* rows, int* cols, int* tokens) {
	if(!read_board_dimensions(rows, cols)) {
		return false;
	}
	
	if(!read_tokens_to_win(tokens, *rows)) {
		return false;
	}

	return true;
}

/**
 * Function length: 6 lines.
 *
 * Reads the requested board rows and columns.
 * Returns true if inserted values were properly typed, otherwise false.
 */
bool read_board_dimensions(int* rows, int* cols) {
	do {
		if(!read_dim_param(MSG_GET_BOARD_ROWS, rows)) {
			return false;
		}
		
		if(!read_dim_param(MSG_GET_BOARD_COLS, cols)) {
			return false;
		}
	} while(*rows > *cols);
	
	return true;
}

/**
 * Function length: 4 lines.
 *
 * Reads the requested board rows and columns.
 * The dim(dimension) parameter indicates the actual value for rows/cols.
 * Returns true if inserted values were properly typed, otherwise false.
 */
bool read_dim_param(int param_msg_index, int* dim) {
	do {
		if(!read_single_param(param_msg_index, dim)) {
			return false;
		}
	} while(*dim < MIN_TOKENS || *dim > BOARD_MAX_SIDE);
		
	return true;
}

/**
 * Function length: 4 lines.
 *
 * Reads the amount of tokens required to win.
 * Returns true if inserted values were properly typed, otherwise false.
 */
bool read_tokens_to_win(int* tokens, int rows) {
	do {
		if(!read_single_param(MSG_GET_NUMBER_TOKENS, tokens)) {
			return false;
		}
	} while(!(*tokens >= MIN_TOKENS && *tokens <= rows));
	
	return true;
}

/**
 * Function length: 5 lines.
 *
 * Reads a single game parameter.
 * Returns true if inserted values were properly typed, otherwise false.
 */
bool read_single_param(int param_msg_index, int* param) {
	char const* const possible_params[] = {"rows", "columns", "tokens"};
	int num_valid_inputs = 0;
	
	printf("Please enter number of %s: ", possible_params[param_msg_index]);
	num_valid_inputs = scanf("%d", param);
	
	return num_valid_inputs == 1;
}

/**
 * Function length: 7 lines.
 *
 * Asks the player to choose their color.
 * Returns true if inserted values were properly typed, otherwise false.
 */
bool read_starting_color(char* color) {
	int num_valid_inputs = 0;
	do {
		printf("Please choose starting color (Y)ellow or (R)ed: ");
		num_valid_inputs = scanf(" %c", color);
		if(num_valid_inputs != 1) {
			return false;
		}
	} while(*color != RED_SLOT_SYMBOL && *color != YELLOW_SLOT_SYMBOL);
	
	return true;
}

/**
 * Function length: 5 lines.
 *
 * Assigns each player a token color, with regards to the starting color.
 */
void set_players_tokens(char players_tokens[NUM_PLAYERS], char starting_color) {
	if(starting_color == RED_SLOT_SYMBOL) {
		players_tokens[FIRST_PLAYER-1] = RED_SLOT_SYMBOL;
		players_tokens[SECOND_PLAYER-1] = YELLOW_SLOT_SYMBOL;
	}
	
	else {
		players_tokens[FIRST_PLAYER-1] = YELLOW_SLOT_SYMBOL;
		players_tokens[SECOND_PLAYER-1] = RED_SLOT_SYMBOL;
	}
}


//---------------------- Game Sequence ----------------------------//

/**
 * Function length: 12 lines.
 *
 * Main game sequenece function - manages the main game loop.
 * Returns true if inserted values were properly typed, otherwise false.
 */
int game_sequence(char players_tokens[NUM_PLAYERS], int cols, int rows, int tokens) {
	int winner = UNDEFINED_VALUE, current_player = FIRST_PLAYER, used_tokens = 0, history[HISTORY_SIZE] = {UNDEFINED_VALUE};
		
	char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE] = {{EMPTY_SLOT_SYMBOL}};
	init_board(board);
	print_board(board, rows, cols);
	
	// A flag to indicate if the move input was correctly typed.
	bool success = false;
	
	// Main game loop
	while(winner == UNDEFINED_VALUE) {
		success = make_move(board, history, current_player, cols, rows, &used_tokens,
				  players_tokens[current_player-1], tokens, &winner);
		
		if(!success) {
			return UNDEFINED_VALUE;
		}
		
		print_board(board, rows, cols);
		switch_player(&current_player);
	}
	
	return winner;
}

/**
 * Function length: 3 lines.
 *
 * Inits game board with empty slots symbols.
 */
void init_board(char board[][BOARD_MAX_SIDE]) {
	for(int i=0; i<BOARD_MAX_SIDE; i++) {
		for(int j=0; j<BOARD_MAX_SIDE; j++) {
			board[i][j] = EMPTY_SLOT_SYMBOL;
		}
	}
}
 
/**
 * Function length: 8 lines.
 *
 * Main move function, calls all relevant functions to read, validate and commit a move.
 * Returns true if inserted values were properly typed, otherwise false.
 */
bool make_move(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int player, int cols,
			   int rows, int* used_tokens, char token, int tokens_to_win, int* winner) {
	int chosen_col = UNDEFINED_VALUE;
	// A flag to indicate if the move was successfully committed.
	bool success = false;
	
	printf("Your move, player %d. ", player);
	
	// If the move chosen was illegal, we keep asking the user to enter it again
	while(!success) {
		if(!read_move(&chosen_col)) {
			return false;
		}
		
		success = commit_move(board, history, used_tokens, cols, rows, chosen_col, token,
					tokens_to_win, player, winner);
	}
	
	return true;
}

/**
 * Function length: 4 lines.
 *
 * Reads the requested column to put a token in.
 * Returns true if inserted values were properly typed, otherwise false.
 */
bool read_move(int* col) {
	print_enter_column_message();
	
	int num_valid_inputs = scanf("%d", col);
	// The player inserts a column number starting from 1. We should start from 0;
	if(num_valid_inputs) {
		(*col)--;
	}

	
	return num_valid_inputs == 1;
}

/**
 * Function length: 7 lines.
 *
 * Decides which kind of move to perform - place a token, undo, or redo.
 * Returns true if the move was executed successfully, otherwise false
 */
bool commit_move(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int* used_tokens, int cols,
				 int rows, int chosen_col, char token, int tokens_to_win, int player, int* winner) {
	if(chosen_col >= 0 && chosen_col < cols) {
		return validate_and_place_token(board, history, used_tokens, rows, cols,
						   chosen_col, token, tokens_to_win, player, winner);
	}
	
	if(chosen_col+1== UNDO_MOVE) {
		return undo_move(board, history, used_tokens, rows);
	}
	
	if(chosen_col+1 == REDO_MOVE) {
		return redo_move(board, history, used_tokens, rows, token);
	}
	
	return false;
}

/**
 * Function length: 11 lines.
 *
 * Makes sure that inserting a token is "physically" possible and calls relevant
 * functions to execute it.
 *
 * Returns true if the token was placed successfully, otherwise false.
 */
bool validate_and_place_token(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int* used_tokens, int rows, int cols, int chosen_col, char token, int tokens_to_win, int player, int *winner) {
	
	// Which row to put the token in - that is the most bottom available space in the chosen column
	int bottom_free_row = get_bottom_free_row(board, rows, chosen_col);
	if(bottom_free_row == UNDEFINED_VALUE) {
		printf("Column full. ");
		return false;
	}
	
	// "Physically" add the token and check if the current user has won
	add_token(board, history, bottom_free_row, chosen_col, rows, used_tokens, token);
	
	if(check_winner(board, history, rows, cols, *used_tokens, tokens_to_win)) {
		// Save winner value
		*winner = player;
	} else if(*used_tokens == rows*cols) {
		// No winner, save tie value
		*winner = TIE;
	}

	// If there were moves that were undone, we should clear them.
	clear_history_undo(history, *used_tokens);
	
	return true;
}

/**
 * Function length: 3 lines.
 *
 * Places a token in the board.
 */
void add_token(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int row, int col,
			   int rows, int* used_tokens, char token) {
	board[row][col] = token;
	(*used_tokens)++;
	
	// Save the move in history
	history[(*used_tokens)-1] = flat_array_index(row, col, rows);
}

/**
 * "Flattens" array indexes.
 * The function turns two-dimentional indexes into a one-dimentional index.
 * Returns the flat index.
 */
int flat_array_index(int row, int col, int rows) {
	return rows*col+row;
}

/**
 * Function length: 2 lines.
 * Extracts the row and column indexes from a flat index.
 */
void spread_array_index(int* row, int* col, int flat_index, int rows) {
	*row = flat_index%rows;
	*col = flat_index/rows;
}


/**
 * Function length: 4 lines.
 *
 * Gets the row index in the requsted column in which the token will be inserted.
 * Returns the row index. If no free row was found(full column) it returns an undefined value.
 */
int get_bottom_free_row(char board[][BOARD_MAX_SIDE], int rows, int col) {
	// We look for the first empty cell (from the bottom)
	for(int i=rows-1; i>=0; i--) {
		if(board[i][col] == EMPTY_SLOT_SYMBOL) {
			return i;
		}
	}
	
	return UNDEFINED_VALUE;
}

/**
 * Function length: 8 lines.
 *
 * Undo last move.
 *
 * In this function we use "used_tokens" as an indicator to tell the history array where we are.
 * This way, we can increment the indictor and move forward in history to redo moves.
 * It also complies with the actual amount of tokens physically set in the board.
 *
 * returns the row index. If no free row was found(full column) it returns -1.
 */
bool undo_move(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE],
			   int* used_tokens, int rows) {
	// We can't undo a move if the board is empty...
	if(*used_tokens == 0) {
		print_unavailable_undo_redo_message();
		return false;
	}
	
	// Get the row and column from history
	int row = 0, col = 0;
	spread_array_index(&row, &col, history[(*used_tokens)-1], rows);
	
	// Remove last inserted token and decrement history index (used_tokens)
	board[row][col] = EMPTY_SLOT_SYMBOL;
	(*used_tokens)--;
	
	return true;
}

/**
 * Function length: 4 lines.
 *
 * If a new token was inserted, it deletes all moves that were undone.
 */
void clear_history_undo(int history[HISTORY_SIZE], int used_tokens) {
	// We look for all upcoming history cells and clear them (put -1)
	for(int i = used_tokens; i < HISTORY_SIZE; i++) {
		if(history[used_tokens] == UNDEFINED_VALUE) {
			break;
		}
		
		history[used_tokens] = UNDEFINED_VALUE;
	}
}

/**
 * Function length: 7 lines.
 *
 * Redo the last move that was undone.
 * Returns true if the move was redone successfully, and otherwise false.
 */
bool redo_move(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE],
			   int* used_tokens, int rows, char token) {
	/* Redo is impossible if the board is full or if no move was undone
	 (when we have an undefined value in history) */
	if((*used_tokens)+1 == HISTORY_SIZE || history[(*used_tokens)] == UNDEFINED_VALUE) {
		print_unavailable_undo_redo_message();
		return false;
	}
	
	int row = 0, col = 0;
	spread_array_index(&row, &col, history[(*used_tokens)], rows);
	
	// Restore the move in the board and move it to the last made move in history
	add_token(board, history, row, col, rows, used_tokens, token);
	
	return true;
}

/**
 * Function length: 9 lines.
 *
 * Main function to check the game's winner.
 * Returns true if a winner was found. Otherwise returns false.
 */
bool check_winner(char board[][BOARD_MAX_SIDE], int history[HISTORY_SIZE], int rows, int cols,
				  int used_tokens, int tokens_to_win) {
	// Extract current row and column from history
	int row = 0, col = 0;
	spread_array_index(&row, &col, history[used_tokens-1], rows);
	
	// Check diagonal win
	if(scan_space(INCREASE_SCAN_INDEX, INCREASE_SCAN_INDEX, tokens_to_win, board, row, col,
				  rows, cols)) {
		return true;
	}
	
	// Check oposite diagonal win
	if(scan_space(DECREASE_SCAN_INDEX, INCREASE_SCAN_INDEX, tokens_to_win, board, row, col,
				  rows, cols)) {
		return true;
	}
	
	// Check vertical win
	if(scan_space(INCREASE_SCAN_INDEX, SKIP_SCAN_INDEX, tokens_to_win, board, row, col,
				  rows, cols)) {
		return true;
	}
	
	// Check lateral win
	return scan_space(SKIP_SCAN_INDEX, INCREASE_SCAN_INDEX, tokens_to_win, board, row, col,
					  rows, cols);
}

/**
 * Function length: 9 lines.
 *
 * Scans the entire currently inserted token space(from all directions),
 * to find if current player has won.
 * The function assumes that the token it needs to scan is the token in the provided row and column.
 *
 * row_step - tells the scanner which direction to scan a row(1,-1), or to not scan at all(0).
 * col_step - tells the scanner which direction to scan a column(1,-1), or to not scan at all(0).
 * row - requested row to put the token.
 * col - requested column to put the token.
 * rows - amount or rows in the board.
 * cols - amount or columns in the board.
 *
 * Returns true if enough tokens to win were found, otherwise false.
 */
bool scan_space(int row_step, int col_step, int tokens_to_win,
				char board[][BOARD_MAX_SIDE], int row, int col, int rows, int cols) {
	bool success = false; // Required amount of tokens were found
	char token_to_scan = board[row][col];
	/*
	 * We set the starting row and column, and start the counter from 1 (since we don't want to
	 * count the current cell twice
	 */
	int current_row = row+row_step, current_col = col+col_step, counter = 1;

	// Checking one side of neighbors
	success = scan_side(board, token_to_scan, tokens_to_win, &current_row, &current_col,
						&counter, rows, cols, row_step, col_step);
	
	if(success) {
		return success;
	}
	
	// We are now switching search direction so we need to initialize relevant parameters
	current_row = row-row_step;
	current_col = col-col_step;
	
	// Checking the opposite side of neighbors
	return scan_side(board, token_to_scan, tokens_to_win, &current_row, &current_col,
					 &counter, rows, cols, (-row_step), (-col_step));
}

/**
 * Function length: 8 lines.
 *
 * Scans one side of the token's neighbors (up/down, left/right etc.).
 *
 * token_to_scan - tells the function which token color to look for.
 * current_row(pointer) - the current row to start scanning from.
 * current_col(pointer) - the current column to start scanning from.
 * counter(pointer) - amount of neighboring tokens with the same colors counted.
 * row_step - tells the scanner which direction to scan a row(1,-1), or to not scan at all(0)
 * col_step - tells the scanner which direction to scan a column(1,-1), or to not scan at all(0)
 *
 * Returns true if enough tokens to win were found, otherwise false.
 */
bool scan_side(char board[][BOARD_MAX_SIDE], char token_to_scan, char tokens_to_win,
			   int* current_row, int* current_col, int* counter, int rows, int cols, int row_step,
			   int col_step) {
	bool detected_token = false;
	
	while(*current_row < rows && *current_col < cols) {
		detected_token = scan_cell(board, counter, current_row, current_col, row_step, col_step, token_to_scan);
		
		if(*counter == tokens_to_win) {
			return true;
		}
		
		if(!detected_token) {
			return false;
		}
	}
	
	return false;
}

/**
 * Function length: 6 lines.
 *
 * Scans a single board cell.
 *
 * counter(pointer) - amount of neighboring tokens with the same colors counted.
 * current_row(pointer) - the current row to start scanning from.
 * current_col(pointer) - the current column to start scanning from.
 * row_step - tells the scanner which direction to scan a row(1,-1), or to not scan at all(0).
 * col_step - tells the scanner which direction to scan a column(1,-1), or to not scan at all(0).
 * token_to_scan - tells the function which token color to look for.
 *
 * Returns true if the requested token color is in the currently scanned cell.
 */
bool scan_cell(char board[][BOARD_MAX_SIDE], int* counter, int* current_row, int* current_col,
			   int row_step, int col_step, char token_to_scan) {
	if(board[*current_row][*current_col] == token_to_scan) {
		// We increment the counter and move the scanner to the next cell if the requested token was found.
		(*counter)++;
		*current_row = *current_row+row_step;
		*current_col = *current_col+col_step;
		return true;
	}
	
	return false;
}

/**
 * Function length: 3 lines.
 *
 * Changes the currently playing player id after a move was done.
 */
void switch_player(int* current_player) {
	if(*current_player == FIRST_PLAYER) {
		*current_player = SECOND_PLAYER;
	} else {
		*current_player = FIRST_PLAYER;
	}
}

// Requests user to print a column number
void print_enter_column_message() {
    printf("Please enter column: ");
}

void print_unavailable_undo_redo_message() {
    printf("No moves to undo/redo. ");
}

/**
 * Function length: 8 lines.
 *
 * Outputs game board.
 */
void print_board(char board[][BOARD_MAX_SIDE], int rows, int cols) {
//    assert(IS_IN_RANGEI(board_side[0], 0, BOARD_MAX_SIDE)
//        && IS_IN_RANGEI(board_side[1], 0, BOARD_MAX_SIDE));
		
    for (int row = 0; row < rows; ++row) {
        printf("\n%c", BOARD_VERT_SEP);
		
		for (int col = 0; col < cols; ++col) {
			printf("%c%c", board[row][col], BOARD_VERT_SEP);
		}
    }
	
    printf("\n%c", BOARD_LEFT_ANG);
    
	for (int ii = 0; ii < cols - 1; ++ii) {
		printf("%c%c", BOARD_BOTTOM, BOARD_BOTTOM_SEP);
	}
	
    printf("%c%c\n", BOARD_BOTTOM, BOARD_RIGHT_ANG);
}

/**
 * Function length: 3 lines.
 *
 * Outputs winner or tie message.
 */
void print_winner(int player_id) {
    if (player_id > TIE)
        printf("Player %d won! \n", player_id);
    else
        printf("That's a tie. \n");
}
