#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 1000000000

typedef struct {
    int n, m;
    int *head, *next, *to;
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
    g->next = malloc(2 * max_edges * sizeof(int));
    g->to = malloc(2 * max_edges * sizeof(int));
    for (int i = 0; i < n; i++) g->head[i] = -1;
    return g;
}

void add_directed(Graph *g, int u, int v) {
    int e = g->m++;
    g->to[e] = v;
    g->next[e] = g->head[u];
    g->head[u] = e;
}

void add_edge(Graph *g, int u, int v) {
    add_directed(g, u, v);
    add_directed(g, v, u);
}

void free_graph(Graph *g) {
    free(g->head);
    free(g->next);
    free(g->to);
    free(g);
}

void multi_source_bfs(Graph *g, int *hubs, int K, int R, int *owner, int *dist) {
    int n = g->n;
    int *queue = malloc(n * sizeof(int));
    int head = 0, tail = 0;
    for (int v = 0; v < n; v++) {
        owner[v] = -1;
        dist[v] = -1;
    }
    for (int i = 0; i < K; i++) {
        if (owner[hubs[i]] != -1) continue;
        owner[hubs[i]] = i + 1;
        dist[hubs[i]] = 0;
        queue[tail++] = hubs[i];
    }
    while (head < tail) {
        int u = queue[head++];
        if (dist[u] == R) continue;
        for (int e = g->head[u]; e != -1; e = g->next[e]) {
            int v = g->to[e];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                queue[tail++] = v;
            }
        }
    }
    free(queue);
}

void single_bfs(Graph *g, int src, int *d, int *queue) {
    for (int v = 0; v < g->n; v++) d[v] = -1;
    int head = 0, tail = 0;
    d[src] = 0;
    queue[tail++] = src;
    while (head < tail) {
        int u = queue[head++];
        for (int e = g->head[u]; e != -1; e = g->next[e]) {
            int v = g->to[e];
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                queue[tail++] = v;
            }
        }
    }
}

void naive_voronoi(Graph *g, int *hubs, int K, int R, int *owner, int *dist) {
    int n = g->n;
    int *d = malloc(n * sizeof(int));
    int *queue = malloc(n * sizeof(int));
    int *best = malloc(n * sizeof(int));
    int *who = malloc(n * sizeof(int));
    for (int v = 0; v < n; v++) {
        best[v] = INF;
        who[v] = -1;
    }
    for (int i = 0; i < K; i++) {
        single_bfs(g, hubs[i], d, queue);
        for (int v = 0; v < n; v++) {
            if (d[v] != -1 && d[v] < best[v]) {
                best[v] = d[v];
                who[v] = i + 1;
            }
        }
    }
    for (int v = 0; v < n; v++) {
        if (best[v] > R) {
            owner[v] = -1;
            dist[v] = -1;
        } else {
            owner[v] = who[v];
            dist[v] = best[v];
        }
    }
    free(d);
    free(queue);
    free(best);
    free(who);
}

Graph *random_graph(int n, int m) {
    Graph *g = new_graph(n, m);
    for (int i = 0; i < m; i++) add_edge(g, rng() % n, rng() % n);
    return g;
}

void pick_hubs(int n, int K, int *hubs) {
    char *used = calloc(n, 1);
    for (int i = 0; i < K; i++) {
        int h;
        do h = rng() % n; while (used[h]);
        used[h] = 1;
        hubs[i] = h;
    }
    free(used);
}

int main() {
    Graph *g = new_graph(10, 8);
    for (int i = 0; i < 8; i++) add_edge(g, i, i + 1);
    int hubs[2] = {1, 5};
    int owner[10], dist[10];
    multi_source_bfs(g, hubs, 2, 2, owner, dist);
    printf("Sample: path 0-1-...-8, vertex 9 isolated, hubs = {1, 5}, R = 2\n");
    printf("vertex owner distance\n");
    for (int v = 0; v < 10; v++) printf("%-6d %-5d %d\n", v, owner[v], dist[v]);
    free_graph(g);

    int passed = 0, tests = 1000;
    for (int t = 0; t < tests; t++) {
        int n = 1 + rng() % 25;
        int m = rng() % 40;
        int K = 1 + rng() % (n < 6 ? n : 6);
        int R = rng() % 7;
        Graph *h = random_graph(n, m);
        int hb[6];
        pick_hubs(n, K, hb);
        int o1[25], d1[25], o2[25], d2[25];
        multi_source_bfs(h, hb, K, R, o1, d1);
        naive_voronoi(h, hb, K, R, o2, d2);
        int ok = 1;
        for (int v = 0; v < n; v++) if (o1[v] != o2[v] || d1[v] != d2[v]) ok = 0;
        passed += ok;
        free_graph(h);
    }
    printf("\nValidation against K separate BFS runs: %d / %d random tests passed\n", passed, tests);

    FILE *fp = fopen("results.csv", "w");
    fprintf(fp, "vertices,edges,hubs,radius,multi_bfs_ms,naive_ms\n");
    printf("\nvertices   edges     hubs radius multi(ms)  naive(ms)\n");
    for (int i = 1; i <= 10; i++) {
        int n = 20000 * i, m = 3 * n, K = 20, R = 10;
        Graph *h = random_graph(n, m);
        int *hb = malloc(K * sizeof(int));
        pick_hubs(n, K, hb);
        int *o = malloc(n * sizeof(int));
        int *d = malloc(n * sizeof(int));
        double t1 = 0, t2 = 0;
        for (int r = 0; r < 5; r++) {
            clock_t t0 = clock();
            multi_source_bfs(h, hb, K, R, o, d);
            t1 += (double)(clock() - t0) * 1000.0 / CLOCKS_PER_SEC;
        }
        for (int r = 0; r < 2; r++) {
            clock_t t0 = clock();
            naive_voronoi(h, hb, K, R, o, d);
            t2 += (double)(clock() - t0) * 1000.0 / CLOCKS_PER_SEC;
        }
        t1 /= 5;
        t2 /= 2;
        printf("%-10d %-9d %-4d %-6d %-10.3f %.3f\n", n, m, K, R, t1, t2);
        fprintf(fp, "%d,%d,%d,%d,%.4f,%.4f\n", n, m, K, R, t1, t2);
        free(hb);
        free(o);
        free(d);
        free_graph(h);
    }
    fclose(fp);
    return 0;
}
