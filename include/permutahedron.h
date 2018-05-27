#pragma once
#include "types.h"
#include "arrangement.h"
#include "swap.h"
#include "word.h"


// A class encapsulating a single node in the Permutahedron graph
class Node {
public:
  Node();

// private:
  Arrangement _arr;
  Word _word;
  std::vector<Node*> _pred, _succ;
};

using level = std::vector<Node>;

class Permutahedron {
public:
  Permutahedron();
  void buildPermutahedron(std::vector<Swap>& swaps, Arrangement& start, Arrangement& end);
  void display() const;

private:
  std::vector<level> _levels;
};
