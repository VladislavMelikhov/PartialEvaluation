#pragma once
#include <tuple>
#include "ConverterAdapter.h"
#include "Splitter.h"
#include "IndexesFactory.h"

template <typename ...Types>
class TupleMaker {

public:
	std::tuple<Types...> makeTuple(std::string const& source, char const& delim);
};

template<typename ...Types>
inline std::tuple<Types...> TupleMaker<Types...>::makeTuple(std::string const& source, char const& delim)
{
	Strings strings = Splitter().split(source, delim);

	typedef IndexesFactory<sizeof...(Types)>::IndexesType Indexes;
	return ConverterAdapter<Indexes, Types...>().convert(strings);
}
