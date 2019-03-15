#pragma once
#include "KTFile.h"
#include "KTLinkIterator.h"

typedef std::vector<KTFile> TFiles;

class KStorage {
public:
	explicit KStorage(TFiles const& files);

	TFiles const& getFiles() const;

	KTLinkIterator beginLink();
	KTLinkIterator endLink();

private:
	TFiles files;
};