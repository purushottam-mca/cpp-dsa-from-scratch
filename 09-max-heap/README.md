# Max Heap From Scratch

## Interview question

"Build a max heap with push, pop, and top."

Often paired with: "find the k largest items" or "merge k sorted lists." Both lean on this exact code.

## What to build

- `push(value)` adds an item.
- `pop()` removes the biggest item.
- `top()` looks at the biggest item.
- `empty()` and `size()` report the state.

## Approach in simple words

A heap is a complete binary tree stored in a plain array. No pointers. The parent of index i sits at (i-1)/2, its children at 2*i+1 and 2*i+2. Because every level is filled left to right, the array never has holes.

One rule keeps it working: every parent is bigger than its children. Push adds at the end and bubbles the new item up while it is bigger than its parent. Pop moves the last item to the front and sinks it down, each time swapping with the bigger child, until the rule holds again.

Say the index math out loud in the interview. That is the part they check.

## Complexity in short

- `push`, `pop`: height steps, logarithmic. The tree stays shallow because it is always complete.
- `top`: constant time, it just reads index 0.
- Building a heap from a ready array can be done in linear time by sinking down from the middle. Mention it if they ask.
- Memory: one array, nothing else.

## Common follow ups

- "Top k largest?" Push everything, pop k times. Or keep a min heap of size k for streams.
- "Heap vs sorted array?" Heap gives the max in constant time and insert in log time. Sorted array gives the max fast too but insert costs linear.
- "Heap sort?" Fill a heap, pop everything. Log linear time, constant extra memory if done in place.
