#pragma once
#include <vector>
#include "Converter.h"
#include "Indexes.h"

typedef std::vector<std::string> Strings;

template <typename Tp = Indexes<>, typename ... Types>
class ConverterAdapter;

template <int ... Nums, typename ... Types>
class ConverterAdapter<Indexes<Nums...>, Types...> {

public:
	std::tuple<Types...> convert(Strings const& strings);
};

template<int ...Nums, typename ...Types>
inline std::tuple<Types...> ConverterAdapter<Indexes<Nums...>, Types...>::convert(Strings const& strings)
{
	return std::tuple<Types...>(
		Converter<Types>().convert(strings[Nums]) ...
	);
}
