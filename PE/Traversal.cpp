#include "pch.h"
#include "Traversal.h"
#include "KVertex.h"
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
	
}
