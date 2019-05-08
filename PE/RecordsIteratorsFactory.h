#pragma once

#include <tuple>
#include "Indexes.h"

template <typename Files, typename Indexes>
class RecordsIteratorsFactory;

template <typename ... Files, int ... Nums>
class RecordsIteratorsFactory<std::tuple<Files...>, Indexes<Nums...>> {
public:

	typedef std::tuple<Files...> Files;
	
	static decltype(auto) getBegins(Files const& files) {
		return std::make_tuple((std::get<Nums>(files).getRecords().begin())...);
	}

	static decltype(auto) getEnds(Files const& files) {
		return std::make_tuple((std::get<Nums>(files).getRecords().end())...);
	}
};