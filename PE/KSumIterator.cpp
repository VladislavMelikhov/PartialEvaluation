#include "pch.h"
#include "KSumIterator.h"

KSumIterator::KSumIterator(Records const& records, int const treeHeight) :
	KPostIterator(records, treeHeight),
	sum(new int[treeHeight + 1])
{
	for (int i = 0; i <= treeHeight; ++i) {
		sum[i] = 0;
	}
}

KSumIterator::~KSumIterator()
{
	//delete[] sum;
}

int const& KSumIterator::getResult()
{
	return sum[0];
}

void KSumIterator::onNext(KRecord const& record) {
	std::cout << record << std::endl;
	sum[getTreeHeight()] += record.getValue();
}

void KSumIterator::onBranch(int const level) {
	int const nextLevel = level + 1;

	sum[level] += sum[nextLevel];
	std::cout << sum[nextLevel] << std::endl;
	sum[nextLevel] = 0;
}