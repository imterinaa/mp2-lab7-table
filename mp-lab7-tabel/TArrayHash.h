#pragma once
#include "THashTable.h"

class TArrayHash : public THashTable {
protected:
	TRecord free;
	TRecord del;

	TRecord* arr;

	int size;
	int step;
	int curr;
public:
	TArrayHash(int _size = 50, int _step = 5);
	~TArrayHash();

	bool IsFull() const override;

	bool Find(TKey key);

	bool Insert(TRecord trec);
	bool Delete(TKey key);

	void Reset();
	void GoNext();
	bool IsEnd();
	void Print(std::ostream& os);
	TKey GetCurrentKey() const
	{
		return arr[curr].key;
	}
	TValue GetCurrentValue() const
	{
		return arr[curr].val;
	}
};

TArrayHash::TArrayHash(int _size, int _step)
{
	size = _size;
	step = _step;
	arr = new TRecord[size];

	free.key = -1;

	for (int i = 0; i < size; i++)
		arr[i] = free;
}

TArrayHash::~TArrayHash()
{
	delete[] arr;
}

bool TArrayHash::IsFull() const
{
	return (DataCount == size);
}

bool TArrayHash::Find(TKey key)
{
	int flag = -1;
	int Currpos = HashFunc(key) % size;

	for (int i = 0; i < size; i++) {
		Eff++;

		if (arr[Currpos].key == key) {
			curr = Currpos;
			return true;
		}

		if (arr[Currpos] == del && flag == -1) {
			curr = Currpos;
			flag = 1;
		}

		if (arr[Currpos] == free) {
			if (flag == -1)
				curr = Currpos;
			break;
		}

		Currpos = (Currpos + step) % size;
	}

	return false;
}


bool TArrayHash::Insert(TRecord rec)
{
	if (IsFull()) return false;
	if (Find(rec.key)) return false;

	arr[curr] = rec;
	DataCount++;
	Eff++;
	return true;
}

bool TArrayHash::Delete(TKey key)
{
	if (IsEmpty()) return false;
	if (!Find(key)) return false;

	for (Reset(); !IsEnd(); GoNext()) {
		if (arr[curr].key == key) {
			arr[curr] = del;
		}
		Eff++;
	}

	DataCount--;
	return true;
}

void TArrayHash::Reset()
{
	for (curr = 0; curr < size; curr++)
		if (arr[curr] != del && arr[curr] != free)
			return;
}

void TArrayHash::GoNext()
{
	for (curr++; curr < size; curr++)
		if (arr[curr] != del && arr[curr] != free)
			return;
}

bool TArrayHash::IsEnd()
{
	return curr == size;
}

void TArrayHash::Print(std::ostream& os)
{
	for (Reset(); !IsEnd(); GoNext()) {
		os << arr[curr] << std::endl;
	}
	Reset();
	os << std::endl;
}