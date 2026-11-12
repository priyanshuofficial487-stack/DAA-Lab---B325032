#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *p, *par, *sz;
} DSU;

void dsu_init(DSU *d, int n)
{
    d->p = malloc((size_t)n * sizeof(int));
    d->par = calloc((size_t)n, sizeof(int));
    d->sz = malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        d->p[i] = i;
        d->sz[i] = 1;
    }
}

void dsu_free(DSU *d)
{
    free(d->p);
    free(d->par);
    free(d->sz);
}

int find(DSU *d, int x, int *px)
{
    int r = x, acc = 0;
    while (d->p[r] != r) {
        acc ^= d->par[r];
        r = d->p[r];
    }
    int cur = x, cp = acc;
    while (cur != r) {
        int next = d->p[cur];
        int np = cp ^ d->par[cur];
        d->p[cur] = r;
        d->par[cur] = cp;
        cur = next;
        cp = np;
    }
    *px = acc;
    return r;
}

int try_add_edge(DSU *d, int u, int v)
{
    int pu, pv;
    int ru = find(d, u, &pu), rv = find(d, v, &pv);
    if (ru == rv)
        return pu != pv;
    if (d->sz[ru] > d->sz[rv]) {
        int t = ru;
        ru = rv;
        rv = t;
    }
    d->p[ru] = rv;
    d->par[ru] = pu ^ pv ^ 1;
    d->sz[rv] += d->sz[ru];
    return 1;

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
    printf("Enter number of edges E: ");
    if (scanf("%d", &E) != 1 || E < 0) {
        printf("Invalid input\n");
        return 1;
    }
    DSU d;
    dsu_init(&d, V);
    int added = 0, skipped = 0;
    for (int i = 0; i < E; i++) {
        int u, v;
        printf("Enter edge %d (u v): ", i + 1);
        if (scanf("%d %d", &u, &v) != 2 || u < 0 || u >= V || v < 0 || v >= V) {
            printf("Invalid input\n");
            return 1;
        }
        if (try_add_edge(&d, u, v)) {
            printf("  edge (%d, %d): added, graph is still bipartite\n", u, v);
            added++;
        } else {
            printf("  edge (%d, %d): creates an odd cycle, skipped\n", u, v);
            skipped++;
        }
    }
    printf("Edges added: %d, edges skipped: %d\n", added, skipped);
    printf("Vertex colours (0/1):");
    for (int i = 0; i < V; i++) {
        int c;
        find(&d, i, &c);
        printf(" %d", c);
    }
    printf("\n");
    dsu_free(&d);
    return 0;
}
