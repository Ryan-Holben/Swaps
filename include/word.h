#pragma once
#include "arrangement.h"
#include "swap.h"

// A sequence of swaps.  This serves as a convenience container for swaps.
// It should be able to print the letter sequence, and have a convenience
// function for applying the swaps, in order, to an arrangement.
class Word {
public:
  Word();
  void append(const swapPtr swap);
  void append(const std::vector<swapPtr>& swaps);
  std::string getString() const;
  Arrangement apply(const Arrangement& lhs) const;
  friend bool getEdge(const Word& pred, const Word& succ, swapPtr swap);
  void operator =(const Word& rhs);

private:
  std::vector<swapPtr> _swaps;
};

Arrangement operator *(Arrangement & lhs, const Word & rhs);
