#pragma once
#include<vector>

typedef std::vector<std::string> Strings;

class Splitter {
public:
	Strings split(std::string const& string, char const& delim);
};