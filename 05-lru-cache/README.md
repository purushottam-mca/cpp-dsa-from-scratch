# LRU Cache From Scratch

## Interview question

"Build an LRU cache with get and put, both in constant time. When the cache is full, drop the least recently used entry."

They almost always test it with capacity 2 and a fixed put and get order.

## What to build

- `get(key)` returns the value, or -1 when missing. A hit marks the key as most recently used.
- `put(key, value)` inserts or updates. An update also marks the key as most recently used. When over capacity, the least recently used entry is dropped.
- Capacity comes from the constructor and must be above zero.

## Approach in simple words

One tool alone cannot do this. A map finds keys fast but has no sense of order. A list keeps order but cannot find keys fast. So you glue them together.

Keep a doubly linked list with the most used entry at the front and the least used at the back. Keep a map from key to the exact list node. Get looks up the node in the map and moves that node to the front. Put adds a new node at the front, and when the cache grows past capacity, it cuts the node at the back and erases it from the map too.

Moving a node means fixing four links: its old neighbors join each other, then the node goes in front of the old head. Forgetting either half is the classic bug, so say both halves out loud in the interview.

Note on honesty: the list part here is handwritten, the lookup part reuses `unordered_map`. That is the normal interview split. They are testing whether you can wire the two halves together, not whether you can rewrite hashing again.

## Complexity in short

- `get` and `put`: constant time average, thanks to the map plus a fixed number of pointer fixes.
- Memory: one node per entry plus one map slot per entry.

## Common follow ups

- "What changes for MRU?" Evict from the front instead of the back. Same code, one line difference. That is your next topic.
- "What if get should not change order?" Then it is not LRU any more. Plain expiry or plain insert order would do.
- "Thread safety?" Real caches add a lock around get and put. Say it, but do not code it unless asked.
