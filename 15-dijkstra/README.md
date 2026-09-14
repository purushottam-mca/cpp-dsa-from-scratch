# Dijkstra From Scratch

## Interview question

"Find the shortest path from one source to all vertices in a weighted graph."

They will state or expect non-negative weights. If they say negative, the answer changes (see follow ups).

## What to build

- `addEdge(u, v, w)` stores a weighted link. Undirected in this folder.
- `shortest(src)` returns the cheapest distance to every vertex. Unreachable stays at infinity.

## Approach in simple words

Dijkstra is BFS with a sense of cost. Keep a best-known distance per vertex, starting at zero for the source and infinity elsewhere. Repeatedly pick the unsettled vertex with the smallest known distance, settle it, and try to improve its neighbors through it. A min heap always hands you that nearest vertex.

Two lines carry the whole algorithm. Relaxation: if reaching neighbor v through u is cheaper than v's current best, update it and push the new offer into the heap. Stale skip: when a popped offer no longer matches the recorded best, throw it away, because a cheaper offer for that vertex already won.

The demo pins the classic trap: the direct road 0 to 1 costs 4, but the detour through 2 costs 1 plus 2. The algorithm must report 3. If your code says 4, relaxation is broken.

Honesty note: the heap here is `priority_queue`. The hand-rolled min heap lives in `10-min-heap`. Dijkstra tests the greedy wiring, not a second copy of sift code. Say that if asked.

## Complexity in short

- Time: each edge can trigger one heap push, so edges times log vertices.
- Memory: the distance array plus the heap.
- Weights must be non-negative. One negative edge breaks the greedy promise.

## Common follow ups

- "Negative weights?" Dijkstra fails. Bellman-Ford handles them and reports negative cycles. Name it even if you do not code it.
- "Shortest path in edges, not weights?" Plain BFS from `13-graph`. Say when each tool fits.
- "The actual path, not just the distance?" Keep a parent array: every time you relax v through u, record u. Walk parents back from the target.
- "Many queries on one map?" One Dijkstra run per source. All-pairs is Floyd-Warshall, cubic, only for small dense graphs.
