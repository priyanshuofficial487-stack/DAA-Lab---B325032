#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int min3(int a, int b, int c)
{
    int m = a < b ? a : b;
    return m < c ? m : c;
}

int edit_distance(const char *A, const char *B, int verbose)
{
    int m = (int)strlen(A), n = (int)strlen(B), w = n + 1;
    int *D = malloc((size_t)(m + 1) * w * sizeof(int));
    for (int i = 0; i <= m; i++)
        D[i * w] = i;
    for (int j = 0; j <= n; j++)
        D[j] = j;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            D[i * w + j] = min3(D[(i - 1) * w + j - 1] + (A[i - 1] != B[j - 1]),
                                D[(i - 1) * w + j] + 1,
                                D[i * w + j - 1] + 1);
    int result = D[m * w + n];
    if (verbose) {
        int cap = m + n + 1;
        char *op = malloc((size_t)cap);
        int *ia = malloc((size_t)cap * sizeof(int));
        int *ib = malloc((size_t)cap * sizeof(int));
        int k = 0, i = m, j = n;
        while (i > 0 || j > 0) {
            if (i > 0 && j > 0 &&
                D[i * w + j] == D[(i - 1) * w + j - 1] + (A[i - 1] != B[j - 1])) {
                op[k] = A[i - 1] == B[j - 1] ? 'M' : 'S';
                ia[k] = i - 1;
                ib[k] = j - 1;
                i--;
                j--;
            } else if (i > 0 && D[i * w + j] == D[(i - 1) * w + j] + 1) {
                op[k] = 'D';
                ia[k] = i - 1;
                ib[k] = -1;
                i--;
            } else {
                op[k] = 'I';
                ia[k] = -1;
                ib[k] = j - 1;
                j--;
            }
            k++;
        }
        printf("Traceback (start to end):\n");
        int step = 0;
        for (int t = k - 1; t >= 0; t--) {
            if (op[t] == 'M')
                printf("  keep       '%c'\n", A[ia[t]]);
            else if (op[t] == 'S')
                printf("  %2d substitute '%c' -> '%c' at A[%d]\n", ++step, A[ia[t]], B[ib[t]], ia[t]);
            else if (op[t] == 'D')
                printf("  %2d delete     '%c' at A[%d]\n", ++step, A[ia[t]], ia[t]);
            else
                printf("  %2d insert     '%c' from B[%d]\n", ++step, B[ib[t]], ib[t]);
        }
        free(op);
        free(ia);
        free(ib);
    }
    free(D);
    return result;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    static char A[100001], B[100001];
    printf("Enter string A: ");
    if (scanf("%100000s", A) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter string B: ");
    if (scanf("%100000s", B) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int d = edit_distance(A, B, 1);
    printf("Minimum edit distance: %d\n", d);
    return 0;
}
