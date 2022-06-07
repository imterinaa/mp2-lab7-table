#include <iostream>
#include <clocale>
#include <cmath>
#include <cstdlib>
#include <random>
#include "TSortTable.h"
#include "TArrayHash.h"
#include "TTreeTable.h"

using namespace std;

TTable* pTable;

void fill_table(TTable* table, int Count, int key)
{
	for (int i = 0; i < Count; i++)
	{
		TKey randKey = (int)((double)rand() / (RAND_MAX + 1) * (key + 1));

		bool inserted = table->Insert(
			TRecord(randKey, "value" + to_string(randKey))
		);
		
	}
}

void show_table(TTable* table)
{

		if (!(*pTable).IsEmpty())
		{
		((TTreeTable*)table)->Print(cout);
			cout << "\n";
		}
		else
			cout << "�����.\n\n";

}

int main()
{
	setlocale(LC_ALL, "russian");

	pTable = new TTreeTable();
	

	
	while (true)
	{


		int tableSize = -1;


		int Count;
		cout << "�����  �������: ";
		cin >>Count;

		int keyMax;
		cout << "��������� ������������ ����: ";
		cin >> keyMax;

		fill_table(pTable,Count , keyMax);
		cout << "������� �������������.\n";
		cout << "������������� ���������: "
			<< pTable->GetEff() << "\n\n";
		show_table(pTable);

		pTable->ClearEff();

		while (true)
		{
			TKey key;
			cout << "���� : ";
			cin >> key;
			cout << '\n';
			if (key == -1) break;

			cout << "����� - 1\n" ;
			cout << "���������� - 2\n";
			cout << "�������� - 3\n ";

			int op;
			cin >> op;

			if (op == 1)
			{
				bool result = pTable->Find(key);



				if (result)
					cout << "������� ����� ������� " << key << ". "
					<< "�������������: " << pTable->GetEff()
					<< "\n\n";
				else
					cout << "�� ������� ����� ������� " << key << ". "
					<< "�������������: " << pTable->GetEff()
					<< "\n\n";
				pTable->ClearEff();
			}
			else if (op == 2)
			{
				bool result = false;

				try
				{
					result = pTable->Insert(
						TRecord(key, "value" + to_string(key)));

					if (result)
					{
						cout << "���������� ������� ���������. "
							<< "�������������: "
							<< pTable->GetEff() << "\n\n";
						cout << "������� ������:\n";
						show_table(pTable);
					}
					else
						cout << "������� � ����� ������ ��� ���� � "
						<< "�������. �������������: "
						<< pTable->GetEff() << "\n\n";
				}
				catch (...)
				{
					cout << "�� ������� �������� �������: "
						<< "������� �����������.\n\n";
				}

				pTable->ClearEff();
			}
			else if (op == 3)
			{
				bool result = pTable->Delete(key);

				if (result)
				{
					cout << "������� ������� ������ � �����. "
						<< "�������������: "
						<< pTable->GetEff() << "\n\n";
					cout << "������� ������:\n";
					show_table(pTable);
				}
				else
					cout << "������� � ����� ������ �� ������. "
					<< "�������������: "
					<< pTable->GetEff() << '\n';

				pTable->ClearEff();
			}
		}
	}
}
