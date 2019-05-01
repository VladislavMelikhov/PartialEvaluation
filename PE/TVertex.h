#pragma once

#include <iostream>
#include "TRecord.h"

template <typename Tuple, typename Key>
class TVertex {
public:

	TVertex() : level(0), record(nullptr) {};

	void setLevel(int const value) {
		level = value;
	}

	int const& getLevel() const {
		return level;
	}

	void setRecord(TRecord<Tuple, Key> const* value) {
		record = value;
	}

	TRecord<Tuple, Key> const& getRecord() const {
		return record;
	}

	friend std::ostream& operator << (std::ostream& os, TVertex<Tuple, Key> const& vertex) {
		os << "(" << vertex.level;
		if (vertex.record != nullptr) {
			os << ", " << *vertex.record;
		}
		os << ")";
		return os;
	}

private:
	int level;
	TRecord<Tuple, Key> const* record;
};