# DAA Lab-04 — Applications of Sorting

BTech (CS-B and CE), 3rd Semester
Instructor: Dr. Ajaya Kumar Dash

This repo has the solutions to all 6 questions from Lab-04. Each question has its own
folder with:

- **`qX.c`** — the C program that solves the problem, taking input interactively
  from the console (this is the "proper input representation" each question asks for)
- **`graph.png`** — a graph of measured runtime vs input size, compared against the
  theoretical time complexity
- **`README.md`** — a simple explanation of the problem, the input representation
  chosen, the algorithm idea, and the complexity

## Questions at a glance

| # | Problem | Idea | Time Complexity |
|---|---------|------|------------------|
| 1 | [Sort by Colour](Q1_SortByColour/) | Bucket by colour, keep order inside each bucket | O(n) |
| 2 | [Pair Sum in Two Sets](Q2_PairSum/) | Sort one set, binary search the other | O(n log n) |
| 3 | [k Numbers Summing to T](Q3_KSum/) | Sort once, fix k-2 numbers, two-pointer for the rest | O(n^(k-1) · log n) |
| 4 | [Peak Crowd at a Party](Q4_MaxPeople/) | Turn entries/exits into +1/-1 events, sweep | O(n log n) |
| 5 | [Merge Overlapping Intervals](Q5_MergeIntervals/) | Sort by start, merge as you go | O(n log n) |
| 6 | [Point Covered by Most Intervals](Q6_MaxPointOverlap/) | Same sweep-line idea as Q4 | O(n log n) |

## How to run any question

```bash
cd Q1_SortByColour
gcc -o q1 q1.c
./q1
```

Then just answer the prompts the program prints (it will ask for `n` and the
items one at a time). Run it from the **integrated terminal**, not the
editor's "Run" button, so the working directory is correct if a program
needs it.

## About the graphs

Each `graph.png` shows the algorithm's measured runtime (on inputs growing from a
few hundred up to hundreds of thousands of elements) plotted against a scaled version
of its theoretical time-complexity curve, so you can see the measured line tracking
the theory line.
