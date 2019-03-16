#pragma once
#include <string>
#include <vector>
#include "KRecord.h"
#include "KSumIterator.h"

typedef std::vector<KRecord> Records;

class KFile
{
public:
	explicit KFile(std::string const filename);

	~KFile();

	friend std::ostream& operator << (std::ostream& os, KFile const& file);

	//KSumIterator beginSum();
	//KSumIterator endSum();

private:
	
	Records records;
};