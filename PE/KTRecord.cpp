#include "pch.h"
#include "KTRecord.h"


KTRecord::KTRecord(int const n) : n(n), keys(new int[n])
{
}

KTRecord::~KTRecord()
{
	delete[] keys;
}

KTRecord::KTRecord(KTRecord const& other) : n(other.n), keys(new int[other.n])
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
	//TODO: debug log
	//std::cout << "Compare: " << n << " " << other.n << std::endl;
	int const min_n = min(n, other.n);
	for (int i = 0; i < min_n; ++i) {
		if (keys[i] != other.keys[i]) {
			return i;
		}
	}
	if (value != other.value) {
		return min_n;
	}
	return min_n + 1;
}

int* const KTRecord::getKeys() const
{
	return keys;
}

int const& KTRecord::getN() const
{
	return n;
}

int const& KTRecord::getValue() const
{
	return value;
}

bool const KTRecord::containsKey(KTRecord const& other) const
{
	int const other_n = other.n;
	if (other_n > n) {
		return false;
	}
	else {
		for (int i = 0; i < other_n; ++i) {
			if (keys[i] != other.keys[i]) {
				return false;
			}
		}
		return true;
	}
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
