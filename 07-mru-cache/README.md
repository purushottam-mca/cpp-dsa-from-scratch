# MRU Cache From Scratch

## Interview question

"Build an MRU cache with get and put in constant time. When full, drop the most recently used entry."

If you already did LRU, they may ask this as a one line follow up: "now flip it." This folder is that answer.

## What to build

- `get(key)` returns the value, or -1 when missing. A hit marks the key as most recently used.
- `put(key, value)` inserts or updates. An update also marks the key as most recently used. When over capacity, the most recently used entry is dropped.
- Capacity comes from the constructor and must be above zero.

## Approach in simple words

Copy the LRU design exactly: a doubly linked list for order plus a map from key to list node. Most used at the front, least used at the back. The only change is which end you cut. LRU cuts the back. MRU cuts the front.

Walk through the classic test with capacity 2: put 1, put 2, get 1, put 3. After get 1, the front holds 1. Put 3 adds another node and the cache overflows, so the front (key 1) is erased from both the list and the map. Key 2 survives. That is the exact opposite of LRU and the whole point of the exercise.

Same honesty note as LRU: the list is handwritten, lookup reuses `unordered_map`. Interviews test the wiring, not a second copy of hashing.

## Complexity in short

- `get` and `put`: constant time average.
- Memory: one node per entry plus one map slot per entry.

## When is MRU actually useful

Say this if they ask why anyone would want it. When you scan a big file once and never look back, the newest page is the least likely to be needed again, so dropping it protects the older pages you may still revisit. Databases use this idea for one pass scans.

## Common follow ups

- "Show me the diff from LRU." One eviction line: drop head instead of tail. Everything else is identical.
- "What breaks if get does not move the node?" Then recently read keys would be evicted as if untouched, which violates the MRU rule.
