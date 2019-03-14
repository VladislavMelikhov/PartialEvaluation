#include "pch.h"
#include "KTRecord.h"


KTRecord::KTRecord(int const n) : n(n), keys(new int[n])
{
}

KTRecord::~KTRecord()
{
	delete[] keys;
}

KTRecord::KTRecord(KTRecord const & other) : n(other.n), keys(new int[other.n])
{
	for (int i = 0; i < n; ++i) {
		keys[i] = other.keys[i];
	}
	value = other.value;
}


int const& min(int const& a, int const& b) {
	return a < b ? a : b;
}

int KTRecord::compare(KTRecord const& other) const
{
	for (int i = 0; i < min(n, other.n); ++i) {
		if (keys[i] != other.keys[i]) {
			return i;
		}
	}
	return 0;
}

std::ostream& operator << (std::ostream& os, KTRecord const& record) {
	os << "(";
	for (int i = 0; i < record.n; ++i) {
		os << record.keys[i] << ", ";
	}
	os << record.value << ")";
	return os;
}

std::istream& operator >> (std::istream& is, KTRecord& record) {
	char spacing = '_';
	is >> spacing;
	for (int i = 0; i < record.n; ++i) {
		is >> record.keys[i] >> spacing;
	}
	is >> record.value >> spacing;
	return is;
}
