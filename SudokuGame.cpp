#include <iostream>   // for input and output stream
#include <cstdlib>    // for random numbers
#include <ctime>      // for random numbers

using namespace std;

#define tableNumbers 81

namespace PSu
{
	int sudoku[9][9] = { 0 };
	int g = 0;

	int i, j, num;
}

namespace SSu
{
	int sudoku[9][9] = { 0 };
}

//Declaring functions:
void tableMaker(int nCount, int srandI);
void showTable(int sudoku[9][9], char D);
bool isOk(int table[9][9], int row, int col, int num);
void tableCleaner(int sudoku[9][9]);
bool rowcolcheck(int sudoku[9][9]);
void tableConvertor(int table1[9][9], int table2[9][9]);
bool sudokuSolver(int sudoku[9][9]);
void getNumber();
void CAP();
bool isComplete();
void play(int NON, char D);
void callPlay();
//-----------------------print functions------------------------
void Pcongratulations();
void Pstrart();
void PchooseDifficulty();

//--------------------------------------------------------------
//==============================================================
//--------------------------------------------------------------

int main()
{
start:
	system("cls");
	Pstrart();
	char input;
	cin >> input;

	switch (input)
	{
	case 'a':
		PchooseDifficulty();
		callPlay();
		goto start;

	case 'b':

	case 'q':
		cout << "have a nice day :)";
		break;

	default:
		cout << "invalid input!!!";
		goto start;
	}
}

bool isComplete()
{
	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {
			if (PSu::sudoku[j][i] == 0)
			{
				return false;
			}
		}
	}
	return true;
}

void CAP() // Check And Place
{
	if (PSu::sudoku[PSu::j - 1][PSu::i - 1] != 0)
	{
		cout << "\x1B[31mWRONG:\033[0m" << "There is already a number!" << '\n'
			<< "Please choose another please.";
		//return false;
	}
	else if (!isOk(PSu::sudoku, PSu::j - 1, PSu::i - 1, PSu::num))
	{
		cout << "\x1B[31mWRONG:\033[0m" << "same number in the same row, column or subtable!" << '\n'
			<< "Please choose another please.";
		//return false;
	}
	else if (SSu::sudoku[PSu::j - 1][PSu::i - 1] != PSu::num)
	{
		cout << "\x1B[31mWRONG!\033[0m" << '\n';
		//return false;
	}

	if (SSu::sudoku[PSu::j - 1][PSu::i - 1] == PSu::num)
	{
		cout << "\x1B[32mCORRECT!\033[0m" << '\n';
		PSu::sudoku[PSu::j - 1][PSu::i - 1] = PSu::num;
		//return true;
	}
	cout << '\n';
}

void getNumber()
{
	cout << '\n';

takei:
	cout << "please enter Column (" << "\033[3;106;30mi\033[0m" << "): ";
	cin >> PSu::i;
	if (9 < PSu::i || PSu::i < 1) { PSu::i = 0; cout << "The entered number MUST BE FROM '1' TO '9'" << endl; goto takei; }

takej:
	cout << "please enter Row    (" << "\033[3;105;30mj\033[0m" << "): ";
	cin >> PSu::j;
	if (9 < PSu::j || PSu::j < 1) { PSu::j = 0; cout << "The entered number MUST BE FROM '1' TO '9'" << endl; goto takej; }

taken:
	cout << "Enter the number you want to put there: ";
	cin >> PSu::num;
	if (9 < PSu::num || PSu::num < 1) { PSu::num = 0; cout << "The entered number MUST BE FROM '1' TO '9'" << endl; goto taken; }
}

bool sudokuSolver(int sudoku[9][9])
{
	int row, col;
	bool isEmpty = false;

	for (row = 0; row < 9; row++) {
		for (col = 0; col < 9; col++) {
			if (sudoku[row][col] == 0) {
				isEmpty = true;
				break;
			}
		}
		if (isEmpty) {
			break;
		}
	}

	if (!isEmpty) {
		return true;
	}

	for (int num = 1; num <= 9; num++)
	{
		if (isOk(sudoku, row, col, num))
		{
			sudoku[row][col] = num;


			if (sudokuSolver(sudoku))
			{
				return true;
			}

			sudoku[row][col] = 0;
		}
	}

	return false;
}

void tableConvertor(int table1[9][9], int table2[9][9])
{
	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {
			table2[j][i] = table1[j][i];
		}
	}
}

void tableMaker(int NON, int srandI) //NON : number of numbers , srandI : srand Handle
{
	//tableCleaner();

	int x = time(0);
	srand(x + srandI);

	int n = 17;
	do {
		int y = (rand() % 9);
		int x = (rand() % 9);
		int num = 1 + (rand() % 9);

		if (isOk(PSu::sudoku, y, x, num) && PSu::sudoku[y][x] == 0) {
			PSu::sudoku[y][x] = num;
			n--;
		}
	} while (n > 0);

	if (!sudokuSolver(PSu::sudoku)) {
		PSu::g++;
		tableMaker(17, PSu::g);
	}
	else {
		tableConvertor(PSu::sudoku, SSu::sudoku);
	}

randomdelet:
	int w = tableNumbers - NON;
	do {
		int y = (rand() % 9);
		int x = (rand() % 9);

		if (PSu::sudoku[y][x] != 0) {
			PSu::sudoku[y][x] = 0;
			w--;
		}
	} while (w > 0);

	if (!rowcolcheck(PSu::sudoku))
	{
		//PSu::g++;
		tableCleaner(PSu::sudoku);
		tableConvertor(SSu::sudoku, PSu::sudoku);
		//tableMaker(17, PSu::g);
		goto randomdelet;
	}

}

bool rowcolcheck(int sudoku[9][9])
{
	int RowColSum;

	// col check
	for (int i = 0; i < 9; i++) {
		RowColSum = 0;
		for (int j = 0; j < 9; j++) {
			RowColSum += sudoku[j][i];
		}
		if (RowColSum == 0) {
			return false;
		}
	}

	// row check
	for (int j = 0; j < 9; j++) {
		RowColSum = 0;
		for (int i = 0; i < 9; i++) {
			RowColSum += sudoku[j][i];
		}
		if (RowColSum == 0) {
			return false;
		}
	}

	//subtable check
	//for(int cs = 0; cs < 9; cs + 3)
	//{
	//	for (int rs = 0; rs < 9; rs + 3)
	//	{
	//		RowColSum = 0;
	//		for (int j = 0; j < 3; j++)
	//		{
	//			for (int i = 0; i < 3; i++)
	//			{
	//				RowColSum += sudoku[j + cs][i + rs];
	//			}
	//		}
	//		if (RowColSum == 0) {
	//			return false;
	//		}
	//	}
	//}

	return true;
}

void tableCleaner(int sudoku[9][9])
{
	for (int j = 0; j < 9; j++) {
		for (int i = 0; i < 9; i++) {
			sudoku[j][i] = 0;
		}
	}
}

void showTable(int sudoku[9][9], char D)
{
	cout << "\x1B[33m";
	cout << "+------------------------+" << endl;
	cout << "|                        |" << endl;
	cout << "|        !SUDOKU!        |" << endl;
	cout << "|                        |" << endl;
	cout << "+------------------------+" << endl;
	switch (D)
	{
	case 'E':
		cout << "|    difficulty:\x1B[32mEezy\x1B[33m     |" << endl;
		break;
	case 'M':
		cout << "|    difficulty:\033[36mMedium\x1B[33m   |" << endl;
		break;
	case 'H':
		cout << "|    difficulty:\x1B[31mHARD\x1B[33m     |" << endl;
		break;
	case 'J':
		cout << "|    difficulty:\033[35m(JLLII)\x1B[33m  |" << endl;
		break;
	}
	cout << "==========================" << endl;
	cout << "|                        |" << endl;
	cout << "\x1B[33m|  " << "\033[2;105;30mj\033[0m" << "                     \x1B[33m|" << endl;
	cout << "\x1B[33m| " << "\033[2;106;30mi= 1 2 3 4 5 6 7 8 9\033[0m" << "   \x1B[33m|" << endl;

	for (int j = 0; j < 9; j++)
	{
		cout << "|  " << "\033[2;105;30m" << j + 1 << "\033[0m" << " ";
		for (int i = 0; i < 9; i++)
		{
			if ((i < 3 && j < 3) || (i < 3 && j > 5) || (i > 5 && j < 3) || (i > 5 && j > 5) || (2 < i && i < 6 && 2 < j && j < 6))
			{
				if (i == 2 || i == 8 || i == 5)
				{
					cout << "\033[2;47;35m" << sudoku[j][i] << "\033[0m" << " ";
				}
				else
				{
					cout << "\033[2;47;35m" << sudoku[j][i] << " " << "\033[0m";
				}
			}
			else
			{
				cout << "\033[0m" << sudoku[j][i] << " " << "\033[0m";
			}
		}
		cout << "  \x1B[33m|" << endl;
	}
	cout << "|                        |" << endl;
	cout << "==========================" << endl;
	cout << "|  \033[36mSADRAJABBARISANI.COM\x1B[33m  |" << endl;
	cout << "+------------------------+" << endl;
	cout << "\033[0m";
}

bool isOk(int table[9][9], int row, int col, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (table[row][i] == num)
			return false;
	}

	for (int i = 0; i < 9; i++)
	{
		if (table[i][col] == num)
			return false;
	}

	int rowBegin = row - row % 3;
	int colBegin = col - col % 3;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			if (table[j + rowBegin][i + colBegin] == num) {
				return false;
			}
		}
	}

	return true;
}

//----------------------------------------------------------------

void Pcongratulations()
{
	system("cls");
	cout << "log" << '\n' << '\n';
	cout << "\x1B[33m";
	cout << "+------------------------+" << endl;
	cout << "|                        |" << endl;
	cout << "|        !SUDOKU!        |" << endl;
	cout << "|                        |" << endl;
	cout << "+------------------------+" << endl;
	cout << "|    difficulty:HARD     |" << endl;
	cout << "==========================" << endl;
	cout << "|                        |" << endl;
	cout << "|    \x1B[32mcongratulations!\x1B[33m    |" << endl;
	cout << "|                        |" << endl;
	cout << "|         \x1B[32myou won\x1B[33m        |" << endl;
	cout << "|                        |" << endl;
	cout << "==========================" << endl;
	cout << "|  \033[36mSADRAJABBARISANI.COM\x1B[33m  |" << endl;
	cout << "+------------------------+" << endl;
	cout << "\033[0m";
}

void Pstrart()
{
	cout << "log" << '\n' << '\n';
	cout << "\x1B[33m";
	cout << "+------------------------+" << endl;
	cout << "|                        |" << endl;
	cout << "|        !SUDOKU!        |" << endl;
	cout << "|                        |" << endl;
	cout << "+------------------------+" << endl;
	cout << "|        welcome         |" << endl;
	cout << "==========================" << endl;
	cout << "|                        |" << endl;
	cout << "|    \033[35mchoose one:\x1B[33m         |" << endl;
	cout << "|                        |" << endl;
	cout << "|        a.play          |" << endl;
	cout << "|                        |" << endl;
	cout << "|        b.solve         |" << endl;
	cout << "|                        |" << endl;
	cout << "|        q.quit          |" << endl;
	cout << "|                        |" << endl;
	cout << "|                        |" << endl;
	cout << "|                        |" << endl;
	cout << "|                        |" << endl;
	cout << "|                        |" << endl;
	cout << "==========================" << endl;
	cout << "|  \033[36mSADRAJABBARISANI.COM\x1B[33m  |" << endl;
	cout << "+------------------------+" << endl;
	cout << "\033[0m";
}

void PchooseDifficulty()
{
	system("cls");
	cout << "log" << '\n' << '\n';
	cout << "\x1B[33m";
	cout << "+------------------------+" << endl;
	cout << "|                        |" << endl;
	cout << "|        !SUDOKU!        |" << endl;
	cout << "|                        |" << endl;
	cout << "+------------------------+" << endl;
	cout << "|          Play          |" << endl;
	cout << "==========================" << endl;
	cout << "|                        |" << endl;
	cout << "|    \033[35mchoose one:\x1B[33m         |" << endl;
	cout << "|                        |" << endl;
	cout << "|        e.Eazy          |" << endl;
	cout << "|                        |" << endl;
	cout << "|        m.Medium        |" << endl;
	cout << "|                        |" << endl;
	cout << "|        h.Hard          |" << endl;
	cout << "|                        |" << endl;
	cout << "|        j.JLLII         |" << endl;
	cout << "|  (JustLikeLivinInIran) |" << endl;
	cout << "|                        |" << endl;
	cout << "|        g.Go back       |" << endl;
	cout << "==========================" << endl;
	cout << "|  \033[36mSADRAJABBARISANI.COM\x1B[33m  |" << endl;
	cout << "+------------------------+" << endl;
	cout << "\033[0m";
}

//----------------------------------------------------------------

void play(int NON, char D)
{
	system("cls");
	cout << "loading...";

	tableCleaner(PSu::sudoku);
	tableMaker(NON, PSu::g);
	system("cls");
	cout << "Start!" << '\n' << '\n';
	while (isComplete() == false)
	{
		showTable(PSu::sudoku, D);
		getNumber();
		system("cls");
		CAP();
	}
	Pcongratulations();
	cout << "Enter any char to continue";
	char* ptr = new char;
	cin >> *ptr;
	delete ptr;
}

void callPlay()
{
first:
	char input;
	cin >> input;
	switch (input)
	{
	case 'e':
		play(50, 'E');
		break;

	case 'm':
		play(38, 'M');
		break;

	case 'h':
		play(28, 'H');
		break;

	case 'j':
		play(17, 'J');
		break;

	case 't':
		play(80, 'E');
		break;

	case 'g':
		break;

	default:
		cout << "invalid input!";
		goto first;
	}
}