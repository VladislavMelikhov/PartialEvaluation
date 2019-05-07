#pragma once
#include "TFile.h"

template <typename ... Files>
class TStorage {
public:
	std::tuple<Files...> files;
public:
	TStorage(std::tuple<Files...> files) : files(files) {}
};