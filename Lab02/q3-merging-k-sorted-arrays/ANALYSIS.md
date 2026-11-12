# Q3 — Merging k Sorted Arrays (each of size n)

Total input size is `kn`.

## Method 1 — Sequential pairwise merge
Merge array 1 and array 2 (sizes `n` and `n`) → cost `Θ(2n)`.
Merge that result (size `2n`) with array 3 (size `n`) → cost `Θ(3n)`.
Merge that result (size `3n`) with array 4 (size `n`) → cost `Θ(4n)`.
...
Merge the accumulated result (size `(k-1)n`) with array k (size `n`) → cost `Θ(kn)`.

Total work:

```
T(n,k) = Θ(n) * (2 + 3 + 4 + ... + k)
       = Θ(n) * ( k(k+1)/2 - 1 )
       = Θ(n k^2)
```

**Worst-case running time: `Θ(n k²)`.**

This is the classic "repeated merge" pattern — merging grows linearly worse
with each additional array because every element already merged gets
touched again in every subsequent merge step.

## Method 2 — Pairwise tournament (divide and conquer) merge
Pair up the `k` arrays into `k/2` pairs, merge each pair in `Θ(n)` time
(each pair has `2n` total elements) → this level costs `Θ(kn)` total and
produces `k/2` arrays of size `2n`.
Repeat: pair those up into `k/4` arrays of size `4n`, costing another
`Θ(kn)` total for that level.
This continues for `log₂ k` levels (like the merge phase of ordinary merge
sort, but starting from `k` size-`n` runs instead of `k` size-1 runs), and
each level does `Θ(kn)` total work.

```
T(n,k) = Θ(kn) * log₂ k = Θ(kn log k)
```

**Worst-case running time: `Θ(kn log k)`.**

## Comparison
| Method | Complexity |
|---|---|
| 1. Sequential merge | `Θ(n k²)` |
| 2. Pairwise tournament merge | `Θ(n k log k)` |

For any `k > 2`, `k log k` grows much more slowly than `k²`, so **Method 2
is asymptotically far better** — this is exactly analogous to why ordinary
merge sort (`Θ(n log n)`, i.e. repeatedly pairwise-merging runs of size 1)
beats an algorithm that repeatedly merges one new element into a growing
sorted array (`Θ(n²)`, i.e. insertion sort).

`k_merge.c` implements and times both methods for fixed `n` while varying
`k` (and vice versa), and `plot_q3.py` renders the resulting curves next
to the `k²` and `k log k` reference shapes.
