#pragma once
#include "TRecord.h"

template <typename Tuple, typename Key>
class TFile {

public:
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

private:
	std::vector<TRecord<Tuple, Key>> records;
};