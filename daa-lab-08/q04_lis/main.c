#include <stdio.h>
#include <stdlib.h>

int lis_quadratic(const int *a, int n, int *seq)
{
    int *dp = malloc((size_t)n * sizeof(int));
    int *prev = malloc((size_t)n * sizeof(int));
    int best = 0, end = -1;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > best) {
            best = dp[i];
            end = i;
        }
    }
    if (seq) {
        int k = best;
        for (int i = end; i != -1; i = prev[i])
            seq[--k] = a[i];
    }
    free(dp);
    free(prev);
    return best;
}

int lis_fast(const int *a, int n)
{
    int *tail = malloc((size_t)n * sizeof(int));
    int len = 0;
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = len;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (tail[mid] < a[i])
                lo = mid + 1;
            else
                hi = mid;
        }
        tail[lo] = a[i];
        if (lo == len)
            len++;
    }
    free(tail);
    return len;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;
    int *a = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1)
            return 1;
    int *seq = malloc((size_t)n * sizeof(int));
    int len = lis_quadratic(a, n, seq);
    printf("Length (O(n^2) DP): %d\n", len);
    printf("Length (O(n log n)): %d\n", lis_fast(a, n));
    printf("One LIS:");
    for (int i = 0; i < len; i++)
        printf(" %d", seq[i]);
    printf("\n");
    free(a);
    free(seq);
    return 0;
}
