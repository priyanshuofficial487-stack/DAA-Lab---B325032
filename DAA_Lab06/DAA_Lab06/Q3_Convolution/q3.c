#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double re, im;
} Complex;

Complex cAdd(Complex a, Complex b) {
    Complex r; r.re = a.re + b.re; r.im = a.im + b.im; return r;
}

Complex cSub(Complex a, Complex b) {
    Complex r; r.re = a.re - b.re; r.im = a.im - b.im; return r;
}

Complex cMul(Complex a, Complex b) {
    Complex r;
    r.re = a.re * b.re - a.im * b.im;
    r.im = a.re * b.im + a.im * b.re;
    return r;
}

void fft(Complex *a, int n, int invert) {
    if (n == 1) return;

    Complex *even = malloc((n / 2) * sizeof(Complex));
    Complex *odd = malloc((n / 2) * sizeof(Complex));
    for (int i = 0; i < n / 2; i++) {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    double angle = 2 * M_PI / n * (invert ? -1 : 1);
    Complex w = {1, 0};
    Complex wn = {cos(angle), sin(angle)};

    for (int i = 0; i < n / 2; i++) {
        Complex t = cMul(w, odd[i]);
        a[i] = cAdd(even[i], t);
        a[i + n / 2] = cSub(even[i], t);
        if (invert) {
            a[i].re /= 2; a[i].im /= 2;
            a[i + n / 2].re /= 2; a[i + n / 2].im /= 2;
        }
        w = cMul(w, wn);
    }

    free(even);
    free(odd);
}

int nextPowerOfTwo(int x) {
    int p = 1;
    while (p < x) p *= 2;
    return p;
}

int *convolve(int *A, int m, int *B, int n, int *resultSize) {
    int outSize = m + n - 1;
    int size = nextPowerOfTwo(outSize);

    Complex *fa = malloc(size * sizeof(Complex));
    Complex *fb = malloc(size * sizeof(Complex));

    for (int i = 0; i < size; i++) {
        fa[i].re = (i < m) ? A[i] : 0;
        fa[i].im = 0;
        fb[i].re = (i < n) ? B[i] : 0;
        fb[i].im = 0;
    }

    fft(fa, size, 0);
    fft(fb, size, 0);

    for (int i = 0; i < size; i++)
        fa[i] = cMul(fa[i], fb[i]);

    fft(fa, size, 1);

    int *C = malloc(outSize * sizeof(int));
    for (int i = 0; i < outSize; i++)
        C[i] = (int)round(fa[i].re);

    free(fa);
    free(fb);
    *resultSize = outSize;
    return C;
}

int *convolveNaive(int *A, int m, int *B, int n, int *resultSize) {
    int outSize = m + n - 1;
    int *C = calloc(outSize, sizeof(int));
    for (int k = 0; k < outSize; k++) {
        long long sum = 0;
        for (int j = 0; j < m; j++) {
            int idx = k - j;
            if (idx >= 0 && idx < n) sum += (long long)A[j] * B[idx];
        }
        C[k] = (int)sum;
    }
    *resultSize = outSize;
    return C;
}

int main() {
    srand(1);
    FILE *fp = fopen("complexity.csv", "w");
    fprintf(fp, "n,fft_time,naive_time\n");

    int sizes[] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *A = malloc(n * sizeof(int));
        int *B = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            A[i] = rand() % 100;
            B[i] = rand() % 100;
        }

        int resSize;
        clock_t t1 = clock();
        int *cFFT = convolve(A, n, B, n, &resSize);
        clock_t t2 = clock();
        double tFFT = (double)(t2 - t1) / CLOCKS_PER_SEC;
        free(cFFT);

        double tNaive = -1;
        if (n <= 4096) {
            t1 = clock();
            int *cNaive = convolveNaive(A, n, B, n, &resSize);
            t2 = clock();
            tNaive = (double)(t2 - t1) / CLOCKS_PER_SEC;
            free(cNaive);
        }

        fprintf(fp, "%d,%f,%f\n", n, tFFT, tNaive);

        free(A);
        free(B);
    }

    fclose(fp);
    printf("Done. Results written to complexity.csv\n");

    int A[] = {1, 2, 3};
    int B[] = {4, 5, 6};
    int resSize;
    int *result = convolve(A, 3, B, 3, &resSize);
    printf("\nA = [1, 2, 3], B = [4, 5, 6]\n");
    printf("Convolution (FFT) result: ");
    for (int i = 0; i < resSize; i++) printf("%d ", result[i]);
    printf("\n");
    free(result);

    int *resultNaive = convolveNaive(A, 3, B, 3, &resSize);
    printf("Convolution (naive) result: ");
    for (int i = 0; i < resSize; i++) printf("%d ", resultNaive[i]);
    printf("\n");
    free(resultNaive);

    return 0;
}
