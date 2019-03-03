// PE.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include "KRecord.h"
#include "Traversal.h"
#include <tuple>
#include <string>
#include "TuplePrinter.h"

typedef std::vector<KRecord> Records;

void inputRecordsFromFile(Records & records) {
	
	std::ifstream fin("../PE/input/Records.txt");

	KRecord record = KRecord();
	while (fin >> record) {
		records.push_back(record);
	}
}

void outputRecords(Records const& records) {
	for (KRecord const& record : records) {
		std::cout << record << std::endl;
	}
}

int main()
{
	//Records records = Records();
	//inputRecordsFromFile(records);
	//outputRecords(records); 

	//performTraversal(records, 4);

	typedef std::tuple<int, int, double> Tuple;
	Tuple tuple = std::make_tuple(4, 3, 1.1);
	printTuple(tuple);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
