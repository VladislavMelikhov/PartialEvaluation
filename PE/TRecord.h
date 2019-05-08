#pragma once
#include <iostream>
#include "TupleMaker.h"
#include "TuplePrinter.h"
#include "Key.h"
#include "Level.h"
#include "LevelComparator.h"

template <typename Tuple, typename Key, typename Level>
class TRecord;

template <typename ... Types, int ... Indexes, int ... Numbers>
class TRecord<std::tuple<Types...>, Key<Indexes...>, Level<Numbers...>> {


	typedef TRecord<std::tuple<Types...>, Key<Indexes...>, Level<Numbers...>> Record;

public:

	typedef std::tuple<Types...> TupleType;

	friend std::ostream& operator << (std::ostream& os, Record const& record) {
		return printTuple(os, record.tuple);
	}

	friend std::istream& operator >> (std::istream& is, Record& record) {
		std::string source;
		if (is >> source) {
			record.tuple = TupleMaker<Types...>().makeTuple(trimBraces(source), ';');
		}
		return is;
	}

	int compare(Record const& record) const {
		return LevelComparator<
			std::tuple<Types...>, sizeof...(Indexes), sizeof...(Numbers),
			Key<Indexes...>,
			Level<Numbers...>
		>::compare(tuple, record.tuple) + 1;
	}

	std::tuple<Types...> const& getTuple() const {
		return tuple;
	}

private:
	std::tuple<Types...> tuple;

	static std::string& trimBraces(std::string& string) {
		string.erase(string.begin());
		string.erase(string.end() - 1);
		return string;
	}
};