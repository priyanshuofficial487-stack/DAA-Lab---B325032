# Q1: Shortest Path on Parity-Constrained Graphs (0-1 BFS)

Since every weight is 0 or 1, W(P) = k1(P), so Cost(P) = k1 if k1 is even and k1 + C if k1 is odd.
The cost depends only on the number of weight-1 edges and its parity.

## Algorithm
1. Split every vertex v into two states: (v, even) and (v, odd), the parity of weight-1 edges used so far.
2. A weight-0 edge keeps the parity at cost 0. A weight-1 edge flips the parity at cost 1.
3. Run 0-1 BFS from (S, even) with a deque: weight-0 relaxations go to the front, weight-1 relaxations go to the back.
4. For each v: answer = min(dist[v][even], dist[v][odd] + C). If both are infinite, v is unreachable.

## Input representation
Adjacency list stored in arrays (head, next, to, wt). The product graph is implicit, so no extra edges are stored.

## Complexity
- The product graph has 2V states and 2E edges.
- Each state is finalised once and each product edge is relaxed once, and a deque push/pop costs O(1).
- Time O(V + E), space O(V + E).

## Validation
Compared with Bellman-Ford on the same state graph for 1000 random graphs: 1000 / 1000 passed.

## Run
```
gcc -O2 -o prog code.c && ./prog
```
Files: code.c, results.csv (running time vs size), graph.png.
