#pragma once

#include <iostream>
#include "TRecord.h"

template <typename Tuple, typename Key, typename Level>
class TVertex {

	typedef TRecord<Tuple, Key, Level> Record;

public:

	TVertex() : level(0), record(nullptr) {};

	void setLevel(int const value) {
		level = value;
	}

	int const& getLevel() const {
		return level;
	}

	void setRecord(Record const* value) {
		record = value;
	}

	Record const& getRecord() const {
		return *record;
	}

	friend std::ostream& operator << (std::ostream& os, TVertex<Tuple, Key, Level> const& vertex) {
		os << "(" << vertex.level;
		if (vertex.record != nullptr) {
			os << ", " << *vertex.record;
		}
		os << ")";
		return os;
	}

private:
	int level;
	Record const* record;
};