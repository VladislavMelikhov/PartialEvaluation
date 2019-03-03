#include "pch.h"
#include "KVertex.h"


KVertex::KVertex() : level(0), index(0), record(nullptr)
{
}

KVertex::KVertex(
	int const level, 
	int const index, 
	KRecord & record) : level(level), index(index), record(&record)
{
}


KVertex::~KVertex()
{
}

int const& KVertex::getLevel() const
{
	return level;
}

void KVertex::setLevel(int const& value)
{
	level = value;
}

int const& KVertex::getIndex() const
{
	return index;
}

void KVertex::setIndex(int const& value)
{
	index = value;
}

KRecord const& KVertex::getRecord() const
{
	return *record;
}

void KVertex::setRecord(KRecord const* value)
{
	record = value;
}

std::ostream & operator<<(std::ostream & os, KVertex const& vertex)
{
	for (int i = 0; i < vertex.level; ++i) {
		os << "\t";
	}

	os << "("
		<< vertex.level << ", "
		<< vertex.index;

	if (vertex.record != nullptr) {
		os << ", " << *(vertex.record);
	}
	os << ")";

	return os;
}
