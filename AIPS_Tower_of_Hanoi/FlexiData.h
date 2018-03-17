#pragma once


template <class T, class R>
class FlexiData {
public:
	FlexiData();
	~FlexiData();

	R getData(T);

	R(*callback)(T entry);
};