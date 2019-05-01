#pragma once
#include "KRecord.h"
#include <vector>
#include "KStorage.h"
#include "TFile.h"
#include "TVertex.h"

void performTraversal(
	std::vector<KRecord> const& records,
	const int height,
	int* sum);

void performTraversal(
	std::vector<KRecord> const& records,
	const int height);

void performTraversal(KStorage const& storage);

template <typename Tuple, typename Key>
void performTraversal(TFile<Tuple, Key> const& file) {
	

	std::size_t const height = std::tuple_size<Tuple>::value;
	int sum[height];
	for (std::size_t i = 0; i <= height; ++i) {
		sum[i] = 0;
	}


	typedef TVertex<Tuple, Key> Vertex;
	typedef std::stack<Vertex> VertexesStack;
	typedef TFile<Tuple, Key>::RecordType Record;
	
	std::vector<Record> records = file.getRecords();

	Vertex vertex = Vertex();
	VertexesStack stack = VertexesStack();
	std::vector<Record>::const_iterator iterator = records.begin();
	std::vector<Record>::const_iterator end = --records.end();

	Record const* currentRecord = &(*iterator);
	Record const* nextRecord = nullptr;
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
				vertex.setRecord(nextRecord);
			}
			else {
				vertex.setLevel(height + 1);
			}
		}
	}

	for (std::size_t i = 0; i <= height; ++i) {
		std::cout << i << " : " << sum[i] << std::endl;
	}
}