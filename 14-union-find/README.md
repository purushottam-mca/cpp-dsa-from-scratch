# Union-Find From Scratch

## Interview question

"Build a union-find (disjoint set) with union, find, and connected."

Kruskal and cycle questions usually hide behind it as follow ups.

## What to build

- `find(x)` returns the representative of x's set.
- `unite(a, b)` merges the two sets. Returns false when already together.
- `connected(a, b)` answers true or false.
- `count()` tells how many separate sets remain.

## Approach in simple words

Give every item a parent pointer. Items in the same family eventually point up to one shared root. Find follows parents to that root. Union joins two roots together.

Two tricks keep it fast. Path compression: during find, repoint every visited node straight at the root, so the next lookup is one hop. Union by rank: hang the shorter tree under the taller one, so trees stay shallow instead of chaining. Together they make each operation almost constant time. Say both names in the interview. They are the keywords being listened for.

A redundant union is a safe no-op that returns false. That return value is what Kruskal uses to skip edges that would form a cycle.

## Complexity in short

- `find`, `unite`, `connected`: almost constant time per call (inverse Ackermann, effectively flat).
- Memory: two small arrays, parent and rank, one slot per item.

## Common follow ups

- "Cycle in an undirected graph?" Process edges one by one. If an edge joins two already connected vertices, you found a cycle.
- "Kruskal MST?" Sort edges by weight, take each unless its ends are connected, union when taken. The boolean from `unite` drives it.
- "Number of islands or provinces?" One union per land bridge, answer is `count`. Classic LeetCode 200 and 547.
- "Why not BFS for connectivity?" BFS answers one query. Union-find answers a whole stream of merges and queries online.
