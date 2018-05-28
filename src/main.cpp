#include <iostream>

#include "helpers.h"
#include "permutahedron.h"

int main() {
  // Create the containers for our data
  Arrangement start, end;
  std::vector<swapPtr> swaps;

  // Fill those containers with a 1D array to do permutations on
  create1DArrangement(6, &start, swaps);

  // Build the end permutation that we're targeting
  end = start.getReverse();

  // Initialize & build a permutahedron
  Permutahedron perm = Permutahedron();
  perm.buildPermutahedron(swaps, start, end);
  perm.display();

  return 0;
}
