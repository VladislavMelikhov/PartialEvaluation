#pragma once

#include <stack>

template <typename StackWrapper>
class StorageIterator;

template <typename StackWrapper>
class StorageIterator
	: public std::iterator<
	std::forward_iterator_tag,
	std::remove_cv_t<typename StackWrapper::VertexesTuple>
> {

	static int const height = StackWrapper::LastIndex;

private:
	typedef typename StackWrapper::VertexesTuple Tuple;
	typedef std::stack<int> VertexesStack;

	StackWrapper stackWrapper;
	VertexesStack levels;
	int level;
	int branchHeight;
	bool isEndOfSource;

	int getDepth() const {
		return stackWrapper.getDepth();
	}

public:

	StorageIterator(StackWrapper const& stackWrapper, bool const& isEndOfSource) :
		stackWrapper(stackWrapper),
		levels(VertexesStack()),
		level(0),
		branchHeight(0),
		isEndOfSource(isEndOfSource) {}

	StorageIterator& operator++() {
		while (true) {
			stackWrapper.pop();
			while (level <= height) {
				stackWrapper.push();
				levels.push(level);
				++level;
			}
			if (stackWrapper.isEmpty()) {
				isEndOfSource = true;
				break;
			}

			level = levels.top();
			levels.pop();

			if (level == height) {
				//printTuple(std::cout, stackWrapper.stack);
				//std::cout << "Level : " << level << std::endl;

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
				//printTuple(std::cout, stackWrapper.stack);
				//std::cout << "Branch : " << level << std::endl;
				if (level == branchHeight) {
					//stackWrapper.pop();
					//stackWrapper.push();
				}
				else {
					level = height + 1;
				}
			}
			
			break;
		}
		return *this;
	}

	bool operator!=(StorageIterator const& other) const {
		if (isEndOfSource && other.isEndOfSource) {
			return false;
		}
		else {
			return true;
		}
	}

	Tuple const& operator*() const {
		return stackWrapper.getStack();
	}

	Tuple const& operator->() const {
		return stackWrapper.getStack();
	}

	bool isLeaf() const {
		return getLevel() == height + 1;
	}

	int getLevel() const {
		return getDepth();
	}
};