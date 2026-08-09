#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

static void merge2(int *arr, int lo, int mid, int hi, int *buf) {
    int i = lo, j = mid, k = lo;
    while (i < mid && j < hi) buf[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i < mid) buf[k++] = arr[i++];
    while (j < hi)  buf[k++] = arr[j++];
    memcpy(arr + lo, buf + lo, (hi - lo) * sizeof(int));
}
static void merge_sort2(int *arr, int lo, int hi, int *buf) {
    if (hi - lo <= 1) return;
    int mid = lo + (hi - lo) / 2;
    merge_sort2(arr, lo, mid, buf);
    merge_sort2(arr, mid, hi, buf);
    merge2(arr, lo, mid, hi, buf);
}

static void merge3(int *arr, int lo, int m1, int m2, int hi, int *buf) {
    int i = lo, j = m1, k = m2, w = lo;
    while (i < m1 && j < m2 && k < hi) {
        int a = arr[i], b = arr[j], c = arr[k];
        if (a <= b && a <= c) buf[w++] = arr[i++];
        else if (b <= a && b <= c) buf[w++] = arr[j++];
        else buf[w++] = arr[k++];
    }
    while (i < m1 && j < m2) buf[w++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (j < m2 && k < hi) buf[w++] = (arr[j] <= arr[k]) ? arr[j++] : arr[k++];
    while (i < m1 && k < hi) buf[w++] = (arr[i] <= arr[k]) ? arr[i++] : arr[k++];
    while (i < m1) buf[w++] = arr[i++];
    while (j < m2) buf[w++] = arr[j++];
    while (k < hi) buf[w++] = arr[k++];
    memcpy(arr + lo, buf + lo, (hi - lo) * sizeof(int));
}
static void merge_sort3(int *arr, int lo, int hi, int *buf) {
    int len = hi - lo;
    if (len <= 1) return;
    if (len == 2) {
        int mid = lo + 1;
        merge_sort3(arr, lo, mid, buf);
        merge_sort3(arr, mid, hi, buf);
        merge2(arr, lo, mid, hi, buf);
        return;
    }
    int third = len / 3;
    int m1 = lo + third;
    int m2 = lo + 2 * third;
    merge_sort3(arr, lo, m1, buf);
    merge_sort3(arr, m1, m2, buf);
    merge_sort3(arr, m2, hi, buf);
    merge3(arr, lo, m1, m2, hi, buf);
}

static int *random_array(int n, unsigned seed) {
    int *a = malloc(sizeof(int) * n);
    srand(seed);
    for (int i = 0; i < n; i++) a[i] = rand();
    return a;
}
static int is_sorted(int *a, int n) {
    for (int i = 1; i < n; i++) if (a[i - 1] > a[i]) return 0;
    return 1;
}

int main(void) {
    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int REPEATS = 5;

    FILE *f = fopen("results_q2.csv", "w");
    fprintf(f, "algorithm,n,time_ms\n");

    for (int si = 0; si < num_sizes; si++) {
        int n = sizes[si];
        int *buf = malloc(sizeof(int) * n);

        double total2 = 0.0, total3 = 0.0;
        for (int r = 0; r < REPEATS; r++) {
            int *base = random_array(n, 1000 + si * 17 + r);

            int *a2 = malloc(sizeof(int) * n);
            memcpy(a2, base, sizeof(int) * n);
            double t0 = now_seconds();
            merge_sort2(a2, 0, n, buf);
            double t1 = now_seconds();
            if (!is_sorted(a2, n)) { fprintf(stderr, "BUG: merge_sort2 failed at n=%d\n", n); exit(1); }
            total2 += (t1 - t0);
            free(a2);

            int *a3 = malloc(sizeof(int) * n);
            memcpy(a3, base, sizeof(int) * n);
            t0 = now_seconds();
            merge_sort3(a3, 0, n, buf);
            t1 = now_seconds();
            if (!is_sorted(a3, n)) { fprintf(stderr, "BUG: merge_sort3 failed at n=%d\n", n); exit(1); }
            total3 += (t1 - t0);
            free(a3);

            free(base);
        }
        fprintf(f, "merge_sort_2way,%d,%f\n", n, total2 / REPEATS * 1000.0);
        fprintf(f, "merge_sort_3way,%d,%f\n", n, total3 / REPEATS * 1000.0);
        printf("n=%8d  2-way: %8.3f ms   3-way: %8.3f ms\n", n,
               total2 / REPEATS * 1000.0, total3 / REPEATS * 1000.0);
        free(buf);
    }

    fclose(f);
    printf("Done. Results written to results_q2.csv\n");
    return 0;
}
