#pragma once

#include "LIFO.h"
#include "TowerDisc.h"
#include <sstream>
#include <conio.h>


#define INITIALIZED true
#define NOT_INITIALIZED false

#define DISC_LIMIT 10
#define NO_OF_DISCS 3

#define STATUS_MOVED 1
#define STATUS_LIMIT -1
#define STATUS_EMPTY 0
#define STATUS_UNMOVABLE -2

#define MARGIN_BOTTOM 3

#define BASE L"▒"
#define SPACE L" "


class Towers
{
public:
	Towers();
	Towers(int); // number of discs

	~Towers();

	int moveFromTo(int, int);

	
	std::wstring towersState();


	void resetToOrigin();
	void resetToOrigin(int);

	bool isWin();


	bool getStatus() const;


private:
	void initializeVector();
	void initializeFirstTower();

	void stringTower(int&, std::vector<std::wstring>&);

	std::wstring towerBase();

	std::vector<LIFO<TowerDisc>*> * towers;

	bool checkMove(int, int);

	int discCount;

	bool status;
};

