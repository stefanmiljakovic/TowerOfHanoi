#include "stdafx.h"
#include "Towers.h"

Towers::Towers()
{
	status = NOT_INITIALIZED;
}

Towers::Towers(int n) {

	status = INITIALIZED;

	if (n > DISC_LIMIT || n < 1)
		discCount = DISC_LIMIT;
	else
		discCount = n;

	initializeVector();
}

Towers::~Towers()
{
}


void Towers::initializeVector() {

	towers = new std::vector<LIFO<TowerDisc>*>(NO_OF_DISCS);

	for (int i = 0; i < NO_OF_DISCS; i++) {
		towers->at(i) = new LIFO<TowerDisc>([](TowerDisc e) -> std::wstring {
			
			std::wstring buffer = L"";

			std::wstring temp = e.toString();
			int len = temp.length();

			int width = DISC_LIMIT * 2 + 1;

			for (int i = 0; i < (width - len) / 2; i++)
				buffer += SPACE;

			buffer += temp;

			for (int i = 0; i < (width - len) / 2; i++)
				buffer += SPACE;

			return buffer;
		}, discCount);
	}

	initializeFirstTower();

}

void Towers::initializeFirstTower() {

	for (int i = discCount; i >= 1; i--) {
		towers->at(0)->push(TowerDisc(i));
	}
}

int Towers::moveFromTo(int from, int to) {

	if (from < 0 || from >= NO_OF_DISCS ||
		to < 0 || from >= NO_OF_DISCS)
		return STATUS_LIMIT;

	if (towers->at(from)->isEmpty())
		return STATUS_EMPTY;

	if (!checkMove(from, to))
		return STATUS_UNMOVABLE;

	towers->at(to)->push(towers->at(from)->pop());
	return STATUS_MOVED;
}

bool Towers::checkMove(int from, int to) {
	if (towers->at(to)->isEmpty())
		return true;

	if (towers->at(to)->getTopElement().getRadius() >
		towers->at(from)->getTopElement().getRadius())
		return true;

	return false;

}


void Towers::stringTower(int& n, std::vector<std::wstring>& display){

	int * counter = new int(0);

	for (int i = towers->at(n)->getLenght(); i < DISC_LIMIT; i++) {
		for (int j = 0; j < DISC_LIMIT * 2 + 1; j++) {
			if (j == DISC_LIMIT) {
				display[*counter] += BASE;
				continue;
			}
			display[*counter] += SPACE;
		}
		display[*counter] += SPACE;
		(*counter)++;
	}


	for each(std::wstring obj in towers->at(n)->getDataReversed()) {
		display[*counter] += obj + SPACE;
		(*counter)++;
	}
	
	display[*counter] += towerBase() + SPACE;

	delete counter;
	
}

std::wstring Towers::towersState() {

	std::wstringstream temp;

	std::vector<std::wstring> display(DISC_LIMIT + MARGIN_BOTTOM, L"");

	for (int i = 0; i < NO_OF_DISCS; i++) {
		stringTower(i, display);
	}

	temp << L"\n\n";

	for each(std::wstring obj in display) {
		temp << obj << L"\n";
	}

	return temp.str();
}

void Towers::resetToOrigin() {
	

}

void Towers::resetToOrigin(int n) {
	if (n > 1 && n <= 10)
		discCount = n;

	resetToOrigin();
}

std::wstring Towers::towerBase() {

	std::wstring temp = L"";

	for (int i = 0; i < DISC_LIMIT * 2 + 1; i++)
		temp += BASE;

	return temp;
}

bool Towers::getStatus() const {
	return status;
}

bool Towers::isWin() {
	if (towers->at(0)->isEmpty() && towers->at(1)->isEmpty())
		return true;
	return false;
}