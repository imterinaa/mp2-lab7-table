#pragma once
#include "TTreeTable.h"
class TBalTree : public TTreeTable
{
public:
	int leftTreeBalIns(TNode*& p) {
		Eff++;
		int result = 0;

		if (p->Bal == 1) {
			p->Bal = 0;
			result = 0;
		}
		else if (p->Bal == 0) {
			p->Bal = -1;
			result = 1;
		}
		else {
			TNode* leftNode = p->pLeft;

			if (leftNode->Bal == -1) {
				p->pLeft = leftNode->pRight;
				leftNode->pRight = p;
				p->Bal = 0;
				leftNode->Bal = 0;
				result = 0;
				p = leftNode;
			}
			else if (leftNode->Bal == 1) {
				TNode* rightNode = leftNode->pRight;

				leftNode->pRight = rightNode->pRight;
				p->pLeft = rightNode->pRight;
				rightNode->pLeft = leftNode;
				rightNode->pRight = p;

				if (rightNode->Bal == -1) {
					rightNode->Bal = 0;
					leftNode->Bal = 1;
					p->Bal = 1;
				}
				else {
					rightNode->Bal = 1;
					leftNode->Bal = 0;
					p->Bal = 0;
				}

				result = 0;
				p = rightNode;
			}
		}

		return result;
	}

	int rightTreeBalIns(TNode*& p) {
		Eff++;
		int result = 0;

		if (p->Bal == 0) {
			p->Bal = 1;
			result = 1;
		}
		else if (p->Bal == -1) {
			p->Bal = 0;
			result = 0;
		}
		else {
			TNode* rightNode = p->pRight;

			if (rightNode->Bal == 1) {
				p->pRight = rightNode->pLeft;
				rightNode->pLeft = p;
				p->Bal = 0;
				rightNode->Bal = 0;
				result = 0;
				p = rightNode;
			}
			else if (rightNode->Bal == -1) {
				TNode* leftNode = rightNode->pLeft;

				rightNode->pLeft = leftNode->pRight;
				p->pRight = leftNode->pLeft;
				leftNode->pRight = rightNode;
				leftNode->pLeft = p;

				if (leftNode->Bal == -1) {
					rightNode->Bal = 0;
					leftNode->Bal = -1;
					p->Bal = 0;
				}
				else {
					rightNode->Bal = -1;
					leftNode->Bal = 0;
					p->Bal = -1;
				}

				result = 0;
				p = leftNode;
			}
		}

		return result;
	}

	int leftTreeBalDel(TNode*& p) {
		Eff++;
		int result = 0;

		if (p->Bal == 1)
		{
			p->Bal = 0;
			result = -1;
		}
		else if (p->Bal == 0)
		{
			p->Bal = -1;
			result = 0;
		}
		else {
			TNode* leftNode = p->pLeft;

			if (leftNode->Bal == -1)
			{
				p->pLeft = leftNode->pRight;
				leftNode->pRight = p;

				leftNode->Bal = 0;
				p->Bal = 0;

				p = leftNode;
				result = -1;
			}
			else if (leftNode->Bal == 1)
			{
				TNode* plpr = leftNode->pRight;

				leftNode->pRight = plpr->pLeft;
				plpr->pLeft = leftNode;
				p->pLeft = plpr->pRight;
				plpr->pRight = p;
				if (plpr->Bal == -1)
				{
					p->Bal = 1;
				}
				else
				{
					p->Bal = 0;
				}
				if (plpr->Bal == 1)
				{
					leftNode->Bal = -1;
				}
				else
				{
					leftNode->Bal = 0;
				}
				p = plpr;
				p->Bal = 0;
				result = -1;
			}
			else
			{
				TNode* pp = p;
				TNode* plpl = leftNode->pLeft;
				TNode* plpr = leftNode->pRight;

				p = leftNode;
				p->pLeft = plpl;
				p->pRight = pp;
				pp->pLeft = plpr;
				leftNode->Bal = 1;
				return 0;
			}
		}
		return result;
	}

	int rightTreeBalDel(TNode*& p) {
		Eff++;
		int result = 0;

		if (p->Bal == -1)
		{
			p->Bal = 0;
			result = -1;
		}
		else if (p->Bal == 0)
		{
			p->Bal = 1;
			result = 0;
		}
		else
		{
			TNode* rightNode = p->pRight;
			if (rightNode->Bal == 1)
			{
				p->pRight = rightNode->pLeft;
				rightNode->pLeft = p;

				rightNode->Bal = 0;
				p->Bal = 0;

				p = rightNode;
				result = -1;
			}
			else if (rightNode->Bal == -1)
			{
				TNode* prpl = rightNode->pLeft;

				rightNode->pLeft = prpl->pRight;
				prpl->pRight = rightNode;
				p->pRight = prpl->pLeft;
				prpl->pLeft = p;
				if (prpl->Bal == 1)
				{
					p->Bal = -1;
				}
				else
				{
					p->Bal = 0;
				}
				if (prpl->Bal == -1)
				{
					rightNode->Bal = 1;
				}
				else
				{
					rightNode->Bal = 0;
				}
				p = prpl;
				p->Bal = 0;
				result = -1;
			}
			else
			{
				TNode* pp = p;
				TNode* prpl = rightNode->pLeft;
				TNode* prpr = rightNode->pRight;

				p = rightNode;
				p->pLeft = pp;
				p->pRight = prpr;
				pp->pRight = prpl;
				rightNode->Bal = -1;
				return 0;
			}
		}
		return result;
	}

	int insBalTree(TNode*& p, TRecord rec) {
		Eff++;
		int result = 0;

		if (p == NULL) {
			p = new TNode(rec);
			result = 1;
			DataCount++;
		}
		else if (p->rec.key > rec.key) {
			int tmp = insBalTree(p->pLeft, rec);

			if (tmp == 1) {
				result = leftTreeBalIns(p);
			}
		}
		else {
			int tmp = insBalTree(p->pRight, rec);

			if (tmp == 1) {
				result = rightTreeBalIns(p);
			}
		}

		return result;
	}

	int delBalTree(TNode*& p, TKey key) {
		Eff++;
		int result = 0;

		if (p == NULL) {
			return result;
		}
		if (key > p->rec.key) {
			int tmp = delBalTree(p->pRight, key);

			if (tmp != 0) {
				result = leftTreeBalDel(p);
			}
		}
		else if (key < p->rec.key) {
			int tmp = delBalTree(p->pLeft, key);

			if (tmp != 0) {
				result = rightTreeBalDel(p);
			}
		}
		else if (key == p->rec.key) {
			DataCount--;
			if (p->pLeft == NULL && p->pRight == NULL) {
				delete p;
				p = NULL;
				result = -1;
			}
			else if (p->pLeft != NULL && p->pRight == NULL) {
				p->rec = p->pLeft->rec;
				delete p->pLeft;
				p->pLeft = NULL;
				p->Bal = 0;
				result = -1;
			}
			else if (p->pLeft == NULL && p->pRight != NULL) {
				p->rec = p->pRight->rec;
				delete p->pRight;
				p->pRight = NULL;
				p->Bal = 0;
				result = 1;
			}
			else {
				TNode* leftNode = p->pLeft;
				TNode* rightNode = p->pRight;
				TNode* pMax = FindMax(leftNode);

				p->rec = pMax->rec;
				int tmp = delBalTree(p->pLeft, pMax->rec.key);

				if (tmp != 0) {
					result = rightTreeBalDel(p->pRight);
				}
			}
		}
		return result;
	}

	TNode* FindMax(TNode* p) const {
		while (p->pRight != NULL) {
			p = p->pRight;
		}
		return p;
	}

	bool Insert(TRecord rec) {
		if (Find(rec.key)) return false;

		insBalTree(pRoot, rec);
		return true;
	}

	bool Delete(TKey key) {
		if (!Find(key)) return false;

		delBalTree(pRoot, key);
		return true;
	}

};

