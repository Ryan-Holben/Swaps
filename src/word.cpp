#include "word.h"

Word::Word() {}

void Word::append(const std::shared_ptr<Swap> swap) {
  _swaps.push_back(swap);
}

void Word::append(const std::vector<std::shared_ptr<Swap>>& swaps) {
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

// Get the Swap s such that succ = pred * s.  That is, get the edge connecting
// two Arrangement "nodes" in a permutahedron.
bool getEdge(const Word& pred, const Word& succ, std::shared_ptr<Swap> swap) {
  // if (swap == nullptr) {
  //   return false;
  // }
  // if (pred._swaps.size() + 1 != succ._swaps.size()) {
  //   return false;
  // }
  // for (size_t i = 0; i < pred._swaps.size(); ++i) {
  //   if (pred._swaps[i] != succ._swaps[i]) {
  //     return false;
  //   }
  // }

  swap = succ._swaps.back();
  return true;
}
