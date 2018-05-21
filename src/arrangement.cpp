#include "arrangement.h"

Arrangement::Arrangement(size_t size) : _size(size) {
  for (size_t i = 1; i < _size+1; ++i) {
    _spaces.push_back(i);
  }
}

// Declare that two spaces are adjacent
void Arrangement::defineAdjacency(size_t a, size_t b) {
  _adjacency[a] = b;
  _adjacency[b] = a;
}

void Arrangement::display() {
  std::cout << "[";
  for (size_t i = 0; i < _size-1; ++i) {
    std::cout << _spaces[i] << ", ";
  }
  std::cout << _spaces[_size-1] << "]\n";
}

bool Arrangement::swap(size_t i, size_t j) {
  std::cout << "2\n";
  if (i > _size || j > _size
    || _adjacency.count(i) == 0 || _adjacency.count(j) == 0
    || _adjacency[i] != j) {
      std::cout << "3\n";
    return false;
  }
  std::cout << "4\n";
  value temp = _spaces[i];
  _spaces[i] = _spaces[j];
  _spaces[j] = temp;
  return true;
}

Arrangement create1DArrangement(size_t length) {
  Arrangement arr = Arrangement(length);
  for (size_t i = 0; i < length-1; ++i) {
    arr.defineAdjacency(i, i+1);
  }
  return arr;
}
