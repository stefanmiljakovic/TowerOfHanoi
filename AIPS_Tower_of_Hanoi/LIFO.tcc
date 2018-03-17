
template <class T>
LIFO<T>::LIFO() {
	this->maxSize = 100;
	this->stack.reserve(100);

	this->top = 0;

	this->printEntry = [](T entry) {
		std::wcout << entry;
	};
}

template <class T>
LIFO<T>::LIFO(int size) {
	this->maxSize = size;
	this->stack.reserve(size);

	this->top = 0;

	this->printEntry = [](T entry) {
		std::wcout << entry;
	};
}

template <class T>
LIFO<T>::LIFO(std::wstring(*callback)(T entry)) {
	this->maxSize = 100;
	this->stack.reserve(100);

	this->top = 0;

	this->printEntry = callback;
}

template <class T>
LIFO<T>::LIFO(std::wstring(*callback)(T entry), int size) {
	this->maxSize = size;
	this->stack.reserve(size);

	this->top = 0;

	this->printEntry = callback;
}

template <class T>
LIFO<T>::~LIFO() {

}

template <class T>
void LIFO<T>::push(T data) {
	if (top < maxSize) {
		stack.insert(stack.begin() + top, data);
		top++;
	}
	else
		std::wcout << "Error! Limits of stack have been breached." << std::endl;
}

template <class T>
T LIFO<T>::pop() {

	if (top > 0) {
		top--;
		T tempData = stack.at(top);

		stack.erase(stack.begin() + top);
		
		return tempData;
	}
	else {
		std::wcout << "Stack appears to be empty ? Push data into stack in order to pop it." << std::endl; 
		return nullObj;
	}

}

template <class T>
int LIFO<T>::getMaxSize() {
	return maxSize;
}

template <class T>
int LIFO<T>::getLenght() {
	return stack.size();
}

template <class T>
bool LIFO<T>::isEmpty() {
	return stack.empty();
}

template <class T>
void LIFO<T>::setMaxSize(int size) {
	int minSize = top;

	if (size > minSize) {
		maxSize = size;
		stack.reserve(size);
	}
	else {
		std::wcout << "Error! You would lose data if you made stack smaller. Aborting!" << std::endl;
	}
}


template <class T>
void LIFO<T>::defineNullObject(T obj) {
	this->nullObj = obj;
}

template <class T>
T LIFO<T>::getTopElement() {
	return stack.at(top - 1);
}

template <class T>
std::vector<std::wstring> LIFO<T>::getDataReversed() {

	std::vector<std::wstring> temp;

	for (int i = top - 1; i >= 0; i--) {
		temp.emplace_back(printEntry(stack.at(i)));
	}

	return temp;
}