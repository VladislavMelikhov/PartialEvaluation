#pragma once

#include <tuple>

template <typename Vertexes, typename Iterators, int N>
class StackUtils;

template <typename ... Vertexes, typename ... Iterators, int N>
class StackUtils<std::tuple<Vertexes...>, std::tuple<Iterators...>, N> {
public:

	typedef std::tuple<Vertexes...> VertexesTuple;
	typedef std::tuple<Iterators...> IteratorsTuple;

	static void pop(VertexesTuple& stack, int depth) {
		if (depth == N) {
			std::get<N>(stack).setRecord(nullptr);
			std::get<N>(stack).setLevel(0);
		}
		else {
			StackUtils<VertexesTuple, IteratorsTuple, N - 1>::pop(stack, depth);
		}
	}

	static void push(VertexesTuple& stack, IteratorsTuple& iterators, int depth) {
		if (depth == N) {
			decltype(auto) iterator = std::get<N>(iterators);
			std::get<N>(stack).setRecord(&(*iterator));
			std::get<N>(stack).setLevel(depth);
			++iterator;
		}
		else {
			StackUtils<VertexesTuple, IteratorsTuple, N - 1>::push(stack, iterators, depth);
		}
	}
};

template <typename ... Vertexes, typename ... Iterators>
class StackUtils<std::tuple<Vertexes...>, std::tuple<Iterators...>, 0> {
public:

	typedef std::tuple<Vertexes...> VertexesTuple;
	typedef std::tuple<Iterators...> IteratorsTuple;

	static void pop(VertexesTuple& stack, int depth) {
		if (depth == 0) {
			std::get<0>(stack).setRecord(nullptr);
			std::get<0>(stack).setLevel(0);
		}
		else {
			throw std::logic_error("Stack overflow");
		}
	}

	static void push(VertexesTuple& stack, IteratorsTuple& iterators, int depth) {
		if (depth == 0) {
			decltype(auto) iterator = std::get<0>(iterators);
			std::get<0>(stack).setRecord(&(*iterator));
			std::get<0>(stack).setLevel(depth);
			++iterator;
		}
		else {
			throw std::logic_error("Stack overflow");
		}
	}
};