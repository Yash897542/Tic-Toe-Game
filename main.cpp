#include <iostream>
#include <vector>
#include <limits>

// --- Global Variables ---
char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char current_marker;
int current_player;

// --- Function Prototypes ---
void draw_board();
bool place_marker(int slot);
int check_winner();
void swap_player_and_marker();
void game_loop();

// --- Main Function ---
int main() {
    game_loop();
    return 0;
}

// --- Function Implementations ---

// Draws the game board in the console
void draw_board() {
    std::cout << "\n";
    std::cout << "     |     |     \n";
    std::cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "  \n";
    std::cout << "_____|_____|_____\n";
    std::cout << "     |     |     \n";
    std::cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "  \n";
    std::cout << "_____|_____|_____\n";
    std::cout << "     |     |     \n";
    std::cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "  \n";
    std::cout << "     |     |     \n";
    std::cout << "\n";
}

// Places a marker on the board if the slot is valid
bool place_marker(int slot) {
    // Adjust slot to be 0-indexed
    int index = slot - 1;
    if (index >= 0 && index < 9 && board[index] != 'X' && board[index] != 'O') {
        board[index] = current_marker;
        return true;
    }
    return false;
}

// Checks for a winner or a draw
// Returns 1 for a win, 0 for a draw, -1 to continue
int check_winner() {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) return 1;
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) return 1;
    }
    // Check diagonals
    if (board[0] == board[4] && board[4] == board[8]) return 1;
    if (board[2] == board[4] && board[4] == board[6]) return 1;
    
    // Check for a draw (no empty slots left)
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 'X' && board[i] != 'O') {
            return -1; // Game is not over
        }
    }

    return 0; // It's a draw
}

// Swaps the current player and their marker
void swap_player_and_marker() {
    if (current_marker == 'X') {
        current_marker = 'O';
        current_player = 2;
    } else {
        current_marker = 'X';
        current_player = 1;
    }
}

// The main game loop
void game_loop() {
    std::cout << "--- Tic Tac Toe ---" << std::endl;
    current_player = 1;
    current_marker = 'X';

    draw_board();
    
    int game_status = -1;
    while (game_status == -1) {
        std::cout << "Player " << current_player << ", enter a number (1-9): ";
        int slot_choice;
        std::cin >> slot_choice;

        if (std::cin.fail() || slot_choice < 1 || slot_choice > 9) {
            std::cout << "Invalid input. Please enter a number between 1 and 9." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (!place_marker(slot_choice)) {
            std::cout << "That slot is already taken! Try another one." << std::endl;
            continue;
        }

        draw_board();
        game_status = check_winner();
        
        if (game_status == 1) {
            std::cout << "Player " << current_player << " wins! Congratulations!" << std::endl;
        } else if (game_status == 0) {
            std::cout << "It's a draw!" << std::endl;
        } else {
            swap_player_and_marker();
        }
    }
}
