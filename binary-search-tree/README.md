# Binary Search Tree From Scratch

## Interview question

"Build a binary search tree with insert, search, and delete."

Delete is where they watch you. It has three cases and you should name them before coding.

## What to build

- `insert(key)` adds a key. Duplicates are ignored in this version.
- `contains(key)` answers true or false.
- `remove(key)` deletes a key. Missing key is a safe no-op.
- `inorder()` returns keys in sorted order. Handy for proving the tree is right.

## Approach in simple words

Every node follows one rule: everything in the left subtree is smaller, everything in the right subtree is bigger. Insert walks down comparing until it finds an empty spot and grows a leaf there. Search does the same walk without growing anything.

Delete has three cases. Leaf: just free it. One child: let the child take its place. Two children: find the smallest key in the right subtree (the successor), copy it into the node, then delete that successor down below where it has at most one child. Say these three cases out loud before you write. Interviewers love that sentence.

Inorder walk visits left, node, right. On a valid BST that order always comes out sorted, so it doubles as your correctness check.

## Complexity in short

- `insert`, `contains`, `remove`: fast on a balanced tree, height steps. Slow to linear on a skewed tree, for example inserting sorted input 1, 2, 3 builds a chain.
- That skew problem is exactly why AVL exists. It is the next folder.
- Memory: one node per key, two pointers each.

## Common follow ups

- "Validate a BST?" Inorder must be strictly sorted, or recurse with a min and max range per node.
- "Find min or max?" Walk left all the way for min, right all the way for max.
- "Successor of a node?" Smallest key in its right subtree, or the nearest ancestor you turned left at.
- "Why do sorted inserts hurt?" Each new key goes one level deeper, so the tree becomes a linked list. Height balancing fixes it.
