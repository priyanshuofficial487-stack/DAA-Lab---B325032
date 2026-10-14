#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

static int find(int *p, int x)
{
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

void max_after_deletions(int V, const ll *w, int E, const int *eu, const int *ev, const int *P, ll *ans)
{
    int *start = calloc((size_t)V + 1, sizeof(int));
    for (int i = 0; i < E; i++) {
        start[eu[i] + 1]++;
        start[ev[i] + 1]++;
    }
    for (int i = 0; i < V; i++)
        start[i + 1] += start[i];
    int *fill = malloc((size_t)V * sizeof(int));
    for (int i = 0; i < V; i++)
        fill[i] = start[i];
    int *adj = malloc((size_t)(2 * E + 1) * sizeof(int));
    for (int i = 0; i < E; i++) {
        adj[fill[eu[i]]++] = ev[i];
        adj[fill[ev[i]]++] = eu[i];
    }
    int *p = malloc((size_t)V * sizeof(int));
    int *sz = malloc((size_t)V * sizeof(int));
    ll *sum = malloc((size_t)V * sizeof(ll));
    char *active = calloc((size_t)V, 1);
    ll best = 0;
    ans[V] = 0;
    for (int j = V - 1; j >= 0; j--) {
        int v = P[j];
        active[v] = 1;
        p[v] = v;
        sz[v] = 1;
        sum[v] = w[v];
        for (int k = start[v]; k < start[v + 1]; k++) {
            int u = adj[k];
            if (!active[u])
                continue;
            int a = find(p, v), b = find(p, u);
            if (a == b)
                continue;
            if (sz[a] < sz[b]) {
                int t = a;
                a = b;
                b = t;
            }
            p[b] = a;
            sz[a] += sz[b];
            sum[a] += sum[b];
        }
        ll cur = sum[find(p, v)];
        if (cur > best)
            best = cur;
        ans[j] = best;
    }
    free(start);
    free(fill);
    free(adj);
    free(p);
    free(sz);
    free(sum);
    free(active);
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int V, E;
    printf("Enter number of vertices V (vertices are 0 to V-1): ");
    if (scanf("%d", &V) != 1 || V <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    ll *w = malloc((size_t)V * sizeof(ll));
    printf("Enter %d non-negative vertex values: ", V);
    for (int i = 0; i < V; i++) {
        if (scanf("%lld", &w[i]) != 1 || w[i] < 0) {
            printf("Invalid input\n");
            return 1;
        }
    }
    printf("Enter number of edges E: ");
    if (scanf("%d", &E) != 1 || E < 0) {
        printf("Invalid input\n");
        return 1;
    }
    int *eu = malloc((size_t)(E + 1) * sizeof(int));
    int *ev = malloc((size_t)(E + 1) * sizeof(int));
    for (int i = 0; i < E; i++) {
        printf("Enter edge %d (u v): ", i + 1);
        if (scanf("%d %d", &eu[i], &ev[i]) != 2 || eu[i] < 0 || eu[i] >= V || ev[i] < 0 || ev[i] >= V) {
            printf("Invalid input\n");
            return 1;
        }
    }
    int *P = malloc((size_t)V * sizeof(int));
    char *seen = calloc((size_t)V, 1);
    printf("Enter the deletion order (%d distinct vertices): ", V);
    for (int i = 0; i < V; i++) {
        if (scanf("%d", &P[i]) != 1 || P[i] < 0 || P[i] >= V || seen[P[i]]) {
            printf("Invalid input\n");
            return 1;
        }
        seen[P[i]] = 1;
    }
    ll *ans = malloc((size_t)(V + 1) * sizeof(ll));
    max_after_deletions(V, w, E, eu, ev, P, ans);
    printf("Before any deletion: %lld\n", ans[0]);
    for (int i = 0; i < V; i++)
        printf("After deleting vertex %d: %lld\n", P[i], ans[i + 1]);
    free(w);
    free(eu);
    free(ev);
    free(P);
    free(seen);
    free(ans);
    return 0;
}
