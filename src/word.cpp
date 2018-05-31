#include "word.h"

Word::Word() {}

void Word::append(const swapPtr swap) {
  _swaps.push_back(swap);
}

void Word::append(const std::vector<swapPtr>& swaps) {
  _swaps.insert(_swaps.end(), swaps.begin(), swaps.end());
}
std::string Word::getString() const {
  if (_swaps.size() == 0) {
    return "1";
  }
  std::string ret;
  for (const auto & swap : _swaps) {
    ret += swap->getName();
  }
  return ret;
}

Arrangement Word::apply(const Arrangement& lhs) const {
  Arrangement arr = lhs;
  for (const auto & swap : _swaps) {
    arr *= *swap;
  }
  return arr;
}

void Word::operator =(const Word& rhs) {
  _swaps.clear();
  _swaps = rhs._swaps;
}

Arrangement operator *(Arrangement & lhs, const Word & rhs) {
  return rhs.apply(lhs);
}
