#include "pch.h"
#include "KTLinkIterator.h"

KTLinkIterator::KTLinkIterator(TFiles const& files): KTPostIterator(files)
{
}

KTLinkIterator::~KTLinkIterator()
{
}

void KTLinkIterator::onNext(KTRecord const& record)
{
	int* const keys = record.getKeys();
	std::cout << "(" << keys[0];

	for (int i = 1; i < record.getN(); ++i) {
		std::cout << ", " << keys[i];
	}
	
	TVertexesStack vertexesStack = TVertexesStack(getStack());
	TVertexesStack reversedStack = TVertexesStack();

	while (!vertexesStack.empty()) {
		reversedStack.push(vertexesStack.top());
		vertexesStack.pop();
	}

	while (!reversedStack.empty()) {
		std::cout << ", " << reversedStack
			.top()
			.getRecord()
			.getValue();
		reversedStack.pop();
	}

	std::cout << ", " << record.getValue() << ")" << std::endl;
}
