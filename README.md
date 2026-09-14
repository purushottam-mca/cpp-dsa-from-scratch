# Data Structures From Scratch

I am preparing for interviews, so I am building common data structures by hand in C++. No shortcuts. Each folder has one topic, one code file, and one README that explains the idea in plain words.

## How this repo is set up

Each topic lives in its own folder like this:

```text
01-vector/
  vector.cpp
  README.md
```

The cpp file has the full implementation plus a small demo in `main()`. The README has the interview question, what to build, and the approach in simple terms.

## Topics

1. `01-vector/` - dynamic array that grows by itself
2. `02-stack/` - last in, first out
3. `03-queue/` - first in, first out
4. `04-hashmap/` - key value store built on hashing (HashSet idea included)
5. `05-lru-cache/` - cache that drops the least recently used entry
6. `06-smart-pointers/` - simple UniquePtr and SharedPtr to learn ownership
7. `07-mru-cache/` - cache that drops the most recently used entry
8. `08-binary-search-tree/` - ordered tree with three-case delete
9. `09-max-heap/` - biggest item always on top
10. `10-min-heap/` - smallest item always on top, top-k stream trick included
11. `11-avl-tree/` - self balancing BST with rotations
12. `12-trie/` - letter tree for prefix search
13. `13-graph/` - adjacency list with BFS, DFS, cycle check
14. `14-union-find/` - disjoint sets with path compression
15. `15-dijkstra/` - shortest paths with a min heap

Coming next: red black tree, segment tree, topological sort.

## How to run any topic

You only need `g++`. No CMake, no extra setup.

```bash
g++ -std=c++17 -Wall -Wextra 01-vector/vector.cpp -o /tmp/vector && /tmp/vector
g++ -std=c++17 -Wall -Wextra 02-stack/stack.cpp -o /tmp/stack && /tmp/stack
g++ -std=c++17 -Wall -Wextra 03-queue/queue.cpp -o /tmp/queue && /tmp/queue
g++ -std=c++17 -Wall -Wextra 04-hashmap/hashmap.cpp -o /tmp/hashmap && /tmp/hashmap
g++ -std=c++17 -Wall -Wextra 05-lru-cache/lru-cache.cpp -o /tmp/lru && /tmp/lru
g++ -std=c++17 -Wall -Wextra 06-smart-pointers/smart-pointers.cpp -o /tmp/smart && /tmp/smart
g++ -std=c++17 -Wall -Wextra 07-mru-cache/mru-cache.cpp -o /tmp/mru && /tmp/mru
g++ -std=c++17 -Wall -Wextra 08-binary-search-tree/binary-search-tree.cpp -o /tmp/bst && /tmp/bst
g++ -std=c++17 -Wall -Wextra 09-max-heap/max-heap.cpp -o /tmp/maxheap && /tmp/maxheap
g++ -std=c++17 -Wall -Wextra 10-min-heap/min-heap.cpp -o /tmp/minheap && /tmp/minheap
g++ -std=c++17 -Wall -Wextra 11-avl-tree/avl-tree.cpp -o /tmp/avl && /tmp/avl
g++ -std=c++17 -Wall -Wextra 12-trie/trie.cpp -o /tmp/trie && /tmp/trie
g++ -std=c++17 -Wall -Wextra 13-graph/graph.cpp -o /tmp/graph && /tmp/graph
g++ -std=c++17 -Wall -Wextra 14-union-find/union-find.cpp -o /tmp/uf && /tmp/uf
g++ -std=c++17 -Wall -Wextra 15-dijkstra/dijkstra.cpp -o /tmp/dij && /tmp/dij
```

## Ground rules for this repo

- One file per topic, self contained, compiles on its own.
- Core logic written by hand, not by calling STL for the main part.
- READMEs stay simple. Short sentences. Everyday examples. No bluff.
