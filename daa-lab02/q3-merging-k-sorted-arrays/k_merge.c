#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

typedef struct { int *data; int len; } Arr;

static Arr merge2(Arr a, Arr b) {
    Arr r; r.len = a.len + b.len; r.data = malloc(sizeof(int) * r.len);
    int i = 0, j = 0, w = 0;
    while (i < a.len && j < b.len) r.data[w++] = (a.data[i] <= b.data[j]) ? a.data[i++] : b.data[j++];
    while (i < a.len) r.data[w++] = a.data[i++];
    while (j < b.len) r.data[w++] = b.data[j++];
    return r;
}

static Arr arr_copy(Arr a) {
    Arr r; r.len = a.len; r.data = malloc(sizeof(int) * a.len);
    memcpy(r.data, a.data, sizeof(int) * a.len);
    return r;
}

static Arr method1_sequential(Arr *arrays, int k) {
    Arr acc = arr_copy(arrays[0]);
    for (int i = 1; i < k; i++) {
        Arr merged = merge2(acc, arrays[i]);
        free(acc.data);
        acc = merged;
    }
    return acc;
}

static Arr method2_pairwise(Arr *arrays, int k) {
    Arr *cur = malloc(sizeof(Arr) * k);
    for (int i = 0; i < k; i++) cur[i] = arr_copy(arrays[i]);
    int cnt = k;
    while (cnt > 1) {
        int pairs = cnt / 2;
        int newcnt = pairs + (cnt % 2);
        Arr *next = malloc(sizeof(Arr) * newcnt);
        for (int i = 0; i < pairs; i++) {
            next[i] = merge2(cur[2 * i], cur[2 * i + 1]);
            free(cur[2 * i].data);
            free(cur[2 * i + 1].data);
        }
        if (cnt % 2) next[newcnt - 1] = cur[cnt - 1];
        free(cur);
        cur = next;
        cnt = newcnt;
    }
    Arr result = cur[0];
    free(cur);
    return result;
}

static Arr *make_k_sorted_arrays(int k, int n, unsigned seed) {
    srand(seed);
    Arr *arrays = malloc(sizeof(Arr) * k);
    for (int i = 0; i < k; i++) {
        arrays[i].len = n;
        arrays[i].data = malloc(sizeof(int) * n);
        int v = 0;
        for (int j = 0; j < n; j++) { v += rand() % 10 + 1; arrays[i].data[j] = v; }
    }
    return arrays;
}
static void free_arrays(Arr *arrays, int k) { for (int i = 0; i < k; i++) free(arrays[i].data); free(arrays); }
static int is_sorted(Arr a) { for (int i = 1; i < a.len; i++) if (a.data[i - 1] > a.data[i]) return 0; return 1; }

int main(void) {
    {
        int n = 500;
        int ks[] = {2, 4, 8, 16, 32, 64, 128, 256};
        int num_ks = sizeof(ks) / sizeof(ks[0]);
        int REPEATS = 5;

        FILE *f = fopen("results_q3_vary_k.csv", "w");
        fprintf(f, "method,n,k,time_ms\n");

        for (int ki = 0; ki < num_ks; ki++) {
            int k = ks[ki];
            double total1 = 0.0, total2 = 0.0;
            for (int r = 0; r < REPEATS; r++) {
                Arr *arrays = make_k_sorted_arrays(k, n, 42 + r * 7 + ki);

                double t0 = now_seconds();
                Arr res1 = method1_sequential(arrays, k);
                double t1 = now_seconds();
                if (!is_sorted(res1)) { fprintf(stderr, "BUG method1\n"); exit(1); }
                total1 += (t1 - t0);
                free(res1.data);

                t0 = now_seconds();
                Arr res2 = method2_pairwise(arrays, k);
                t1 = now_seconds();
                if (!is_sorted(res2)) { fprintf(stderr, "BUG method2\n"); exit(1); }
                total2 += (t1 - t0);
                free(res2.data);

                free_arrays(arrays, k);
            }
            fprintf(f, "sequential,%d,%d,%f\n", n, k, total1 / REPEATS * 1000.0);
            fprintf(f, "pairwise,%d,%d,%f\n", n, k, total2 / REPEATS * 1000.0);
            printf("[vary k] n=%d k=%4d  sequential: %8.4f ms   pairwise: %8.4f ms\n",
                   n, k, total1 / REPEATS * 1000.0, total2 / REPEATS * 1000.0);
        }
        fclose(f);
    }

    {
        int k = 16;
        int ns[] = {200, 400, 800, 1600, 3200, 6400, 12800, 25600};
        int num_ns = sizeof(ns) / sizeof(ns[0]);
        int REPEATS = 5;

        FILE *f = fopen("results_q3_vary_n.csv", "w");
        fprintf(f, "method,n,k,time_ms\n");

        for (int ni = 0; ni < num_ns; ni++) {
            int n = ns[ni];
            double total1 = 0.0, total2 = 0.0;
            for (int r = 0; r < REPEATS; r++) {
                Arr *arrays = make_k_sorted_arrays(k, n, 100 + r * 7 + ni);

                double t0 = now_seconds();
                Arr res1 = method1_sequential(arrays, k);
                double t1 = now_seconds();
                total1 += (t1 - t0);
                free(res1.data);

                t0 = now_seconds();
                Arr res2 = method2_pairwise(arrays, k);
                t1 = now_seconds();
                total2 += (t1 - t0);
                free(res2.data);

                free_arrays(arrays, k);
            }
            fprintf(f, "sequential,%d,%d,%f\n", n, k, total1 / REPEATS * 1000.0);
            fprintf(f, "pairwise,%d,%d,%f\n", n, k, total2 / REPEATS * 1000.0);
            printf("[vary n] k=%d n=%6d  sequential: %8.4f ms   pairwise: %8.4f ms\n",
                   k, n, total1 / REPEATS * 1000.0, total2 / REPEATS * 1000.0);
        }
        fclose(f);
    }

    printf("Done. Results written to results_q3_vary_k.csv and results_q3_vary_n.csv\n");
    return 0;
}
