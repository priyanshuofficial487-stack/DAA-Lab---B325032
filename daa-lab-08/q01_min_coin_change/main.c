#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int min_coins(const int *c, int n, int V)
{
    int *dp = malloc((size_t)(V + 1) * sizeof(int));
    dp[0] = 0;
    for (int v = 1; v <= V; v++) {
        dp[v] = INF;
        for (int i = 0; i < n; i++) {
            if (c[i] <= v && dp[v - c[i]] != INF && dp[v - c[i]] + 1 < dp[v])
                dp[v] = dp[v - c[i]] + 1;
        }
    }
    int r = dp[V] == INF ? -1 : dp[V];
    free(dp);
    return r;
}

int main(void)
{
    int n, V;
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;
    int *c = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++)
        if (scanf("%d", &c[i]) != 1 || c[i] <= 0)
            return 1;
    if (scanf("%d", &V) != 1 || V < 0)
        return 1;
    printf("%d\n", min_coins(c, n, V));
    free(c);
    return 0;
}
