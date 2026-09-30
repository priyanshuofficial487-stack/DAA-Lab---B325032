#include <stdio.h>
#include <stdlib.h>

#define INF 1e18

double optimal_bst(const double *p, const double *q, int n, int **root_out)
{
    int W = n + 2;
    double *e = malloc((size_t)W * W * sizeof(double));
    double *w = malloc((size_t)W * W * sizeof(double));
    int *root = calloc((size_t)W * W, sizeof(int));
    for (int i = 1; i <= n + 1; i++) {
        e[i * W + i - 1] = q[i - 1];
        w[i * W + i - 1] = q[i - 1];
    }
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i * W + j] = INF;
            w[i * W + j] = w[i * W + j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = e[i * W + r - 1] + e[(r + 1) * W + j] + w[i * W + j];
                if (t < e[i * W + j]) {
                    e[i * W + j] = t;
                    root[i * W + j] = r;
                }
            }
        }
    }
    double cost = e[1 * W + n];
    free(e);
    free(w);
    if (root_out)
        *root_out = root;
    else
        free(root);
    return cost;
}

static void print_tree(const int *root, int W, int i, int j, int parent, const char *side)
{
    if (i > j) {
        printf("  d%d is the %s child of k%d\n", j, side, parent);
        return;
    }
    int r = root[i * W + j];
    if (parent == 0)
        printf("  k%d is the root\n", r);
    else
        printf("  k%d is the %s child of k%d\n", r, side, parent);
    print_tree(root, W, i, r - 1, r, "left");
    print_tree(root, W, r + 1, j, r, "right");
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0)
        return 1;
    double *p = calloc((size_t)(n + 1), sizeof(double));
    double *q = calloc((size_t)(n + 1), sizeof(double));
    for (int i = 1; i <= n; i++)
        if (scanf("%lf", &p[i]) != 1)
            return 1;
    for (int i = 0; i <= n; i++)
        if (scanf("%lf", &q[i]) != 1)
            return 1;
    int *root;
    double cost = optimal_bst(p, q, n, &root);
    printf("Minimum expected search cost: %.4f\n", cost);
    printf("Structure of the optimal tree:\n");
    print_tree(root, n + 2, 1, n, 0, "");
    free(p);
    free(q);
    free(root);
    return 0;
}
