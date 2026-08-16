#include <stdio.h>
#include <stdlib.h>

void xorConvolve(int a[], int b[], int c[], int n) {
    if (n == 1) {
        c[0] = a[0] * b[0];
        return;
    }

    int half = n / 2;

    int *a0 = a;
    int *a1 = a + half;

    int *b0 = b;
    int *b1 = b + half;

    int *p00 = (int *)malloc(half * sizeof(int));
    int *p11 = (int *)malloc(half * sizeof(int));
    int *p01 = (int *)malloc(half * sizeof(int));
    int *p10 = (int *)malloc(half * sizeof(int));

    xorConvolve(a0, b0, p00, half);
    xorConvolve(a1, b1, p11, half);
    xorConvolve(a0, b1, p01, half);
    xorConvolve(a1, b0, p10, half);

    int *cLow  = c;
    int *cHigh = c + half;

    for (int i = 0; i < half; i++) {
        cLow[i]  = p00[i] + p11[i];
        cHigh[i] = p01[i] + p10[i];
    }

    free(p00); free(p11); free(p01); free(p10);
}

int isPowerOf2(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

void naiveMultiplyFull(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main() {
    int n;
    printf("Enter n (matrix size, must be a power of 2, e.g. 2,4,8): ");
    scanf("%d", &n);

    if (!isPowerOf2(n)) {
        printf("Error: n must be a power of 2 for this special-pattern algorithm.\n");
        return 1;
    }

    int **A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(n * sizeof(int *));
    int **Cnaive = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
        Cnaive[i] = (int *)malloc(n * sizeof(int));
    }

    printf("Enter elements of matrix A (%d x %d).\n", n, n);
    printf("(It must follow the pattern: top-left block = bottom-right block,\n");
    printf(" top-right block = bottom-left block, recursively down to numbers.\n");
    printf(" We ask for the FULL matrix here so the pattern can be verified.)\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of matrix B (%d x %d), following the same pattern:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    int *genA = (int *)malloc(n * sizeof(int));
    int *genB = (int *)malloc(n * sizeof(int));
    int *genC = (int *)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
        genA[j] = A[0][j];
        genB[j] = B[0][j];
    }

    xorConvolve(genA, genB, genC, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = genC[i ^ j];

    printf("\nResult using Special-Pattern D&C algorithm (O(n^2)):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    naiveMultiplyFull(A, B, Cnaive, n);
    int same = 1;
    for (int i = 0; i < n && same; i++)
        for (int j = 0; j < n && same; j++)
            if (C[i][j] != Cnaive[i][j]) same = 0;

    printf("\nValidation against normal O(n^3) multiplication: %s\n",
           same ? "MATCH (correct!)" : "MISMATCH (bug!)");

    for (int i = 0; i < n; i++) {
        free(A[i]); free(B[i]); free(C[i]); free(Cnaive[i]);
    }
    free(A); free(B); free(C); free(Cnaive);
    free(genA); free(genB); free(genC);

    return 0;
}
