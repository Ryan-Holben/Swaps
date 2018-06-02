#include "helpers.h"

// Helper functions to create standard arrangements
bool create1DArrangement(size_t length, Arrangement* arr, std::vector<swapPtr>& swaps) {
  if (arr == nullptr) {
    return false;
  }

  *arr = Arrangement(length); // This is surely inefficient
  std::string strName;
  char name = 'a';
  for (size_t i = 0; i < length-1; ++i) {
    arr->defineAdjacency(i, i+1);
    strName = name;
    swaps.emplace_back(std::make_shared<Swap>(i, i+1, strName));
    name += 1;
  }
  return true;
}

// 0 ... width-1
// width ... 2*width-1
// 

bool create2DArrangement(size_t length, size_t width, Arrangement* arr, std::vector<swapPtr>& swaps) {
  if (arr == nullptr) {
    return false;
  }

  *arr = Arrangement(length*width); // This is surely inefficient
  std::string strName;
  char name = 'a';
  for (size_t i = 0; i < length-1; ++i) {
    arr->defineAdjacency(i, i+1);
    strName = name;
    swaps.emplace_back(std::make_shared<Swap>(i, i+1, strName));
    name += 1;
  }
  return true;
}
