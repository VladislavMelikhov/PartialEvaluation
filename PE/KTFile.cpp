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

KSumIterator KTFile::beginSum()
{
	return dynamic_cast<KSumIterator&>(++KSumIterator(records, n + 1));
}

KSumIterator KTFile::endSum()
{
	return KSumIterator(records, n + 1);
}

TRecords const & KTFile::getRecords() const
{
	return records;
}
