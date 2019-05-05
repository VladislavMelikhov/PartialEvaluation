#pragma once
#include "TRecord.h"

template <typename Tuple, typename Key, typename Level>
class TFile {

public:

	typedef TRecord<Tuple, Key, Level> RecordType;

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

	std::vector<RecordType> const& getRecords() const {
		return records;
	}

private:
	std::vector<RecordType> records;
};