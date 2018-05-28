#pragma once
#include "types.h"
#include "arrangement.h"
#include "swap.h"
#include "word.h"


// Forward declarations
class Node;
using nodePtr = std::shared_ptr<Node>;
using edgeTuple = std::tuple<swapPtr, Word, nodePtr>;

// A class encapsulating a single node in the Permutahedron graph
class Node {
public:
  Node();
  Node(const Arrangement& arr, const Word& word);
  std::vector<swapPtr> getPredecessorSwaps() const;
  std::vector<swapPtr> getSuccessorSwaps(const std::vector<swapPtr>& swaps) const;
  Arrangement getArrangement() const;
  Word getWord() const;
  friend bool connectNodes(Node& pred, Node& succ);

// private:
  Arrangement _arr;
  Word _word;
  std::vector<edgeTuple> _pred, _succ;
};

using level = std::vector<Node>;

class Permutahedron {
public:
  Permutahedron();
  void buildPermutahedron(std::vector<swapPtr>& swaps, Arrangement& start, Arrangement& end);
  void display() const;

private:
  std::vector<level> _levels;
};
