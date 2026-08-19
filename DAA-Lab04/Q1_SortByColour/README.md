# Q1 — Sort by Colour

## The problem, in simple words

We have `n` items. Each item is a (number, colour) pair, and colour is always
red, blue, or yellow. The items already come sorted by their number.

We want to regroup them so all reds come first, then all blues, then all
yellows — but within each colour group, the numbers must **stay in the same
order** they were in originally.

## The idea

Since we only have 3 colours, we don't need a comparison-based sort at all.
Just walk through the array once, and drop each item into one of three
buckets based on its colour:

1. Create three empty lists: `red`, `blue`, `yellow`.
2. Go through the input left to right (it's already sorted by number).
3. Push each item into its colour's bucket, in the order you see it.
4. Because we never change the relative order of items *within* a bucket,
   the numbers inside each bucket stay sorted automatically.
5. Concatenate `red + blue + yellow` — that's the answer.

This is really just a 3-bucket counting sort where the "key" is the colour.

## Input representation

Each item is stored as a small `struct Item { int number; int colour; }`,
where `colour` is encoded as `0 = red`, `1 = blue`, `2 = yellow`. This keeps
the comparison in the sort down to a single integer check instead of string
comparisons, which is what lets the algorithm run in true O(n).

The program takes this input **interactively from the user** at the
console: it first asks for `n`, then asks for each item's number and
colour one at a time (colour typed as `r`, `b`, or `y`). This matches the
problem statement's requirement of "choosing the proper input
representation" — you decide the format, and the program prompts for
exactly that format.

## Time complexity

- One pass to bucket the items: O(n)
- One pass to concatenate the buckets: O(n)
- **Total: O(n)** — no comparisons, no log factor.
- Extra space: O(n) for the three buckets.

## Files

- `q1.c` — prompts the user for `n` items and their colours, then sorts
- `graph.png` — measured runtime (on inputs from 1,000 to 800,000 items) vs the O(n) line

## Run it

```bash
gcc -o q1 q1.c
./q1
```

Example session:

```
Enter number of items (n): 8
Enter the 8 items, one at a time.
Items must already be sorted by number (as the problem assumes).
For colour, type: r (red), b (blue), or y (yellow)

Item 1 - number: 1
Item 1 - colour (r/b/y): b
Item 2 - number: 3
Item 2 - colour (r/b/y): r
...
```
