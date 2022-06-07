#pragma once
#include <iostream>
#include "TScanTable.h"



class TSortTable : public TScanTable {
	void QuickSort(int first, int last);
	///void SelectionSort();
	void Sort();
public:
	TSortTable(int _size = 10);
	
	TSortTable(TScanTable& st);

	bool Find(TKey key);
	bool Insert(TRecord rec);
	bool Delete(TKey key);
};

 TSortTable::TSortTable(int _size) : TScanTable(_size) {}

 TSortTable::TSortTable(TScanTable& st) : TScanTable(st.GetSize()) {
	DataCount = st.GetDataCount();
	int i;
	for (i = 0, st.Reset(); !st.IsEnd(); st.GoNext(), i++)
	{
		arr[i] = TRecord(st.GetCurrentKey(), st.GetCurrentValue());
		Eff++;
	}
	Sort();

}

 bool TSortTable::Find(TKey key) {
	int begin = 0, end = DataCount - 1, mid;
	while (begin <= end) {
		Eff++;
		mid = (begin + end) / 2;
		if (key < arr[mid].key) {
			end = mid - 1;
		}
		else if (key > arr[mid].key) {
			begin = mid + 1;
		}
		else {
			curr = mid;
			return true;
		}
	}
	curr = begin;
	return false;
}

bool TSortTable::Insert(TRecord rec) {
	if (IsFull()) {
		return false;
	}
	if (Find(rec.key)) {
		return false;
	}

	for (int i = DataCount - 1; i >= curr; i--) {
		arr[i + 1] = arr[i];
		Eff++;
	}

	arr[curr] = rec;
	DataCount++;
	Eff++;
	return true;
}

bool TSortTable::Delete(TKey key) {
	if (!Find(key)) {
		return false;
	}

	for (int i = curr; i < DataCount - 1; i++) {
		arr[i] = arr[i + 1];
		Eff++;
	}

	DataCount--;
	Eff++;
	return true;
}

 void TSortTable::QuickSort(int first, int last) {
	TKey midKey = arr[(first + last) / 2].key;

	int f = first, l = last;
	while (f < l)
	{
		while (arr[f].key < midKey)
		{
			f++;
			Eff++;
		}
		while (arr[l].key > midKey)
		{
			l--;
			Eff++;
		}

		if (f <= l)
		{
			std::swap(arr[f], arr[l]);
			f++; l--;
			Eff++;
		}
	}

	if (first < l)
		QuickSort(first, l);
	if (last > f)
		QuickSort(f, last);

}

// void TSortTable::SelectionSort()
//{
//	int Currpos;
//
//	for (int i = 0; i < DataCount; i++)
//	{
//		Currpos = i;
//
//		for (int j = i; j < DataCount; j++)
//		{
//			Eff++;
//			if (arr[j].key < arr[Currpos].key)
//				Currpos = j;
//		}
//
//		std::swap(arr[Currpos], arr[i]);
//		Eff++;
//	}
//}

 void TSortTable::Sort()
{
	{
		QuickSort(0, DataCount - 1);
	}
}
