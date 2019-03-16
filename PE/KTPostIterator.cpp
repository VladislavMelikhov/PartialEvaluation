#include "pch.h"
#include "KTPostIterator.h"

KTPostIterator::KTPostIterator(TFiles const& files):
	KTBasePostIterator(files.size() - 1),
	iterators(RecordsIterators()),
	ends(RecordsIterators())
{
	FilesIterator iterator = files.begin();
	FilesIterator end = files.end();

	for (; iterator != end; ++iterator) {
		TRecords const& records = (*iterator).getRecords();
		iterators.push_back(records.begin());
		ends.push_back(records.end());
	}
}

void KTPostIterator::onPush(int const& level)
{
	setCurrentRecord(*iterators[level]);
	++iterators[level];
}

bool KTPostIterator::isEndOfSource() const
{
	int const& treeHeight = getTreeHeight();
	return iterators[treeHeight] == ends[treeHeight];
}

KTRecord const& KTPostIterator::readNext() const
{
	return *(iterators[getTreeHeight()]);
}
