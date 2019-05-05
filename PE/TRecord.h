#pragma once
#include <iostream>
#include "TupleMaker.h"
#include "TuplePrinter.h"
#include "Key.h"
#include "LevelComparator.h"

template <typename Tp = std::tuple<>, typename key = Key<>>
class TRecord;

template <typename ... Types, int ... Indexes>
class TRecord<std::tuple<Types...>, Key<Indexes...>> {
	
public:
	friend std::ostream& operator << (std::ostream& os, TRecord<std::tuple<Types...>, Key<Indexes...>> const& record) {
		return printTuple(os, record.tuple);
	}

	friend std::istream& operator >> (std::istream& is, TRecord<std::tuple<Types...>, Key<Indexes...>>& record) {
		std::string source;
		if (is >> source) {
			record.tuple = TupleMaker<Types...>().makeTuple(trimBraces(source), ';');
		}
		return is;
	}

	int compare(TRecord<std::tuple<Types...>, Key<Indexes...>> const& record) const {
		return LevelComparator<std::tuple<Types...>, sizeof...(Indexes), Key<Indexes...>>::compare(tuple, record.tuple) + 1;
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