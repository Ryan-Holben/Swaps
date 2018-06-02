#include "permutahedron.h"

// --------- Node method definitions ---------
Node::Node() {}

Node::Node(const Arrangement& arr) : _arr(arr) {}

Arrangement Node::getArrangement() const { return _arr; }

std::unordered_set<std::string> Node::getWords() const {
  return _words;
}

// Build & return a list of all predecessor swaps
std::vector<swapPtr> Node::getPredecessorSwaps() const {
  std::vector<swapPtr> ret;
  for (const auto& predNode : _pred) {
    ret.push_back(predNode->_swap);
  }
  return ret;
}

// Build & return a list of all successor swaps
std::vector<swapPtr> Node::getSuccessorSwaps() const {
  std::vector<swapPtr> ret;
  for (const auto& succNode : _succ) {
    ret.push_back(succNode->_swap);
  }
  return ret;
}

std::vector<edgePtr> Node::getSuccessorEdges() const {
  return _succ;
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
  bool success = true;
  if (succ.getArrangement().getString() == pred.getArrangement().getString()) {
    cout << "ERROR: connecting " << succ.getArrangement().getString() << " to itself.";
    cout << " Addresses are " << &pred << " and " << &succ << "\n";
    success = false;
  }
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

  // Build a new connection and register it
  edgePtr edge = std::make_shared<Edge>(swap, predPtr, succPtr);
  pred._succ.push_back(edge);
  succ._pred.push_back(edge);
  return success;
}

// Using this node's words,
void Node::buildNextWords() {
  std::string newWord;
  for (const auto & word : _words) {
    for (const auto & edge : _succ) {
      newWord = word + edge->_swap->getName();
      edge->_succ->addWord(newWord);
    }
  }
}

// Adds a word to this Node's _words
bool Node::addWord(std::string& word) {
  if (_words.count(word) != 0) {
    return false;
  }
  _words.insert(word);
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
            if (!connectNodes(prevNode, currNode, swap)) {
              cout << "Node was already found, and swap was " << swap->getName() << "\n";
            } else {
              cout << "Successfully connected " << prevNode.getArrangement().getString() << " to " << currNode.getArrangement().getString() << " with " << swap->getName() << "\n";
            }
            foundNode = true;
            break;
          }
        }
        if (!foundNode) {
          // Yes, is a new result?  Build a new Node and connect to it
          // cout << "new ";
          Node newNode(newArr);
          if (!connectNodes(prevNode, newNode, swap)) {
            cout << "Node is new, and swap was " << swap->getName() << "\n";
            cout << "prevNode.getArrangement().getString() = " << prevNode.getArrangement().getString() << "\n";
            cout << "swap->getName() = " << swap->getName() << "\n";
            swap->displayInfo();
            cout << "newNode.getArrangement().getString() = " << newNode.getArrangement().getString() << "\n";
            cout << "newArr = " << newArr.getString() << "\n";

            return;
          } else {
            cout << "Successfully connected " << prevNode.getArrangement().getString() << " to " << newNode.getArrangement().getString() << " with " << swap->getName() << "\n";
          }
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

  std::cout << "\n";
  for (size_t i = 0; i < _levels.size(); ++i) {
    const auto& level = _levels[i];
    std::cout << i << "\t";
    for (size_t j = 0; j < level.size()-1; ++j) {
      std::cout << level[j].getArrangement().getString() << ", ";
    }
    std::cout << level.back().getArrangement().getString() << "\n";
  }

  // for (const auto& level : _levels) {
  //   cout << "--Level--\n";
  //   for (const auto& node : level) {
  //     cout << "----node----\n";
  //     for (const auto & word : node.getWords()) {
  //       cout << word << ", ";
  //     }
  //     cout << "\n";
  //   }
  // }
}

nodePtr Permutahedron::front() const {
  return std::make_shared<Node>(_levels.front()[0]);
}

nodePtr Permutahedron::back() const {
  return std::make_shared<Node>(_levels.back()[0]);
}

// Builds all words. These are stored in the nodes.
// This should be called after buildPermutahedron(), and then queries
// can be made, reductions can be made, etc.
void Permutahedron::buildAllWords() {
  std::vector<Word> words;
  // This is kind of inefficient!  Will use lots of memory.

  // Loop through levels, front() to back()
  // For each node on a given level, follow all of its edges to the next
  //    level successors, and add the resulting words to those successors.

  for (auto& level : _levels) {
    for (auto& node : level) {
      node.buildNextWords();
    }
  }
}

void Permutahedron::writeGEXF(std::string filename) const {
  ofstream out;
  out.open(filename);
  out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
  out << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
  out << "\t<graph mode=\"static\" defaultedgetype=\"directed\">\n";
  out << "\t\t<nodes>\n";
  for (const auto& level : _levels) {
    out << "\t\t\t<nodes>\n";
    for (const auto& node : level) {
      std::string name = node.getArrangement().getString();
      out << "\t\t\t\t<node id=\"" << name << "\" label=\"" << name << "\" />\n";
    }
    out << "\t\t\t</nodes>\n";
  }
  out << "\t\t</nodes>\n";
  out << "\t\t<edges>\n";
  size_t i = 0;
  for (const auto& level : _levels) {
    for (const auto& node : level) {
      for (const auto& edge : node.getSuccessorEdges()) {
        std::string sourceName = node.getArrangement().getString();
        std::string targetName = edge->_succ->getArrangement().getString();
        std::string label = edge->_swap->getName();
        out << "\t\t\t<edge id=\"" << i << "\" source=\"" << sourceName << "\" target=\"" << targetName << "\" label=\"" << label << "\" />\n";
        i += 1;
      }
    }
  }
  out << "\t\t</edges>\n";
  out << "\t</graph>\n";
  out << "</gexf>\n";
  out.close();
}
