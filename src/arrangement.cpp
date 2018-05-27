#include "arrangement.h"

Arrangement::Arrangement() {}

Arrangement::Arrangement(size_t size) : _size(size) {
  for (size_t i = 0; i < _size; ++i) {
    _spaces.push_back((value)i);
  }
}

// Declare that two spaces are adjacent
void Arrangement::defineAdjacency(size_t a, size_t b) {
  _adjacency[a] = b;
  _adjacency[b] = a;
}

std::string Arrangement::getString(std::string delim) const {
  std::string ret = "[";
  for (size_t i = 0; i < _size-1; ++i) {
    ret +=  std::to_string(_spaces[i]);
    ret += delim;
  }
  ret += std::to_string(_spaces[_size-1]);
  ret += "]";
  return ret;
}

bool Arrangement::swap(size_t i, size_t j) {
  if (i > _size || j > _size
    || _adjacency.count(i) == 0 || _adjacency.count(j) == 0
    || _adjacency[i] != j) {
    return false;
  }
  value temp = _spaces[i];
  _spaces[i] = _spaces[j];
  _spaces[j] = temp;
  return true;
}

void Arrangement::operator =(const Arrangement& rhs) {
  _size = rhs._size;
  _spaces = rhs._spaces;
  _adjacency = rhs._adjacency;
}

void Arrangement::reverse() {
  std::reverse(_spaces.begin(), _spaces.end());
}

Arrangement Arrangement::getReverse() {
  Arrangement arr = *this;
  arr.reverse();
  return arr;
}
