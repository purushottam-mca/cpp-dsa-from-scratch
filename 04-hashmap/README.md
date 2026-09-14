# HashMap From Scratch

## Interview question

"Build a hash map from scratch with put, get, remove, and handling for collisions."

Sometimes they add: "What is a HashSet then?" The answer is one line and it is at the bottom of this page.

## What to build

- `put(key, value)` inserts or updates.
- `get(key)` returns the value or throws if missing.
- `contains(key)` answers true or false.
- `remove(key)` deletes the entry. Missing key is a safe no-op.
- `size()` and bucket count.
- Rehashing when the map gets crowded.

## Approach in simple words

Think of a row of buckets. To store a key, you run it through a hash function and take the remainder by the bucket count. That tells you which bucket to use.

Two keys can land in the same bucket. That is called a collision and it is normal. Each bucket holds a small linked list, so colliding keys just line up one after another. Lookup walks that short list and compares keys.

When the map holds more items than 75 percent of the bucket count, you double the buckets and move every entry to its new home. This step is called rehashing. It keeps the little lists short so lookups stay fast.

Update does not grow the map. If the key is already there, you just replace its value.

## Complexity in short

- `put`, `get`, `remove`: fast on average, constant time, as long as lists stay short.
- Worst case with everything in one bucket: linear time. Rehashing exists to stop that.
- Memory: one bucket array plus one small node per entry.

## HashSet in one paragraph

A HashSet is the same machine with values removed. It stores only keys to answer "have I seen this before". You could build it from this code by ignoring the value field. Interviews accept that answer.

## Common follow ups

- "How do you handle collisions?" This version uses chaining, a linked list per bucket. The other option is open addressing, where you probe for the next free slot.
- "When do you rehash?" When items divided by buckets passes 0.75. Then double and move everything.
- "What makes a good hash?" Fast to compute and spreads keys evenly. Here we reuse `std::hash` and focus on the table logic.
