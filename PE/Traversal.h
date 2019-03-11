#pragma once
#include "KRecord.h"
#include <vector>
#include "KStorage.h"

void performTraversal(
	std::vector<KRecord> const& records,
	const int height,
	int* sum);

void performTraversal(
	std::vector<KRecord> const& records,
	const int height);

void performTraversal(KStorage const& storage);