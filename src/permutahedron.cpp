#include "permutahedron.h"

// --------- Node method definitions ---------
Node::Node() {}

Node::Node(const Arrangement& arr, const Word& word) : _arr(arr), _word(word) {}

// Return all swaps that got us to this Node
std::vector<swapPtr> Node::getPredecessorSwaps() const {
  std::cout << "TEST 1: _pred.size() = " << _pred.size() << "\n";
  for (const auto & predNode : _pred) {
    std::cout << "predNode->_arr = " << predNode->_arr.getString() << "\n";
  }
  std::vector<swapPtr> ret;

  swapPtr tempSwap;
  std::vector<Swap> prevSwaps;
  std::cout << "- Predecessor swaps: \n";
  // std::cout << _word.getString() << "\n";
  // std::cout << _pred[0]->_word.getString() << "\n";
  for (const auto & node : _pred) {
    getEdge(node->_word, _word, tempSwap);
    std::cout << tempSwap->getName() << " ";
    ret.push_back(tempSwap);
  }
  std::cout << "\n";
  return ret;
}

// Return all swaps that aren't predecessors of this Node
std::vector<swapPtr> Node::getSuccessorSwaps(const std::vector<swapPtr>& swaps) const {
  std::vector<swapPtr> ret;

  std::cout << "Getting successors of Node containing " << _arr.getString() << "\n";
  std::vector<swapPtr> prevSwaps = getPredecessorSwaps();
  std::cout << " - prevSwaps.size() = " << prevSwaps.size() << "\n";

  // Build & return a list of all Swaps *not* in prevSwaps
  for (const auto & swap : swaps) {
    if (std::find(prevSwaps.begin(), prevSwaps.end(), swap) == prevSwaps.end()) {
      ret.push_back(swap);
    }
  }
  return ret;
}

Arrangement Node::getArrangement() const { return _arr; }

Word Node::getWord() const { return _word; }

// Helpful friend function to properly connect pred to succ
bool connectNodes(Node& pred, Node& succ) {
  std::cout << "CALLED ";
  std::shared_ptr<Node> predPtr = std::make_shared<Node>(pred);
  std::shared_ptr<Node> succPtr = std::make_shared<Node>(succ);

  if (std::find(pred._succ.begin(), pred._succ.end(), succPtr) != pred._succ.end() ||
      std::find(succ._pred.begin(), succ._pred.end(), predPtr) != succ._pred.end()) {
        return false;
  }

  pred._succ.push_back(succPtr);
  succ._pred.push_back(predPtr);
  std::cout << "(" << pred._pred.size() << ", " << succ._succ.size() << ")\n";
  return true;
}

// --------- Permutahedron method definitions ---------
Permutahedron::Permutahedron() {}

void Permutahedron::buildPermutahedron(std::vector<swapPtr>& swaps, Arrangement& start, Arrangement& end) {
  // Seed the permutahedron
  Word startWord;
  Node startNode(start, startWord);
  _levels.push_back({startNode});

  // Loop through all the levels that we want to create
  for (size_t i = 1; i < 3; ++i) {
    _levels.push_back({});
    auto& prevLevel = _levels[i-1];
    auto& currLevel = _levels[i];
    std::cout << "\nOn level " << i << "\n";

    for (auto& prevNode : prevLevel) {
      // For each arrangement (Node) on the previous level....
      std::cout << "- Looking at node w/ arrangement " << prevNode.getArrangement().getString() << "\n";

      for (const auto& swap : prevNode.getSuccessorSwaps(swaps)) {
        // ...try multiplying it by an appropriate swap
        Arrangement newArr = prevNode.getArrangement() * (*swap);

        // Is the result new?
        bool found = false;
        for (auto& otherNode : currLevel) {
          if (otherNode.getArrangement() == newArr) {
            // If it's not new, connect to the pre-existing node
            connectNodes(prevNode, otherNode);
            found = true;
            break;
          }
        }

        std::cout << "-- Multiplying by swap: " << swap->getName() << "\t Result: " << newArr.getString() << " --> " << (found ? "old" : "new") << "\n";

        if (!found) {
          // If it is new, create a new node and connect to it
          Word newWord = prevNode.getWord();
          newWord.append(swap);
          Node newNode(newArr, newWord);
          connectNodes(prevNode, newNode);
          currLevel.emplace_back(newNode);
        }

      }
    }
  }
}
void Permutahedron::display() const {
  std::cout << "_levels.size() = " << _levels.size() << "\n";
  for (size_t i = 0; i < _levels.size(); ++i) {
    std::cout << "_levels[" << i << "].size() = " << _levels[i].size() << "\n";
  }

  for (const auto & node : _levels[0]) {
    std::cout << "(" << node._pred.size() << ", " << node._succ.size() << ") ";
  }
  std::cout << "\n";

  for (const auto & node : _levels[1]) {
    std::cout << "(" << node._pred.size() << ", " << node._succ.size() << ") ";
  }
  std::cout << "\n";
  // std::cout << "\n";
  // for (size_t i = 0; i < _levels.size(); ++i) {
  //   const auto& level = _levels[i];
  //   std::cout << i << "\t";
  //   for (size_t j = 0; j < level.size()-1; ++j) {
  //     std::cout << level[j].getArrangement().getString() << ", ";
  //   }
  //   std::cout << level.back().getArrangement().getString() << "\n";
  // }
}
