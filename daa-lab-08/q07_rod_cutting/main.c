#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll rod_cut(const int *p, int n, int *pieces, int *count)
{
    ll *r = malloc((size_t)(n + 1) * sizeof(ll));
    int *cut = malloc((size_t)(n + 1) * sizeof(int));
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        r[j] = -1;
        for (int i = 1; i <= j; i++) {
            if (p[i] + r[j - i] > r[j]) {
                r[j] = p[i] + r[j - i];
                cut[j] = i;
            }
        }
    }
    ll best = r[n];
    if (pieces) {
        int k = 0;
        for (int j = n; j > 0; j -= cut[j])
            pieces[k++] = cut[j];
        *count = k;
    }
    free(r);
    free(cut);
    return best;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;
    int *p = malloc((size_t)(n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++)
        if (scanf("%d", &p[i]) != 1)
            return 1;
    int *pieces = malloc((size_t)n * sizeof(int));
    int count = 0;
    ll best = rod_cut(p, n, pieces, &count);
    printf("Maximum revenue: %lld\n", best);
    printf("Pieces:");
    for (int i = 0; i < count; i++)
        printf(" %d", pieces[i]);
    printf("\n");
    free(p);
    free(pieces);
    return 0;
}
