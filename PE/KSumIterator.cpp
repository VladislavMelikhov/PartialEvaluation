#include "pch.h"
#include "KSumIterator.h"

KSumIterator::KSumIterator(TRecords const& records, int const treeHeight) :
	KPostIterator(records, treeHeight),
	sum(new int[treeHeight + 1])
{
	for (int i = 0; i <= treeHeight; ++i) {
		sum[i] = 0;
	}
}

KSumIterator::~KSumIterator()
{
	delete[] sum;
}

KSumIterator::KSumIterator(KSumIterator const& other) : 
	KPostIterator(other),
	sum(new int[other.getTreeHeight() + 1])
{
	for (int i = 0; i <= other.getTreeHeight(); ++i) {
		sum[i] = other.sum[i];
	}
}

int const& KSumIterator::getResult()
{
	return sum[0];
}

void KSumIterator::onNext(KTRecord const& record) const {
	std::cout << record << std::endl;
	sum[getTreeHeight()] += record.getValue();
}

void KSumIterator::onBranch(int const& level) const {
	int const nextLevel = level + 1;

	sum[level] += sum[nextLevel];
	std::cout << sum[nextLevel] << std::endl;
	sum[nextLevel] = 0;
}