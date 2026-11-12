# Q3 — Max and Min using Divide and Conquer

**File:** `3_max_min_dc.c`

Compile & run:
```bash
gcc -o q3 3_max_min_dc.c
./q3
```

## Files in this folder
- `3_max_min_dc.c` — the algorithm (comments removed)
- `q3_maxmin_comparisons.csv` — comparisons used by the D&C method vs a
  naive two-pass method, for `n` from 10 up to 1,000,000, alongside a
  `3n/2` reference line
- `q3_maxmin_graph.png` — plot of the CSV data

## What the data shows
The divide-and-conquer method consistently uses noticeably fewer
comparisons than the naive two-pass approach (which needs close to `2n`
comparisons), and both grow linearly with `n`. The D&C count tracks the
`3n/2` reference line closely; for a few `n` values that aren't exact
powers of two the count can drift slightly above the plain `3n/2` line
because the recursive split isn't perfectly even, but it stays firmly
`O(n)` and well below the naive `2n` curve.
