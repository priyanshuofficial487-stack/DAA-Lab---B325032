#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int R, C, count;
    int *p, *sz;
    char *land;
} Grid;

void grid_init(Grid *g, int R, int C)
{
    g->R = R;
    g->C = C;
    g->count = 0;
    g->p = malloc((size_t)R * C * sizeof(int));
    g->sz = malloc((size_t)R * C * sizeof(int));
    g->land = calloc((size_t)R * C, 1);
    for (int i = 0; i < R * C; i++) {
        g->p[i] = i;
        g->sz[i] = 1;
    }
}

void grid_free(Grid *g)
{
    free(g->p);
    free(g->sz);
    free(g->land);
}

static int find(int *p, int x)
{
    while (p[x] != x) {
        p[x] = p[p[x]];
        x = p[x];
    }
    return x;
}

int grid_add(Grid *g, int r, int c)
{
    int id = r * g->C + c;
    if (g->land[id])
        return g->count;
    g->land[id] = 1;
    g->count++;
    static const int dr[4] = {-1, 1, 0, 0};
    static const int dc[4] = {0, 0, -1, 1};
    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr < 0 || nr >= g->R || nc < 0 || nc >= g->C)
            continue;
        int nid = nr * g->C + nc;
        if (!g->land[nid])
            continue;
        int a = find(g->p, id), b = find(g->p, nid);
        if (a == b)
            continue;
        if (g->sz[a] < g->sz[b]) {
            int t = a;
            a = b;
            b = t;
        }
        g->p[b] = a;
        g->sz[a] += g->sz[b];
        g->count--;
    }
    return g->count;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int R, C, k;
    printf("Enter number of rows R and columns C: ");
    if (scanf("%d %d", &R, &C) != 2 || R <= 0 || C <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter number of land additions k: ");
    if (scanf("%d", &k) != 1 || k < 0) {
        printf("Invalid input\n");
        return 1;
    }
    Grid g;
    grid_init(&g, R, C);
    for (int i = 0; i < k; i++) {
        int r, c;
        printf("Enter position %d (row column, 0-indexed): ", i + 1);
        if (scanf("%d %d", &r, &c) != 2 || r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid input\n");
            return 1;
        }
        printf("  after adding (%d, %d): %d island(s)\n", r, c, grid_add(&g, r, c));
    }
    grid_free(&g);
    return 0;
}
