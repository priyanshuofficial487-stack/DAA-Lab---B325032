#include <stdio.h>
#include <stdlib.h>

int **allocMatrix(int n) {
    int **m = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        m[i] = (int *)calloc(n, sizeof(int));
    return m;
}

void freeMatrix(int **m, int n) {
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void addMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassenMultiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;

    int **A11 = allocMatrix(newSize), **A12 = allocMatrix(newSize);
    int **A21 = allocMatrix(newSize), **A22 = allocMatrix(newSize);
    int **B11 = allocMatrix(newSize), **B12 = allocMatrix(newSize);
    int **B21 = allocMatrix(newSize), **B22 = allocMatrix(newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    int **T1 = allocMatrix(newSize), **T2 = allocMatrix(newSize);
    int **M1 = allocMatrix(newSize), **M2 = allocMatrix(newSize);
    int **M3 = allocMatrix(newSize), **M4 = allocMatrix(newSize);
    int **M5 = allocMatrix(newSize), **M6 = allocMatrix(newSize);
    int **M7 = allocMatrix(newSize);

    addMatrix(A11, A22, T1, newSize);
    addMatrix(B11, B22, T2, newSize);
    strassenMultiply(T1, T2, M1, newSize);

    addMatrix(A21, A22, T1, newSize);
    strassenMultiply(T1, B11, M2, newSize);

    subMatrix(B12, B22, T1, newSize);
    strassenMultiply(A11, T1, M3, newSize);

    subMatrix(B21, B11, T1, newSize);
    strassenMultiply(A22, T1, M4, newSize);

    addMatrix(A11, A12, T1, newSize);
    strassenMultiply(T1, B22, M5, newSize);

    subMatrix(A21, A11, T1, newSize);
    addMatrix(B11, B12, T2, newSize);
    strassenMultiply(T1, T2, M6, newSize);

    subMatrix(A12, A22, T1, newSize);
    addMatrix(B21, B22, T2, newSize);
    strassenMultiply(T1, T2, M7, newSize);

    int **C11 = allocMatrix(newSize), **C12 = allocMatrix(newSize);
    int **C21 = allocMatrix(newSize), **C22 = allocMatrix(newSize);

    addMatrix(M1, M4, T1, newSize);
    subMatrix(T1, M5, T2, newSize);
    addMatrix(T2, M7, C11, newSize);

    addMatrix(M3, M5, C12, newSize);

    addMatrix(M2, M4, C21, newSize);

    subMatrix(M1, M2, T1, newSize);
    addMatrix(T1, M3, T2, newSize);
    addMatrix(T2, M6, C22, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j]                     = C11[i][j];
            C[i][j + newSize]           = C12[i][j];
            C[i + newSize][j]           = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(T1, newSize);  freeMatrix(T2, newSize);
    freeMatrix(M1, newSize);  freeMatrix(M2, newSize);
    freeMatrix(M3, newSize);  freeMatrix(M4, newSize);
    freeMatrix(M5, newSize);  freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
}

int nextPowerOf2(int n) {
    int p = 1;
    while (p < n) p *= 2;
    return p;
}

int main() {
    int n;
    printf("Enter size n of the square matrices (n x n): ");
    scanf("%d", &n);

    int size = nextPowerOf2(n);

    int **A = allocMatrix(size);
    int **B = allocMatrix(size);
    int **C = allocMatrix(size);

    printf("Enter elements of Matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassenMultiply(A, B, C, size);

    printf("\nResultant Matrix C = A x B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    freeMatrix(A, size);
    freeMatrix(B, size);
    freeMatrix(C, size);

    return 0;
}
