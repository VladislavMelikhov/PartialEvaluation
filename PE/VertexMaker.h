#pragma once

#include "TFile.h"

template <typename File>
class VertexMaker;


template <typename Tuple, typename Key, typename Level>
class VertexMaker<TFile<Tuple, Key, Level>> {
public:
	typedef TVertex<Tuple, Key, Level> VertexType;

	static VertexType makeVertex() {
		return VertexType();
	}
};