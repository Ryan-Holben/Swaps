#include "helpers.h"

// Helper functions to create standard arrangements
bool create1DArrangement(size_t length, Arrangement* arr, std::vector<Swap>* swaps) {
  if (arr == nullptr || swaps == nullptr) {
    return false;
  }

  *arr = Arrangement(length); // This is surely inefficient
  std::string strName;
  char name = 'a';
  for (size_t i = 0; i < length-1; ++i) {
    arr->defineAdjacency(i, i+1);
    strName = name;
    swaps->emplace_back(i, i+1, strName);
    name += 1;
  }
  return true;
}
