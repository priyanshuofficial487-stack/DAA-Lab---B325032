#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int binarySearch(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int findPairWithSum(int S1[], int n1, int S2[], int n2, int x, int *a, int *b) {
    qsort(S2, n2, sizeof(int), cmp);
    for (int i = 0; i < n1; i++) {
        int need = x - S1[i];
        int pos = binarySearch(S2, n2, need);
        if (pos != -1) {
            *a = S1[i];
            *b = S2[pos];
            return 1;
        }
    }
    return 0;
}

void readSet(const char *label, int arr[], int n) {
    printf("Enter %d elements of %s, separated by spaces:\n", n, label);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
}

int main() {
    int n, x;

    printf("Enter n (size of each set): ");
    scanf("%d", &n);

    int *S1 = malloc(n * sizeof(int));
    int *S2 = malloc(n * sizeof(int));

    readSet("S1", S1, n);
    readSet("S2", S2, n);

    printf("Enter target sum x: ");
    scanf("%d", &x);

    printf("\nS1: ");
    for (int i = 0; i < n; i++) printf("%d ", S1[i]);
    printf("\nS2: ");
    for (int i = 0; i < n; i++) printf("%d ", S2[i]);
    printf("\nTarget sum x = %d\n\n", x);

    int a, b;
    if (findPairWithSum(S1, n, S2, n, x, &a, &b))
        printf("Pair found: %d (from S1) + %d (from S2) = %d\n", a, b, x);
    else
        printf("No pair found that sums to %d\n", x);

    free(S1);
    free(S2);
    return 0;
}
