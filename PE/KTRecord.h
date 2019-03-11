#pragma once

#include <iostream>

template <int N>
class KTRecord {
public:
	KTRecord();

	~KTRecord();

	template <int T>
	friend std::ostream& operator << (std::ostream& os, KTRecord<T> const& record);

	template <int T>
	friend std::istream& operator >> (std::istream& is, KTRecord<T>& record);

private:
	int keys[N];
	int value;
};

template<int N>
inline KTRecord<N>::KTRecord()
{
}

template<int N>
inline KTRecord<N>::~KTRecord()
{
}

template<int N>
inline std::ostream& operator << (std::ostream& os, KTRecord<N> const& record) {
	os << "(";
	for (int i = 0; i < N; ++i) {
		os << record.keys[i] << ", ";
	}
	os << record.value << ")";
	return os;
}

template<int N>
inline std::istream& operator >> (std::istream& is, KTRecord<N>& record) {
	char spacing = '_';
	is >> spacing;
	for (int i = 0; i < N; ++i) {
		is >> record.keys[i] >> spacing;
	}
	is >> record.value >> spacing;
	return is;
}
