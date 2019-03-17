#pragma once
#include "KTBasePostIterator.h"

typedef std::vector<KTRecord> TRecords;
typedef TRecords::const_iterator Iterator;

class KPostIterator : public KTBasePostIterator {
public:
	explicit KPostIterator(TRecords const& records, int const treeHeight);
	virtual ~KPostIterator();
	
private:
	void onPush(int const& level);
	bool isEndOfSource() const;
	KTRecord const& readNext() const;
	int const getBranchHeight(KTRecord const& first, KTRecord const& second) const;

	Iterator iterator;
	Iterator const end;
};