#pragma once
#include <string>
#include "arrangement.h"

// The action that, when applied to an arrangement, swaps two of that
// arrangement's values, and produces a new arrangement object.  It should
// contain the numerical IDs of the spaces that will be swapped, as well as a
// letter-based name for itself for display purposes.
class Swap {
public:
  Swap(size_t i, size_t j, std::string& name);
  void displayInfo() const;
  std::pair<size_t, size_t> getIndices() const;
  Arrangement operator *(const Arrangement& rhs) const;

private:
  size_t _i, _j;
  std::string _name;
};

Arrangement operator *(const Arrangement& lhs, const Swap& rhs);
