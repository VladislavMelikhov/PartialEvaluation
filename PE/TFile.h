#pragma once
#include "TRecord.h"
#include "FileIterator.h"

template <typename Tuple, typename Key, typename Level>
class TFile {

public:

	typedef TRecord<Tuple, Key, Level> RecordType;
	typedef std::vector<RecordType> Records;
	typedef FileIterator<Tuple, Key, Level, typename Records::const_iterator> IteratorType;

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

	IteratorType begin() {
		return ++IteratorType(records.begin(), records.end());
	}

	IteratorType end() {
		return IteratorType(records.begin(), records.end());
	}

private:
	Records records;
};