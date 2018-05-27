#include "word.h"

Word::Word() {}

void Word::append(const Swap& swap) {
  _swaps.push_back(std::make_shared<Swap>(swap));
}

void Word::append(const std::vector<Swap>& swaps) {
  for (const auto & swap : swaps) {
    _swaps.push_back(std::make_shared<Swap>(swap));
  }
}
std::string Word::getString() const {
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

Arrangement operator *(Arrangement & lhs, const Word & rhs) {
  return rhs.apply(lhs);
}


// Get the Swap s such that succ = pred * s.  That is, get the edge connecting
// two Arrangement "nodes" in a permutahedron.
bool getEdge(const Word& pred, const Word& succ, Swap* swap) {
  if (swap == nullptr) {
    return false;
  }
  if (pred._swaps.size() + 1 != succ._swaps.size()) {
    return false;
  }
  for (size_t i = 0; i < pred._swaps.size(); ++i) {
    if (pred._swaps[i] != succ._swaps[i]) {
      return false;
    }
  }

  swap = succ._swaps.back().get();
  return true;
}
