#pragma once
#include "TFile.h"
#include "IndexesFactory.h"
#include "RecordsIteratorsFactory.h"
#include "StackMaker.h"
#include "StackWrapperMaker.h"
#include "StorageIterator.h"

template <typename ... Files>
class TStorage {
public:
	//TODO: files should be private
	std::tuple<Files...> files;

public:

	TStorage(std::tuple<Files...> files) : files(files) {}

	auto cbegin() const {

		typedef IndexesFactory<sizeof...(Files)>::IndexesType Indexes;

		auto wrappedStack = wrapStack(
			StackMaker<Files...>::makeStack(),
			RecordsIteratorsFactory<std::tuple<Files...>, Indexes>::getBegins(files),
			RecordsIteratorsFactory<std::tuple<Files...>, Indexes>::getEnds(files)
		);
		return ++StorageIterator<decltype(wrappedStack)>(wrappedStack, false);
	}

	auto cend() const {

		typedef IndexesFactory<sizeof...(Files)>::IndexesType Indexes;

		auto wrappedStack = wrapStack(
			StackMaker<Files...>::makeStack(),
			RecordsIteratorsFactory<std::tuple<Files...>, Indexes>::getBegins(files),
			RecordsIteratorsFactory<std::tuple<Files...>, Indexes>::getEnds(files)
		);
		return StorageIterator<decltype(wrappedStack)>(wrappedStack, true);
	}
};