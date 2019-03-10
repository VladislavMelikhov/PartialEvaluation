#pragma once
#include "KVertex.h"
#include <stack>
#include <vector>

typedef std::stack<KVertex> VertexesStack;
typedef std::vector<KRecord> Records;
typedef Records::const_iterator Iterator;

class KPostIterator {
public:
	explicit KPostIterator(Records const& records, int const treeHeight);
	virtual ~KPostIterator();
	KPostIterator& operator ++ ();
	bool operator != (KPostIterator const& other) const;
	
protected:
	virtual void onNext(KRecord const& record) = 0;
	virtual void onBranch(int const level) = 0;
	int const& getTreeHeight();

private:
	KVertex vertex;
	VertexesStack stack;
	Iterator iterator;
	Iterator const end;

	KRecord const* currentRecord;
	KRecord const* nextRecord;
	int const treeHeight;
	int branchHeight;
};