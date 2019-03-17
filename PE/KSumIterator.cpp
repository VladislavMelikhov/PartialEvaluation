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


void printKeys(bool const& recordSign, int const& level, KTRecord const& record) {
	int* const keys = record.getKeys();
	std::cout << "(" << recordSign << ", ";

	int i = 0;
	for (; i < level; ++i) {
		std::cout << keys[i] << ", ";
	}
	for (; i < record.getN(); ++i) {
		std::cout << "_ ,";
	}
}

void KSumIterator::onNext(KTRecord const& record) const {
	printKeys(0, record.getN(), record);
	std::cout << record.getValue() << ")" << std::endl;
	sum[getTreeHeight()] += record.getValue();
}

void KSumIterator::onBranch(int const& level, KTRecord const& record) const {
	printKeys(1, level, record);
	int const nextLevel = level + 1;

	sum[level] += sum[nextLevel];
	std::cout << sum[nextLevel] << ")" << std::endl;
	sum[nextLevel] = 0;
}