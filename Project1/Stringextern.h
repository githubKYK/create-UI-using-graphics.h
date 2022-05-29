#pragma once
#include <string>
#include "Mymath.h"
#include <iostream>

using namespace std;

template<typename T>
class Array {
public:
	Array() {
		arr = nullptr;
		index = 0;
		size = 0;
		sizeExten = 10;
	}

	~Array() {
		clear();
	}

	void externArr(int et = 1) {

		if (!arr) {
			arr = new T[et];
			size = et;
			return;
		}
		
		T* temp = arr;

		int m = min(size, size + et);
		size += et;
		arr = new T[size];

		for (size_t i = 0; i < m; i++)
		{
			arr[i] = temp[i];
		}

		delete[] temp;

	}

	void addElement(const T& value) {
		if (size <= index)
			externArr(1);
		arr[index++] = value;
	}

	void deleteElement(const T& value, const int& mode = 0) {
		if (!arr)
			return;
		for (size_t i = 0; i < index; i++)
		{
			if (arr[i] == value) {
				index--;
				for (size_t j = i; j < index; j++)
				{
					arr[j] = arr[j + 1];
				}
				externArr(-1);
				i--;
				if (mode == 0)
					break;
			}
		}
	}

	T getElement(const int& idx) {
		if(idx < index)
			return arr[idx];
	}

	int getSize() {
		return size;
	}

	bool empty() {
		return arr == NULL;
	}

	void clear() {
		delete[] arr;
		index = 0;
		size = 0;
	}

private:
	T* arr;
	int index;
	int size;
	int sizeExten;
};

void split(Array<string> &rslt, string str, const char& delim) {
	//int size = 1;
	//for (size_t i = 0; i < str.length(); i++)
	//	if (str[i] == delim)
	//		size++;
	//Array<string> result;
	//for (size_t i = 0; i < size - 1; i++) {
	//	result.addElement(str.substr(0, str.find(delim)));
	//	str.erase(0, str.find(delim) + 1);
	//}

	//result.addElement(str);

	Array<string> result;

	while (true)
	{
		int l = str.find(delim);
		if (l < 0) {
			rslt.addElement(str);
			break;
		}
		rslt.addElement(str.substr(0, l));
		str.erase(0, l + 1);
	}
}
