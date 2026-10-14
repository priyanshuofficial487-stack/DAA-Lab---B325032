#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll sum;
    int root, ver;
} Node;

static void sift_up(Node *h, int i)
{
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h[i].sum <= h[p].sum)
            break;
        Node t = h[i];
        h[i] = h[p];
        h[p] = t;
        i = p;
    }
}

static void sift_down(Node *h, int n, int i)
{
    for (;;) {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < n && h[l].sum > h[m].sum)
            m = l;
        if (r < n && h[r].sum > h[m].sum)
            m = r;
        if (m == i)
            break;
        Node t = h[i];
        h[i] = h[m];
        h[m] = t;
        i = m;
    }
}

static int find(int *p, int x)
{
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

void max_comp_weight(int V, int K, const ll *w, int E, const int *eu, const int *ev, ll *ans)
{
    int *p = malloc((size_t)V * sizeof(int));
    int *sz = malloc((size_t)V * sizeof(int));
    int *ver = calloc((size_t)V, sizeof(int));
    ll *sum = malloc((size_t)V * sizeof(ll));
    Node *h = malloc((size_t)(V + E) * sizeof(Node));
    int hs = 0;
    for (int i = 0; i < V; i++) {
        p[i] = i;
        sz[i] = 1;
        sum[i] = w[i];
        if (K >= 1) {
            h[hs].sum = w[i];
            h[hs].root = i;
            h[hs].ver = 0;
            sift_up(h, hs++);
        }
    }
    ans[0] = hs > 0 ? h[0].sum : 0;
    for (int e = 0; e < E; e++) {
        int a = find(p, eu[e]), b = find(p, ev[e]);
        if (a != b) {
            if (sz[a] < sz[b]) {
                int t = a;
                a = b;
                b = t;
            }
            p[b] = a;
            sz[a] += sz[b];
            sum[a] += sum[b];
            ver[a]++;
            if (sz[a] <= K) {
                h[hs].sum = sum[a];
                h[hs].root = a;
                h[hs].ver = ver[a];
                sift_up(h, hs++);
            }
        }
        while (hs > 0) {
            Node t = h[0];
            if (p[t.root] == t.root && ver[t.root] == t.ver && sz[t.root] <= K)
                break;
            h[0] = h[--hs];
            sift_down(h, hs, 0);
        }
        ans[e + 1] = hs > 0 ? h[0].sum : 0;
    }
    free(p);
    free(sz);
    free(ver);
    free(sum);
    free(h);
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int V, K, E;
    printf("Enter number of vertices V (vertices are 0 to V-1): ");
    if (scanf("%d", &V) != 1 || V <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter size threshold K: ");
    if (scanf("%d", &K) != 1 || K < 0) {
        printf("Invalid input\n");
        return 1;
    }
    ll *w = malloc((size_t)V * sizeof(ll));
    printf("Enter %d vertex weights: ", V);
    for (int i = 0; i < V; i++) {
        if (scanf("%lld", &w[i]) != 1) {
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
    ll *ew = malloc((size_t)(E + 1) * sizeof(ll));
    for (int i = 0; i < E; i++) {
        printf("Enter edge %d (u v weight): ", i + 1);
        if (scanf("%d %d %lld", &eu[i], &ev[i], &ew[i]) != 3 || eu[i] < 0 || eu[i] >= V || ev[i] < 0 || ev[i] >= V) {
            printf("Invalid input\n");
            return 1;
        }
    }
    ll *ans = malloc((size_t)(E + 1) * sizeof(ll));
    max_comp_weight(V, K, w, E, eu, ev, ans);
    printf("Before any edge: %lld\n", ans[0]);
    for (int i = 0; i < E; i++)
        printf("After edge %d (%d, %d): %lld\n", i + 1, eu[i], ev[i], ans[i + 1]);
    free(w);
    free(eu);
    free(ev);
    free(ew);
    free(ans);
    return 0;
}
