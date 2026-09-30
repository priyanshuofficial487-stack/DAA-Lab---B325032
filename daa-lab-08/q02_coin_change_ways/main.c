#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long u64;

u64 count_ways(const int *c, int n, int V)
{
    u64 *dp = calloc((size_t)(V + 1), sizeof(u64));
    dp[0] = 1;
    for (int i = 0; i < n; i++)
        for (int v = c[i]; v <= V; v++)
            dp[v] += dp[v - c[i]];
    u64 r = dp[V];
    free(dp);
    return r;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n, V;
    printf("Enter number of coins: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    int *c = malloc((size_t)n * sizeof(int));
    printf("Enter %d coin values: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &c[i]) != 1 || c[i] <= 0) {
            printf("Invalid input\n");
            return 1;
        }
    }
    printf("Enter target amount V: ");
    if (scanf("%d", &V) != 1 || V < 0) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Number of ways: %llu\n", count_ways(c, n, V));
    free(c);
    return 0;
}
