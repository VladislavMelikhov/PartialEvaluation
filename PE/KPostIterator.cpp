#include "pch.h"
#include "KPostIterator.h"

KPostIterator::KPostIterator(TRecords const& records, int const treeHeight) :
	KTBasePostIterator(treeHeight),
	iterator(records.begin()),
	end(records.end())
{
	setCurrentRecord(*iterator);
}

KPostIterator::~KPostIterator()
{
}

KPostIterator::KPostIterator(KPostIterator const& other) :
	KTBasePostIterator(other),
	iterator(other.iterator),
	end(other.end)
{
	//TODO: correct copy constructor
}

void KPostIterator::onPush(int const& level)
{
	if (level == getTreeHeight() && !isEndOfSource()) {
		++iterator;
	}
}

bool KPostIterator::isEndOfSource() const
{
	return iterator == end;
}

KTRecord const& KPostIterator::readNext() const
{
	return *iterator;
}

int const KPostIterator::getBranchHeight(KTRecord const& first, KTRecord const& second) const
{
	return KTBasePostIterator::getBranchHeight(first, second) + 1;
}
