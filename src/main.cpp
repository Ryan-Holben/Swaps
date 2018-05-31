#include <iostream>

#include "helpers.h"
#include "permutahedron.h"

int main() {
  std::cout << "\n";
  // Create the containers for our data
  Arrangement start, end;
  std::vector<swapPtr> swaps;

  // Fill those containers with a 1D array to do permutations on
  create1DArrangement(4, &start, swaps);
  // start = Arrangement(4);
  // start.defineAdjacency(0, 1);
  // std::string name = "a";
  // swaps.emplace_back(std::make_shared<Swap>(0, 1, name));
  // start.defineAdjacency(0, 2);
  // name = "b";
  // swaps.emplace_back(std::make_shared<Swap>(0, 2, name));
  // start.defineAdjacency(1, 3);
  // name = "c";
  // swaps.emplace_back(std::make_shared<Swap>(1, 3, name));
  // start.defineAdjacency(2, 3);
  // name = "d";
  // swaps.emplace_back(std::make_shared<Swap>(2, 3, name));

  // Initialize & build a permutahedron
  Permutahedron perm = Permutahedron();
  perm.buildPermutahedron(swaps, start);

  // Display the results
  perm.display();

  cout << perm.front()->getArrangement().getString() << "\n";
  cout << perm.back()->getArrangement().getString() << "\n";

  return 0;
}
