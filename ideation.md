# Notes on generalizing Swaps

## Miscellaneous thoughts
A sequence of swaps should be called a **mixing**.  Because mixing occurs when particles blend _locally_, rather than jumping.  And as this happens over time, particles can more fully mix.  

I want to generalize the swap problem & solutions.  This means having the swap squares, rectangles, cubes, etc., in addition to linear swapping.

## Definitions
**Swaps** are defined to be pairwise exchanges of adjacent items which occupy spaces in some array or other configuration of spaces.

## Objects
1. **arrangement**.  An array of spaces.  These should be numbered.  The arrangement also owns and keeps track of the values that occupy all of its spaces.
2. **value**.  The object that occupies one of the spaces in an arrangement.  Each value should be instantiated with one number in the range 1...n.  This is unrelated from the numbering of spaces.
2. **swap**.  The action that, when applied to an arrangement, swaps two of that arrangement's values, and produces a new arrangement object.  It should contain the numerical IDs of the spaces that will be swapped, as well as a letter-based name for itself for display purposes.
3. **mixing** or **word**.  A sequence of swaps.  This serves as a convenience container for swaps.  It should be able to print the letter sequence, and have a convenience function for applying the swaps, in order, to an arrangement.
4. **permutahedron**.  A directed graph of arrangement/mixing pairs as nodes, whose edges are swaps.
  a. **level**.  One level of the graph structure.
  b. **node**.
    i. Contains an arrangement.
    ii. Contains the full word used to produce this arrangement.
    iii. `predecessors` - A vector of all predecessor nodes
    iv. `successors` - A vector of all successor nodes.
    v. A helper function exists which looks like `edge(pred, succ)` which returns the swap used to get from `pred` to `succ`.  This means we won't explicitly have edge objects.

### Other data structures
1. Arrangement dictionary - unordered_map<string, vector<mixing>> - The keys are string arrangements (comma-separated strings of ids), and the values are a vector of all mixings that produce them.  So we can do O(1) lookups of words to help determine equality & fundamental rules.


## Architecture

### The setup
1. Define a list of named (or numbered) positions.  Those positions can be filled with named (or numbered) objects, which we will swap.
2. Have the adjacency of those positions _explicitly_ defined, rather than inferred.
  * There is a 1-1 relationship between adjacency rules & swaps.
    a. For every swap, our code should build a swap action.  This is an object.  When we multiply a permutation on the right with this object, we get a new permutation.
  * Later, we can have a separate module that feeds as an input, that takes in arbitrary shapes and dimensions and produces the adjacency rules.
3. Once the adjacency rules are defined, we can begin applying swaps.

### Permuting
1. Fill the spaces with the numbers 1...n.
2. Begin building swap strings.

How do we do full reduction of words in order to find the fundamental rules?
