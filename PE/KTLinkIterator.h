#pragma once
#include "KTPostIterator.h"

class KTLinkIterator : public KTPostIterator {
public:
	KTLinkIterator(TFiles const& files);
	~KTLinkIterator();
private:
	void onNext(KTRecord const& record);
};