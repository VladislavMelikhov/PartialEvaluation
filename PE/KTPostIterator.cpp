#include "pch.h"
#include "KTPostIterator.h"

KTPostIterator::KTPostIterator(TFiles const& files):
	vertex(KTVertex()),
	stack(TVertexesStack()),
	iterators(RecordsIterators()),
	ends(RecordsIterators()),
	currentRecord(nullptr),
	nextRecord(nullptr),
	treeHeight(files.size() - 1),
	branchHeight(treeHeight)
{
	FilesIterator iterator = files.begin();
	FilesIterator end = files.end();

	for (; iterator != end; ++iterator) {
		TRecords const& records = (*iterator).getRecords();
		iterators.push_back(records.begin());
		ends.push_back(records.end());
	}
}

KTPostIterator::~KTPostIterator()
{
}

KTPostIterator& KTPostIterator::operator++()
{
	while (true) {
		while (vertex.getLevel() <= treeHeight) {
			currentRecord = &(*iterators[vertex.getLevel()]);
			vertex.setRecord(currentRecord);
			stack.push(vertex);
			++iterators[vertex.getLevel()];
			vertex.setLevel(vertex.getLevel() + 1);
		}
		if (stack.empty()) {
			vertex.setRecord(nullptr);
			break;
		}
		vertex = stack.top();
		stack.pop();

		if (vertex.getLevel() == treeHeight) {

			onNext(vertex.getRecord());

			if (iterators[treeHeight] == ends[treeHeight]) {
				vertex.setLevel(treeHeight + 1);
			}
			else {
				nextRecord = &(*(iterators[treeHeight]));
				branchHeight = (*currentRecord).compare(*nextRecord);

				if (branchHeight == treeHeight) {
					currentRecord = nextRecord;
					vertex.setRecord(nextRecord);
				}
				else {
					vertex.setLevel(treeHeight + 1);
				}
			}
			break;
		}
		else {
			if (vertex.getLevel() == branchHeight) {
				currentRecord = nextRecord;
				vertex.setRecord(nextRecord);
			}
			else {
				vertex.setLevel(treeHeight + 1);
			}
		}
	}
	return *this;
}

bool KTPostIterator::operator!=(KTPostIterator const& other) const
{
	KTRecord const& record = vertex.getRecord();
	KTRecord const& otherRecord = other.vertex.getRecord();

	if (&record == nullptr && &other == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

TVertexesStack const & KTPostIterator::getStack() const
{
	return stack;
}
