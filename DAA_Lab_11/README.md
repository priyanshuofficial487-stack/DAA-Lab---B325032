# DAA Lab 11 - Applications of BFS

IIIT Bhubaneswar, BTech (CS-B and CE), 3rd Semester. Instructor: Dr. Ajaya Kumar Dash.

| Folder | Problem | Technique | Time |
|--------|---------|-----------|------|
| Q1 | Parity-constrained shortest path | 0-1 BFS on a 2V-state graph | O(V + E) |
| Q2 | Radius-constrained Voronoi cells | Multi-source BFS | O(V + E) |
| Q3 | Word transformation sequence | Bidirectional BFS + hash table | O(N * L^2 * 26) |

Each folder has code.c, results.csv, graph.png and README.md.

## Run everything
```
make
```
This compiles and runs the three programs (they write results.csv) and then draws the graphs with generate_graphs.py (needs python3, pandas, matplotlib).
Run each program from inside its own folder, since results.csv is written to the current directory.
