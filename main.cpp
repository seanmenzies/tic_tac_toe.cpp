#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

void display_board(vector<char>& board);
char evaluate_win(vector<char>& board);
void check_draw(vector<char>& board, bool& game_draw);
bool check_valid(vector<char>& board, int& user_input);
vector<char> board = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
bool play_again = true;
string player_turn;
bool game_over = false;
bool game_draw = false;

int main() {
	while (play_again == true) {
		board = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
		cout << "Welcome to tic-tac-toe\nYou know how this works!\n\n" << endl;
		cout << "Let's see who goes first:\n" << endl;

		srand(time(0));
		int roll = rand() % 2;
		if (roll == 0) {
			player_turn = "computer";
			cout << "\nme first!" << endl;
		}
		else {
			player_turn = "human";
			cout << "\nyou first!" << endl;
		}
		display_board(board);

		while (game_over == false) {
			if (player_turn == "human") {
				cout << "Select your square human\n" << endl;
				int human_turn = 0;
				cin >> human_turn;
				while (check_valid(board, human_turn) == false) {
					cout << "Square taken. Try again:\n";
					cin >> human_turn;
				}
				board[human_turn] = 'X';
				check_draw(board, game_draw);
				if (evaluate_win(board) == 'X') {
					game_over = true;
					cout << "\nI am defeated" << endl;
				}
				else if (game_draw) {
					cout << "\nWe are at a stalemate, my friend!" << endl;
					game_over = true;
				}
				else {
					player_turn = "computer";
					display_board(board);
				}
			}
			else {
				vector<char> open_squares;
				cout << "My turn...\n" << endl;
				for (int i = 0; i < board.size(); i++) {
					if ((board[i] != 'X') && (board[i] != 'O')) {
						open_squares.push_back(i);
					}
				}
				srand(time(0));
				int computer_turn = open_squares[rand() % open_squares.size()];
				board[computer_turn] = 'O';
				check_draw(board, game_draw);
				if (evaluate_win(board) == 'O') {
					game_over = true;
					cout << "\nI am victorious!" << endl;
				}
				else if (game_draw) {
					cout << "\nWe are at a stalemate, my friend!" << endl;
					game_over = true;
				}
				else {
					player_turn = "human";
					display_board(board);
				}
			}
		}
		display_board(board);
		char answer;
		cout << "Shall we play again, human? Y/N: \n" << endl;
		cin >> answer;
		answer = (char)toupper(answer);
		if (answer == 'Y') {
			play_again = true;
			game_over = false;
		}
		else {
			play_again = false;
			cout << "Gay";
		}
	}
	

return 0;
}

void display_board(vector<char>& board) {
	cout << board[0] << " | " << board[1] << " | " << board[2] << "\n";
	cout << "---------\n";
	cout << board[3] << " | " << board[4] << " | " << board[5] << "\n";
	cout << "---------\n";
	cout << board[6] << " | " << board[7] << " | " << board[8] << "\n";
}

bool check_valid(vector<char>& board, int& user_input) {
	if ((board[user_input] == 'X') || (board[user_input] == 'O')) {
		return false;
	}
	else {
		return true;
	}
}

char evaluate_win(vector<char>& board) {
	const int WINNING_ROWS[8][3] = { {0, 1, 2},
		{3, 4 ,5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7},
		{2, 5, 8}, {0, 4, 8}, {2, 4, 6 } };

	for (int i = 0; i < 8; i++) {
		if ((board[WINNING_ROWS[i][0]] == board[WINNING_ROWS[i][1]]) &&
			(board[WINNING_ROWS[i][1]] == board[WINNING_ROWS[i][2]])) {
			char winner = board[WINNING_ROWS[i][0]];
			return winner;
		}
	}
	return '0';
}

void check_draw(vector<char>& board, bool& game_draw) {
	int count = 0;
	for (int i = 0; i < board.size(); i++) {
		if ((board[i] == 'X') || (board[i] == 'O')) {
			count += 1;
		}
		if (count == 9) {
			game_draw = true;
		}
	}
}
