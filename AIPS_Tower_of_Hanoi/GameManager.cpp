#include "stdafx.h"
#include "GameManager.h"

using namespace std;

GameManager::GameManager()
{
	initializeFont();
}


GameManager::~GameManager()
{
}

void GameManager::initializeFont() {

	_setmode(_fileno(stdout), _O_U16TEXT);

	FONT_BOX.cbSize = sizeof(FONT_BOX);
	FONT_BOX.nFont = 0;
	FONT_BOX.dwFontSize.X = 16;
	FONT_BOX.dwFontSize.Y = 16;
	FONT_BOX.FontFamily = FF_DONTCARE;
	FONT_BOX.FontWeight = FW_BOLD;

	FONT_START.cbSize = sizeof(FONT_START);
	FONT_START.nFont = 0;
	FONT_START.dwFontSize.Y = 20;
	FONT_START.dwFontSize.X = 0;
	FONT_START.FontFamily = FF_SWISS;
	FONT_START.FontWeight = FW_BOLD;

	FONT_DEFAULT.cbSize = sizeof(FONT_DEFAULT);
	FONT_DEFAULT.nFont = 0;
	FONT_DEFAULT.dwFontSize.Y = 16;
	FONT_DEFAULT.FontFamily = FF_DONTCARE;
	FONT_DEFAULT.FontWeight = FW_NORMAL;

	FONT_VICTORY.cbSize = sizeof(FONT_DEFAULT);
	FONT_VICTORY.nFont = 0;
	FONT_VICTORY.dwFontSize.Y = 24;
	FONT_VICTORY.FontFamily = FF_DONTCARE;
	FONT_VICTORY.FontWeight = FW_NORMAL;

}
void GameManager::setFont(CONSOLE_FONT_INFOEX& f) {
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &f);

}

void GameManager::start() {
	infoScreen();

	initializeGame();
	initializeVariables();
	mainGame();
}

void GameManager::initializeVariables() {

	counter = 0;

	emptyLine = L"";

	for (int i = 0; i < (DISC_LIMIT + 1) * 2 * NO_OF_DISCS; i++)
		emptyLine.append(L" ");
}
void GameManager::initializeGame() {
	system("CLS");

	wcout << L"Enter number of discs to play with (2-10): ";

	std::string n;

	cin >> n;


	try {
		stoi(n);
	}
	catch (exception e) {
		cin.clear();
		initializeGame();
		return;
	}

	if (stoi(n) < 2 || stoi(n) > 10)
		initializeGame();

	game = new Towers(stoi(n));
	counter = 0;
	
}

wstring GameManager::generateArrow(int n) {

	wstring temp = L"";

	for (int i = 0; i < 2*(DISC_LIMIT + 1) * n + DISC_LIMIT; i++) {
		temp.append(SPACE);
	}

	temp.append(ARROW);

	return temp;

}

void GameManager::colorize(int k) {

	// red = 12, default 0
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		k
		);
}

void GameManager::victoryScreen() {
	setFont(FONT_VICTORY);

	wcout << L"VICTORY!\n\n";

	system("pause");
	system("CLS");
	setFont(FONT_START);

	wcout << L"Victory was reached in " << to_wstring(counter)
		<< " moves.\n\n";

	system("pause");

	this->start();
}

void GameManager::mainGame() {

	system("CLS");

	if (game->isWin()) {
		victoryScreen();
		return;
	}

	currArrow = 0;
	selector = -1;

	wstring towerString = game->towersState();
	wstring movesMade = L"Moves made so far: " + to_wstring(counter);

	wcout << movesMade << endl << towerString;

	wcout << generateArrow(currArrow);

	int rightLimit = 2;
	int leftLimit = 0;

	bool loop = true;

	while (loop) {

		char key = _getch();

		if (key == -32) {
			switch (_getch()) {
			case 77: // RIGHT ARROW

				if (currArrow + 1 == selector && selector == 1)
					currArrow++;

				if (currArrow < rightLimit) {
					wcout << L"\r" << emptyLine;
					currArrow++;
					wcout << L"\r" << generateArrow(currArrow % NO_OF_DISCS);
				}
				break;
			case 75: // LEFT ARROW
				if (currArrow - 1 == selector && selector == 1)
					currArrow--;
				
				if (currArrow > leftLimit) {
					wcout << L"\r" << emptyLine;
					currArrow--;
					wcout << L"\r" << generateArrow(currArrow % NO_OF_DISCS);
				}
				break;
			}
		}

		else if (key == 32) { // SPACE


			if (selector != -1) {
				int status = game->moveFromTo(selector, currArrow);

				switch (status) {
				case STATUS_MOVED:
					counter++;
					loop = !loop;
					break;
				case STATUS_EMPTY:
					system("CLS");
					wcout << L"Selected stack was empty!\n\n";
					system("pause");
					break;
				case STATUS_UNMOVABLE:
					system("CLS");
					wcout << L"Illegal move!\n\n";
					system("pause");
					break;
				case STATUS_LIMIT:
					system("CLS");
					wcout << L"Vector range breached ?\n\n"; // shouldn't happen, ever
					system("pause");
					break;
				}

				loop = !loop;
				mainGame();
			}
			else {
				selector = currArrow;

				colorize(12);
				wcout << L"\r" << emptyLine << L"\r" << generateArrow(selector) << endl;
				colorize(15);


				switch (selector) {
				case 0:
					currArrow = 1;
					leftLimit = 1;
					rightLimit = 2;
					break;
				case 1:
					currArrow = 0;
					leftLimit = 0;
					rightLimit = 2;
					break;
				case 2:
					currArrow = 0;
					leftLimit = 0;
					rightLimit = 1;
					break;
				}

				wcout << generateArrow(currArrow);
			}
		}

		else if (key == 8) { // ESC
			mainGame();
		}

	}

	
	wcout << "\r" << emptyLine;

}

void GameManager::infoScreen() {
	setFont(FONT_START);

	system("CLS");

	wcout << L"Welcome!";

	wcout << L"\n\nControls:"
		<< L"\nArrow Key Left/Right (←, →) - move cursor"
		<< L"\nSpace - Select/Move To"
		<< L"\nBackspace - Remove selection"
		<< L"\n\nObjective:\nMove all discs to third stack."
		<< L"\n\n\nGood Luck!\n\n\n\n";

	system("pause");
}