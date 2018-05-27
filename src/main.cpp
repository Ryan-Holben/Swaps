#include <iostream>

#include "helpers.h"
#include "permutahedron.h"

using namespace std;

int main() {
  // Create the containers for our data
  Arrangement start, end;
  std::vector<Swap> swaps;

  // Fill those containers with a 1D array to do permutations on
  create1DArrangement(6, &start, &swaps);

  // Build the end permutation that we're targeting
  end = start.getReverse();

  // Initialize & build a permutahedron
  Permutahedron perm = Permutahedron();
  perm.buildPermutahedron(swaps, start, end);
  perm.display();

  // Word w1, w2;
  // std::vector<Swap> l1 {swaps[0], swaps[2], swaps[1]};
  // std::vector<Swap> l2 {swaps[2]};
  // w1.append(l1);
  // w2.append(l1);
  // w2.append(l2);
  // Swap s;
  // getEdge(w1, w2, &s);
  // s.displayInfo();
  // swaps[2].displayInfo();

  return 0;
}
