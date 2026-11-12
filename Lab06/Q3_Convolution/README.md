# Q3 - Convolution via Divide and Conquer (FFT), O(n log n)

## Problem

Convolution of vectors A (length m) and B (length n), n >= m:

```
C[k] = sum over j of A[j] * B[k-j]
```

Computed directly this takes O(m.n) = O(n^2) time. Using the Fast Fourier
Transform (a divide and conquer algorithm) it can be done in O(n log n).

## Idea

1. Zero-pad A and B to a length `size` that is a power of two and at least
   `m + n - 1` (the length of the result).
2. Compute the DFT of the padded A and padded B using FFT: `O(size log size)`.
3. Multiply the two transformed vectors point-wise: `O(size)`.
4. Apply the inverse FFT to get the convolution result: `O(size log size)`.

The FFT itself is a divide and conquer algorithm:

```
T(n) = 2T(n/2) + O(n)  =>  T(n) = O(n log n)
```

At each level the array is split into even-indexed and odd-indexed halves,
recursively transformed, and then combined in O(n) using the "butterfly"
combine step with the complex roots of unity.

## Files

- `q3.c` - source code (FFT, FFT-based convolution, naive convolution + timing driver)
- `complexity.csv` - measured running time of FFT vs naive convolution for
  increasing vector size `n`
- `graph.png` - time vs input size plot, FFT vs naive

## How it was run

```
gcc -O2 -o q3 q3.c -lm
./q3
```

The naive O(n^2) version is only timed up to n = 4096 since it becomes very
slow beyond that. The FFT version is timed up to n = 16384. The program also
prints a small demo (A = [1,2,3], B = [4,5,6]) comparing the FFT result with
the naive result to confirm correctness.

## Observation

The naive method's time grows quadratically while the FFT method's time
grows near-linearly (n log n), and the gap widens quickly as `n` increases,
matching the theoretical complexities.
