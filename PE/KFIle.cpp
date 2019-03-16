#include "pch.h"
#include <fstream>
#include "KFile.h"

KFile::KFile(std::string const filename) : records(Records())
{
	std::ifstream fin(filename);
	KRecord record = KRecord();
	while (fin >> record) {
		records.push_back(record);
	}
}

KFile::~KFile()
{
}

//KSumIterator KFile::beginSum()
//{
//	return dynamic_cast<KSumIterator&>(++KSumIterator(records, 4));
//}
//
//KSumIterator KFile::endSum()
//{
//	return KSumIterator(records, 4);
//}

std::ostream& operator<<(std::ostream& os, KFile const& file)
{
	for (KRecord const& record : file.records) {
		os << record << std::endl;
	}
	return os;
}
