# Q4 - Sorting a Permutation Using reverse(p, i, j)

We are given a permutation `p` of `1..n` and the only allowed operation is
`reverse(p, i, j)`, which reverses the elements `p[i..j]`. Two things are
asked:

1. Show that any permutation can be sorted using **O(n) reversals**.
2. Design an algorithm that sorts `p` in **O(n log^2 n) cost**, where the
   cost of `reverse(p, i, j)` equals its length `|j - i| + 1`.

---

## Part 1: Sorting with O(n) reversals (proof + algorithm)

**Claim:** Any permutation of size `n` can be sorted using at most `2n`
reversals (i.e. O(n) reversals).

**Proof / construction (selection-sort by reversal):**

For `i = 0` to `n-1`:
1. Find `pos`, the index of the value `i+1` in `p[i..n-1]` (a linear scan).
2. `reverse(p, i, pos)` — this moves the value `i+1` to index `i`, but also
   reverses everything between, which is fine since that region is still
   unsorted.
3. `reverse(p, i+1, pos)` — this restores the relative order of the
   remaining unsorted suffix elements that got flipped when the block above
   was reversed (needed so we don't disturb work already reasoned about;
   it also keeps the algorithm simple to state/prove).

Each iteration of the loop uses **at most 2 reversals**, and there are `n`
iterations, so the total number of reversals is at most `2n = O(n)`. Since
after each iteration `p[0..i]` is fixed in its final sorted position and
never touched again, after `n` iterations the whole array is sorted. ∎

This is implemented as `selectionSortByReversal()` in `q4.c`. Its reversal
**count** is O(n), but since each reversal can be as long as `n`, its total
**cost** (sum of reversal lengths) is O(n^2) in the worst case — which
motivates Part 2.

---

## Part 2: Sorting in O(n log^2 n) cost

Simply minimizing the number of reversals (Part 1) does not minimize total
**cost**, since a reversal's cost is its length. We instead adapt merge sort,
replacing the usual "merge into an auxiliary array" step with an **in-place
merge built entirely out of reversals**.

### Building block: rotate using 3 reversals

A left-rotation of a block `p[l..r]` around split point `m` (i.e. swapping
the two contiguous sub-blocks `p[l..m]` and `p[m+1..r]`) can be done with
exactly 3 reversals:

```
reverse(p, l, m)
reverse(p, m+1, r)
reverse(p, l, r)
```

Total cost of one rotate = O(r - l + 1) (three reversals whose lengths sum
to about `2(r-l+1)`).

### In-place merge using rotation (O(k log k) for a merge of total size k)

Given two adjacent sorted blocks `p[l..m]` and `p[m+1..r]`:

1. If `p[m] <= p[m+1]`, the two blocks are already in order — done, no cost.
2. Otherwise, split the **left** block at its midpoint `m1`.
3. Binary search inside the **right** block for the position `m2` where
   `p[m1]` would be inserted to keep the block sorted.
4. Rotate `p[m1..m]` and `p[m+1..m2-1]` (3 reversals) so all elements
   smaller than `p[m1]` move before it. `p[m1]` is now at its final
   position `newm1` in this merge.
5. Recurse the same merge procedure on the two remaining pieces:
   `(l, m1-1, newm1-1)` and `(newm1+1, ..., r)`.

Because a binary search is used to always cut the smaller side in half,
each merge of `k` total elements does O(log k) levels of rotation, each
level touching O(k) elements total, giving a merge cost of **O(k log k)**.

### Putting it together

```
mergeSortByReversal(l, r):
    if l >= r: return
    m = (l + r) / 2
    mergeSortByReversal(l, m)
    mergeSortByReversal(m+1, r)
    mergeByRotation(l, m, r)      // O(k log k), k = r - l + 1
```

The recurrence for the total cost is:

```
T(n) = 2T(n/2) + O(n log n)
```

By the Master theorem this solves to:

```
T(n) = O(n log^2 n)
```

which is exactly the bound asked for.

### Correctness

- The base case (`l >= r`) is a single element, trivially sorted.
- By induction, `mergeSortByReversal(l, m)` and `mergeSortByReversal(m+1, r)`
  leave `p[l..m]` and `p[m+1..r]` each individually sorted.
- `mergeByRotation` merges two sorted blocks into one sorted block using
  only reversals (no auxiliary array), so `p[l..r]` ends up fully sorted.
- Hence by induction on the size of the range, `mergeSortByReversal(0, n-1)`
  sorts the entire permutation.

## Files

- `q4.c` - source code:
  - `selectionSortByReversal` — Part 1, O(n) reversals, O(n^2) cost
  - `mergeSortByReversal` + `mergeByRotation` + `rotate` — Part 2, O(n log^2 n) cost
  - a timing/cost driver that measures both algorithms on random permutations
- `complexity.csv` - reversal count, total reversal cost, and running time for
  both algorithms, for increasing `n`
- `graph.png` - reversal cost and reversal count vs `n` for both algorithms

## How it was run

```
gcc -O2 -o q4 q4.c
./q4
```

For every input size, the program checks with `isSorted()` that both
algorithms actually produce a sorted array, then logs the reversal count and
total cost. It also prints a small 5-element demo for both algorithms.

## Observation

In `complexity.csv`, the selection-by-reversal cost grows roughly
quadratically with `n` (cost multiplies by about 4x when `n` doubles), while
the rotation-based merge sort's cost grows much more slowly, consistent with
O(n^2) vs O(n log^2 n).
