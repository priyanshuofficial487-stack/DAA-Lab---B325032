# Q2: Multi-Source BFS for Radius-Constrained Voronoi Partitioning

## Algorithm
1. Put all hubs in the queue at distance 0 in index order (h1, h2, ..., hK), with owner[h_i] = i.
2. Run one BFS. When a vertex is first discovered, it copies the owner of the vertex that discovered it.
3. Do not expand vertices whose distance equals R, so everything farther than R keeps owner = -1.

## Why the tie-break is correct
Vertices in the queue are always ordered by distance, and within one distance level by non-decreasing owner index.
This holds at level 0 because hubs are inserted in index order, and it carries to the next level because vertices are discovered in queue order.
So the first vertex to discover v has the smallest owner index among all neighbours of v at distance d - 1, which is the smallest hub index at distance dmin(v).

## Input representation
Undirected graph as an adjacency list in arrays (each edge stored in both directions), hubs as an array of vertex ids.

## Complexity
- Every vertex enters the queue at most once and every edge is scanned at most twice.
- Time O(V + E), independent of K. Space O(V + E).
- The naive approach (one BFS per hub) is O(K(V + E)), see graph.png.

## Validation
Compared with K separate BFS runs plus a minimum scan (smallest index on ties) for 1000 random graphs: 1000 / 1000 passed.

## Run
```
gcc -O2 -o prog code.c && ./prog
```
Files: code.c, results.csv (multi-source vs naive timing), graph.png.
