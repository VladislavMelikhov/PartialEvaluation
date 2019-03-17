#pragma once
#include "KTPostIterator.h"
#include <stdexcept>

class KTLinkIterator : public KTPostIterator {
public:
	KTLinkIterator(TFiles const& files);
	~KTLinkIterator();
private:
	void onNext(KTRecord const& record) const;
	void onBranch(int const& level, KTRecord const& record) const;
};