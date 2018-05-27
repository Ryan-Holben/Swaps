#include "permutahedron.h"

// --------- Node method definitions ---------
Node::Node() {}

Node::Node(const Arrangement& arr, const Word& word) : _arr(arr), _word(word) {}

std::vector<std::shared_ptr<Swap>> Node::getSuccessorSwaps(const std::vector<std::shared_ptr<Swap>>& swaps) const {
  std::vector<std::shared_ptr<Swap>> ret;
  for (const auto & swap : swaps) {
    if (std::find(_pred.begin(), _pred.end(), swap) != _pred.end()) {
      ret.push_back(swap);
    }
  }
  return ret;
}

Arrangement& Node::getArrangement() { return _arr; }

Word& Node::getWord() { return _word; }

// Helpful friend function to properly connect pred to succ
bool connectNodes(std::shared_ptr<Node>& pred, std::shared_ptr<Node>& succ) {
  if (std::find(pred->_succ.begin(), pred->_succ.end(), succ) != pred->_succ.end() ||
      std::find(succ->_pred.begin(), succ->_pred.end(), pred) != succ->_pred.end()) {
        return false;
  }

  pred->_succ.push_back(succ);
  succ->_pred.push_back(pred);
  return true;
}

// --------- Permutahedron method definitions ---------
Permutahedron::Permutahedron() {}

void Permutahedron::buildPermutahedron(std::vector<Swap>& swaps, Arrangement& start, Arrangement& end) {
  // Seed the permutahedron
  Word startWord;
  Node startNode(start, startWord);
  _levels.push_back({startNode});
  for (size_t i = 1; i < 2; ++i) {
    _levels.push_back({});
    // For each arrangement (Node) on the previous level....
    for (const auto& node : _levels[i-1]) {
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
