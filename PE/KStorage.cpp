#include "pch.h"
#include "KStorage.h"

KStorage::KStorage(TFiles const& files) : files(files)
{
}

TFiles const& KStorage::getFiles() const
{
	return files;
}

KTLinkIterator KStorage::beginLink()
{
	return dynamic_cast<KTLinkIterator&>(++KTLinkIterator(getFiles()));
}

KTLinkIterator KStorage::endLink()
{
	return KTLinkIterator(getFiles());
}
