#pragma once

#include "StackUtils.h"

template <typename Vertexes, typename Iterators>
class StackWrapper;

template <typename ... Vertexes, typename ... Iterators>
class StackWrapper<std::tuple<Vertexes...>, std::tuple<Iterators...>> {

private:


	typedef std::tuple<Iterators...> IteratorsTuple;

	int depth;

public:

	typedef std::tuple<Vertexes...> VertexesTuple;

	static int const LastIndex = sizeof...(Vertexes) - 1;

	StackWrapper(VertexesTuple const& stack,
		IteratorsTuple const& iterators,
		IteratorsTuple const& ends) : stack(stack), iterators(iterators), ends(ends), depth(0) {}

	VertexesTuple stack;
	IteratorsTuple iterators;
	IteratorsTuple ends;


	void push() {
		StackUtils<VertexesTuple, IteratorsTuple, LastIndex>::push(stack, iterators, depth);
		++depth;
	}

	void pop() {
		if (depth != 0) {
			--depth;
			StackUtils<VertexesTuple, IteratorsTuple, LastIndex>::pop(stack, depth);
		}
	}

	bool isEmpty() const {
		return depth == 0;
	}

	bool isEndOfSource() const {
		return std::get<LastIndex>(iterators) == std::get<LastIndex>(ends);
	}

	int getBranchHeight() const {
		decltype(auto) currentRecord = std::get<LastIndex>(stack).getRecord();
		decltype(auto) nextRecord = *std::get<LastIndex>(iterators);
		return currentRecord.compare(nextRecord) - 1;
	}

	VertexesTuple const& getStack() const {
		return stack;
	}

	int getDepth() const {
		return depth;
	}
};