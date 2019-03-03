#pragma once
template<typename Type, int N>
class TuplePrinter;

template<typename Type, int N>
class TuplePrinter {
public:
	static void print(Type const& tuple) {
		TuplePrinter<Type, N - 1>::print(tuple);
		std::cout << ", " << std::get<N - 1>(tuple);
	}
};

template<typename Type>
class TuplePrinter<Type, 1> {
public:
	static void print(Type const& tuple) {
		std::cout << std::get<0>(tuple);
	}
};

template<typename ... Args>
void printTuple(std::tuple<Args...>& tuple) {
	std::cout << "(";
	TuplePrinter<std::tuple<Args...>, sizeof...(Args)>::print(tuple);
	std::cout << ")";
}