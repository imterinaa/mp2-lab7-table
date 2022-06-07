#pragma once
#include <iostream>
using namespace std;

template <class T>
class TStack {
	T* mas;
	int size;
	int Currpos;
public:
	TStack(int _size = 10);
	~TStack();
	TStack(const TStack& ts);

	bool IsEmpty();
	bool IsFull();
	void Clear();

	void Push(T elem);
	T Pop();
	T Top();

	bool operator==(const TStack& ts) const;
	bool operator!=(const TStack& ts) const;
	TStack& operator=(const TStack& ts);


	friend ostream& operator<<(ostream& out, const TStack& ts) {
		for (int i = 0; i <= ts.Currpos; i++) {
			out << ts.arr[i] << ' ';
		}
		return out;
	}
};

template <class T>
TStack<T>::TStack(int _size) {
	if (_size <= 0) {
		throw "ERROR";
	}
	size = _size;
	mas = new T[size];
	Currpos = -1;
}

template <class T>
TStack<T>::~TStack() {
	delete[] mas;
}

template <class T>
TStack<T>::TStack(const TStack& ts) {
	size = ts.size;
	Currpos = ts.Currpos;
	mas = new T[size];
	for (int i = 0; i <= Currpos; i++) {
		mas[i] = ts.mas[i];
	}
}

template <class T>
bool TStack<T>::IsEmpty() {
	return (Currpos == -1);
}

template<class T>
bool TStack<T>::IsFull()
{
	return (Currpos == size - 1);
}

template <class T>
void TStack<T>::Push(T elem) {
	if (IsFull()) {
		throw "ERROR";
	}

	Currpos++;
	mas[Currpos] = elem;
}

template<class T>
void TStack<T>::Clear()
{
	Currpos = -1;
}

template <class T>
T TStack<T>::Pop() {
	if (IsEmpty()) {
		throw "ERROR";
	}

	T elem = mas[Currpos];
	Currpos--;
	return elem;
}

template<class T>
T TStack<T>::Top()
{
	if (IsEmpty()) {
		throw "ERROR";
	}

	return mas[Currpos];
}

template<class T>
bool TStack<T>::operator==(const TStack& ts) const
{
	if (size != ts.size) {
		return false;
	}

	for (int i = 0; i < size; i++) {
		if (mas[i] != ts.mas[i]) {
			return false;
		}
	}

	return true;
}

template<class T>
bool TStack<T>::operator!=(const TStack& ts) const
{
	return !(this == &ts);
}

template<class T>
TStack<T>& TStack<T>::operator=(const TStack& ts)
{
	if (size != ts.size) {
		delete[] mas;
		size = ts.size;
		mas = new T[size];
	}
	Currpos = ts.Currpos;

	for (int i = 0; i <= Currpos; i++) {
		mas[i] = ts.mas[i];
	}
	return *this;
}
