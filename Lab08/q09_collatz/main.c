#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long u64;

static int collatz_step(u64 n, u64 *out)
{
    if (n % 2 == 0) {
        *out = n / 2;
        return 1;
    }
    if (n > (ULLONG_MAX - 1) / 3)
        return 0;
    *out = 3 * n + 1;
    return 1;
}

static void single(u64 start)
{
    size_t cap = 64, len = 0;
    u64 *t = malloc(cap * sizeof(u64));
    u64 n = start, peak = start;
    int ok = 1;
    t[len++] = n;
    while (n != 1) {
        u64 nx;
        if (!collatz_step(n, &nx)) {
            ok = 0;
            break;
        }
        n = nx;
        if (len == cap) {
            cap *= 2;
            t = realloc(t, cap * sizeof(u64));
        }
        t[len++] = n;
        if (n > peak)
            peak = n;
    }
    printf("Trajectory:");
    for (size_t i = 0; i < len; i++)
        printf(" %llu", t[i]);
    printf("\n");
    if (ok) {
        printf("Start: %llu\n", start);
        printf("Steps to reach 1: %zu\n", len - 1);
        printf("Peak value: %llu\n", peak);
    } else {
        printf("Stopped: next value would overflow 64-bit unsigned integer\n");
    }
    free(t);
}

static void interval(u64 a, u64 b)
{
    u64 *peak = calloc(b + 1, sizeof(u64));
    unsigned *steps = calloc(b + 1, sizeof(unsigned));
    size_t cap = 1024, len;
    u64 *path = malloc(cap * sizeof(u64));
    peak[1] = 1;
    steps[1] = 0;
    u64 best_start = a, best_steps = 0, peak_start = a, peak_val = 0;
    u64 overflowed = 0;
    double sum = 0;
    for (u64 s = a; s <= b; s++) {
        len = 0;
        u64 n = s;
        int ok = 1;
        while (!(n <= b && peak[n] != 0)) {
            if (len == cap) {
                cap *= 2;
                path = realloc(path, cap * sizeof(u64));
            }
            path[len++] = n;
            u64 nx;
            if (!collatz_step(n, &nx)) {
                ok = 0;
                break;
            }
            n = nx;
        }
        if (!ok) {
            overflowed++;
            continue;
        }
        u64 cur_steps = steps[n], cur_peak = peak[n];
        for (size_t i = len; i-- > 0;) {
            cur_steps++;
            if (path[i] > cur_peak)
                cur_peak = path[i];
            if (path[i] <= b) {
                steps[path[i]] = (unsigned)cur_steps;
                peak[path[i]] = cur_peak;
            }
        }
        u64 ss = steps[s], pp = peak[s];
        sum += (double)ss;
        if (ss > best_steps) {
            best_steps = ss;
            best_start = s;
        }
        if (pp > peak_val) {
            peak_val = pp;
            peak_start = s;
        }
    }
    printf("Interval: [%llu, %llu]\n", a, b);
    printf("Longest trajectory: start %llu with %llu steps\n", best_start, best_steps);
    printf("Highest peak: start %llu reaches %llu\n", peak_start, peak_val);
    printf("Average steps: %.4f\n", sum / (double)(b - a + 1 - overflowed));
    printf("Starts skipped due to overflow: %llu\n", overflowed);
    free(peak);
    free(steps);
    free(path);
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int mode;
    printf("Enter mode (1 = single number, 2 = interval): ");
    if (scanf("%d", &mode) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (mode == 1) {
        u64 n;
        printf("Enter starting value n (>= 1): ");
        if (scanf("%llu", &n) != 1 || n < 1) {
            printf("Invalid input\n");
            return 1;
        }
        single(n);
    } else if (mode == 2) {
        u64 a, b;
        printf("Enter interval a and b (1 <= a <= b): ");
        if (scanf("%llu %llu", &a, &b) != 2 || a < 1 || b < a) {
            printf("Invalid input\n");
            return 1;
        }
        interval(a, b);
    } else {
        printf("Invalid mode\n");
        return 1;
    }
    return 0;
}
