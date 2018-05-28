#pragma once
#include "types.h"
#include "arrangement.h"
#include "swap.h"
#include "word.h"


// A class encapsulating a single node in the Permutahedron graph
class Node {
public:
  Node();
  Node(const Arrangement& arr, const Word& word);
  std::vector<std::shared_ptr<Swap>> getPredecessorSwaps() const;
  std::vector<std::shared_ptr<Swap>> getSuccessorSwaps(const std::vector<std::shared_ptr<Swap>>& swaps) const;
  Arrangement getArrangement() const;
  Word getWord() const;
  friend bool connectNodes(Node& pred, Node& succ);

// private:
  Arrangement _arr;
  Word _word;
  std::vector<std::shared_ptr<Node>> _pred, _succ;
};

using level = std::vector<Node>;

class Permutahedron {
public:
  Permutahedron();
  void buildPermutahedron(std::vector<std::shared_ptr<Swap>>& swaps, Arrangement& start, Arrangement& end);
  void display() const;

private:
  std::vector<level> _levels;
};
