#pragma once
#include <sstream>

template <typename T>
class Converter {
public:
	T convert(std::string const& convertable);
};

template<typename T>
inline T Converter<T>::convert(std::string const& convertable)
{
	std::istringstream stream(convertable);
	T converted;
	stream >> converted;
	return converted;
}
