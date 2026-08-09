# Q2 — Merge Sort vs. Modified (3-way) Merge Sort

## Standard merge sort
Divide the array into 2 halves, recursively sort each half (size `n/2`), and
merge the two sorted halves in `Θ(n)` time.

```
T(n) = 2T(n/2) + Θ(n)
```

By the Master Theorem (case 2: `a = 2, b = 2, f(n) = Θ(n) = Θ(n^{log_b a})`):

```
T(n) = Θ(n log n)
```

## Modified merge sort (divide into thirds)
Divide the array into 3 equal parts, recursively sort each third (size
`n/3`), and combine using a **3-way merge**. A k-way merge of `k` sorted
lists whose total length is `n` still touches each of the `n` elements a
constant number of times (compare the fronts of the 3 lists, output the
smallest, repeat) — so a 3-way merge is Θ(n), just like a 2-way merge
(only the constant factor changes: each output step now compares 3
candidates instead of 2, but that's still O(1) work per element for a
fixed 3).

```
T(n) = 3T(n/3) + Θ(n)
```

By the Master Theorem (case 2 again: `a = 3, b = 3, f(n) = Θ(n) = Θ(n^{log_3 3}) = Θ(n)`):

```
T(n) = Θ(n log n)
```

## Conclusion
**Both algorithms are Θ(n log n) in the worst case.** Dividing into thirds
does not change the asymptotic order of growth — it only changes the
*constant factor* and the *base of the logarithm* inside the recursion
tree (the recursion tree has `log_3 n` levels instead of `log_2 n` levels,
but each level still does Θ(n) total work, so the total remains
`Θ(n · log n)` either way, since `log_3 n = log_2 n / log_2 3` differs
from `log_2 n` only by a constant factor).

In practice, the 3-way merge does slightly more comparisons per merge step
(up to 2 comparisons to pick the minimum of 3 candidates vs. 1 comparison
for 2 candidates), so the modified version is usually a bit slower in
absolute wall-clock time despite having the same asymptotic complexity —
this is exactly what `merge_sort.c` / `plot_q2.py` should show: two curves
with the same `n log n` shape, offset by a roughly constant multiplicative
factor.
