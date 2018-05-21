#include <iostream>
#include "arrangement.h"
#include "swap.h"


using namespace std;

int main() {
  // Arrangement arr(5);
  // arr.define_adjacency(1, 2);
  // arr.display();
  Arrangement arr = create1DArrangement(6);
  arr.display();
  std::string name = "a";
  Swap s(1, 2, name);
  s.displayInfo();
  (s*arr).display();

  return 0;
}
