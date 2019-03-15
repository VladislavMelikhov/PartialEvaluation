#pragma once
#include <string>
#include <vector>
#include "KTRecord.h"

typedef std::vector<KTRecord> TRecords;

class KTFile
{
public:
	explicit KTFile(std::string const filename, int const n);

	~KTFile();

	friend std::ostream& operator << (std::ostream& os, KTFile const& file);

	//KTFile& operator = (KTFile const& other);

	TRecords const& getRecords() const;

private:
	TRecords records;
	int const n;
};