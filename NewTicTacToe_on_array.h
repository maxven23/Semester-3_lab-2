#pragma once
#include "BinaryTree.h"
using namespace std;

typedef pair<int, int> p;

const string human = "O";
const string ai = "X";


// Checking for equality of three values
bool Equals(string a, string b, string c) {
	return (a == b) && (b == c) && (a != " ");
}


class TicTacToe {
private:
	string Type;
	string Player;
	string Board[3][3] = {
		{" ", " ", " "},
		{" ", " ", " "},
		{" ", " ", " "}
	};
public:

	TicTacToe(string Type) {
		this->Type = Type;
	}


	// Player turn
	void Move(string Next, string Curr) {
		int i, j;
		while (true) {
			system("cls");
			PrintBoard();
			cout << endl << endl;
			if (Curr == human) {
				cout << "1st Player turn" << endl;
			}
			else {
				cout << "2nd Player turn" << endl;
			}
			cout << "Enter your spot (x y):  ";
			cin >> i >> j;
			if (Board[i][j] == " ") {
				Board[i][j] = Curr;
				break;
			}
		}
		this->Player = Next;
	}

	// Cheching for a winner
	string checkWinner() {
		string winner = " ";

		// Horizontal
		for (int i = 0; i < 3; i++) {
			if (Equals(Board[i][0], Board[i][1], Board[i][2])) {
				winner = Board[i][0];
			}
		}

		// Vertical
		for (int i = 0; i < 3; i++) {
			if (Equals(Board[0][i], Board[1][i], Board[2][i])) {
				winner = Board[0][i];
			}
		}

		// Diagonal
		if (Equals(Board[0][0], Board[1][1], Board[2][2])) {
			winner = Board[0][0];
		}
		if (Equals(Board[2][0], Board[1][1], Board[0][2])) {
			winner = Board[2][0];
		}

		int openSpots = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (Board[i][j] == " ") {
					openSpots++;
				}
			}
		}

		if (winner == " " && openSpots == 0) {
			return "Tie";
		}
		else {
			return winner;
		}
	}

	//====================================================AI=TURN===============================================


	void bestMove() {
		// AI chooses turn
		int bestScore = -MAXINT;
		p move;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// Checking if spot is empty
				if (this->Board[i][j] == " ") {
					this->Board[i][j] = ai;
					int score = minimax(Board, 0, false);
					this->Board[i][j] = " ";
					if (score > bestScore) {
						bestScore = score;
						move = { i, j };
					}
				}
			}
		}
		this->Board[move.first][move.second] = ai;
		this->Player = human;
	}


	int minimax(string board[3][3], int depth, bool isMaximizing) {
		string result = checkWinner();
		if (result != " ") {
			if (result == "O") return -10;
			else if (result == "X") return 10;
			else if (result == "Tie") return 0;
		}

		if (isMaximizing) {
			int bestScore = -MAXINT;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					// Checking if spot is empty
					if (board[i][j] == " ") {
						board[i][j] = ai;
						int score = minimax(board, depth + 1, false);
						board[i][j] = " ";
						bestScore = max(score, bestScore);
					}
				}
			}
			return bestScore;
		}
		else {
			int bestScore = MAXINT;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					// Checking if spot is empty
					if (board[i][j] == " ") {
						board[i][j] = human;
						int score = minimax(board, depth + 1, true);
						board[i][j] = " ";
						bestScore = min(score, bestScore);
					}
				}
			}
			return bestScore;
		}
	}

	//===========================================================================================================


	// Start "Game"
	void Play() {
		if (Type == "PVE") {
			int FIRST = 0;
			while (FIRST != 1 && FIRST != 2) {
				system("cls");
				cout << "WHO STARTS? (1 - you; 2 - ai):  ";
				cin >> FIRST;
			}

			if (FIRST == 1) {
				this->Player = human;
			}
			else if (FIRST == 2) {
				this->Player = ai;
			}

			if (this->Player == ai) {
				int spot = rand() % 2;
				if (spot == 0) {
					this->Board[0][0] = ai;
					PrintBoard();
					system("pause>>VOID");
				}
				else {
					this->Board[1][1] = ai;
					PrintBoard();
					system("pause>>VOID");
				}
				this->Player = human;
			}

			// While game isn't finished
			while (checkWinner() != ai && checkWinner() != human && checkWinner() != "Tie") {
				if (Player == human) {
					Move(ai, human);
					system("cls");
					PrintBoard();
					system("pause>>VOID");
				}
				else if (Player == ai) {
					system("cls");
					bestMove();
				}
			}
			if (checkWinner() == ai) {
				system("cls");
				PrintBoard();
				cout << endl << endl;
				cout << "AI wins!";
				system("pause>>VOID");
			}
			else if (checkWinner() == human) {
				system("cls");
				PrintBoard();
				cout << endl << endl;
				cout << "You win!";
				system("pause>>VOID");
			}
			else if (checkWinner() == "Tie") {
				system("cls");
				PrintBoard();
				cout << endl << endl;
				cout << "Tie!";
				system("pause>>VOID");
			}
		}
		else if (Type == "PVP") {
			this->Player = human;
			while (checkWinner() != ai && checkWinner() != human && checkWinner() != "Tie") {
				if (Player == human) {
					Move(ai, human);
				}
				else if (Player == ai) {
					Move(human, ai);
				}
			}
			if (checkWinner() == ai) {
				system("cls");
				PrintBoard();
				cout << endl << endl;
				cout << "2nd Player ('X') wins!";
				system("pause>>VOID");
			}
			else if (checkWinner() == human) {
				system("cls");
				PrintBoard();
				cout << endl << endl;
				cout << "1st Player ('O') wins!";
				system("pause>>VOID");
			}
			else if (checkWinner() == "Tie") {
				system("cls");
				PrintBoard();
				cout << endl << endl;
				cout << "Tie!";
				system("pause>>VOID");
			}
		}
	}

	// Print Board
	void PrintBoard() {
		cout << "y\\x   0 1 2" << endl << endl;
		for (int i = 0; i < 2; ++i) {
			cout << i << "     " << Board[0][i] << "|" << Board[1][i] << "|" << Board[2][i] << endl;
			cout << "      -+-+-" << endl;
		}
		cout << "2     " << Board[0][2] << "|" << Board[1][2] << "|" << Board[2][2] << endl;
	}
};