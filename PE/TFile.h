#pragma once
#include "TRecord.h"
#include "TVertex.h"
#include "FileIterator.h"

template <typename Tuple, typename Key, typename Level>
class TFile {

public:
	typedef TVertex<Tuple, Key, Level> VertexType;
	typedef TRecord<Tuple, Key, Level> RecordType;
	typedef typename TRecord<Tuple, Key, Level>::TupleType Tuple;
	typedef std::vector<RecordType> Records;
	typedef FileIterator<const Tuple, Key, Level, typename Records::const_iterator> const_iterator;

	explicit TFile(std::string const& filepath) {
		std::ifstream fin(filepath);
		RecordType record;
		while (fin >> record) {
			records.push_back(record);
		}
	}

	friend std::ostream& operator<<(std::ostream& os, TFile<Tuple, Key, Level> const& file) {
		for (RecordType const& record : file.records) {
			os << record << std::endl;
		}
		return os;
	}

	Records const& getRecords() const {
		return records;
	}

	const_iterator cbegin() {
		return ++const_iterator(records.begin(), records.end());
	}

	const_iterator cend() {
		return const_iterator(records.begin(), records.end());
	}

private:
	Records records;
};