# Q4 — Matrix Multiplication using Strassen's Method

**File:** `4_strassen_matrix_mult.c`

Compile & run:
```bash
gcc -o q4 4_strassen_matrix_mult.c
./q4
```

## Files in this folder
- `4_strassen_matrix_mult.c` — the algorithm (comments removed)
- `q4_strassen_timing.csv` — running time of Strassen's method vs naive
  `O(n^3)` multiplication, for `n` from 2 up to 256
- `q4_strassen_graph.png` — plot of the CSV data (log-log scale)

## What the data shows
At these matrix sizes the naive `O(n^3)` method is actually *faster* in
wall-clock time than Strassen's method, even though Strassen does fewer
raw multiplications. This is a well-known, real effect: Strassen's
implementation here allocates many small submatrices and does extra
matrix additions/subtractions at every recursion level, and that
overhead dominates until `n` becomes very large. It illustrates why
Strassen's algorithm is mostly of theoretical/asymptotic interest for
these sizes — its `O(n^2.81)` advantage over `O(n^3)` only pays off once
`n` is large enough for the lower exponent to outweigh the constant
overhead.
