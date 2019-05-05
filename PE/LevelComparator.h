#pragma once
#include "Key.h"

template <typename Type, int KeySize, typename Key>
class LevelComparator;

template <typename Type, int KeySize, int Index, int ... Indexes>
class LevelComparator<Type, KeySize, Key<Index, Indexes...>> {
private:
	static int const index = KeySize - sizeof...(Indexes) - 1;

public:
	static int compare(Type const& first, Type const& second) {
		
		if (std::get<Index>(first) != std::get<Index>(second)) {
			return index;
		}
		else {
			return LevelComparator<Type, KeySize, Key<Indexes...>>::compare(first, second);
		}
	}
};

template <typename Type, int KeySize, int Index>
class LevelComparator<Type, KeySize, Key<Index>> {
private:
	static int const index = KeySize - 1;

public:
	static int compare(Type const& first, Type const& second) {

		if (std::get<Index>(first) != std::get<Index>(second)) {
			return index;
		}
		else {
			return index + 1;
		}
	}
};