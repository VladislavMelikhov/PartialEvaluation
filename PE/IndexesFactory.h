#pragma once
#include "Indexes.h"


template <int Num, typename Indexes = Indexes<>>
class IndexesFactory {

};

template <int Num, int ... Nums>
class IndexesFactory<Num, Indexes<Nums...>> 
	: public IndexesFactory<Num - 1, Indexes<Nums ..., sizeof ... (Nums)>> {

};

template <int ... Nums>
class IndexesFactory<0, Indexes<Nums...>> {
public:
	typedef Indexes<Nums...> IndexesType;
};