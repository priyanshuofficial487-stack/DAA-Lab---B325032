# Q6 — Loop Invariants in Selection Sort

**File:** `6_selection_sort_loop_invariant.c`

Compile & run:
```bash
gcc -o q6 6_selection_sort_loop_invariant.c
./q6
```

## Files in this folder
- `6_selection_sort_loop_invariant.c` — the algorithm (comments removed)
- `q6_selection_sort.csv` — comparisons and running time vs `n`, for `n`
  from 10 up to 16,000, alongside the expected `n(n-1)/2`
- `q6_selection_sort_graph.png` — plot of the CSV data

## What the data shows
The comparison count matches `n(n-1)/2` exactly for every `n` tested
(selection sort always scans the full remaining unsorted part, so this
count never changes regardless of the input). Running time grows in
step with it, both curves bending upward as a clear `Θ(n^2)` shape —
confirming selection sort gets quadratically slower as `n` grows, with
no speed-up even though the array was randomly generated (not
pre-sorted).
