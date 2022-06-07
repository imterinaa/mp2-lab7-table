#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include "TSortTable.h"
#include "TArrayTable.h"
#include "TScanTable.h"
#include "TTreeTable.h"
#include "TArrayHash.h"
#include "TBalTree.h"

using namespace std;

TTable* table;
bool result = true;
int Eff = 0;




void NewTable(int _type)
{
	switch (_type)
	{
	case 1: {
		table = new TScanTable();
		break;
	}

	case 2: {
		table = new TSortTable();
		break;
	}

	case 3: {
		table = new TArrayHash();
		break;
	}

	case 4: {
		table = new TTreeTable();
		break;
	}
	case 5: {
		table = new TBalTree();
		break;
	}
	default:
		break;
	}

	srand(time(NULL));

	TRecord insertRec;
	for (int i = 0; i < 10; i++) {
		insertRec.key = rand() % 100;
		bool inserted = table->Insert(
			TRecord(insertRec.key, "value" + to_string(insertRec.key)));
	}
}

void InsTable()
{
	TRecord rec;
	cout << "���� : " << endl;
	cin >> rec.key;
	cout << " ������ :" << endl;
	cin >> rec.val;


	Eff = table->GetEff();
	if (table->Insert(rec)) {
		cout << "������� ���������" << endl;
	}
	else {
		cout << "������� �� ���������" << endl;
	}
	cout << "�������������:\n" << table->GetEff() - Eff << endl;
}

void findKey()
{
	TKey key;
	cout << "������� ���� ��� ������ " << endl;
	cin >> key;

	Eff = table->GetEff();
	if (table->Find(key)) {
		cout << "������� ������" << endl;
	}
	else {
		cout << "������� �� ������" << endl;
	}
	cout << "�������������:\n" << table->GetEff() - Eff << endl;
}

void deleteKey()
{
	TKey key;
	cout << "������� ���� ��� �������� " << endl;
	cin >> key;

	Eff = table->GetEff();
	if (table->Delete(key)) {
		cout << "������� ������" << endl;
	}
	else {
		cout << "������� �� ������" << endl;
	}
	cout << "�������������:\n" << table->GetEff() - Eff << endl;

}

void main() {
	int n = 0;
	setlocale(LC_ALL, "Russian");
	int type;
	while (true) {
		cout << "1 - ������� ������� " << endl;
		cout << "2 - ������� �� �����" << endl;
		cout << "3 - ����� � ������� " << endl;
		cout << "4 - ������� �� ������� " << endl;
		cout << "5 - �������� � ������� " << endl;
		cout << "������� �����: " << endl;
		cin >> n;

		switch (n)
		{
		case 1:
		{
			cout << "��������� ���� ������:\n";
			cout << "1  -  ��������������� (TScanTable);\n";
			cout << "2  -  ��������������� (TSortTable);\n";
			cout << "3  -  ���-������� �� ������� (TArrayHash);\n";
			cout << "4  -  ������� �� ������ (TTreeTable);\n";
			cout << "5  -  ������� �� ���������������� ������ (TBalTree);\n";
			cout << "������� ��� �������: " << endl;
			cin >> type;
			NewTable(type);
			break;
		}
		case 2:
		{
			table->Print(cout);
			break;
		}
		case 3:
		{
			findKey();
			break;
		}
		case 4:
		{
			deleteKey();
			break;
		}
		case  5:
		{
			InsTable();
			break;
		}
		default:
			break;
		}
	}

}