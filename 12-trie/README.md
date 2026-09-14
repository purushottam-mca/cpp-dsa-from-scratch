# Trie From Scratch

## Interview question

"Build a trie with insert, search, and startsWith."

Autocomplete and word dictionary follow ups come free once this works.

## What to build

- `insert(word)` stores a word.
- `search(word)` is true only for a full word that was inserted.
- `startsWith(prefix)` is true when some inserted word begins with it.

## Approach in simple words

A trie is a tree of letters. The root is empty. Each step down picks the child for the next letter. Words that share a beginning share the same path, then split where they differ. A small flag on a node says a word ends here.

That flag is the whole difference between search and startsWith. Apple, app, and application all walk the same a-p-p road. The node after the second p carries the flag because app is a word. The node after appl does not, so search for appl is false while startsWith for appl is true.

This version keeps lowercase a-z only and stores children in a fixed array of 26. That is the standard interview shape. Say the tradeoff out loud: the array wastes space on missing letters but makes each step a direct jump with no hashing.

## Complexity in short

- `insert`, `search`, `startsWith`: one step per letter, so time grows with word length, not with how many words are stored.
- Memory: one node per letter of each distinct prefix path. Shared beginnings cost nothing extra.

## Common follow ups

- "Count words with a prefix?" Keep a counter on each node, bumped on every insert that passes through.
- "Delete a word?" Walk down, then prune back up while nodes have no children and no end flag. Only asked sometimes.
- "Why not a hash set?" A hash set answers full words fast but cannot list completions for a prefix. The trie keeps prefix order for free.
- "Memory heavy?" For sparse alphabets, swap the array for a map of used children only. Say it, keep the array version as your written answer.
