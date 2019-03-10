#pragma once
#include "KPostIterator.h"

class KSumIterator : public KPostIterator {
public:
	KSumIterator(Records const& records, int const treeHeight);
	~KSumIterator();

	int const& getResult();
private:
	void onNext(KRecord const & record);
	void onBranch(int const level);
	int *const sum;
};