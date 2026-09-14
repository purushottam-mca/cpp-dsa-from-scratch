# Segment Tree From Scratch

## Interview question

"Build a segment tree with range sum query and point update."

Range minimum follows the same shape with min instead of plus. Lazy propagation is the usual follow up.

## What to build

- Constructor from an array, builds the tree in linear time.
- `query(l, r)` returns the sum over the inclusive range.
- `update(index, value)` sets one position and refreshes the path above it.
- Bad ranges and indexes throw instead of answering wrong.

## Approach in simple words

Think of the array cut into halves again and again until single items remain. Each tree node stores the sum of its slice. The root holds the whole array, its children hold the left and right halves, down to leaves holding one item each.

A query walks down and collects slices. Fully outside the question contributes zero. Fully inside is taken whole, no need to go deeper. Partial overlap splits and asks both halves. Update walks to the single leaf, writes the new value, then recomputes every sum on the way back up.

The tree lives in a plain array of size 4 times n, which is safely big enough. Node 1 is the root. Children of node i sit at 2*i and 2*i+1, the same indexing trick as the binary heap. No pointers anywhere.

## Complexity in short

- Build: linear time, each level totals to n work.
- `query`, `update`: logarithmic. Each level visits only a few nodes.
- Memory: one array of 4 times n.
- Naive scan would answer each query in linear time. This tree trades memory for speed.

## Common follow ups

- "Range minimum instead of sum?" Same code with min in place of plus and a large identity for outside ranges.
- "Range add, not just point set?" That needs lazy propagation: park pending adds on nodes and push them down only when visited. Sketch it in words unless they ask for code.
- "Fenwick tree instead?" Smaller code and memory for prefix sums, but it cannot answer every range question a segment tree can. Name both and pick per problem.
