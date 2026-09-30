#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll msis(const int *a, int n, int *seq, int *len)
{
    ll *dp = malloc((size_t)n * sizeof(ll));
    int *prev = malloc((size_t)n * sizeof(int));
    ll best = 0;
    int end = -1;
    for (int i = 0; i < n; i++) {
        dp[i] = a[i];
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + a[i] > dp[i]) {
                dp[i] = dp[j] + a[i];
                prev[i] = j;
            }
        }
        if (dp[i] > best) {
            best = dp[i];
            end = i;
        }
    }
    if (seq) {
        int k = 0;
        for (int i = end; i != -1; i = prev[i])
            seq[k++] = a[i];
        for (int i = 0; i < k / 2; i++) {
            int t = seq[i];
            seq[i] = seq[k - 1 - i];
            seq[k - 1 - i] = t;
        }
        *len = k;
    }
    free(dp);
    free(prev);
    return best;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;
    int *a = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1 || a[i] <= 0)
            return 1;
    int *seq = malloc((size_t)n * sizeof(int));
    int len = 0;
    ll best = msis(a, n, seq, &len);
    printf("Maximum sum: %lld\n", best);
    printf("Subsequence:");
    for (int i = 0; i < len; i++)
        printf(" %d", seq[i]);
    printf("\n");
    free(a);
    free(seq);
    return 0;
}
