#pragma once

#include <vector>
#include <iostream>


template <class T>
class LIFO
{

public:
	// for primitive data types
	LIFO();
	LIFO(int);

	// for structures / objects
	LIFO(std::wstring(*callback)(T entry));
	LIFO(std::wstring(*callback)(T entry), int);

	~LIFO();

	void push(T);
	T pop();

	T getTopElement();


	void setMaxSize(int);
	int getMaxSize();

	int getLenght();
	bool isEmpty();

	void defineNullObject(T);

	std::vector<std::wstring> getDataReversed();

private:
	int maxSize;
	int top;

	std::wstring(*printEntry)(T entry);

	T nullObj;

	std::vector<T> stack;

};


#include "LIFO.tcc"