# Design and Analysis of Algorithms — Lab 02

BTech (CS-B and CE), 3rd Semester · August 4, 2026
Instructor: Dr. Ajaya Kumar Dash

Solutions to Lab-02: dictionary ADT complexity analysis, merge sort
variants, and k-way array merging. Each question has its own folder with
a written analysis, a C program that empirically validates the theoretical
claim, and a Python script that plots the results.

## Structure

```
daa-lab02/
├── q1-dictionary-operations/
│   ├── ANALYSIS.md          # complexity table + reasoning for all 6 structures
│   ├── dictionary_ops.c     # implements & times all 7 ops on all 6 structures
│   ├── plot_q1.py           # generates plots/q1_<operation>.png
│   └── plots/                # (generated) order-of-growth plots
├── q2-merge-sort-variants/
│   ├── ANALYSIS.md          # Theta(n log n) derivation for both variants
│   ├── merge_sort.c         # classic 2-way vs. modified 3-way merge sort
│   ├── plot_q2.py           # generates plots/q2_runtime.png, q2_normalized.png
│   └── plots/
└── q3-merging-k-sorted-arrays/
    ├── ANALYSIS.md          # Theta(nk^2) vs Theta(nk log k) derivation
    ├── k_merge.c            # sequential vs. pairwise (tournament) merge
    ├── plot_q3.py            # generates plots/q3_vs_k.png, q3_vs_n.png, ...
    └── plots/
```

## How to run

Each `q*` folder is self-contained. From inside a folder:

```bash
gcc -O2 -Wall -o <program> <program>.c
./<program>              # writes results_*.csv
pip install matplotlib   # if not already installed
python3 plot_q*.py       # reads the CSV, writes PNGs into plots/
```

For example:

```bash
cd q1-dictionary-operations
gcc -O2 -Wall -o dictionary_ops dictionary_ops.c
./dictionary_ops
python3 plot_q1.py
```

## Summary of results

**Q1 — Dictionary operations worst-case complexity**

| Structure | Search | Insert | Delete | Max | Min | Pred | Succ |
|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Unsorted array | O(n) | O(1) | O(1) | O(n) | O(n) | O(n) | O(n) |
| Sorted array | O(log n) | O(n) | O(n) | O(1) | O(1) | O(1) | O(1) |
| Singly linked, unsorted | O(n) | O(1) | O(n) | O(n) | O(n) | O(n) | O(n) |
| Singly linked, sorted | O(n) | O(n) | O(n) | O(n) | O(1) | O(n) | O(1) |
| Doubly linked, unsorted | O(n) | O(1) | O(1) | O(n) | O(n) | O(n) | O(n) |
| Doubly linked, sorted | O(n) | O(n) | O(1) | O(1) | O(1) | O(1) | O(1) |

See `q1-dictionary-operations/ANALYSIS.md` for the reasoning behind each entry.

**Q2 — Merge sort into halves vs. thirds**

Both are `Θ(n log n)` in the worst case — dividing into thirds changes the
recursion tree's branching factor and the base of the logarithm, but not
the asymptotic order of growth. See
`q2-merge-sort-variants/ANALYSIS.md` for the Master Theorem derivation.

**Q3 — Merging k sorted arrays of size n**

| Method | Complexity |
|---|---|
| 1. Sequential pairwise merge | `Θ(n k²)` |
| 2. Pairwise "tournament" merge | `Θ(n k log k)` |

Method 2 is asymptotically much better for large `k` — same relationship
as merge sort (Θ(n log n)) vs. insertion sort (Θ(n²)). See
`q3-merging-k-sorted-arrays/ANALYSIS.md` for the full derivation.
