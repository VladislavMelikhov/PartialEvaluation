#pragma once

#include "VertexMaker.h"

template <typename ... Files>
class StackMaker {

public:

	static decltype(auto) makeStack() {
		return std::make_tuple(VertexMaker<Files>::makeVertex()...);
	}
};