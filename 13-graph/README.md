# Graph From Scratch

## Interview question

"Build a graph with BFS and DFS from scratch."

Cycle check and component count are the two follow ups that come up most, so both live in this folder.

## What to build

- `addEdge(u, v)` links two vertices. Undirected here, so both sides record it.
- `bfs(start)` returns visit order, level by level.
- `dfs(start)` returns visit order, deep first. Iterative with an explicit stack.
- `hasCycle()` answers true or false for the whole graph.
- `components()` counts the separate pieces.

## Approach in simple words

Store the graph as a list of neighbor lists. Vertex 0 holds everyone it connects to, vertex 1 holds its own, and so on. Adding an edge appends to both lists. That is the whole data structure.

BFS uses a queue. Take the front, visit it, line up its unseen neighbors at the back. Because the queue is first in first out, nearer vertices always come out before farther ones. That level order is why BFS gives shortest paths on unweighted graphs.

DFS uses a stack. Take the top, visit it, pile its unseen neighbors on top. The newest neighbor gets visited next, so the walk dives deep before it goes wide. Neighbors are pushed in reverse so the first neighbor still comes out first.

Cycle check runs BFS while remembering each node's parent. Reaching an already seen node that is not your parent means you found a second road to it, which is exactly what a cycle is. Components just repeats a reachability sweep from every unseen vertex and counts the sweeps.

## Complexity in short

- `addEdge`: constant time.
- `bfs`, `dfs`, `hasCycle`, `components`: each touches every vertex and edge once.
- Memory: one entry per edge on each side, plus a seen flag per vertex.

## Common follow ups

- "BFS or DFS for shortest path?" BFS on unweighted graphs. DFS does not promise shortest.
- "Directed cycle check?" Different tool: three colors (unvisited, on the current path, done). Finding an on-path neighbor means a cycle. Say this even though this folder is undirected.
- "Disconnected graph?" Loop over all vertices and start a fresh search from each unseen one. That is what `components` does.
- "Topological sort?" DFS finishing order on a directed acyclic graph. Natural next topic once this folder feels easy.
