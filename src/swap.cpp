#include "swap.h"

Swap::Swap() {}

Swap::Swap(size_t i, size_t j, std::string& name)
    : _i(i), _j(j), _name(name) {}

void Swap::displayInfo() const {
  std::cout << "\""<< _name << "\" is a swap object that acts on the positions " << _i << " & " << _j << ".\n";
}

std::string Swap::getName() const {
  return _name;
}

std::pair<size_t, size_t> Swap::getIndices() const {
  return std::make_pair(_i, _j);
}

// Multiply the swap on the RIGHT by the arrangement, return an arrangement
Arrangement Swap::operator *(const Arrangement& rhs) const {
  Arrangement ret = rhs;
  ret.swap(_i, _j);
  return ret;
}

bool Swap::operator ==(const Swap& rhs) const {
  return (_i == rhs._i && _j == rhs._j);
}

bool Swap::operator !=(const Swap& rhs) const {
  return !(*this == rhs);
}

// Multiply the swap on the LEFT by the arrangement, return an arrangement
Arrangement operator *(const Arrangement& lhs, const Swap& rhs) {
  Arrangement ret = lhs;
  auto indices = rhs.getIndices();
  ret.swap(indices.first, indices.second);
  return ret;
}

// Multiply the swap on the LEFT by the arrangement, store the result in that
// arrangement
void operator *=(Arrangement& lhs, const Swap& rhs) {
  auto indices = rhs.getIndices();
  lhs.swap(indices.first, indices.second);
}
