#pragma once

#include <iostream>

class KTRecord {
public:
	explicit KTRecord(int const n);

	~KTRecord();

	KTRecord(KTRecord const& other);

	friend std::ostream& operator << (std::ostream& os, KTRecord const& record);

	friend std::istream& operator >> (std::istream& is, KTRecord& record);

	int compare(KTRecord const& other) const;

	int* const getKeys() const;

	int const& getN() const;

	int const& getValue() const;

	bool const containsKey(KTRecord const& other) const;

private:
	int const n;
	int* const keys;
	int value;
};