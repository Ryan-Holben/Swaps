#pragma once
#include "arrangement.h"
#include "swap.h"

// A sequence of swaps.  This serves as a convenience container for swaps.
// It should be able to print the letter sequence, and have a convenience
// function for applying the swaps, in order, to an arrangement.
class Word {
public:
  Word();
  void append(Swap& swap);
  void append(std::vector<Swap>& swaps);
  std::string getString() const;
  Arrangement apply(Arrangement& lhs) const;

private:
  std::vector<Swap> _swaps;
};

Arrangement operator *(Arrangement & lhs, Word & rhs);
