#pragma once

template <typename Type, int N>
class TupleComparator;

template <typename Type, int N>
class TupleComparator {
private:
	static int const index = std::tuple_size<Type>::value - N;

public:
	static int compare(Type const& first, 
					   Type const& second) {
		
		if (std::get<index>(first) != std::get<index>(second)) {
			return index;
		}
		else {
			return TupleComparator<Type, N - 1>::compare(first, second);
		}
	}
};

template <typename Type>
class TupleComparator<Type, 1> {
private:
	static int const index = std::tuple_size<Type>::value - 1;

public:
	static int compare(Type const& first, 
					   Type const& second) {
		
		if (std::get<index>(first) != std::get<index>(second)) {
			return index;
		}
		else {
			return index + 1;
		}
	}
};

template <typename ... Args>
int compareTuples(std::tuple<Args...> const& first,
				  std::tuple<Args...> const& second) {

	return TupleComparator<std::tuple<Args...>, sizeof...(Args)>::compare(first, second);
}