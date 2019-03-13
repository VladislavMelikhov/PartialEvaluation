#pragma once
#include <string>
#include <vector>
#include "KTRecord.h"

class KTFile
{
public:
	explicit KTFile(std::string const filename, int const n);

	~KTFile();

	friend std::ostream& operator << (std::ostream& os, KTFile const& file);

	//KTFile& operator = (KTFile const& other);

//TODO: records should be private

	std::vector<KTRecord> records;
	int const n;
};