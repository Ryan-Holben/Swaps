#include <iostream>

#include "helpers.h"
#include "permutahedron.h"

int main() {
  std::cout << "\n";
  // Create the containers for our data
  Arrangement start, end;
  std::vector<swapPtr> swaps;

  // Fill those containers with a 1D array to do permutations on
  create1DArrangement(5, &start, swaps);

  // Initialize & build a permutahedron
  Permutahedron perm = Permutahedron();
  perm.buildPermutahedron(swaps, start);

  // Display the results
  perm.display();

  cout << perm.front()->getArrangement().getString() << "\n";
  cout << perm.back()->getArrangement().getString() << "\n";

  return 0;
}
