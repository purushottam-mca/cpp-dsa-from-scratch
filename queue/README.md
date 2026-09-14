# Queue From Scratch

## Interview question

"Build a queue class from scratch with enqueue, dequeue, front, and empty check."

That is the core. The hidden part they watch for is how you avoid shifting the whole array on every dequeue.

## What to build

- `enqueue(value)` adds to the back.
- `dequeue()` removes from the front.
- `front()` looks at the front item.
- `empty()` and `size()` report the state.

## Approach in simple words

A queue is a line at a ticket counter. New people join at the back. The person at the front gets served and leaves. Nobody cuts in the middle.

The trick is the circular array. Keep a `head` index for the front and compute the back from head plus size. When you reach the end of the array, you wrap back to index 0 using the remainder trick. Dequeue just moves head forward. No shifting. Nothing copied.

When the array is full, double it like a vector, but copy items in line order starting from head, then reset head to 0. That keeps the line in the right order in the new bigger room.

## Complexity in short

- `enqueue`, `dequeue`, `front`: constant time.
- Growing step: linear time, happens rarely.
- Memory: one array plus a head index.

## Common follow ups

- "Why not just shift everything left on dequeue?" That makes every dequeue linear. The circular trick keeps it constant.
- "Queue from two stacks?" Push into stack one. For dequeue, pour stack one into stack two if stack two is empty, then pop from stack two.
- "Circular buffer full vs empty?" Both look like head equals tail, so this version tracks size separately. Say that if they ask.
