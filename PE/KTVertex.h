#pragma once

#include "KTRecord.h"

class KTVertex {
public:

	KTVertex();

	void setLevel(int const value);

	int const& getLevel() const;

	void setRecord(KTRecord const* value);

	KTRecord const& getRecord() const;

	friend std::ostream& operator << (std::ostream& os, KTVertex const& vertex);

private:
	int level;
	KTRecord const * record;
};