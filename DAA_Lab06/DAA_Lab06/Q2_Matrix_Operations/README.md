# Q2 - 2D Square Matrix Operations and Their Complexities

Given two n x n square matrices, this program implements and analyses the
worst-case complexity of common matrix operations.

## Complexity Table

| Operation | Worst-case Complexity | Notes |
|---|---|---|
| Matrix Addition | O(n^2) | add each of the n^2 entries once |
| Matrix Multiplication | O(n^3) | standard triple-loop multiplication |
| Zero matrix check | O(n^2) | scan every entry |
| Symmetric matrix check | O(n^2) | compare A[i][j] with A[j][i] |
| Determinant | O(n^3) | Gaussian elimination with partial pivoting |
| In-place transpose | O(n^2) | swap upper and lower triangle entries |
| Eigenvalue and eigenvector | O(k.n^2) | power iteration, k = fixed iteration count |

Determinant via cofactor expansion is O(n!), so Gaussian elimination
(O(n^3)) is used instead, which is the standard practical approach.

Finding *all* eigenvalues/eigenvectors of a general matrix needs iterative
numerical methods (QR algorithm etc.) with no exact closed-form worst case.
Here, the **power iteration** method is used on a symmetric matrix to find
the dominant eigenvalue and its eigenvector; each iteration costs O(n^2)
(one matrix-vector multiply), so k iterations cost O(k.n^2).

## Files

- `q2.c` - source code (all 7 operations + a timing driver)
- `complexity.csv` - measured running time of each operation for increasing `n`
- `graph.png` - time vs matrix size plot for all operations

## How it was run

```
gcc -O2 -o q2 q2.c -lm
./q2
```

The program times each operation for matrix sizes `n = 10` to `300`, then
prints a demo run on a fixed 3x3 matrix showing every operation's output.

## Observation

Multiplication and determinant (both O(n^3)) grow noticeably faster than
addition, zero-check, symmetric-check and transpose (all O(n^2)) as `n`
increases, matching the theoretical analysis.
