#pragma once
#include "TTable.h"

class TArrayTable : public TTable {
protected:
	TRecord* arr;
	int size, curr;
public:
	TArrayTable(int _size = 10);
	~TArrayTable()
	{
		delete[] arr;
	}

	int GetSize() { return size; }
	bool IsFull() const { return DataCount == size; }

	TKey GetCurrentKey() const
	{
		return arr[curr].key;
	}
	TValue GetCurrentValue() const
	{
		return arr[curr].val;
	}

	void Reset() { curr = 0; }
	void GoNext() { curr++ ; }
	
	bool IsEnd() { return curr == DataCount; }
};

 TArrayTable::TArrayTable(int _size) 
{
	size = _size;
	arr = new TRecord[size];
	curr = -1;
}

