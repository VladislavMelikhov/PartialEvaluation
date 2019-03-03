#include "pch.h"
#include "KRecord.h"

KRecord::KRecord(
	int const key1,
	int const key2,
	int const key3,
	int const value) : key1(key1), key2(key2), key3(key3), value(value)
{
}

KRecord::KRecord() : key1(0), key2(0), key3(0), value(0) 
{
}

KRecord::~KRecord()
{
}

int KRecord::compare(KRecord const & other) const
{
	if (key1 != other.key1) {
		return 1;
	}
	if (key2 != other.key2) {
		return 2;
	}
	if (key3 != other.key3) {
		return 3;
	}
	if (value != other.value) {
		return 4;
	}
	return 5;
}

std::ostream& operator<<(std::ostream& os, KRecord const& record)
{
	return os << "("
		<< record.key1 << ","
		<< record.key2 << ","
		<< record.key3 << ","
		<< record.value
		<< ")";
}

std::istream& operator>>(std::istream& is, KRecord & record)
{
	char spacing = '_';
	return is >> spacing 
		>> record.key1 >> spacing
		>> record.key2 >> spacing
		>> record.key3 >> spacing
		>> record.value >> spacing;
}
