#include <stdio.h>
#include <stdlib.h>

static int find(int *p, int x)
{
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

void smallest_permutation(int n, int *a, int m, const int *eu, const int *ev)
{
    int *p = malloc((size_t)n * sizeof(int));
    int *sz = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        p[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        int x = find(p, eu[i]), y = find(p, ev[i]);
        if (x == y)
            continue;
        if (sz[x] < sz[y]) {
            int t = x;
            x = y;
            y = t;
        }
        p[y] = x;
        sz[x] += sz[y];
    }
    int *start = calloc((size_t)n + 1, sizeof(int));
    int *root = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        root[i] = find(p, i);
        start[root[i] + 1]++;
    }
    for (int i = 0; i < n; i++)
        start[i + 1] += start[i];
    int *fill = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++)
        fill[i] = start[i];
    int *pos = malloc((size_t)n * sizeof(int));
    int *val = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int k = fill[root[i]]++;
        pos[k] = i;
        val[k] = a[i];
    }
    for (int r = 0; r < n; r++)
        if (start[r + 1] - start[r] > 1)
            qsort(val + start[r], (size_t)(start[r + 1] - start[r]), sizeof(int), cmp_int);
    for (int k = 0; k < n; k++)
        a[pos[k]] = val[k];
    free(p);
    free(sz);
    free(start);
    free(root);
    free(fill);
    free(pos);
    free(val);
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int n, m;
    printf("Enter n (permutation of 1..n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    int *a = malloc((size_t)n * sizeof(int));
    char *seen = calloc((size_t)n + 1, 1);
    printf("Enter the permutation of %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1 || a[i] < 1 || a[i] > n || seen[a[i]]) {
            printf("Invalid input\n");
            return 1;
        }
        seen[a[i]] = 1;
    }
    printf("Enter number of allowed swaps m: ");
    if (scanf("%d", &m) != 1 || m < 0) {
        printf("Invalid input\n");
        return 1;
    }
    int *eu = malloc((size_t)(m + 1) * sizeof(int));
    int *ev = malloc((size_t)(m + 1) * sizeof(int));
    for (int i = 0; i < m; i++) {
        printf("Enter swap %d (positions u v, 1-indexed): ", i + 1);
        if (scanf("%d %d", &eu[i], &ev[i]) != 2 || eu[i] < 1 || eu[i] > n || ev[i] < 1 || ev[i] > n) {
            printf("Invalid input\n");
            return 1;
        }
        eu[i]--;
        ev[i]--;
    }
    smallest_permutation(n, a, m, eu, ev);
    printf("Lexicographically smallest permutation:");
    for (int i = 0; i < n; i++)
        printf(" %d", a[i]);
    printf("\n");
    free(a);
    free(seen);
    free(eu);
    free(ev);
    return 0;
}
