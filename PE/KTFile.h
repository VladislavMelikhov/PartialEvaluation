#pragma once
#include <string>
#include <vector>
#include "KTRecord.h"

template <int N>
class KTFile
{
public:
	explicit KTFile(std::string const filename);

	~KTFile();

	template <int T>
	friend std::ostream& operator << (std::ostream& os, KTFile<T> const& file);

//TODO: records should be private

	std::vector<KTRecord<N>> records;
};

template<int T>
inline std::ostream & operator<<(std::ostream& os, KTFile<T> const& file)
{
	for (KTRecord<T> const& record : file.records) {
		os << record << std::endl;
	}
	return os;
}

template<int N>
inline KTFile<N>::KTFile(std::string const filename)
{
	std::ifstream fin(filename);
	KTRecord<N> record = KTRecord<N>();
	while (fin >> record) {
		records.push_back(record);
	}
}

template<int N>
inline KTFile<N>::~KTFile()
{
}
