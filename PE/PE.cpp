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
#include "KFile.h"
#include "KTFile.h"
#include "KStorage.h"

int main()
{
	KFile file = KFile("../PE/input/Records.txt");
	//std::cout << file;

	//KSumIterator& it = file.beginSum();
	//KSumIterator const& end = file.endSum();

	//for (; it != end; ++it) {
	//	std::cout << "!" << std::endl;
	//}

	KTFile f1 = KTFile("../PE/input/F1.txt", 1);
	KTFile f2 = KTFile("../PE/input/F2.txt", 2);
	KTFile f3 = KTFile("../PE/input/F3.txt", 3);

	std::cout << f1;
	std::cout << f2;
	std::cout << f3;

	std::vector<KTFile> files = std::vector<KTFile>();
	files.push_back(f1);
	files.push_back(f2);
	files.push_back(f3);

	KStorage storage = KStorage(files);

	performTraversal(storage);

	std::tuple<int, double> t = std::make_tuple(1, 2.2);
	printTuple(t);
	std::get<0>(t) = 12;
	printTuple(t);
	//std::cout << it.getResult() << ":)" << std::endl;

	//performTraversal(records, 4);

	//typedef std::tuple<int, int, double> Tuple;
	//Tuple tuple = std::make_tuple(4, 3, 1.1);
	//printTuple(tuple);
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
