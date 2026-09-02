# Q1 - 1D Array Operations and Their Complexities

Given an unsorted integer array of size `n`, this program implements and analyses
the worst-case complexity of common array operations.

## Complexity Table

| Operation | Worst-case Complexity | Notes |
|---|---|---|
| Finding the maximum element | O(n) | single linear scan |
| Finding first and second largest | O(n) | single pass, track two variables |
| Finding the mean | O(n) | sum of elements / n |
| Finding the median | O(n log n) | sort the array, pick middle element(s) |
| Finding the standard deviation | O(n) | needs mean first, then one more pass |
| Finding the mode | O(n log n) | sort, then scan for longest run |
| Removing all duplicates | O(n log n) | sort, then remove adjacent equal values |
| Reversing the array | O(n) | swap from both ends toward the middle |
| Partitioning around a pivot | O(n) | Lomuto-style single pass partition |

Median and mode can be solved in O(n) on average using hashing/quickselect,
but the array-sort approach is used here since it is simple and still gives
an easily provable O(n log n) worst case.

## Files

- `q1.c` - source code (all 9 operations + a timing driver)
- `complexity.csv` - measured running time of each operation for increasing `n`
- `graph.png` - time vs input size plot for all operations

## How it was run

```
gcc -O2 -o q1 q1.c -lm
./q1
```

The program first runs a timing experiment over `n = 1000` to `400000` and
writes `complexity.csv`, then prints a demo run on a small 7-element array
showing every operation's output.

## Observation

The graph clearly separates two families of curves:
- Flat, near-zero lines: max, first/second largest, mean, std-dev, reverse,
  partition (all O(n))
- Faster-growing curves: median, mode, remove-duplicates (all O(n log n),
  dominated by the `qsort` call)
