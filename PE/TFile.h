#pragma once
#include "TRecord.h"

template <typename Tuple, typename Key>
class TFile {

public:

	typedef TRecord<Tuple, Key> RecordType;

	explicit TFile(std::string const& filepath) {
		std::ifstream fin(filepath);
		TRecord<Tuple, Key> record;
		while (fin >> record) {
			records.push_back(record);
		}
	}

	friend std::ostream& operator<<(std::ostream& os, TFile<Tuple, Key> const& file) {
		for (TRecord<Tuple, Key> const& record : file.records) {
			os << record << std::endl;
		}
		return os;
	}

	std::vector<RecordType> const& getRecords() const {
		return records;
	}

private:
	std::vector<TRecord<Tuple, Key>> records;
};