#include "pch.h"
#include "Split.h"
#include <sstream>

Strings split(std::string const& splitable, char const& delim)
{
	Strings strings = Strings();
	std::string string = "";
	std::istringstream stream(splitable);
	while (std::getline(stream, string, delim)) {
		strings.push_back(string);
	}
	return strings;
}
