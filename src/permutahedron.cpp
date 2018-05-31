#include "permutahedron.h"

// --------- Node method definitions ---------
Node::Node() {}

Node::Node(const Arrangement& arr) : _arr(arr) {}

Arrangement Node::getArrangement() const { return _arr; }

std::vector<swapPtr> Node::getPredecessorSwaps() const {
  std::vector<swapPtr> ret;
  for (const auto& predNode : _pred) {
    ret.push_back(predNode->_swap);
  }
  return ret;
}

std::vector<swapPtr> Node::getSuccessorSwaps() const {
  std::vector<swapPtr> ret;
  for (const auto& succNode : _succ) {
    ret.push_back(succNode->_swap);
  }
  return ret;
}

// Given the predecessor nodes that this Node currently stores, return a list
// of all swaps that remain (and thus are viable candidates for successors).
std::vector<swapPtr> Node::computeSuccessorSwaps(const std::vector<swapPtr>& swaps) const {
  std::vector<swapPtr> ret;
  auto prevSwaps = getPredecessorSwaps();
  for (const auto& swap : swaps) {
    if (std::find(prevSwaps.begin(), prevSwaps.end(), swap) == prevSwaps.end()) {
      ret.push_back(swap);
    }
  }
  return ret;
}

// Helpful friend function to properly connect pred to succ
bool connectNodes(Node& pred, Node& succ, swapPtr swap) {
  // std::cout << "CALLED ";
  nodePtr predPtr = std::make_shared<Node>(pred);
  nodePtr succPtr = std::make_shared<Node>(succ);

  // Check if we're already connected
  for (const auto& edge : pred._succ) {
    if (edge->_succ == succPtr) {
      return false;
    }
  }
  for (const auto& edge : succ._pred) {
    if (edge->_pred == predPtr) {
      return false;
    }
  }

  edgePtr edge = std::make_shared<Edge>(swap, predPtr, succPtr);

  pred._succ.push_back(edge);
  succ._pred.push_back(edge);
  // std::cout << "(" << pred._pred.size() << ", " << succ._succ.size() << ")\n";
  return true;
}

// --------- Permutahedron method definitions ---------
Permutahedron::Permutahedron() {}

void Permutahedron::buildPermutahedron(std::vector<swapPtr>& swaps, Arrangement& start) {
  // Seed the permutahedron
  cout << "Building permutahedron\n";
  cout << "Seeding level 0\n";
  Node startNode(start);
  _levels.push_back({startNode});

  // Loop through all the additional levels that we want to create
  size_t i = 1;
  // for (size_t i = 1; i < 6; ++i){
  while (_levels[i-1].size() != 1 || i == 1) {
    cout << "Building level " << i << "\n";
    _levels.push_back({});
    auto& prevLevel = _levels[i-1];
    auto& currLevel = _levels[i];

    // For each Arrangement/Node on the previous level...
    for (auto& prevNode : prevLevel) {
      // Loop through that node's potential next swaps.
      // cout << "- Looking at a prevNode.  It has " << prevNode.computeSuccessorSwaps(swaps).size() << " possible swaps we can try.\n";
      // cout << "-- ";
      for (const auto& swap : prevNode.computeSuccessorSwaps(swaps)) {
        // For each such swap, try multiplying by prevNode.
        Arrangement newArr = prevNode.getArrangement() * (*swap);

        // Is the result new?
        bool foundNode = false;
        for (auto & currNode : currLevel) {
          // Not a new result?  Connect to the already existing Node
          if (newArr == currNode.getArrangement()) {
            // cout << "old ";
            connectNodes(prevNode, currNode, swap);
            foundNode = true;
            break;
          }
        }
        if (!foundNode) {
          // Yes, is a new result?  Build a new Node and connect to it
          // cout << "new ";
          Node newNode(newArr);
          connectNodes(prevNode, newNode, swap);
          currLevel.push_back(newNode); // And also add it to the Permutahedron
        }
      }
      // cout << "\n";
    }
    i += 1;
  }
}

void Permutahedron::display() const {
  if (_levels.size() == 0) {
    return;
  }
  std::cout << "_levels.size() = " << _levels.size() << "\n";
  for (size_t i = 0; i < _levels.size(); ++i) {
    std::cout << "_levels[" << i << "].size() = " << _levels[i].size() << "\n";
  }

  // for (size_t i = 0; i < _levels.size(); ++i) {
  //   for (const auto & node : _levels[i]) {
  //     std::cout << "(" << node._pred.size() << ", " << node._succ.size() << ") ";
  //   }
  //   cout << "\n";
  // }

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
