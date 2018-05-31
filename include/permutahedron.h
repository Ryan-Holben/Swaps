#pragma once
#include "types.h"
#include "arrangement.h"
#include "swap.h"
#include "word.h"


// Forward declarations
class Node;
struct Edge;
using nodePtr = std::shared_ptr<Node>;
using edgePtr = std::shared_ptr<Edge>;

// Directed edge
struct Edge {
  swapPtr _swap;
  nodePtr _pred, _succ;

  Edge(swapPtr s, nodePtr pred, nodePtr succ) : _swap(s), _pred(pred), _succ(succ) {}
};

// A class encapsulating a single node in the Permutahedron graph
class Node {
public:
  Node();
  Node(const Arrangement& arr);
  Arrangement getArrangement() const;
  std::vector<swapPtr> getPredecessorSwaps() const;
  std::vector<swapPtr> getSuccessorSwaps() const;
  std::vector<swapPtr> computeSuccessorSwaps(const std::vector<swapPtr>& swaps) const;
  friend bool connectNodes(Node& pred, Node& succ, swapPtr swap);

// private:
  Arrangement _arr;
  std::vector<edgePtr> _pred, _succ;
};

using level = std::vector<Node>;

class Permutahedron {
public:
  Permutahedron();
  void buildPermutahedron(std::vector<swapPtr>& swaps, Arrangement& start);
  void display() const;
  nodePtr front() const;
  nodePtr back() const;

private:
  std::vector<level> _levels;
};
