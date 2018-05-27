#include "word.h"

Word::Word() {}

void Word::append(Swap& swap) {
  _swaps.push_back(swap);
}

void Word::append(std::vector<Swap>& swaps) {
  _swaps.insert(_swaps.end(), swaps.begin(), swaps.end());
}
std::string Word::getString() const {
  std::string ret;
  for (const auto & swap : _swaps) {
    ret += swap.getName();
  }
  return ret;
}

Arrangement Word::apply(Arrangement& lhs) const {
  Arrangement arr = lhs;
  for (const auto & swap : _swaps) {
    // arr = arr*swap;
    arr *= swap;
  }
  return arr;
}

Arrangement operator *(Arrangement & lhs, Word & rhs) {
  return rhs.apply(lhs);
}
