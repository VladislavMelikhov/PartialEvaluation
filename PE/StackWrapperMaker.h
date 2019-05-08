#pragma once

#include "StackWrapper.h"

template <typename Vertexes, typename Iterators>
StackWrapper<Vertexes, Iterators> wrapStack(Vertexes const& vertexes, Iterators const& iterators, Iterators const& ends) {
	return StackWrapper<Vertexes, Iterators>(vertexes, iterators, ends);
}
