# Q3: Bidirectional BFS for the Shortest Transformation Sequence

## Algorithm
1. Store the N words in an array and index them with a hash table (open addressing), so a word lookup is O(L).
2. If B is not in D, return -1. If A = B, return 0. If A is not in D, add it as an extra node (it can only be the start).
3. Run two BFS searches, one from A and one from B. Always expand the smaller frontier by one full level.
4. To expand a word, change each of its L positions to each of the 25 other letters and look the result up in the hash table.
5. When a generated word was already visited by the other side, the answer is dist_this + 1 + dist_other. If either frontier becomes empty, return -1.

## Input representation
Dictionary words in an array plus a hash table word -> index. The graph is implicit: neighbours are generated on the fly, so no adjacency lists (which could take O(N^2) space) are stored.

## Complexity
- Expanding one word costs about 25 * L lookups, each O(L), so O(26 * L^2) per word.
- Worst case time O(N * L^2 * 26), space O(N * L).
- Bidirectional search explores about 2 * b^(d/2) words instead of b^d, which is why it visits far fewer words in graph.png.

## Validation
Compared with a plain BFS using pairwise Hamming distance for 500 random dictionaries: 500 / 500 passed.
Benchmark queries on 10,000 to 100,000 words (L = 10) gave identical answers from both searches.

## Run
```
gcc -O2 -o prog code.c && ./prog
```
Files: code.c, results.csv (bidirectional vs unidirectional), graph.png.
