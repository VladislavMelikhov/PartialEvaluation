#include "pch.h"
#include "KTBasePostIterator.h"

KTBasePostIterator::KTBasePostIterator(int const& treeHeight) :
	vertex(KTVertex()),
	stack(TVertexesStack()),
	currentRecord(nullptr),
	nextRecord(nullptr),
	treeHeight(treeHeight),
	branchHeight(treeHeight)
{
}

KTBasePostIterator::~KTBasePostIterator()
{
}

KTBasePostIterator& KTBasePostIterator::operator++()
{
	while (true) {
		while (vertex.getLevel() <= treeHeight) {
			onPush(vertex.getLevel());
			vertex.setRecord(currentRecord);
			stack.push(vertex);
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

			if (isEndOfSource()) {
				vertex.setLevel(treeHeight + 1);
			}
			else {
				nextRecord = &readNext();
				branchHeight = getBranchHeight(*currentRecord, *nextRecord);

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
			onBranch(vertex.getLevel());

			if (vertex.getLevel() == branchHeight) {
				currentRecord = nextRecord;
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

bool KTBasePostIterator::operator!=(KTBasePostIterator const& other) const
{
	KTRecord const& record = vertex.getRecord();
	KTRecord const& otherRecord = other.vertex.getRecord();

	if (&record == nullptr && &otherRecord == nullptr) {
		return false;
	}
	else {
		//TODO: compare records!
		return true;
	}
}

int const KTBasePostIterator::getBranchHeight(KTRecord const& first, KTRecord const& second) const
{
	return first.compare(second);
}

TVertexesStack const& KTBasePostIterator::getStack() const
{
	return stack;
}

int const& KTBasePostIterator::getTreeHeight() const
{
	return treeHeight;
}

void KTBasePostIterator::setCurrentRecord(KTRecord const& value)
{
	currentRecord = &value;
}
