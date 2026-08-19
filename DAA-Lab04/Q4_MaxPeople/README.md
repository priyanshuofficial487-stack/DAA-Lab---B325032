# Q4 — Peak Crowd at a Party

## The problem, in simple words

A camera logs each guest's entry time `a_i` and exit time `b_i`. We want to
find the moment when the most people were in the party at the same time.

## The idea (sweep line)

Think of every entry as a `+1` event and every exit as a `-1` event:

1. Turn the `n` entry times and `n` exit times into `2n` events.
2. Sort all `2n` events by time — O(n log n).
3. Sweep left to right, keeping a running `count`. Add `+1` on an entry
   event, `-1` on an exit event. Track the maximum value `count` ever
   reaches, and the time at which that happens.

Since the problem says all times are distinct, we don't need to worry about
ties — an exit and an entry never happen at exactly the same instant.

## Input representation

Each person's `(entry, exit)` pair is stored in two parallel `int` arrays.
This is enough because the sweep-line algorithm only needs to turn each
pair into two independent events — it never needs to know which person a
time belongs to.

The program takes this input **interactively from the user** at the
console: it asks for `n`, then the entry and exit time for each person.

## Time complexity

- Building events: O(n)
- Sorting events: O(n log n)
- Sweeping: O(n)
- **Total: O(n log n)**

## Files

- `q4.c` — prompts the user for each person's entry/exit time, then finds the peak
- `graph.png` — measured runtime (on inputs from 1,000 to 800,000 people) vs the O(n log n) line

## Run it

```bash
gcc -o q4 q4.c
./q4
```
