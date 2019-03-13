#include "pch.h"
#include "KTVertex.h"

KTVertex::KTVertex() : level(0), record(nullptr)
{
}

void KTVertex::setLevel(int const value)
{
	level = value;
}

int const& KTVertex::getLevel() const
{
	return level;
}

void KTVertex::setRecord(KTRecord const* value)
{
	record = value;
}

std::ostream & operator<<(std::ostream& os, KTVertex const& vertex)
{
	os << "(" << vertex.level;
	if (vertex.record != nullptr) {
		os << ", " << *vertex.record;
	}
	os << ")";
	return os;
}
