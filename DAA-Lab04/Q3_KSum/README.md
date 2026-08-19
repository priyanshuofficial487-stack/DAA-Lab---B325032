# Q3 — k Numbers That Sum to T

## The problem, in simple words

We have a set `S` of `n` integers, a target `T`, and a number `k`. We want to
know if we can pick `k` numbers from `S` (all different positions) that add
up to `T`.

## The idea

This is the natural generalisation of the classic "2-sum" and "3-sum" tricks:

1. Sort `S` once — O(n log n).
2. Fix the first `k - 2` numbers using nested loops (this costs O(n^(k-2))
   combinations).
3. For whatever target remains, solve the last 2 numbers with the standard
   **two-pointer** technique on the sorted array — O(n) per call.
4. Multiply it out: O(n^(k-2)) × O(n) = O(n^(k-1)), plus the one-time
   O(n log n) sort.

Our C program implements this recursively: `kSumRec` peels off one number
at a time until only 2 numbers are left, then calls a two-pointer `twoSum`.

## Input representation

The set `S` is a plain `int` array of size `n`. `k` and `T` are read as
separate integers. Keeping `S` as a flat array (rather than, say, a linked
list) is what makes sorting and the two-pointer scan efficient.

The program takes this input **interactively from the user** at the
console: it asks for `n`, then the `n` numbers of `S`, then `k`, then `T`.

## Time complexity

- Sort: O(n log n)
- Recursive fixing + two-pointer finish: O(n^(k-1))
- **Total: O(n^(k-1) · log n)** — matches what the question asks for.

Note: for `k = 3` this is O(n² log n), which grows much faster than the
O(n log n) algorithms in the other questions — that's why the benchmark
used to build `graph.png` used smaller input sizes.

## Files

- `q3.c` — prompts the user for `S`, `k`, and `T`, then searches for a combination
- `graph.png` — measured runtime of a 3-sum instance (on inputs from 200 to 3,000 elements) vs the O(n² log n) line

## Run it

```bash
gcc -o q3 q3.c
./q3
```
