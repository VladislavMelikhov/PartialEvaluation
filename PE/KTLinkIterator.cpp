#include "pch.h"
#include "KTLinkIterator.h"
#include <sstream>

KTLinkIterator::KTLinkIterator(TFiles const& files): KTPostIterator(files)
{
}

KTLinkIterator::~KTLinkIterator()
{
}

TVertexesStack reverseStack(TVertexesStack vertexesStack) {
	TVertexesStack reversedStack = TVertexesStack();

	while (!vertexesStack.empty()) {
		reversedStack.push(vertexesStack.top());
		vertexesStack.pop();
	}
	return reversedStack;
}

void printKeys(KTRecord const& record) {
	int* const keys = record.getKeys();
	std::cout << "(" << keys[0];

	for (int i = 1; i < record.getN(); ++i) {
		std::cout << ", " << keys[i];
	}
}

void validateRecords(KTRecord const& previousRecord, KTRecord const& currentRecord) {

	if (!previousRecord.containsKey(currentRecord)) {
		std::stringstream stream = std::stringstream();
		stream << "Record " << previousRecord << " doesn't match any record of parent file.";

		throw std::logic_error(stream.str());
	}
}

void validateRecordsChain(KTRecord const& record, TVertexesStack vertexesStack) {
	KTRecord const* previousRecord = &record;
	KTRecord const* currentRecord = previousRecord;

	while (!vertexesStack.empty()) {
		currentRecord = &vertexesStack
			.top()
			.getRecord();

		validateRecords(*previousRecord, *currentRecord);
		previousRecord = currentRecord;
		vertexesStack.pop();
	}
}

void KTLinkIterator::onNext(KTRecord const& record)
{	
	TVertexesStack const& stack = getStack();

	validateRecordsChain(record, stack);
	TVertexesStack reversedStack = reverseStack(stack);
	printKeys(record);

	while (!reversedStack.empty()) {
		std::cout << ", " << reversedStack
			.top()
			.getRecord()
			.getValue();
		reversedStack.pop();
	}

	std::cout << ", " << record.getValue() << ")" << std::endl;
}