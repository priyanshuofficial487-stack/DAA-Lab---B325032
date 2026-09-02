# DAA Lab 5

Design and Analysis of Algorithms — Lab 5 solutions, written in C.

Each question has its own folder containing (in order):
1. **Code** (`.c` file)
2. **Data** (`.csv` file used to plot the complexity graph)
3. **Graph** (`.png` complexity graph)
4. **Explanation** (`README.md` — approach + complexity analysis)

## Folder structure

```
daa_lab_5/
├── Q1_median_without_sorting/
│   ├── median.c
│   ├── complexity_data.csv
│   ├── complexity_graph.png
│   └── README.md
├── Q2_kth_smallest_without_sorting/
│   ├── kth_smallest.c
│   ├── complexity_data.csv
│   ├── complexity_graph.png
│   └── README.md
├── Q3_quicksort_file/
│   ├── quicksort.c
│   ├── complexity_data.csv
│   ├── complexity_graph.png
│   └── README.md
└── Q4_heapsort_file/
    ├── heapsort.c
    ├── complexity_data.csv
    ├── complexity_graph.png
    └── README.md
```

## Problems

| # | Folder | Problem |
|---|--------|---------|
| 1 | `Q1_median_without_sorting` | Find the median of N numbers without sorting the list |
| 2 | `Q2_kth_smallest_without_sorting` | Find the K'th smallest element of N numbers without sorting the list |
| 3 | `Q3_quicksort_file` | Quick Sort of N random elements stored in a file |
| 4 | `Q4_heapsort_file` | Heap Sort of N randomly generated elements stored in a file |

## Complexity Summary

| Q | Algorithm | Best | Average | Worst | Space |
|---|-----------|------|---------|-------|-------|
| 1 | Median via Quickselect | O(N) | O(N) | O(N²) | O(1) extra |
| 2 | Kth Smallest via Quickselect | O(N) | O(N) | O(N²) | O(1) extra |
| 3 | QuickSort | O(N log N) | O(N log N) | O(N²) | O(log N) stack |
| 4 | HeapSort | O(N log N) | O(N log N) | O(N log N) | O(1) extra |

See each folder's `README.md` for the full approach explanation and
complexity graph specific to that question.

## How to compile and run

```bash
gcc -o median Q1_median_without_sorting/median.c
./median

gcc -o kth Q2_kth_smallest_without_sorting/kth_smallest.c
./kth

gcc -o qsort Q3_quicksort_file/quicksort.c
./qsort

gcc -o hsort Q4_heapsort_file/heapsort.c
./hsort
```

Programs 3 and 4 create `input.txt` (random unsorted numbers) and
`output.txt` (sorted numbers) in the folder they're run from.
