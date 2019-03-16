#pragma once
#include "KTBasePostIterator.h"

typedef std::stack<KTVertex> TVertexesStack;
typedef std::vector<TRecords::const_iterator> RecordsIterators;
typedef std::vector<KTFile> TFiles;
typedef TFiles::const_iterator FilesIterator;

class KTPostIterator : public KTBasePostIterator {
public:
	explicit KTPostIterator(TFiles const& files);

private:
	void onPush(int const& level);
	bool isEndOfSource() const;
	KTRecord const& readNext() const;

	RecordsIterators iterators;
	RecordsIterators ends;
};
