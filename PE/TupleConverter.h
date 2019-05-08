#pragma once

#include <tuple>
#include "IndexesFactory.h"

template <typename ... Vertexes>
auto convertVertexesToTuples(std::tuple<Vertexes...> const& vertexes) {
	typedef IndexesFactory<sizeof...(Vertexes)>::IndexesType Indexes;
	return TupleConverter< std::tuple<Vertexes...>, Indexes>::convert(vertexes);
}

template <typename Vertexes, typename Indexes>
class TupleConverter;

template <typename ... Vertexes, int ... Numbers>
class TupleConverter<std::tuple<Vertexes...>, Indexes<Numbers...>> {

public:
	static auto convert(std::tuple<Vertexes...> const& vertexes) {
		return std::make_tuple(std::get<Numbers>(vertexes).getRecord().getTuple()...);
	}
};
