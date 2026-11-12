#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *lcs(const char *X, const char *Y, int *len)
{
    int m = (int)strlen(X), n = (int)strlen(Y), w = n + 1;
    int *L = calloc((size_t)(m + 1) * w, sizeof(int));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                L[i * w + j] = L[(i - 1) * w + j - 1] + 1;
            else if (L[(i - 1) * w + j] >= L[i * w + j - 1])
                L[i * w + j] = L[(i - 1) * w + j];
            else
                L[i * w + j] = L[i * w + j - 1];
        }
    }
    int k = L[m * w + n];
    *len = k;
    char *s = malloc((size_t)k + 1);
    s[k] = '\0';
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            s[--k] = X[i - 1];
            i--;
            j--;
        } else if (L[(i - 1) * w + j] >= L[i * w + j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    free(L);
    return s;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    static char X[100001], Y[100001];
    printf("Enter first string: ");
    if (scanf("%100000s", X) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Enter second string: ");
    if (scanf("%100000s", Y) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int len;
    char *s = lcs(X, Y, &len);
    printf("Length: %d\n", len);
    printf("LCS: %s\n", s);
    free(s);
    return 0;
}
