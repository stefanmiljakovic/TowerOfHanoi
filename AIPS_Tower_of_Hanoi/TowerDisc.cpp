#include "stdafx.h"
#include "TowerDisc.h"


TowerDisc::TowerDisc()
{
	this->radius = NULL;
}

TowerDisc::TowerDisc(uint r)
{
	this->radius = r;
}

TowerDisc::~TowerDisc()
{

}

int TowerDisc::getRadius() {
	return radius;
}

std::wstring TowerDisc::toString() const{

	std::wstring temp = L"";
	
	for (int i = 0; i < 2 * radius - 1; i++)
		temp += DISC;

	return temp;
	
}
