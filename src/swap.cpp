#include "swap.h"

Swap::Swap(size_t i, size_t j, std::string& name)
    : _i(i), _j(j), _name(name) {}

void Swap::displayInfo() {
  std::cout << "\""<< _name << "\" is a swap object that acts on the positions " << _i << " & " << _j << ".\n";
}

// Multiply the swap on the RIGHT by the arrangement, return an arrangement
Arrangement Swap::operator *(Arrangement rhs) {
  std::cout << "1\n";
  Arrangement ret = rhs;
  ret.swap(_i, _j);
  return ret;
}
