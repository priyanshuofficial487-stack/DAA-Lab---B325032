# Q1 — Binary vs Ternary Search

**File:** `1_binary_vs_ternary_search.c`

Compile & run:
```bash
gcc -o q1 1_binary_vs_ternary_search.c
./q1
```

## Files in this folder
- `1_binary_vs_ternary_search.c` — the algorithm (comments removed)
- `q1_search_comparisons.csv` — comparisons used by each method, averaged
  over 25 random searches, for `n` from 10 up to 1,000,000
- `q1_binary_vs_ternary_graph.png` — plot of the CSV data

## What the data shows
Binary search consistently uses fewer comparisons than ternary search as
`n` grows, even though ternary search discards a bigger fraction (2/3) of
the array each step. This is because ternary search needs more comparisons
per level to decide which of the three parts to search next, and that
extra per-level cost outweighs the benefit of the extra split — matching
the `2*log2(n)` vs `4*log3(n)` analysis.
