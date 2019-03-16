#pragma once
#include <string>
#include <vector>
#include "KTRecord.h"
#include "KSumIterator.h"

typedef std::vector<KTRecord> TRecords;

class KTFile
{
public:
	explicit KTFile(std::string const filename, int const n);

	~KTFile();

	friend std::ostream& operator << (std::ostream& os, KTFile const& file);

	//KTFile& operator = (KTFile const& other);

	KSumIterator beginSum();
	KSumIterator endSum();

	TRecords const& getRecords() const;

private:
	TRecords records;
	int const n;
};