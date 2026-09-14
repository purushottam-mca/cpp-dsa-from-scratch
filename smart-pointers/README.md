# Smart Pointers From Scratch

## Interview question

"Build a simplified unique pointer and shared pointer. Explain ownership, move, and reference counting."

They care more about your explanation than about matching every line of the real STL.

## What to build

- `UniquePtr`: one owner only. Supports move, `get`, `release`, `reset`, and `*` access. Copies are banned.
- `SharedPtr`: many owners. Supports copy, move, `use_count`, `reset`, and `*` access. The last owner cleans up.

## Approach in simple words

A unique pointer is like a house key that cannot be copied. You can hand the key to someone else, but then you no longer have it. In code, handing over is a move. The old pointer is set to empty so only one owner ever deletes the object. `release` gives up the key without deleting, so the caller takes charge.

A shared pointer is like a shared flat where everyone counts heads. A small counter on the side tracks how many owners exist. Each copy adds one. Each owner going away subtracts one. When the count hits zero, the last person out deletes the object and the counter. Move just passes your share without touching the count.

Both free their memory in the destructor. That idea has a name: RAII. It means cleanup happens on its own when the owner goes out of scope, so you never write delete by hand in normal code.

## Complexity in short

- All operations here are constant time. Copying a shared pointer only bumps a number.
- Memory: unique adds nothing extra, shared adds one small counter per object.
- This version is not thread safe. The real one uses atomic counts. Say that if they ask.

## Common follow ups

- "Why ban copies on unique?" Two owners would both try to delete. That is a double free and it crashes.
- "What is a weak pointer?" An observer that looks without adding to the count. It breaks cycles where two shared pointers keep each other alive.
- "What happens on self assign?" Guard with a check, or drop after copying from the other side. Both versions here handle it.
- "Cycles with shared?" If A owns B and B owns A, neither count reaches zero. That is the leak they want you to name.
