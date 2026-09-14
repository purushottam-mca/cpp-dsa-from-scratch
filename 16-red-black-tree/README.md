# Red-Black Tree From Scratch

## Interview question

"Build a red-black tree with insert and search, and explain how it stays balanced."

Insert with fixup is the standard ask. Full delete fixup is almost never required live. The `valid()` checker here is your proof the rules hold.

## What to build

- `insert(key)` adds a key and repairs the coloring on the way up. Duplicates ignored.
- `contains(key)` is the plain BST walk.
- `inorder()` returns sorted keys.
- `valid()` proves every red-black rule holds right now.

## Approach in simple words

Start from a normal BST, then paint every node red or black and enforce three rules: the root is black, a red node never has a red child, and every road from root to leaf passes through the same number of black nodes. Those rules squeeze the height into logarithmic bounds no matter the insert order.

New nodes arrive red, which can only break the no red child rule. Fixup looks at the uncle. Red uncle: repaint parent, uncle, and grandparent, then carry the problem one level up. Black uncle: rotate. If the new node sits on the inner side, rotate it to the outer side first, then rotate the parent up and swap their colors. Mirror everything for the right side. The demo asserts `valid()` after every single insert, so any broken case fails loudly.

Leaves are one shared black sentinel node instead of nulls. That removes all the null checks from rotations and fixup and is the normal textbook shape. Say that line if they ask why the code has no null checks.

## Complexity in short

- `insert`, `contains`: logarithmic always. Height never passes twice log of n.
- Sorted input 1 to 7 stays valid and shallow here. Plain BST would chain.
- Memory: one node per key plus color and parent pointer each.

## Common follow ups

- "Red-black vs AVL?" AVL is stricter, so lookups run a touch faster and inserts rotate more. Red-black rotates less, so write heavy loads prefer it. Both logarithmic.
- "Why must the root end black?" Fixup can paint the root red while pushing problems up. One final repaint keeps rule one true.
- "Delete?" Same three BST removal cases, then a longer fixup that borrows blackness from siblings. Sketch the plan in words. Coding it live is rarely demanded.
- "Where is this used in real life?" Ordered maps in many standard libraries and the Linux scheduler. Name one and move on.
