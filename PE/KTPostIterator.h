#pragma once
#include "KTVertex.h"
#include "KTFile.h"
#include <stack>
#include <vector>

typedef std::stack<KTVertex> TVertexesStack;
typedef std::vector<TRecords::const_iterator> RecordsIterators;
typedef std::vector<KTFile> TFiles;
typedef TFiles::const_iterator FilesIterator;

class KTPostIterator {
public:
	explicit KTPostIterator(TFiles const& files);
	virtual ~KTPostIterator();
	KTPostIterator& operator ++ ();
	bool operator != (KTPostIterator const& other) const;

protected:
	virtual void onNext(KTRecord const& record) = 0;
	TVertexesStack const& getStack() const;
private:
	KTVertex vertex;
	TVertexesStack stack;
	RecordsIterators iterators;
	RecordsIterators ends;

	KTRecord const* currentRecord;
	KTRecord const* nextRecord;
	int const treeHeight;
	int branchHeight;
};
