#include "helpers.h"

// Helper functions to create standard arrangements
bool create1DArrangement(size_t length, Arrangement* arr, std::vector<swapPtr>& swaps) {
  if (arr == nullptr) {
    return false;
  }

  cout << "Initializing data structures for 1x" << length << " arrangement.\n";

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

// Convert 2D coordinates to 1D coordinates, assuming we start at (0,0) in 2D and 0 in 1D
inline size_t convert2Dto1D(size_t x, size_t y, size_t W, size_t H) {
  return y * H + x;
}

bool create2DArrangement(size_t width, size_t height, Arrangement* arr, std::vector<swapPtr>& swaps) {
  if (arr == nullptr) {
    return false;
  }

  cout << "Initializing data structures for " << width << "x" << height << " arrangement.\n";

  const size_t totalLength = width * height;
  *arr = Arrangement(totalLength); // This is surely inefficient

  std::string strName;
  char name = 'a';
  size_t thisSpace, adjacentSpace;

  // Block from (0, 0) through (width - 2, height - 2)
  for (size_t y = 0; y < height-1; ++y) {
    for (size_t x = 0; x < width-1; ++x) {
      thisSpace = convert2Dto1D(x, y, width, height);
      adjacentSpace = thisSpace + 1;
      arr->defineAdjacency(thisSpace, adjacentSpace);
      strName = name;
      swaps.emplace_back(std::make_shared<Swap>(thisSpace, adjacentSpace, strName));
      name += 1;

      adjacentSpace = thisSpace + width;
      arr->defineAdjacency(thisSpace, adjacentSpace);
      strName = name;
      swaps.emplace_back(std::make_shared<Swap>(thisSpace, adjacentSpace, strName));
      name += 1;
    }
  }

  // width - 1 column
  for (size_t y = 0; y < height-1; ++y) {
    thisSpace = convert2Dto1D(width-1, y, width, height);
    adjacentSpace = thisSpace + width;
    arr->defineAdjacency(thisSpace, adjacentSpace);
    strName = name;
    swaps.emplace_back(std::make_shared<Swap>(thisSpace, adjacentSpace, strName));
    name += 1;
  }

  // height - 1 row
  for (size_t x = 0; x < width-1; ++x) {
    thisSpace = convert2Dto1D(x, height-1, width, height);
    adjacentSpace = thisSpace + 1;
    arr->defineAdjacency(thisSpace, adjacentSpace);
    strName = name;
    swaps.emplace_back(std::make_shared<Swap>(thisSpace, adjacentSpace, strName));
    name += 1;
  }

  return true;
}
