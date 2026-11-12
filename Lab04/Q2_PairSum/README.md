# Q2 — Pair Sum Across Two Sets

## The problem, in simple words

We have two sets `S1` and `S2`, both of size `n`, and a target number `x`.
We need to find out if there's some element `a` from `S1` and some element
`b` from `S2` such that `a + b = x`.

## The idea

Checking every pair would take O(n²). We can do much better with sorting:

1. Sort `S2` — O(n log n).
2. For every element `a` in `S1`, we need `b = x - a` to exist in `S2`.
   Since `S2` is sorted, use binary search to check if `x - a` is present —
   O(log n) per lookup.
3. If we find it for any `a`, we're done: `(a, b)` is our pair.

## Input representation

`S1` and `S2` are stored as plain `int` arrays of size `n`. The target `x`
is a single integer. This is the natural representation for "a set of
numbers" and it's all the algorithm needs — no extra structure required
since we only ever look up values, not track where they came from beyond
which set they're in.

The program takes this input **interactively from the user** at the
console: it asks for `n`, then the `n` numbers of `S1`, then the `n`
numbers of `S2`, then the target `x`.

## Time complexity

- Sorting `S2`: O(n log n)
- `n` binary searches, each O(log n): O(n log n)
- **Total: O(n log n)**

## Files

- `q2.c` — prompts the user for `S1`, `S2`, and `x`, then searches for a pair
- `graph.png` — measured runtime (on inputs from 1,000 to 800,000 elements) vs the O(n log n) line

## Run it

```bash
gcc -o q2 q2.c
./q2
```
