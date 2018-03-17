#pragma once

#include "Towers.h"

#include <io.h>
#include <fcntl.h>

#include <cwchar>
#include <Windows.h>

#define ARROW L"▲"


class GameManager
{
public:
	GameManager();
	~GameManager();

	void start();
private:
	int counter;
	int currArrow, selector;

	std::wstring emptyLine;
	Towers * game;

	void colorize(int);

	std::wstring generateArrow(int);

	void setFont(CONSOLE_FONT_INFOEX&);
	void initializeFont();

	void infoScreen();
	void initializeGame();
	void initializeVariables();
	void mainGame();
	void victoryScreen();

	CONSOLE_FONT_INFOEX FONT_BOX;

	CONSOLE_FONT_INFOEX FONT_VICTORY;

	CONSOLE_FONT_INFOEX FONT_START;

	CONSOLE_FONT_INFOEX FONT_DEFAULT;
};

