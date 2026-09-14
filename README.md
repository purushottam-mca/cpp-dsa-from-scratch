# Data Structures From Scratch

I am preparing for interviews, so I am building common data structures by hand in C++. No shortcuts. Each folder has one topic, one code file, and one README that explains the idea in plain words.

## Topics

| # | Topic | ReadMe | Code | Run |
|---|-------|-------|------|-----|
| 1 | Vector, dynamic array that grows | [ReadMe](01-vector/README.md) | [Code](01-vector/vector.cpp) | `g++ -std=c++17 -Wall -Wextra 01-vector/vector.cpp -o /tmp/vector && /tmp/vector` |
| 2 | Stack, last in first out | [ReadMe](02-stack/README.md) | [Code](02-stack/stack.cpp) | `g++ -std=c++17 -Wall -Wextra 02-stack/stack.cpp -o /tmp/stack && /tmp/stack` |
| 3 | Queue, first in first out | [ReadMe](03-queue/README.md) | [Code](03-queue/queue.cpp) | `g++ -std=c++17 -Wall -Wextra 03-queue/queue.cpp -o /tmp/queue && /tmp/queue` |
| 4 | HashMap, hashing with chaining | [ReadMe](04-hashmap/README.md) | [Code](04-hashmap/hashmap.cpp) | `g++ -std=c++17 -Wall -Wextra 04-hashmap/hashmap.cpp -o /tmp/hashmap && /tmp/hashmap` |
| 5 | LRU Cache, drops least used | [ReadMe](05-lru-cache/README.md) | [Code](05-lru-cache/lru-cache.cpp) | `g++ -std=c++17 -Wall -Wextra 05-lru-cache/lru-cache.cpp -o /tmp/lru && /tmp/lru` |
| 6 | Smart Pointers, ownership | [ReadMe](06-smart-pointers/README.md) | [Code](06-smart-pointers/smart-pointers.cpp) | `g++ -std=c++17 -Wall -Wextra 06-smart-pointers/smart-pointers.cpp -o /tmp/smart && /tmp/smart` |
| 7 | MRU Cache, drops most used | [ReadMe](07-mru-cache/README.md) | [Code](07-mru-cache/mru-cache.cpp) | `g++ -std=c++17 -Wall -Wextra 07-mru-cache/mru-cache.cpp -o /tmp/mru && /tmp/mru` |
| 8 | Binary Search Tree, three-case delete | [ReadMe](08-binary-search-tree/README.md) | [Code](08-binary-search-tree/binary-search-tree.cpp) | `g++ -std=c++17 -Wall -Wextra 08-binary-search-tree/binary-search-tree.cpp -o /tmp/bst && /tmp/bst` |
| 9 | Max Heap, biggest on top | [ReadMe](09-max-heap/README.md) | [Code](09-max-heap/max-heap.cpp) | `g++ -std=c++17 -Wall -Wextra 09-max-heap/max-heap.cpp -o /tmp/maxheap && /tmp/maxheap` |
| 10 | Min Heap, smallest on top | [ReadMe](10-min-heap/README.md) | [Code](10-min-heap/min-heap.cpp) | `g++ -std=c++17 -Wall -Wextra 10-min-heap/min-heap.cpp -o /tmp/minheap && /tmp/minheap` |
| 11 | AVL Tree, rotations | [ReadMe](11-avl-tree/README.md) | [Code](11-avl-tree/avl-tree.cpp) | `g++ -std=c++17 -Wall -Wextra 11-avl-tree/avl-tree.cpp -o /tmp/avl && /tmp/avl` |
| 12 | Trie, prefix search | [ReadMe](12-trie/README.md) | [Code](12-trie/trie.cpp) | `g++ -std=c++17 -Wall -Wextra 12-trie/trie.cpp -o /tmp/trie && /tmp/trie` |
| 13 | Graph, BFS DFS cycle check | [ReadMe](13-graph/README.md) | [Code](13-graph/graph.cpp) | `g++ -std=c++17 -Wall -Wextra 13-graph/graph.cpp -o /tmp/graph && /tmp/graph` |
| 14 | Union-Find, path compression | [ReadMe](14-union-find/README.md) | [Code](14-union-find/union-find.cpp) | `g++ -std=c++17 -Wall -Wextra 14-union-find/union-find.cpp -o /tmp/uf && /tmp/uf` |
| 15 | Dijkstra, shortest paths | [ReadMe](15-dijkstra/README.md) | [Code](15-dijkstra/dijkstra.cpp) | `g++ -std=c++17 -Wall -Wextra 15-dijkstra/dijkstra.cpp -o /tmp/dij && /tmp/dij` |
| 16 | Red-Black Tree, color fixup | [ReadMe](16-red-black-tree/README.md) | [Code](16-red-black-tree/red-black-tree.cpp) | `g++ -std=c++17 -Wall -Wextra 16-red-black-tree/red-black-tree.cpp -o /tmp/rb && /tmp/rb` |
| 17 | Segment Tree, range sums | [ReadMe](17-segment-tree/README.md) | [Code](17-segment-tree/segment-tree.cpp) | `g++ -std=c++17 -Wall -Wextra 17-segment-tree/segment-tree.cpp -o /tmp/seg && /tmp/seg` |

Coming next: topological sort, trie extras, bellman-ford.

## How to run any topic

You only need `g++`. No CMake, no extra setup. Every row follows one generic form, so copy the exact command from the Run column above:

```bash
g++ -std=c++17 -Wall -Wextra <folder>/<file>.cpp -o /tmp/<name> && /tmp/<name>
```

## Ground rules for this repo

- One file per topic, self contained, compiles on its own.
- Core logic written by hand, not by calling STL for the main part.
- READMEs stay simple. Short sentences. Everyday examples. No bluff.
