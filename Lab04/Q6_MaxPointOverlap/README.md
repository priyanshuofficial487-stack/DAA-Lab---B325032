# Q6 — Point Covered by the Most Intervals

## The problem, in simple words

We have `n` intervals `[l_i, r_i]` on a number line. We want to find a
single point `p` that lies inside as many of these intervals as possible.
Endpoints count — if `p` equals an interval's `l_i` or `r_i`, that interval
still covers `p`.

## The idea (same sweep line as Q4)

1. For each interval, create a `start` event at `l_i` (+1) and an `end`
   event at `r_i` (-1).
2. Sort all `2n` events by their position. If a start and an end land on
   the exact same coordinate, process the **start before the end** — this
   is what makes an endpoint count as "inside" the interval.
3. Sweep through the sorted events, keeping a running `count`. Track the
   maximum count and the position where it was reached — that position is
   our answer point `p`.

## Input representation

Each interval's endpoints `(l, r)` are stored in two parallel `int`
arrays. The sweep-line approach converts these into `2n` events, so
representing each interval as a simple pair is all that's needed.

The program takes this input **interactively from the user** at the
console: it asks for `n`, then each interval as `l r`.

## Time complexity

- Building events: O(n)
- Sorting events: O(n log n)
- Sweeping: O(n)
- **Total: O(n log n)**

## Files

- `q6.c` — prompts the user for `n` intervals, then finds the best point
- `graph.png` — measured runtime (on inputs from 1,000 to 800,000 intervals) vs the O(n log n) line

## Run it

```bash
gcc -o q6 q6.c
./q6
```

Example session (matches the assignment's example):

```
Enter number of intervals (n): 4
Enter each interval as: l r
Interval 1 - l r: 10 40
Interval 2 - l r: 20 60
Interval 3 - l r: 50 90
Interval 4 - l r: 15 70

Point with maximum overlap: 20
Number of intervals covering it: 3
```
