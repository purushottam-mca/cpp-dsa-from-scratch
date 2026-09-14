# Min Heap From Scratch

## Interview question

"Build a min heap with push, pop, and top."

If you did max heap first, say so and name the diff: every comparison flips. Then they usually follow with the top k problem.

## What to build

- `push(value)` adds an item.
- `pop()` removes the smallest item.
- `top()` looks at the smallest item.
- `empty()` and `size()` report the state.

## Approach in simple words

Same machine as max heap, mirrored. Complete binary tree in a plain array, parent at (i-1)/2, children at 2*i+1 and 2*i+2. One rule: every parent is smaller than its children. Push adds at the end and bubbles up while smaller than its parent. Pop moves the last item to the front and sinks it down through the smaller child.

The demo includes the trick interviewers actually want: keeping the k largest items from a stream. Hold a min heap of size k. For each new value, push it, and if the heap grows past k, pop the smallest. At the end the heap holds exactly the k biggest, with the kth biggest on top.

## Complexity in short

- `push`, `pop`: logarithmic. `top`: constant time.
- Memory: one array.
- The top k pattern costs log k per item instead of log n. Say that line, it shows you see the point.

## Common follow ups

- "Max heap or min heap for k largest?" Min heap of size k. A max heap would have to hold everything.
- "Median of a stream?" Two heaps: a max heap for the lower half and a min heap for the upper half, kept balanced. The tops give the median.
- "Merge k sorted lists?" Push each list head into a min heap, pop the smallest, push its next. Repeat.
