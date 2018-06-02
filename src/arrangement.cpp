#include "arrangement.h"

Arrangement::Arrangement() {}

Arrangement::Arrangement(size_t size) : _size(size) {
  for (size_t i = 0; i < _size; ++i) {
    _spaces.push_back((value)i);
  }
}

// Declare that two spaces are adjacent
void Arrangement::defineAdjacency(size_t a, size_t b) {
  if (_adjacency.count(a) == 0) {
    _adjacency[a] = {b};
  } else {
    _adjacency[a].push_back(b);
  }

  if (_adjacency.count(b) == 0) {
    _adjacency[b] = {a};
  } else {
    _adjacency[b].push_back(a);
  }
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
  // Bounds and existence checking
  if (i > _size || j > _size || _adjacency.count(i) == 0 || _adjacency.count(j) == 0) {
    return false;
  }
  // Detailed adjancecy checking
  if (std::find(_adjacency[i].begin(), _adjacency[i].end(), j) == _adjacency[i].end() ||
      std::find(_adjacency[j].begin(), _adjacency[j].end(), i) == _adjacency[j].end()) {
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

bool Arrangement::operator ==(const Arrangement& rhs) {
  if (_size != rhs._size) {
    return false;
  }

  for (size_t i = 0; i < _size; ++i) {
    if (_spaces[i] != rhs._spaces[i]) {
      return false;
    }
  }

  for (const auto & key : _adjacency) {
    if (rhs._adjacency.count(key.first) == 0) {
      return false;
    }
    for (const auto & val : key.second) {
      if (std::find(rhs._adjacency.at(key.first).begin(),
                rhs._adjacency.at(key.first).end(), val)
                                == rhs._adjacency.at(key.first).end()) {
        return false;
      }
    }
  }

  return true;
}

void Arrangement::reverse() {
  std::reverse(_spaces.begin(), _spaces.end());
}

Arrangement Arrangement::getReverse() {
  Arrangement arr = *this;
  arr.reverse();
  return arr;
}
