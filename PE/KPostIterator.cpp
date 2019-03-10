#include "pch.h"
#include "KPostIterator.h"

KPostIterator::KPostIterator(Records const& records, int const treeHeight) :
	vertex(KVertex()),
	stack(VertexesStack()),
	iterator(records.begin()),
	end(--records.end()),
	currentRecord(&(*iterator)),
	nextRecord(nullptr),
	treeHeight(treeHeight),
	branchHeight(treeHeight)
{
}

KPostIterator::~KPostIterator()
{
}

KPostIterator& KPostIterator::operator++()
{
	while (true) {
		while (vertex.getLevel() <= treeHeight) {
			stack.push(vertex);
			vertex.setLevel(vertex.getLevel() + 1);
			vertex.setRecord(currentRecord);
		}
		if (stack.empty()) {
			vertex.setRecord(nullptr);
			break;
		}
		vertex = stack.top();
		stack.pop();

		if (vertex.getLevel() == treeHeight) {
			
			onNext(vertex.getRecord());

			if (iterator == end) {
				vertex.setLevel(treeHeight + 1);
			}
			else {
				nextRecord = &(*(++iterator));
				branchHeight = (*currentRecord).compare(*nextRecord);

				if (branchHeight == treeHeight) {
					currentRecord = nextRecord;
					vertex.setIndex(vertex.getIndex() + 1);
					vertex.setRecord(nextRecord);
				}
				else {
					vertex.setLevel(treeHeight + 1);
				}
			}
			break;
		}
		else {

			onBranch(vertex.getLevel());

			if (vertex.getLevel() == branchHeight) {
				currentRecord = nextRecord;
				//vertex.setIndex(vertex.getIndex() + 1);
				vertex.setRecord(nextRecord);
			}
			else {
				vertex.setLevel(treeHeight + 1);
			}
			break;
		}
	}
	return *this;
}

bool KPostIterator::operator!=(KPostIterator const& other) const
{
	KRecord const& record = vertex.getRecord();
	KRecord const& otherRecord = other.vertex.getRecord();

	if (&record == nullptr && &other == nullptr) {
		return true;
	}
	else if (&record == nullptr) {
		return false;
	}
	else {
		return record != otherRecord;
	}
}

int const& KPostIterator::getTreeHeight()
{
	return treeHeight;
}
