#include "pch.h"
#include "Splitter.h"
#include <sstream>

Strings Splitter::split(std::string const& splitable, char const& delim)
{
	Strings strings = Strings();
	std::string string = "";
	std::istringstream stream(splitable);
	while (std::getline(stream, string, delim)) {
		strings.push_back(string);
	}
	return strings;
}
