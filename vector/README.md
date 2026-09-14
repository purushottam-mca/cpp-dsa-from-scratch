# Vector From Scratch

## Interview question

"Build a vector class from scratch with push back, pop back, get, set, size, and automatic growing."

That is the full ask. Nothing more hidden in it.

## What to build

- `push_back(value)` adds to the end.
- `pop_back()` removes from the end.
- `operator[]` reads or writes by index.
- `size()` tells how many items you have.
- `capacity()` tells how many slots you have before the next regrow.
- `empty()` tells if there is nothing in it.
- Growing happens on its own when the array is full.

## Approach in simple words

Think of a vector as a hallway with rooms. You rent 1 room first. When friends keep coming and rooms run out, you move to a building with double the rooms and shift everyone over. Old building gets returned.

That is all the growing logic is. Start with capacity 0. First push makes room for 1. Next full push doubles to 2, then 4, then 8. Copy old items over, delete the old block, point to the new one.

Pop does not shrink the building. It just says one less room is in use. This keeps push and pop fast.

Out of range access and pop on empty throw an error. In an interview, say this out loud. They want to hear that you thought about it.

## Complexity in short

- `push_back`: fast most of the time, occasional slow step when growing. Averages to constant time.
- `pop_back`, `get`, `set`: constant time.
- Growing step: copies all items, so it costs linear time, but it happens rarely.
- Memory: one plain array, nothing extra.

## Common follow ups

- "Why double and not add 10 each time?" Doubling keeps the average push cheap. Adding a fixed amount would copy too often.
- "How would you add shrink?" Only shrink when size drops to one fourth of capacity, else push and pop near the edge would keep resizing.
- "What about copy?" Real vectors need a copy constructor and copy assign. This version deletes them to stay short. Say that in the interview so they know you know.
