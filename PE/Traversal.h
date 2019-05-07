#pragma once
#include "KRecord.h"
#include <vector>
#include "KStorage.h"
#include "TFile.h"
#include "TVertex.h"
#include "Key.h"
#include "TStorage.h"
#include "IndexesFactory.h"
#include "TuplePrinter.h"

void performTraversal(
	std::vector<KRecord> const& records,
	const int height,
	int* sum);

void performTraversal(
	std::vector<KRecord> const& records,
	const int height);

void performTraversal(KStorage const& storage);

template <typename Tuple, int ... Indexes, int ... Numbers>
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
	std::vector<Record>::const_iterator end = records.end();

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

template <typename Storage, typename Indexes>
class RecordsIteratorsBuilder;

template <typename ... Files, int ... Nums>
class RecordsIteratorsBuilder<TStorage<Files...>, Indexes<Nums...>> {
public:
	//typedef std::tuple<(Files::Records::const_iterator)...> RecordsIterators;

	static decltype(auto) getBegins(TStorage<Files...> const& storage) {
		return std::make_tuple((std::get<Nums>(storage.files).getRecords().begin())...);
	}

	static decltype(auto) getEnds(TStorage<Files...> const& storage) {
		return std::make_tuple((std::get<Nums>(storage.files).getRecords().end())...);
	}
};

template <typename File>
class VertexBuilder;


template <typename Tuple, typename Key, typename Level>
class VertexBuilder<TFile<Tuple, Key, Level>> {
public: 
	typedef TVertex<Tuple, Key, Level> VertexType;

	static VertexType makeVertex() {
		return VertexType();
	}
};

template <typename ... Files>
class StackBuilder {

public:
	static decltype(auto) makeStack() {
		return std::make_tuple(VertexBuilder<Files>::makeVertex()...);
	}
};

//template <typename ... Files>
//class Stack {
//
//private:
//	decltype(auto) stack = StackBuilder<Files...>::makeStack();
//};


//template <typename ... Files>
//class TraversalPerformer {
//
//public:
//	typedef typename IndexesFactory<sizeof...(Files)>::IndexesType Indexes;
//
//	decltype(RecordsIteratorsBuilder<TStorage<Files...>, Indexes>::getBegins(nullptr)) iterators;
//	decltype(RecordsIteratorsBuilder<TStorage<Files...>, Indexes>::getEnds) ends;
//
//	TStorage<Files...> const& storage;
//
//	TraversalPerformer(TStorage<Files...> const& storage) : storage(storage) {
//		iterators = RecordsIteratorsBuilder<TStorage<Files...>, Indexes>::getBegins(storage);
//		ends = RecordsIteratorsBuilder<TStorage<Files...>, Indexes>::getEnds(storage);
//	}
//
//	void performTraversal() {
//		decltype(auto) it = std::get<1>(iterators);
//		decltype(auto) end = std::get<1>(ends);
//
//		for (; it != end; ++it) {
//			std::cout << *it << std::endl;
//		}
//
//		decltype(auto) stack = StackBuilder<Files...>::makeStack();
//	}
//};

template <typename Vertexes, typename Iterators>
class Stack;

template <typename ... Vertexes, typename ... Iterators>
class Stack<std::tuple<Vertexes...>, std::tuple<Iterators...>> {

private:

	static int const LastIndex = sizeof...(Vertexes) - 1;

	typedef std::tuple<Vertexes...> VertexesTuple;
	typedef std::tuple<Iterators...> IteratorsTuple;

	int depth;

public:
	Stack(VertexesTuple const& stack,
		IteratorsTuple const& iterators,
		IteratorsTuple const& ends) : stack(stack), iterators(iterators), ends(ends), depth(0) {}

	VertexesTuple stack;
	IteratorsTuple iterators;
	IteratorsTuple ends;


	void push() {
		StackHelper<VertexesTuple, IteratorsTuple, LastIndex>::push(*this, depth);
		++depth;
	}

	void pop() {
		--depth;
		StackHelper<VertexesTuple, IteratorsTuple, LastIndex>::pop(*this, depth);
	}

	bool isEmpty() {
		return depth == 0;
	}

	bool isEndOfSource() {
		return std::get<LastIndex>(iterators) == std::get<LastIndex>(ends);
	}

	int getBranchHeight() {
		decltype(auto) currentRecord = std::get<LastIndex>(stack).getRecord();
		decltype(auto) nextRecord = *std::get<LastIndex>(iterators);
		return currentRecord.compare(nextRecord) - 1;
	}
};

template <typename Vertexes, typename Iterators>
Stack<Vertexes, Iterators> makeStack(Vertexes const& vertexes, Iterators const& iterators, Iterators const& ends) {
	return Stack<Vertexes, Iterators>(vertexes, iterators, ends);
}

template <typename Vertexes, typename Iterators, int N>
class StackHelper;

template <typename Vertexes, typename Iterators, int N>
class StackHelper {
public:
	
	static void pop(Stack<Vertexes, Iterators>& stack, int depth) {
		if (depth == N) {
			std::get<N>(stack.stack).setRecord(nullptr);
			std::get<N>(stack.stack).setLevel(0);
		}
		else {
			StackHelper<Vertexes, Iterators, N - 1>::pop(stack, depth);
		}
	}

	static void push(Stack<Vertexes, Iterators>& stack, int depth) {
		if (depth == N) {
			decltype(auto) iterator = std::get<N>(stack.iterators);
			std::get<N>(stack.stack).setRecord(&(*iterator));
			std::get<N>(stack.stack).setLevel(depth);
			++iterator;
		}
		else {
			StackHelper<Vertexes, Iterators, N - 1>::push(stack, depth);
		}
	}
};

template <typename Vertexes, typename Iterators>
class StackHelper<Vertexes, Iterators, 0> {
public:

	static void pop(Stack<Vertexes, Iterators>& stack, int depth) {
		if (depth == 0) {
			std::get<0>(stack.stack).setRecord(nullptr);
			std::get<0>(stack.stack).setLevel(0);
		}
		else {
			throw std::logic_error("Stack overflow");
		}
	}

	static void push(Stack<Vertexes, Iterators>& stack, int depth) {
		if (depth == 0) {
			decltype(auto) iterator = std::get<0>(stack.iterators);
			std::get<0>(stack.stack).setRecord(&(*iterator));
			std::get<0>(stack.stack).setLevel(depth);
			++iterator;
		}
		else {
			throw std::logic_error("Stack overflow");
		}
	}
};

template <typename ... Files>
void performTraversal(TStorage<Files...> const& storage)
{
	//typedef std::tuple<Files::Records::const_iterator...> RecordsIterators;
	typedef IndexesFactory<sizeof...(Files)>::IndexesType Indexes;

	decltype(auto) iterators = RecordsIteratorsBuilder<TStorage<Files...>, Indexes>::getBegins(storage);
	decltype(auto) ends = RecordsIteratorsBuilder<TStorage<Files...>, Indexes>::getEnds(storage);

	//decltype(auto) it = std::get<1>(iterators);
	//decltype(auto) end = std::get<1>(ends);

	//for (; it != end; ++it) {
	//	std::cout << *it << std::endl;
	//}

	decltype(auto) stack = StackBuilder<Files...>::makeStack();

	decltype(auto) stackWrapper = makeStack(stack, iterators, ends);

	int const height = sizeof...(Files) - 1;
	//int level = 0;

	//while (level <= height) {
	//	stackWrapper.push();
	//	++level;
	//}

	//stackWrapper.pop();
	//stackWrapper.push();

	//printTuple(std::cout, stackWrapper.stack);

	//KTVertex vertex = KTVertex();
	//std::stack<KTVertex> stack = std::stack<KTVertex>();
	//RecordsIterators iterators = RecordsIterators();
	//RecordsIterators ends = RecordsIterators();

	//TFiles const& files = storage.getFiles();
	//FilesIterator iterator = files.begin();
	//FilesIterator end = files.end();

	//for (KTFile const& file : files) {
	//	std::cout << file;
	//};

	//for (; iterator != end; ++iterator) {
	//	TRecords const& records = (*iterator).getRecords();
	//	iterators.push_back(records.begin());
	//	ends.push_back(records.end());
	//}

	//int const height = std::tuple_size(iterators);
	//int const height = iterators.size() - 1;
	//KTRecord const* currentRecord = nullptr;
	//KTRecord const* nextRecord = nullptr;
	//int k = height;

	int level = 0;
	int branchHeight = 0;

	std::stack<int>& levels = std::stack<int>();
	
	while (true) {
		while (level <= height) {
			stackWrapper.push();
			levels.push(level);
			++level;
		}
		if (stackWrapper.isEmpty()) {
			break;
		}
		
		level = levels.top();
		levels.pop();

		if (level == height) {
			printTuple(std::cout, stackWrapper.stack);
			std::cout << "Level : " << level << std::endl;

			if (stackWrapper.isEndOfSource()) {
				level = height + 1;
			}
			else {
				branchHeight = stackWrapper.getBranchHeight();
				if (branchHeight == height) {
					//stackWrapper.pop();
					//stackWrapper.push();
				}
				else {
					level = height + 1;
				}
			}
		}
		else {
			printTuple(std::cout, stackWrapper.stack);
			std::cout << "Branch : " << level << std::endl;
			if (level == branchHeight) {
				//stackWrapper.pop();
				//stackWrapper.push();
			}
			else {
				level = height + 1;
			}
		}
		stackWrapper.pop();
	}

	//while (true) {
	//	while (vertex.getLevel() <= height) {
	//		currentRecord = &(*iterators[vertex.getLevel()]);
	//		vertex.setRecord(currentRecord);
	//		std::cout << "Debug: " << *currentRecord << std::endl;
	//		stack.push(vertex);
	//		++iterators[vertex.getLevel()];
	//		vertex.setLevel(vertex.getLevel() + 1);
	//	}
	//	if (stack.empty()) {
	//		break;
	//	}
	//	vertex = stack.top();
	//	stack.pop();

	//	if (vertex.getLevel() == height) {
	//		std::cout << vertex << std::endl;

	//		if (iterators[height] == ends[height]) {
	//			vertex.setLevel(height + 1);
	//		}
	//		else {
	//			nextRecord = &(*(iterators[height]));
	//			k = (*currentRecord).compare(*nextRecord);

	//			if (k == height) {
	//				currentRecord = nextRecord;
	//				vertex.setRecord(nextRecord);
	//			}
	//			else {
	//				vertex.setLevel(height + 1);
	//			}
	//		}
	//	}
	//	else {
	//		std::cout << "!";
	//		std::cout << vertex << std::endl;
	//		if (vertex.getLevel() == k) {
	//			currentRecord = nextRecord;
	//			vertex.setRecord(nextRecord);
	//		}
	//		else {
	//			vertex.setLevel(height + 1);
	//		}
	//	}
	//}
}
