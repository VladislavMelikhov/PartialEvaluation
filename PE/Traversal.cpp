#include "pch.h"
#include "Traversal.h"
#include "KVertex.h"
#include "KTVertex.h"
#include "KTFile.h"
#include <stack>

typedef std::stack<KVertex> VertexesStack;

void performTraversal(
	std::vector<KRecord> const& records, 
	const int height, 
	int* sum) {

	KVertex vertex = KVertex();
	VertexesStack stack = VertexesStack();
	std::vector<KRecord>::const_iterator iterator = records.begin();
	std::vector<KRecord>::const_iterator end = --records.end();

	KRecord const* currentRecord = &(*iterator);
	KRecord const* nextRecord = nullptr;
	int k = height;

	while (true) {
		while (vertex.getLevel() <= height) {
			stack.push(vertex);
			vertex.setLevel(vertex.getLevel() + 1);
			vertex.setRecord(currentRecord);
		}
		if (stack.empty()) {
			break;
		}
		vertex = stack.top();
		stack.pop();

		if (vertex.getLevel() == height) {
			std::cout << vertex << std::endl;
			sum[height] += vertex
				.getRecord()
				.getValue();

			if (iterator == end) {
				vertex.setLevel(height + 1);
			}
			else {
				nextRecord = &(*(++iterator));
				k = (*currentRecord).compare(*nextRecord);

				if (k == height) {
					currentRecord = nextRecord;
					vertex.setIndex(vertex.getIndex() + 1);
					vertex.setRecord(nextRecord);
				}
				else {
					vertex.setLevel(height + 1);
				}
			}
		}
		else {
			std::cout << "!";
			std::cout << vertex;
			sum[vertex.getLevel()] += sum[vertex.getLevel() + 1];
			std::cout << sum[vertex.getLevel() + 1] << std::endl;
			sum[vertex.getLevel() + 1] = 0;
			if (vertex.getLevel() == k) {
				currentRecord = nextRecord;
				//vertex.setIndex(vertex.getIndex() + 1);
				vertex.setRecord(nextRecord);
			}
			else {
				vertex.setLevel(height + 1);
			}
		}
	}
}

void performTraversal(
	std::vector<KRecord> const& records, 
	const int height) {
	
	int sum[5];
	for (int i = 0; i <= 4; ++i) {
		sum[i] = 0;
	}
	performTraversal(records, 4, sum);
	for (int i = 0; i <= 4; ++i) {
		std::cout << i << " : " << sum[i] << std::endl;
	}
}

void performTraversal(KStorage const& storage)
{
	typedef std::vector<std::vector<KTRecord>::const_iterator> RecordsIterators;
	typedef std::vector<KTFile>::const_iterator FilesIterator;

	KTVertex vertex = KTVertex();
	std::stack<KTVertex> stack = std::stack<KTVertex>();
	RecordsIterators iterators = RecordsIterators();
	RecordsIterators ends = RecordsIterators();

	FilesIterator iterator = storage.files.begin();
	FilesIterator end = storage.files.end();

	for (KTFile file : storage.files) {
		std::cout << file;
	};
	
	for (; iterator != end; ++iterator) {
		iterators.push_back((*iterator).records.begin());
		ends.push_back((*iterator).records.end());
	}

	int const height = iterators.size() - 1;
	KTRecord const* currentRecord = nullptr;
	KTRecord const* nextRecord = nullptr;
	int k = height;

	while (true) {
		while (vertex.getLevel() <= height) {
			currentRecord = &(*iterators[vertex.getLevel()]);
			vertex.setRecord(currentRecord);
			std::cout << "Debug: " << *currentRecord << std::endl;
			stack.push(vertex);
			++iterators[vertex.getLevel()];
			vertex.setLevel(vertex.getLevel() + 1);
		}
		if (stack.empty()) {
			break;
		}
		vertex = stack.top();
		stack.pop();

		if (vertex.getLevel() == height) {
			std::cout << vertex << std::endl;
			
			if (iterators[height] == ends[height]) {
				vertex.setLevel(height + 1);
			}
			else {
				nextRecord = &(*(iterators[height]));
				k = (*currentRecord).compare(*nextRecord);

				if (k == height) {
					currentRecord = nextRecord;
					vertex.setRecord(nextRecord);
				}
				else {
					vertex.setLevel(height + 1);
				}
			}
		}
		else {
			std::cout << "!";
			std::cout << vertex << std::endl;
			if (vertex.getLevel() == k) {
				currentRecord = nextRecord;
				vertex.setRecord(nextRecord);
			}
			else {
				vertex.setLevel(height + 1);
			}
		}
	}
}
