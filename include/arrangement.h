#pragma once
#include "types.h"

// An array of spaces.  These should be numbered.  The arrangement also owns
// and keeps track of the values that occupy all of its spaces.
class Arrangement {
public:
  Arrangement();
  Arrangement(size_t size);
  void defineAdjacency(size_t a, size_t b);
  std::string getString(std::string delim = "") const;
  bool swap(size_t i, size_t j);
  void operator =(const Arrangement& rhs);
  void reverse();
  Arrangement getReverse();

private:
  size_t _size;
  std::vector<value> _spaces;
  std::unordered_map<size_t, size_t> _adjacency;
};
