#pragma once
#pragma once
#include "KTVertex.h"
#include "KTFile.h"
#include <stack>
#include <vector>

typedef std::stack<KTVertex> TVertexesStack;
typedef std::vector<TRecords::const_iterator> RecordsIterators;
typedef std::vector<KTFile> TFiles;
typedef TFiles::const_iterator FilesIterator;

class KTBasePostIterator {
public:
	explicit KTBasePostIterator(int const& treeHeight);
	virtual ~KTBasePostIterator();
	KTBasePostIterator& operator ++ ();
	bool operator != (KTBasePostIterator const& other) const;

protected:
	virtual void onNext(KTRecord const& record) const = 0;
	virtual void onPush(int const& level) = 0;
	virtual void onBranch(int const& level) const = 0;
	virtual bool isEndOfSource() const = 0;
	virtual KTRecord const& readNext() const = 0;

	TVertexesStack const& getStack() const;
	int const& getTreeHeight() const;
	void setCurrentRecord(KTRecord const& value);

private:
	KTVertex vertex;
	TVertexesStack stack;
	KTRecord const* currentRecord;
	KTRecord const* nextRecord;
	int const treeHeight;
	int branchHeight;
};