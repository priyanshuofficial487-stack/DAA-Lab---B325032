#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 1000000000

typedef struct {
    int n, m;
    int *head, *next, *to, *wt;
} Graph;

static unsigned state = 2463534242u;

unsigned rng(void) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

Graph *new_graph(int n, int max_edges) {
    Graph *g = malloc(sizeof(Graph));
    g->n = n;
    g->m = 0;
    g->head = malloc(n * sizeof(int));
    g->next = malloc(max_edges * sizeof(int));
    g->to = malloc(max_edges * sizeof(int));
    g->wt = malloc(max_edges * sizeof(int));
    for (int i = 0; i < n; i++) g->head[i] = -1;
    return g;
}

void add_edge(Graph *g, int u, int v, int w) {
    int e = g->m++;
    g->to[e] = v;
    g->wt[e] = w;
    g->next[e] = g->head[u];
    g->head[u] = e;
}

void free_graph(Graph *g) {
    free(g->head);
    free(g->next);
    free(g->to);
    free(g->wt);
    free(g);
}

void combine(int n, int *dist, long long C, long long *ans) {
    for (int v = 0; v < n; v++) {
        long long even = dist[2 * v] < INF ? dist[2 * v] : -1;
        long long odd = dist[2 * v + 1] < INF ? dist[2 * v + 1] + C : -1;
        if (even < 0) ans[v] = odd;
        else if (odd < 0) ans[v] = even;
        else ans[v] = even < odd ? even : odd;
    }
}

void zero_one_bfs(Graph *g, int s, long long C, long long *ans) {
    int n = g->n;
    int start = 2 * g->m + 2;
    int *dist = malloc(2 * n * sizeof(int));
    char *done = calloc(2 * n, 1);
    int *dq = malloc(2 * start * sizeof(int));
    for (int i = 0; i < 2 * n; i++) dist[i] = INF;
    int lo = start, hi = start;
    dist[2 * s] = 0;
    dq[hi++] = 2 * s;
    while (lo < hi) {
        int cur = dq[lo++];
        if (done[cur]) continue;
        done[cur] = 1;
        int u = cur / 2, p = cur % 2;
        for (int e = g->head[u]; e != -1; e = g->next[e]) {
            int nxt = g->to[e] * 2 + (p ^ g->wt[e]);
            int nd = dist[cur] + g->wt[e];
            if (nd < dist[nxt]) {
                dist[nxt] = nd;
                if (g->wt[e] == 0) dq[--lo] = nxt;
                else dq[hi++] = nxt;
            }
        }
    }
    combine(n, dist, C, ans);
    free(dist);
    free(done);
    free(dq);
}

void brute_force(Graph *g, int s, long long C, long long *ans) {
    int n = g->n;
    int *dist = malloc(2 * n * sizeof(int));
    for (int i = 0; i < 2 * n; i++) dist[i] = INF;
    dist[2 * s] = 0;
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int u = 0; u < n; u++) {
            for (int p = 0; p < 2; p++) {
                if (dist[2 * u + p] == INF) continue;
                for (int e = g->head[u]; e != -1; e = g->next[e]) {
                    int nxt = g->to[e] * 2 + (p ^ g->wt[e]);
                    int nd = dist[2 * u + p] + g->wt[e];
                    if (nd < dist[nxt]) {
                        dist[nxt] = nd;
                        changed = 1;
                    }
                }
            }
        }
    }
    combine(n, dist, C, ans);
    free(dist);
}

Graph *random_graph(int n, int m) {
    Graph *g = new_graph(n, m);
    for (int i = 0; i < m; i++) add_edge(g, rng() % n, rng() % n, rng() % 2);
    return g;
}

int main() {
    Graph *g = new_graph(6, 10);
    add_edge(g, 0, 1, 1);
    add_edge(g, 1, 2, 0);
    add_edge(g, 2, 3, 1);
    add_edge(g, 0, 3, 1);
    add_edge(g, 3, 4, 0);
    add_edge(g, 1, 4, 1);
    long long ans[6];
    zero_one_bfs(g, 0, 5, ans);
    printf("Sample: 6 vertices, source 0, penalty C = 5\n");
    for (int v = 0; v < 6; v++) {
        if (ans[v] < 0) printf("vertex %d : unreachable\n", v);
        else printf("vertex %d : %lld\n", v, ans[v]);
    }
    free_graph(g);

    int passed = 0, tests = 1000;
    for (int t = 0; t < tests; t++) {
        int n = 1 + rng() % 12;
        int m = rng() % 30;
        long long C = rng() % 10;
        Graph *h = random_graph(n, m);
        long long a[12], b[12];
        int s = rng() % n;
        zero_one_bfs(h, s, C, a);
        brute_force(h, s, C, b);
        int ok = 1;
        for (int v = 0; v < n; v++) if (a[v] != b[v]) ok = 0;
        passed += ok;
        free_graph(h);
    }
    printf("\nValidation against Bellman-Ford: %d / %d random tests passed\n", passed, tests);

    FILE *fp = fopen("results.csv", "w");
    fprintf(fp, "vertices,edges,time_ms\n");
    printf("\nvertices   edges     time(ms)\n");
    for (int i = 1; i <= 10; i++) {
        int n = 50000 * i, m = 4 * n;
        Graph *h = random_graph(n, m);
        long long *out = malloc(n * sizeof(long long));
        double total = 0;
        for (int r = 0; r < 3; r++) {
            clock_t t0 = clock();
            zero_one_bfs(h, 0, 7, out);
            total += (double)(clock() - t0) * 1000.0 / CLOCKS_PER_SEC;
        }
        total /= 3;
        printf("%-10d %-9d %.3f\n", n, m, total);
        fprintf(fp, "%d,%d,%.4f\n", n, m, total);
        free(out);
        free_graph(h);
    }
    fclose(fp);
    return 0;
}
