# AVL Tree From Scratch

## Interview question

"Build a self balancing BST. Keep it balanced on insert and explain rotations."

Insert with balancing is the standard ask. Delete with balancing is a bonus they rarely require fully.

## What to build

- `insert(key)` adds a key and rebalances on the way back up. Duplicates ignored.
- `contains(key)` is the plain BST walk.
- `inorder()` returns sorted keys.
- `balanced()` checks the whole tree follows the AVL rule. Your proof in code.
- `height()` reports the tree height.

## Approach in simple words

Start from a normal BST, then add one number per node: its height. From that you get the balance factor, left height minus right height. As long as every node sits between -1 and 1, the tree is healthy.

Insert walks down like a BST, grows the leaf, then fixes heights and checks balance on the way back up. When a node hits 2 or -2, you rotate. Four shapes exist but they are two mirrors. Heavy on the outer side needs one rotation: right rotation for left-left, left rotation for right-right. Heavy on the inner side needs two: first fix the child, then the parent. Left-right and right-left are those doubles.

The demo forces each shape with three keys so you can draw them by hand: 30-20-10 for right, 10-20-30 for left, 30-10-20 for left-right, 10-30-20 for right-left. After each, the middle key ends up on top. That sentence alone answers half the follow ups.

## Complexity in short

- `insert`, `contains`: logarithmic always. Balance keeps the height small no matter the input order.
- Sorted input 1 to 7 gives height 3 here. Plain BST would give 7.
- Memory: one node per key plus one height number each. Rotations only rewire pointers.

## Common follow ups

- "AVL vs red black?" AVL is stricter, so lookups are a touch faster and inserts rotate more. Red black rotates less, so heavy write loads prefer it. Both are logarithmic.
- "When do you double rotate?" When the heavy child leans inward. Check the child balance first, fix the child, then the parent.
- "How do you prove balance in a test?" Walk the tree, compute both heights at each node, fail if any differ by more than 1. That is the `balanced()` function here.
- "Delete?" Same three BST cases, then rebalance upward like insert. Say the plan even if you do not code it.
