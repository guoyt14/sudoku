#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
///////////////
#include <cstdlib>
#include <Windows.h>
#include <typeinfo>

using namespace std;

class sudoku {

private: 
	const char UNASSIGNED = ' ';

public:
	char board[10][10];
	bool change[10][10]; // 0 by default, 1 if it's a new input.

	sudoku(); //constructer fun 
	void init_Board(); //initiate the board as per Q1 requirement 
	void print_Board(); //print the board in console
	void save_Board(string filename); //save the current board to txt file
	void clear_Input(string coord); //enter something like ("A5") 
	void clear_Input(int i, int j); //enter something like (1, 5) 
	bool if_Solvable();
};

bool sudoku::if_Solvable() {
	return 0;
}



void sudoku::clear_Input(int i, int j) {
	if (i < 1 || i > 9 || j < 1 || j > 9) {
		cerr << "Please enter a valid coordinate." << endl;
		return;
	}

	if (change[i][j] == 0 && board[i][j] != UNASSIGNED) {
		cerr << "You cannot clear a default cell." << endl;
		return;
	}
	else {
		board[i][j] = UNASSIGNED;
		change[i][j] == 0;
		cout << "Cell " << char(i+'A'-1) << char(j+'1'-1) << " cleared." << endl;
	}
	
}

void sudoku::clear_Input(string coord) {
	if (coord.length() != 2 || coord[0]<'A' || coord[0] >'I' || coord[1] < '1' || coord[1] > '9') {
		cerr << "Please enter a valid coordinate." << endl;
		return;
	}

	int i = coord[0] - 'A' + 1;
	int j = coord[1] - '1' + 1;
	if (change[i][j] == 0 && board[i][j] != UNASSIGNED) {
		cerr << "You cannot clear a default cell." << endl;
		return;
	}
	else {
		board[i][j] = UNASSIGNED;
		change[i][j] == 0;
		cout << "Cell " << coord << " cleared." << endl;
	}
}


//read a board from a txt file, NOT a member function of Class suduku
sudoku read_Board_from_txt(string filename) {
	//need to add resource file to our sln first, otherwise need to type out the extire directory.
	//file must be placed under the same directory as the sln file
	//right-click on "Resource File" -> "Add" -> "Existing Item..."
	ifstream infile;
	infile.open(filename);

	if (infile.fail()) {
		cerr << filename << " does not exist in solution" << endl;
		exit(EXIT_FAILURE);
	}

	string rawBoard; // to store the entire string, deal with it later 
	rawBoard.assign((istreambuf_iterator<char>(infile)), (istreambuf_iterator<char>())); 

	sudoku res;
	int c = 0, i = 1, j = 1;
	
	while (c < rawBoard.length()) {
		if (rawBoard[c] == 'g') { 
			res.change[i][j] = 1;
			c++; 
		}

		res.board[i][j] = rawBoard[c];
		if (j == 9) {
			i++;
			j = 1;
		}
		else { j++; }
		c += 2;
	}
	
	cerr << "Sudoku board read succeefully from " << filename << endl;
	return res;
}


//save the current board to a txt file
void sudoku::save_Board(string filename) {
	ofstream outfile(filename);
	if (outfile.is_open()) {

		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				if (change[i][j] == 1) {
					outfile << "g" << board[i][j] << ",";
				}
				else outfile << board[i][j] << ",";
			}
		}
		outfile.close();
		cout << "Sudoku board successfully saved to " << filename << endl;
	}
	else cout << "Unable to open text file" << endl;
}

sudoku::sudoku() {
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			board[i][j] = UNASSIGNED;
			change[i][j] = 0;
		}
	}
}

void sudoku::init_Board() {
	board[1][1] = '9'; board[1][4] = '6'; board[1][6] = '3'; board[1][7] = '1'; board[1][8] = '2'; board[1][9] = '8';
	board[2][1] = '8'; board[2][4] = '7'; board[2][6] = '1'; board[2][7] = '5'; board[2][8] = '3'; board[2][9] = '9';
	board[3][1] = '1'; board[3][3] = '3'; board[3][4] = '8'; board[3][5] = '9'; board[3][8] = '6';
	board[4][1] = '4'; board[4][2] = '9'; board[4][3] = '2'; board[4][5] = '6'; board[4][7] = '8';
	board[5][2] = '1'; board[5][4] = '3'; board[5][5] = '8'; board[5][7] = '8';
	board[6][2] = '3'; board[6][3] = '8'; board[6][4] = '9'; board[6][5] = '1'; board[6][6] = '2'; board[6][7] = '6'; board[6][8] = '5'; board[6][9] = '4';
	board[7][4] = '2'; board[7][5] = '7'; board[7][6] = '9'; board[7][7] = '3'; board[7][9] = '1';
	board[8][1] = '3'; board[8][2] = '7'; board[8][6] = '8'; board[8][7] = '2';
	board[9][1] = '2'; board[9][3] = '9'; board[9][4] = '1'; board[9][5] = '3'; board[9][6] = '6'; board[9][8] = '8'; board[9][9] = '5';

	change[4][5] = 1;
}

/*
void setcolor(unsigned short color) {                                           
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
*/

void sudoku::print_Board() {
	cout << "   | 1 2 3 | 4 5 6 | 7 8 9 " << endl;
	cout << "---+-------+-------+-------" << endl;
	for (int i = 1; i <= 9; i++) {
		cout << " " << char(i+64) << " | ";
		for (int j = 1; j <= 9; j++) {
			if (change[i][j] == 1) {
				cout << "\x1B[31m" << board[i][j] << "\033[0m" << " "; //print in red
			}
			else cout << board[i][j] << " ";
			if (j % 3 == 0) cout << "| ";
		}
		cout << endl;
		if (i % 3 == 0) cout << "---+-------+-------+-------" << endl;
	}
}

int main() {

	sudoku game;
	game.init_Board();	//initiate the board as per Q1
	game.print_Board();
	game.save_Board("mySudoku.txt");	//save to "mySudoku.txt"

	game.clear_Input("D5");	//clear the user input cell D5
	game.print_Board();

	sudoku game1 = read_Board_from_txt("mySudoku.txt");	
	game1.print_Board();


	return 0;
}