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
#include "KTLinkIterator.h"
#include "Key.h"
#include "TRecord.h"
#include "Splitter.h"
#include "Converter.h"
#include "IndexesFactory.h"
#include "TupleMaker.h"
#include "TRecord.h"

void testSingleFileIterator() {
	std::cout << "Test single source: " << std::endl;
	KTFile file = KTFile("../PE/input/Records.txt", 3);
	std::cout << file;

	std::cout << "Result: " << std::endl;
	KSumIterator& it = file.beginSum();
	KSumIterator const& end = file.endSum();

	while (it != end) {
		++it;
	}
}

void testMultipleFilesIterator() {
	std::cout << "Test multiple sources: " << std::endl;
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

	std::cout << "Result: " << std::endl;
	KTLinkIterator& it = storage.beginLink();
	KTLinkIterator const& end = storage.endLink();

	try {
		while (it != end) { 
			++it; 
		}
	}
	catch (std::logic_error const& e) {
		std::cout << e.what() << std::endl;
	}
}

void testTupleMaker() {

	TupleMaker<std::string, int, double> tupleMaker = TupleMaker<std::string, int, double>();

	std::string first;
	int second;
	double third;
	std::tie(first, second, third) = tupleMaker.makeTuple("Hello; 23; 12.34", ';');

	std::cout << first << std::endl;
	std::cout << second << std::endl;
	std::cout << third << std::endl;
}

int main()
{

	Key<1, 2, 3> key = Key<1, 2, 3>();
	TRecord<std::tuple<std::string, int, int, int>, Key<1, 2, 3>>;

	Strings strings = Splitter().split("Hello, world, 2019", ',');
	for (std::string const& string : strings) {
		std::cout << string << " ";
	}

	int x = Converter<int>().convert("56");
	std::cout << x + 1;


	Indexes<0, 1, 2> idx = Indexes<0, 1, 2>();

	IndexesFactory<3>::IndexesType idx2 = Indexes<0, 1, 2>();


	testTupleMaker();

	TRecord<std::tuple<std::string, int, double>, Key<0, 1>> tRecord;
	//std::cin >> tRecord;
	//std::cout << tRecord;

	std::ifstream fin("../PE/input/TRecords.txt");

	while (fin >> tRecord) {
		std::cout << tRecord << std::endl;
	}
	//testMultipleFilesIterator();
	//testSingleFileIterator();

	//std::tuple<int, double> t = std::make_tuple(1, 2.2);
	//printTuple(t);
	//std::get<0>(t) = 12;
	//printTuple(t);
	//std::cout << it.getResult() << ":)" << std::endl;

	//performTraversal(records, 4);

	//typedef std::tuple<int, int, double> Tuple;
	//Tuple tuple = std::make_tuple(4, 3, 1.1);
	//printTuple(std::cout, tuple);
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
