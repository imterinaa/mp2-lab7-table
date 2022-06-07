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
	cout << "Ключ : " << endl;
	cin >> rec.key;
	cout << " Запись :" << endl;
	cin >> rec.val;


	Eff = table->GetEff();
	if (table->Insert(rec)) {
		cout << "Вставка выполнена" << endl;
	}
	else {
		cout << "Вставка не выполнена" << endl;
	}
	cout << "Эффективность:\n" << table->GetEff() - Eff << endl;
}

void findKey()
{
	TKey key;
	cout << "Введите ключ для поиска " << endl;
	cin >> key;

	Eff = table->GetEff();
	if (table->Find(key)) {
		cout << "Элемент найден" << endl;
	}
	else {
		cout << "Элемент не найден" << endl;
	}
	cout << "Эффективность:\n" << table->GetEff() - Eff << endl;
}

void deleteKey()
{
	TKey key;
	cout << "Введите ключ для удаления " << endl;
	cin >> key;

	Eff = table->GetEff();
	if (table->Delete(key)) {
		cout << "Элемент удален" << endl;
	}
	else {
		cout << "Элемент не удален" << endl;
	}
	cout << "Эффективность:\n" << table->GetEff() - Eff << endl;

}

void main() {
	int n = 0;
	setlocale(LC_ALL, "Russian");
	int type;
	while (true) {
		cout << "1 - Создать таблицу " << endl;
		cout << "2 - Вывести на экран" << endl;
		cout << "3 - Найти в таблице " << endl;
		cout << "4 - Удалить из таблицы " << endl;
		cout << "5 - Вставить в таблицу " << endl;
		cout << "Введите число: " << endl;
		cin >> n;

		switch (n)
		{
		case 1:
		{
			cout << "Доступные типы таблиц:\n";
			cout << "1  -  Просматриваемая (TScanTable);\n";
			cout << "2  -  Отсортированная (TSortTable);\n";
			cout << "3  -  Хэш-таблица на массиве (TArrayHash);\n";
			cout << "4  -  Таблица на дереве (TTreeTable);\n";
			cout << "5  -  Таблица на сбалансированном дереве (TBalTree);\n";
			cout << "Введите тип таблицы: " << endl;
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