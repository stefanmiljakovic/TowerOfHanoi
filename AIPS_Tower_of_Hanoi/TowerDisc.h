#pragma once
#include <string>

#define DISC L"█"

typedef unsigned short int uint;

class TowerDisc
{
public:
	TowerDisc();
	TowerDisc(uint);
	~TowerDisc();

	int getRadius();
	std::wstring toString() const;
private:
	uint radius = NULL;

};

