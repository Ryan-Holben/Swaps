#pragma once

using level = std::vector<Arrangement>;

class Permutahedron {
public:
  Permutahedron();
  void buildPermutahedron(std::vector<Swap>& swaps, Arrangement& start, Arrangement& end);
  void display();

private:
  std::vector<level> _levels;
};
