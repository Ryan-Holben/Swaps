#include "permutahedron.h"

Node::Node() {}

Permutahedron::Permutahedron() {}

void Permutahedron::buildPermutahedron(std::vector<Swap>& swaps, Arrangement& start, Arrangement& end) {
  // Seed the permutahedron
  _levels.push_back({start});
  for (size_t i = 1; i < 2; ++i) {
    _levels.push_back({});
    // For each arrangement on the previous level....
    for (const auto& arr : _levels[i-1]) {
      // ...multiply it by a swap
      for (const auto& swap : swaps) {
        _levels[i].push_back(arr*swap);
      }
    }
  }
}
void Permutahedron::display() const {
  // for (const auto& level : _levels) {
  for (size_t i = 0; i < _levels.size(); ++i) {
    const auto& level = _levels[i];
    std::cout << i << "\t";
    for (size_t j = 0; j < level.size()-1; ++j) {
      std::cout << level[j].getString() << ", ";
    }
    std::cout << level.back().getString() << "\n";
  }
}
