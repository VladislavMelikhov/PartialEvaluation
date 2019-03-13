#include "pch.h"
#include "KTFile.h"
#include <fstream>

std::ostream & operator<<(std::ostream& os, KTFile const& file)
{
	for (KTRecord const& record : file.records) {
		os << record << std::endl;
	}
	return os;
}

KTFile::KTFile(std::string const filename, int const n) : n(n)
{
	std::ifstream fin(filename);
	KTRecord record = KTRecord(n);
	while (fin >> record) {
		records.push_back(record);
	}
}

KTFile::~KTFile()
{
}
