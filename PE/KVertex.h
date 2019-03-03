#pragma once

#include "KRecord.h"
#include <iostream>

class KVertex
{
public:
	KVertex();

	KVertex(
		int const level,
		int const index,
		KRecord& record);

	~KVertex();

	friend std::ostream& operator << (std::ostream& os, KVertex const& vertex);

	int const& getLevel() const;

	void setLevel(int const& value);

	int const& getIndex() const;

	void setIndex(int const& value);

	KRecord const& getRecord() const;

	void setRecord(KRecord const* value);

private:
	int level;
	int index;
	KRecord const* record;
};

