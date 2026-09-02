# DAA Lab-06 — Design and Analysis of Algorithms

BTech (CS-B and CE), 3rd Semester
Instructor: Dr. Ajaya Kumar Dash

This repository contains the solutions for all 4 questions of DAA Lab-06.
Each question has its own folder with the C source code, a `complexity.csv`
of measured timings, a `graph.png` visualizing the results, and a `README.md`
with the complexity analysis / proofs.

## Structure

```
DAA_Lab06/
├── Q1_Array_Operations/
│   ├── q1.c
│   ├── complexity.csv
│   ├── graph.png
│   └── README.md
├── Q2_Matrix_Operations/
│   ├── q2.c
│   ├── complexity.csv
│   ├── graph.png
│   └── README.md
├── Q3_Convolution/
│   ├── q3.c
│   ├── complexity.csv
│   ├── graph.png
│   └── README.md
├── Q4_Sorting_By_Reversal/
│   ├── q4.c
│   ├── complexity.csv
│   ├── graph.png
│   └── README.md
└── README.md
```

## Questions

1. **1D array operations and their complexities** — max, first/second
   largest, mean, median, standard deviation, mode, remove duplicates,
   reverse, and partition around a random pivot.
2. **2D square matrix operations and their complexities** — addition,
   multiplication, zero-matrix check, symmetric check, determinant,
   in-place transpose, and eigenvalue/eigenvector (power iteration).
3. **Convolution via divide and conquer** — O(n log n) convolution using
   the Fast Fourier Transform, compared against the naive O(n^2) approach.
4. **Sorting via reversal** — proof that O(n) reversals suffice to sort any
   permutation, plus a rotation-based merge sort that sorts in O(n log^2 n)
   total reversal cost.

## Building and running

Each `qX.c` is a standalone C file with no external dependencies besides
the standard library and `libm`:

```
gcc -O2 -o q1 q1.c -lm && ./q1
gcc -O2 -o q2 q2.c -lm && ./q2
gcc -O2 -o q3 q3.c -lm && ./q3
gcc -O2 -o q4 q4.c && ./q4
```

Running each program regenerates its `complexity.csv`. The `graph.png`
files were generated separately from the CSVs using `matplotlib`.
