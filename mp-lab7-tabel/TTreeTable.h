#pragma once
#include "TTable.h"
#include "Stack.h"

struct TNode
{
	TRecord rec;

	TNode* pLeft, * pRight;

	int Bal;

	TNode(
		TRecord _rec,
		TNode* _pLeft = nullptr,
		TNode* _pRight = nullptr);



};

TNode::TNode(
	TRecord _rec,
	TNode* _pLeft,
	TNode* _pRight)
{
	rec = _rec;
	pLeft = _pLeft;
	pRight = _pRight;

	Bal = 0;
}
class TTreeTable : public TTable
{
protected:
	TNode* pRoot;

	TNode* pPrev, * pCurr;

	TStack<TNode*> st;

	int Currpos;
	void DelRec(TNode* pDel);

	int level;
	void PrintRec(std::ostream& os, TNode* tmp, int level);



public:
	TTreeTable();
	~TTreeTable();

	bool IsFull() const override;
	bool Find(TKey key) override;
	virtual bool Insert(TRecord rec) override;
	virtual bool Delete(TKey key) override;

	void Reset() override;
	void GoNext() override;
	bool IsEnd() override;


	TKey GetCurrentKey() const override;
	TValue GetCurrentValue() const override;

	void Print(std::ostream& os = std::cout);
};

void TTreeTable::DelRec(TNode* pDel)
{
	if (pDel != nullptr)
	{
		DelRec(pDel->pRight);
		DelRec(pDel->pLeft);
		delete pDel;
	}
}

void TTreeTable::PrintRec(std::ostream& os, TNode* pNode, int level)
{
	if (pNode != nullptr)
	{
		for (int i = 0; i < level; i++)
			os << "  ";
		os << pNode->rec.key << std::endl;



		PrintRec(os, pNode->pLeft, level + 1);
		PrintRec(os, pNode->pRight, level + 1);

	}
}




TTreeTable::TTreeTable() : TTable()
{
	pRoot = pPrev = pCurr = nullptr;
	Currpos = 0;
	level = 0;
}

TTreeTable::~TTreeTable()
{
	DelRec(pRoot);
}

bool TTreeTable::IsFull() const
{
	return false;

}

bool TTreeTable::Find(TKey key)
{
	pPrev = nullptr;
	pCurr = pRoot;

	while (pCurr != nullptr) {
		if (pCurr->rec.key == key) return true;

		pPrev = pCurr;

		if (pCurr->rec.key > key) {
			pCurr = pCurr->pLeft;
		}
		else {
			pCurr = pCurr->pRight;
		}
	}

	pCurr = pPrev;
	return false;
}

bool TTreeTable::Insert(TRecord rec)
{
	if (Find(rec.key)) return false;

	TNode* tmp = new TNode(rec);

	if (IsEmpty()) {
		pRoot = tmp;
	}
	else {
		if (rec.key > pCurr->rec.key) {
			pCurr->pRight = tmp;
		}
		else {
			pCurr->pLeft = tmp;
		}
	}
	Eff++;
	DataCount++;
	return true;
}

bool TTreeTable::Delete(TKey key)
{
	if (!Find(key)) return false;

	TNode* tmp = pCurr;


	if (pCurr->pRight == nullptr)
	{
		Eff++;

		if (pPrev == nullptr)
			pRoot = pCurr->pLeft;

		else
		{
			if (pCurr->rec.key > pPrev->rec.key)
				pPrev->pRight = pCurr->pLeft;

			else
				pPrev->pLeft = pCurr->pRight;
		}
	}

	else if (pCurr->pLeft == nullptr)
	{
		Eff++;

		if (pPrev == nullptr)
			pRoot = pRoot->pRight;

		else
		{
			if (pCurr->rec.key > pPrev->rec.key)
				pPrev->pLeft = pCurr->pRight;

			else
				pPrev->pRight = pCurr->pLeft;
		}
	}

	else
	{
		tmp = tmp->pLeft;

		pPrev = pCurr;

		while (tmp->pRight != nullptr)
		{
			Eff++;
			pPrev = tmp;
			tmp = tmp->pRight;
		}

		pCurr->rec = tmp->rec;

		if (pCurr->pLeft == tmp)
			pPrev->pLeft = tmp->pLeft;

		else
			pPrev->pRight = tmp->pLeft;

		delete tmp;

	}
	Eff++;
	DataCount--;
	return true;
}

void TTreeTable::Reset()
{
	st.Clear();
	Currpos = 0;
	pCurr = pRoot;

	if (pCurr) {
		while (pCurr->pLeft) {
			st.Push(pCurr);
			pCurr = pCurr->pLeft;
		}
	}
	st.Push(pCurr);
}

void TTreeTable::GoNext()
{
	pCurr = st.Top();
	st.Pop();

	if (pCurr) {
		if (pCurr->pRight) {
			pCurr = pCurr->pRight;

			while (pCurr->pLeft) {
				st.Push(pCurr);
				pCurr = pCurr->pLeft;
			}
			st.Push(pCurr);

		}
		else {
			pCurr = st.Top();
		}
		Currpos++;
	}
}

bool TTreeTable::IsEnd()
{
	return (Currpos == DataCount);
}

TKey TTreeTable::GetCurrentKey() const
{
	return pCurr->rec.key;
}

TValue TTreeTable::GetCurrentValue() const
{
	return pCurr->rec.val;
}

void TTreeTable::Print(std::ostream& os)
{
	PrintRec(os, pRoot, 0);

}

