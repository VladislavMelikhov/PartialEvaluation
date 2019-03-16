#include "pch.h"
#include "KPostIterator.h"

KPostIterator::KPostIterator(TRecords const& records, int const treeHeight) :
	KTBasePostIterator(treeHeight),
	iterator(records.begin()),
	end(--records.end())
{
	setCurrentRecord(*iterator);
}

KPostIterator::~KPostIterator()
{
}

void KPostIterator::onPush(int const& level)
{
	if (level == getTreeHeight()) {
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
