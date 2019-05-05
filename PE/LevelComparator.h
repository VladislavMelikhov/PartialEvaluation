#pragma once
#include "Key.h"
#include "Level.h"

template <
	typename Type, int KeySize, int LevelsCount, 
	typename Key, 
	typename Level
>
class LevelComparator;

template <
	typename Type, int KeySize, int LevelsCount, 
	int Index, int ... Indexes, 
	int Number, int ... Numbers
>
class LevelComparator<
	Type, KeySize, LevelsCount,
	Key<Index, Indexes...>,
	Level<Number, Numbers...>
> {
private:
	static int const index = KeySize - sizeof...(Indexes) - 1;
	static int const level = LevelsCount - sizeof...(Numbers) - 1;

public:
	static int compare(Type const& first, Type const& second) {
		
		if (std::get<Index>(first) != std::get<Index>(second)) {
			return level;
		}
		else {
			if (index == Number) {
				return LevelComparator<
					Type, KeySize, LevelsCount, 
					Key<Indexes...>, 
					Level<Numbers...>
				>::compare(first, second);
			}
			else {
				return LevelComparator<
					Type, KeySize, LevelsCount,
					Key<Indexes...>,
					Level<Number, Numbers...>
				>::compare(first, second);
			}
		}
	}
};

template <
	typename Type, int KeySize, int LevelsCount,
	int Index, int ... Indexes,
	int Number
>
class LevelComparator<
	Type, KeySize, LevelsCount,
	Key<Index, Indexes...>,
	Level<Number>
> {
private:
	static int const index = KeySize - sizeof...(Indexes) - 1;
	static int const level = LevelsCount - 1;

public:
	static int compare(Type const& first, Type const& second) {

		if (std::get<Index>(first) != std::get<Index>(second)) {
			return level;
		}
		else {
			return LevelComparator<
				Type, KeySize, LevelsCount,
				Key<Indexes...>,
				Level<Number>
			>::compare(first, second);
		}
	}
};

template <
	typename Type, int KeySize, int LevelsCount,
	int Index,
	int Number, int ... Numbers
>
class LevelComparator<
	Type, KeySize, LevelsCount,
	Key<Index>,
	Level<Number, Numbers...>
> {
private:
	static int const index = KeySize - 1;
	static int const level = LevelsCount - sizeof...(Numbers) - 1;

public:
	static int compare(Type const& first, Type const& second) {

		if (std::get<Index>(first) != std::get<Index>(second)) {
			return level;
		}
		else {
			return LevelComparator<
				Type, KeySize, LevelsCount,
				Key<Index>,
				Level<Numbers...>
			>::compare(first, second);
		}
	}
};

template <
	typename Type, int KeySize, int LevelsCount,
	int Index,
	int Number
>
class LevelComparator<
	Type, KeySize, LevelsCount,
	Key<Index>,
	Level<Number>
> {
private:
	static int const index = KeySize - 1;
	static int const level = LevelsCount - 1;

public:
	static int compare(Type const& first, Type const& second) {

		if (std::get<Index>(first) != std::get<Index>(second)) {
			return level;
		}
		else {
			return level + 1;
		}
	}
};