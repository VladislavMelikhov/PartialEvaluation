#pragma once
#include "KPostIterator.h"

class KSumIterator : public KPostIterator {
public:
	KSumIterator(TRecords const& records, int const treeHeight);
	~KSumIterator();
	KSumIterator(KSumIterator const& other);

	int const& getResult();
private:
	void onNext(KTRecord const& record) const;
	void onBranch(int const& level) const;
	int *const sum;
};