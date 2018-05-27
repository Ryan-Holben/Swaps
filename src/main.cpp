#include <iostream>

#include "helpers.h"

using namespace std;

int main() {
  // Create the containers for our data
  Arrangement arr;
  std::vector<Swap> swaps;

  // Fill those containers with a 1D array to do permutations on
  create1DArrangement(6, &arr, &swaps);
  arr.display();
  for (const auto & swap : swaps) {
    swap.displayInfo();
  }

  return 0;
}
