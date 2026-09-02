#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double **createMatrix(int n) {
    double **m = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) m[i] = malloc(n * sizeof(double));
    return m;
}

void freeMatrix(double **m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

void fillRandom(double **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = rand() % 100;
}

void fillSymmetric(double **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            double v = rand() % 100;
            m[i][j] = v;
            m[j][i] = v;
        }
}

double **matAdd(double **a, double **b, int n) {
    double **c = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
    return c;
}

double **matMultiply(double **a, double **b, int n) {
    double **c = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < n; k++)
                sum += a[i][k] * b[k][j];
            c[i][j] = sum;
        }
    return c;
}

int isZeroMatrix(double **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (m[i][j] != 0) return 0;
    return 1;
}

int isSymmetric(double **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (m[i][j] != m[j][i]) return 0;
    return 1;
}

double determinant(double **input, int n) {
    double **m = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = input[i][j];
    double det = 1;
    for (int i = 0; i < n; i++) {
        int pivotRow = i;
        for (int k = i + 1; k < n; k++)
            if (fabs(m[k][i]) > fabs(m[pivotRow][i])) pivotRow = k;
        if (fabs(m[pivotRow][i]) < 1e-12) { det = 0; break; }
        if (pivotRow != i) {
            double *t = m[i]; m[i] = m[pivotRow]; m[pivotRow] = t;
            det = -det;
        }
        det *= m[i][i];
        for (int k = i + 1; k < n; k++) {
            double factor = m[k][i] / m[i][i];
            for (int j = i; j < n; j++)
                m[k][j] -= factor * m[i][j];
        }
    }
    freeMatrix(m, n);
    return det;
}

void transposeInPlace(double **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            double t = m[i][j]; m[i][j] = m[j][i]; m[j][i] = t;
        }
}

double dominantEigen(double **m, int n, double *eigenVector) {
    double *v = malloc(n * sizeof(double));
    double *w = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) v[i] = 1.0;
    double eigenValue = 0;
    int iterations = 100;
    for (int it = 0; it < iterations; it++) {
        for (int i = 0; i < n; i++) {
            w[i] = 0;
            for (int j = 0; j < n; j++)
                w[i] += m[i][j] * v[j];
        }
        double norm = 0;
        for (int i = 0; i < n; i++) norm += w[i] * w[i];
        norm = sqrt(norm);
        if (norm < 1e-12) break;
        for (int i = 0; i < n; i++) v[i] = w[i] / norm;
        eigenValue = norm;
    }
    for (int i = 0; i < n; i++) eigenVector[i] = v[i];
    free(v); free(w);
    return eigenValue;
}

int main() {
    srand(42);
    FILE *fp = fopen("complexity.csv", "w");
    fprintf(fp, "n,add_time,multiply_time,zerocheck_time,symmetric_time,determinant_time,transpose_time,eigen_time\n");

    int sizes[] = {10, 25, 50, 75, 100, 150, 200, 300};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        double **a = createMatrix(n);
        double **b = createMatrix(n);
        double **sym = createMatrix(n);
        fillRandom(a, n);
        fillRandom(b, n);
        fillSymmetric(sym, n);

        clock_t t1, t2;

        t1 = clock();
        double **c = matAdd(a, b, n);
        t2 = clock();
        double tAdd = (double)(t2 - t1) / CLOCKS_PER_SEC;
        freeMatrix(c, n);

        t1 = clock();
        double **d = matMultiply(a, b, n);
        t2 = clock();
        double tMul = (double)(t2 - t1) / CLOCKS_PER_SEC;
        freeMatrix(d, n);

        t1 = clock();
        isZeroMatrix(a, n);
        t2 = clock();
        double tZero = (double)(t2 - t1) / CLOCKS_PER_SEC;

        t1 = clock();
        isSymmetric(sym, n);
        t2 = clock();
        double tSym = (double)(t2 - t1) / CLOCKS_PER_SEC;

        t1 = clock();
        determinant(a, n);
        t2 = clock();
        double tDet = (double)(t2 - t1) / CLOCKS_PER_SEC;

        t1 = clock();
        transposeInPlace(a, n);
        t2 = clock();
        double tTrans = (double)(t2 - t1) / CLOCKS_PER_SEC;

        double *eigVec = malloc(n * sizeof(double));
        t1 = clock();
        dominantEigen(sym, n, eigVec);
        t2 = clock();
        double tEigen = (double)(t2 - t1) / CLOCKS_PER_SEC;
        free(eigVec);

        fprintf(fp, "%d,%f,%f,%f,%f,%f,%f,%f\n",
                n, tAdd, tMul, tZero, tSym, tDet, tTrans, tEigen);

        freeMatrix(a, n);
        freeMatrix(b, n);
        freeMatrix(sym, n);
    }

    fclose(fp);
    printf("Done. Results written to complexity.csv\n");

    int n = 3;
    double **m1 = createMatrix(n);
    double **m2 = createMatrix(n);
    double vals1[3][3] = {{1,2,3},{4,5,6},{7,8,10}};
    double vals2[3][3] = {{9,8,7},{6,5,4},{3,2,1}};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            m1[i][j] = vals1[i][j];
            m2[i][j] = vals2[i][j];
        }

    printf("\nMatrix A:\n");
    for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) printf("%.0f ", m1[i][j]); printf("\n"); }

    double **sum = matAdd(m1, m2, n);
    printf("\nA + B:\n");
    for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) printf("%.0f ", sum[i][j]); printf("\n"); }
    freeMatrix(sum, n);

    double **prod = matMultiply(m1, m2, n);
    printf("\nA * B:\n");
    for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) printf("%.0f ", prod[i][j]); printf("\n"); }
    freeMatrix(prod, n);

    printf("\nIs A zero matrix? %s\n", isZeroMatrix(m1, n) ? "Yes" : "No");
    printf("Is A symmetric? %s\n", isSymmetric(m1, n) ? "Yes" : "No");
    printf("Determinant of A: %.2f\n", determinant(m1, n));

    transposeInPlace(m1, n);
    printf("\nTranspose of A:\n");
    for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) printf("%.0f ", m1[i][j]); printf("\n"); }

    double sym3[3][3] = {{4,1,2},{1,3,0},{2,0,5}};
    double **s = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            s[i][j] = sym3[i][j];
    double *eigVec = malloc(n * sizeof(double));
    double eigVal = dominantEigen(s, n, eigVec);
    printf("\nDominant eigenvalue of symmetric matrix: %.4f\n", eigVal);
    printf("Corresponding eigenvector: ");
    for (int i = 0; i < n; i++) printf("%.4f ", eigVec[i]);
    printf("\n");
    free(eigVec);

    freeMatrix(m1, n);
    freeMatrix(m2, n);
    freeMatrix(s, n);

    return 0;
}
