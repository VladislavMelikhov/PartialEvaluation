#pragma once
#include <tuple>
#include "Converter.h"
#include "Splitter.h"

template <typename ...Types>
class TupleMaker {

	std::tuple<Types...> makeTuple(std::string const& source) {
		Strings strings = Splitter().split(source);
		return std::tuple<Types...>(Converter<Types>.convert(strings[]));
	}
};
