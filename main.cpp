#include <iostream>
#include <vector>

using namespace std;

// Define the size of the Sudoku grid
#define N 9

// Function to print the Sudoku board
void printBoard(const vector<vector<int> >& board) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if placing a number at board[row][col] is valid
bool isSafe(const vector<vector<int> >& board, int row, int col, int num) {
    // Check the row and column
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check the 3x3 sub-grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int> >& board) {
    int row, col;
    bool emptyCell = false;

    // Find an empty cell (marked with 0)
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                emptyCell = true;
                break;
            }
        }
        if (emptyCell) break;
    }

    // If no empty cell is found, the puzzle is solved
    if (!emptyCell) {
        return true;
    }

    // Try numbers 1-9 for the empty cell
    for (int num = 1; num <= N; num++) {
        if (isSafe(board, row, col, num)) {
            // If the number is safe, place it
            board[row][col] = num;

            // Recursively try to solve the rest of the puzzle
            if (solveSudoku(board)) {
                return true;
            }

            // If placing num didn't work, backtrack
            board[row][col] = 0;
        }
    }

    return false;  // If no number is valid, return false
}

int main() {
    // Initialize the board with 0 values for empty cells
    vector<vector<int> > board(9, vector<int>(9, 0));

    // Sample Sudoku puzzle (0 represents empty cells)
    board[0] = {5, 3, 0, 0, 7, 0, 0, 0, 0};
    board[1] = {6, 0, 0, 1, 9, 5, 0, 0, 0};
    board[2] = {0, 9, 8, 0, 0, 0, 0, 6, 0};
    board[3] = {8, 0, 0, 0, 6, 0, 0, 0, 3};
    board[4] = {4, 0, 0, 8, 0, 3, 0, 0, 1};
    board[5] = {7, 0, 0, 0, 2, 0, 0, 0, 6};
    board[6] = {0, 6, 0, 0, 0, 0, 2, 8, 0};
    board[7] = {0, 0, 0, 4, 1, 9, 0, 0, 5};
    board[8] = {0, 0, 0, 0, 8, 0, 0, 7, 9};

    cout << "Original Sudoku puzzle:" << endl;
    printBoard(board);

    if (solveSudoku(board)) {
        cout << "\nSolved Sudoku puzzle:" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}

