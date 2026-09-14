# Stack From Scratch

## Interview question

"Build a stack class from scratch with push, pop, top, and empty check."

Sometimes they add: "use it to check balanced brackets." That is the classic follow up.

## What to build

- `push(value)` puts an item on top.
- `pop()` removes the top item.
- `top()` looks at the top item without removing it.
- `empty()` and `size()` report the state.

## Approach in simple words

A stack is a pile of plates. You add to the top and take from the top. You never reach into the middle.

Inside, this version is just a plain array with a counter that says where the top is. Push writes at the counter and moves it up. Pop moves the counter down. Top reads one below the counter. When the array fills up, it doubles exactly like a vector.

Pop and top on an empty stack throw an error. Say that line in the interview. It shows you care about safety.

## Complexity in short

- `push`, `pop`, `top`: constant time.
- Memory: one array, nothing else.

## Common follow ups

- "Stack from two queues, or queue from two stacks?" They want to see if you can fake one behavior with the other. For queue from two stacks, push into stack one, and pop from stack two, refilling it when empty.
- "Min stack?" Keep a second stack that tracks the smallest value seen so far.
- "Check brackets?" Push opening brackets, pop when a matching closing one comes. If anything is left over or mismatched, the string is bad.
