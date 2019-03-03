#pragma once

#include <iostream>

class KRecord
{
public:
	explicit KRecord(
		int const key1, 
		int const key2, 
		int const key3, 
		int const value);

	KRecord();

	~KRecord();

	friend std::ostream& operator << (std::ostream& os, KRecord const& record);

	friend std::istream& operator >> (std::istream& is, KRecord& record);

	int compare(KRecord const& other) const;

private:
	int key1;
	int key2;
	int key3;
	int value;
};