#pragma once
#include <iterator>
#include <cstddef>
#include <stack>
#include <vector>
#include "TVertex.h"
#include "Key.h"
#include "Level.h"

template <typename Tuple, typename Key, typename Level, typename Iterator>
class FileIterator;

template <typename Tuple, int ... Indexes, int ... Numbers, typename Iterator>
class FileIterator<Tuple, Key<Indexes...>, Level<Numbers...>, Iterator> : public std::iterator<std::forward_iterator_tag, std::remove_cv_t<Tuple>, std::ptrdiff_t, Tuple*, Tuple&>
{
public:
	static std::size_t const treeHeight = sizeof...(Numbers) + 1;

private:
	typedef TVertex<Tuple, Key<Indexes...>, Level<Numbers...>> Vertex;
	typedef TRecord<Tuple, Key<Indexes...>, Level<Numbers...>> Record;
	typedef std::stack<Vertex> VertexesStack;

	Iterator iterator;
	Iterator const end;
	Vertex vertex;
	VertexesStack stack;
	Record const* currentRecord;
	Record const* nextRecord;
	int branchHeight;
	int levelValue;
	bool isLeafValue;

	void onPush(int const& level)
	{
		if (level == treeHeight && !isEndOfSource()) {
			++iterator;
		}
	}

	bool isEndOfSource() const
	{
		return iterator == end;
	}

	Record const& readNext() const
	{
		return *iterator;
	}

	int const getBranchHeight(Record const& first, Record const& second) const
	{
		return first.compare(second);
	}

	void onNext(int const& level, Record const& record) {
		isLeafValue = true;
		levelValue = level;
	}

	void onBranch(int const& level, Record const& record) {
		isLeafValue = false;
		levelValue = level;
	}

public:

	FileIterator(Iterator const& begin, Iterator const& end) :
		iterator(begin),
		end(end),
		vertex(Vertex()),
		stack(VertexesStack()),
		currentRecord(&(*iterator)),
		nextRecord(nullptr),
		branchHeight(treeHeight),
		levelValue(0),
		isLeafValue(false) {}

	FileIterator& operator++() {
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

				onNext(vertex.getLevel(), vertex.getRecord());

				if (isEndOfSource()) {
					vertex.setLevel(treeHeight + 1);
					branchHeight = treeHeight + 1;
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
				onBranch(vertex.getLevel(), vertex.getRecord());

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

	bool operator!=(FileIterator const& other) const {
		Record const& record = vertex.getRecord();
		Record const& otherRecord = other.vertex.getRecord();

		if (&record == nullptr && &otherRecord == nullptr) {
			return false;
		}
		else {
			//TODO: compare records!
			return true;
		}
	}

	Tuple const& operator* () const {
		return vertex
			.getRecord()
			.getTuple();
	}

	//Extended interface
	bool isLeaf() const {
		return isLeafValue;
	}

	int getLevel() const {
		return levelValue;
	}
};
/*
void performTraversal(TFile<Tuple, Key<Indexes...>, Level<Numbers...>> const& file) {


	std::size_t const height = sizeof...(Numbers) + 1;
	std::size_t const size = height + 1;
	double sum[size];
	for (std::size_t i = 0; i < size; ++i) {
		sum[i] = 0;
	}


	typedef TVertex<Tuple, Key<Indexes...>, Level<Numbers...>> Vertex;
	typedef std::stack<Vertex> VertexesStack;
	typedef TFile<Tuple, Key<Indexes...>, Level<Numbers...>>::RecordType Record;

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
			sum[height] += std::get<1>(vertex
				.getRecord()
				.getTuple());

			if (iterator == end) {
				vertex.setLevel(height + 1);
				k = height + 1;
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
			//std::cout << vertex;
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

	for (std::size_t i = 0; i < size; ++i) {
		std::cout << i << " : " << sum[i] << std::endl;
	}
}
*/