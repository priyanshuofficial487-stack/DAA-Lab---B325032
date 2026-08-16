# Q5 — Multiply Special-Pattern Square Matrices, O(n²)

**File:** `5_special_pattern_matrix_mult.c`

Compile & run:
```bash
gcc -o q5 5_special_pattern_matrix_mult.c
./q5
```

## Files in this folder
- `5_special_pattern_matrix_mult.c` — the algorithm (comments removed)
- `q5_special_pattern_timing.csv` — running time of the `O(n^2)`
  generator-array XOR-convolution vs naive full `O(n^3)` multiplication,
  for `n` from 2 up to 512
- `q5_special_pattern_graph.png` — plot of the CSV data (log-log scale)

## What the data shows
The special-pattern `O(n^2)` algorithm pulls clearly ahead of naive
`O(n^3)` multiplication as `n` grows — by `n = 512` it is roughly 30x
faster. Unlike Q4's Strassen case, here the asymptotic saving (`n^2` vs
`n^3`) is large enough that it shows up even at fairly small sizes,
because the algorithm only ever works with length-`n` generator arrays
instead of full `n x n` matrices.
