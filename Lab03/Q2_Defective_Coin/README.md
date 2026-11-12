# Q2 — Search the Defective (Lighter) Coin

**File:** `2_defective_coin.c`

Compile & run:
```bash
gcc -o q2 2_defective_coin.c -lm
./q2
```

## Files in this folder
- `2_defective_coin.c` — the algorithm (comments removed)
- `q2_coin_weighings.csv` — weighings used vs `n`, compared against the
  theoretical `log2(n)`, for `n` from 10 up to 1,000,000
- `q2_defective_coin_graph.png` — plot of the CSV data

## What the data shows
The number of balance weighings needed to find the defective coin tracks
`log2(n)` closely as `n` grows, confirming the divide-and-conquer
algorithm finds the defective coin in about `log2(n) + c` weighings
rather than checking coins one by one (which would take up to `n-1`
weighings).
