#pragma once
#include "types.h"
#include "arrangement.h"
#include "swap.h"

#include <vector>

// Helper functions to create standard arrangements
bool create1DArrangement(size_t length, Arrangement* arr, std::vector<Swap>* swaps);
