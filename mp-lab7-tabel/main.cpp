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
			cout << "ѕуста.\n\n";

}

int main()
{
	setlocale(LC_ALL, "russian");

	pTable = new TTreeTable();
	

	
	while (true)
	{


		int tableSize = -1;


		int Count;
		cout << "„исло  записей: ";
		cin >>Count;

		int keyMax;
		cout << "¬озможный максимальный ключ: ";
		cin >> keyMax;

		fill_table(pTable,Count , keyMax);
		cout << "“аблица сгенерирована.\n";
		cout << "Ёффективность генерации: "
			<< pTable->GetEff() << "\n\n";
		show_table(pTable);

		pTable->ClearEff();

		while (true)
		{
			TKey key;
			cout << " люч : ";
			cin >> key;
			cout << '\n';
			if (key == -1) break;

			cout << "ѕоиск - 1\n" ;
			cout << "ƒобавление - 2\n";
			cout << "”даление - 3\n ";

			int op;
			cin >> op;

			if (op == 1)
			{
				bool result = pTable->Find(key);



				if (result)
					cout << "”далось найти элемент " << key << ". "
					<< "Ёффективность: " << pTable->GetEff()
					<< "\n\n";
				else
					cout << "Ќе удалось найти элемент " << key << ". "
					<< "Ёффективность: " << pTable->GetEff()
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
						cout << "ƒобавление успешно завершено. "
							<< "Ёффективность: "
							<< pTable->GetEff() << "\n\n";
						cout << "“аблица теперь:\n";
						show_table(pTable);
					}
					else
						cout << "Ёлемент с таким ключом уже есть в "
						<< "таблице. Ёффективность: "
						<< pTable->GetEff() << "\n\n";
				}
				catch (...)
				{
					cout << "Ќе удалось добавить элемент: "
						<< "таблица переполнена.\n\n";
				}

				pTable->ClearEff();
			}
			else if (op == 3)
			{
				bool result = pTable->Delete(key);

				if (result)
				{
					cout << "Ёлемент успешно найден и удалЄн. "
						<< "Ёффективность: "
						<< pTable->GetEff() << "\n\n";
					cout << "“аблица теперь:\n";
					show_table(pTable);
				}
				else
					cout << "Ёлемент с таким ключом не найден. "
					<< "Ёффективность: "
					<< pTable->GetEff() << '\n';

				pTable->ClearEff();
			}
		}
	}
}
