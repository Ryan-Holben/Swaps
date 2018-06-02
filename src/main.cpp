#include <iostream>

#include "helpers.h"
#include "permutahedron.h"

int main() {
  std::cout << "\n";
  // Create the containers for our data
  Arrangement start, end;
  std::vector<swapPtr> swaps;

  // Fill those containers with a 1D array to do permutations on
  // create1DArrangement(4, &start, swaps);
  create2DArrangement(3, 3, &start, swaps);

  for (const auto & swap : swaps) {
    swap->displayInfo();
  }

  // Initialize & build a permutahedron
  Permutahedron perm = Permutahedron();
  perm.buildPermutahedron(swaps, start);

  // Build the words
  // perm.buildAllWords();

  // Display the results
  perm.display();

  // Write to a GEFX file
  perm.writeGEXF("output.gexf");
  return 0;
}
