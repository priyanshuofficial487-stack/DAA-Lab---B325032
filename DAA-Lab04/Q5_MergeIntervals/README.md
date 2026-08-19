# Q5 — Merge Overlapping Intervals

## The problem, in simple words

We have a list of `n` intervals `(x_i, y_i)`. Some of them overlap or touch.
We want to merge all the overlapping ones into single, bigger intervals.

Example: `{(1,3), (2,6), (8,10), (7,18)}` → `{(1,6), (7,18)}`

## The idea

1. Sort the intervals by their start value `x` — O(n log n).
2. Walk through the sorted list, keeping a "current merged interval":
   - If the next interval's start is inside (or touching) the current
     merged interval, stretch the current interval's end if needed.
   - Otherwise, the current interval is finished — save it and start a new
     one with the next interval.
3. At the end, the saved intervals are the answer.

Because the list is sorted by start, once we move past an interval we never
need to look at it again — one linear pass is enough after sorting.

## Input representation

Each interval is stored as a `struct Interval { int x; int y; }` in an
array. Keeping the pair together (rather than two separate arrays) makes
the sort-by-start-value step a single `qsort` call with a clean comparator.

The program takes this input **interactively from the user** at the
console: it asks for `n`, then each interval as `x y`.

## Time complexity

- Sorting: O(n log n)
- One linear merge pass: O(n)
- **Total: O(n log n)**

## Files

- `q5.c` — prompts the user for `n` intervals, then prints the merged result
- `graph.png` — measured runtime (on inputs from 1,000 to 800,000 intervals) vs the O(n log n) line

## Run it

```bash
gcc -o q5 q5.c
./q5
```

Example session (matches the assignment's example):

```
Enter number of intervals (n): 4
Enter each interval as: x y
Interval 1 - x y: 1 3
Interval 2 - x y: 2 6
Interval 3 - x y: 8 10
Interval 4 - x y: 7 18

Merged intervals:
(1, 6) (7, 18)
```
