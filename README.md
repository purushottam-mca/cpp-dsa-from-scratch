# Data Structures From Scratch

I am preparing for interviews, so I am building common data structures by hand in C++. No shortcuts. Each folder has one topic, one code file, and one README that explains the idea in plain words.

## How this repo is set up

Each topic lives in its own folder like this:

```text
vector/
  vector.cpp
  README.md
```

The cpp file has the full implementation plus a small demo in `main()`. The README has the interview question, what to build, and the approach in simple terms.

## Topics

1. `vector/` - dynamic array that grows by itself
2. `stack/` - last in, first out
3. `queue/` - first in, first out
4. `hashmap/` - key value store built on hashing (HashSet idea included)
5. `lru-cache/` - cache that drops the least recently used entry
6. `smart-pointers/` - simple UniquePtr and SharedPtr to learn ownership
7. `mru-cache/` - cache that drops the most recently used entry
8. `binary-search-tree/` - ordered tree with three-case delete
9. `max-heap/` - biggest item always on top
10. `min-heap/` - smallest item always on top, top-k stream trick included
11. `avl-tree/` - self balancing BST with rotations

Coming next: trie, graph, red black tree.

## How to run any topic

You only need `g++`. No CMake, no extra setup.

```bash
g++ -std=c++17 -Wall -Wextra vector/vector.cpp -o /tmp/vector && /tmp/vector
g++ -std=c++17 -Wall -Wextra stack/stack.cpp -o /tmp/stack && /tmp/stack
g++ -std=c++17 -Wall -Wextra queue/queue.cpp -o /tmp/queue && /tmp/queue
g++ -std=c++17 -Wall -Wextra hashmap/hashmap.cpp -o /tmp/hashmap && /tmp/hashmap
g++ -std=c++17 -Wall -Wextra lru-cache/lru-cache.cpp -o /tmp/lru && /tmp/lru
g++ -std=c++17 -Wall -Wextra smart-pointers/smart-pointers.cpp -o /tmp/smart && /tmp/smart
g++ -std=c++17 -Wall -Wextra mru-cache/mru-cache.cpp -o /tmp/mru && /tmp/mru
g++ -std=c++17 -Wall -Wextra binary-search-tree/binary-search-tree.cpp -o /tmp/bst && /tmp/bst
g++ -std=c++17 -Wall -Wextra max-heap/max-heap.cpp -o /tmp/maxheap && /tmp/maxheap
g++ -std=c++17 -Wall -Wextra min-heap/min-heap.cpp -o /tmp/minheap && /tmp/minheap
g++ -std=c++17 -Wall -Wextra avl-tree/avl-tree.cpp -o /tmp/avl && /tmp/avl
```

## Ground rules for this repo

- One file per topic, self contained, compiles on its own.
- Core logic written by hand, not by calling STL for the main part.
- READMEs stay simple. Short sentences. Everyday examples. No bluff.
