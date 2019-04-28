#pragma once
template<typename Type, int N>
class TuplePrinter;

template<typename Type, int N>
class TuplePrinter {
public:
	static std::ostream& print(std::ostream& os, Type const& tuple) {
		TuplePrinter<Type, N - 1>::print(os, tuple);
		os << ", " << std::get<N - 1>(tuple);
		return os;
	}
};

template<typename Type>
class TuplePrinter<Type, 1> {
public:
	static std::ostream& print(std::ostream& os, Type const& tuple) {
		os << std::get<0>(tuple);
		return os;
	}
};

template<typename ... Args>
std::ostream& printTuple(std::ostream& os, std::tuple<Args...> const& tuple) {
	os << "(";
	TuplePrinter<std::tuple<Args...>, sizeof...(Args)>::print(os, tuple);
	os << ")";
	return os;
}