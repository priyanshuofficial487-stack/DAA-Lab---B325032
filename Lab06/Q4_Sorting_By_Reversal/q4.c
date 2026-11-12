#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long reversalCount = 0;
long long reversalCost = 0;

void reverse(int arr[], int i, int j) {
    reversalCount++;
    reversalCost += (j - i + 1);
    while (i < j) {
        int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
        i++; j--;
    }
}

void selectionSortByReversal(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int pos = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[pos]) pos = j;
        if (pos != i) {
            reverse(arr, i, pos);
            reverse(arr, i + 1, pos);
        }
    }
}

void rotate(int arr[], int l, int m, int r) {
    if (l > m || m + 1 > r) return;
    reverse(arr, l, m);
    reverse(arr, m + 1, r);
    reverse(arr, l, r);
}

void mergeByRotation(int arr[], int l, int m, int r) {
    if (l > m || m >= r) return;
    if (arr[m] <= arr[m + 1]) return;

    int m1 = l + (m - l) / 2;
    int lo = m + 1, hi = r + 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < arr[m1]) lo = mid + 1;
        else hi = mid;
    }
    int m2 = lo;

    if (m2 > m + 1) rotate(arr, m1, m, m2 - 1);

    int newm1 = m1 + (m2 - (m + 1));

    mergeByRotation(arr, l, m1 - 1, newm1 - 1);
    mergeByRotation(arr, newm1 + 1, newm1 + (m - m1), r);
}

void mergeSortByReversal(int arr[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSortByReversal(arr, l, m);
    mergeSortByReversal(arr, m + 1, r);
    mergeByRotation(arr, l, m, r);
}

int isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++)
        if (arr[i - 1] > arr[i]) return 0;
    return 1;
}

void makeRandomPermutation(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i + 1;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
    }
}

int main() {
    srand(7);
    FILE *fp = fopen("complexity.csv", "w");
    fprintf(fp, "n,selection_reversal_count,selection_reversal_cost,selection_time,mergesort_reversal_count,mergesort_reversal_cost,mergesort_time\n");

    int sizes[] = {100, 200, 400, 800, 1600, 3200, 6400, 12800};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *base = malloc(n * sizeof(int));
        int *arr = malloc(n * sizeof(int));
        makeRandomPermutation(base, n);

        for (int i = 0; i < n; i++) arr[i] = base[i];
        reversalCount = 0; reversalCost = 0;
        clock_t t1 = clock();
        selectionSortByReversal(arr, n);
        clock_t t2 = clock();
        double tSel = (double)(t2 - t1) / CLOCKS_PER_SEC;
        long long selCount = reversalCount, selCost = reversalCost;
        if (!isSorted(arr, n)) printf("ERROR: selection sort failed for n=%d\n", n);

        for (int i = 0; i < n; i++) arr[i] = base[i];
        reversalCount = 0; reversalCost = 0;
        t1 = clock();
        mergeSortByReversal(arr, 0, n - 1);
        t2 = clock();
        double tMerge = (double)(t2 - t1) / CLOCKS_PER_SEC;
        long long mergeCount = reversalCount, mergeCost = reversalCost;
        if (!isSorted(arr, n)) printf("ERROR: merge sort by reversal failed for n=%d\n", n);

        fprintf(fp, "%d,%lld,%lld,%f,%lld,%lld,%f\n",
                n, selCount, selCost, tSel, mergeCount, mergeCost, tMerge);

        free(base);
        free(arr);
    }

    fclose(fp);
    printf("Done. Results written to complexity.csv\n");

    int demo[] = {5, 3, 1, 4, 2};
    int dn = 5;
    printf("\nDemo permutation: ");
    for (int i = 0; i < dn; i++) printf("%d ", demo[i]);
    printf("\n");

    reversalCount = 0; reversalCost = 0;
    mergeSortByReversal(demo, 0, dn - 1);
    printf("Sorted using rotation-based merge sort: ");
    for (int i = 0; i < dn; i++) printf("%d ", demo[i]);
    printf("\nReversals used: %lld, total cost: %lld\n", reversalCount, reversalCost);

    int demo2[] = {5, 3, 1, 4, 2};
    reversalCount = 0; reversalCost = 0;
    selectionSortByReversal(demo2, dn);
    printf("\nSorted using selection-by-reversal: ");
    for (int i = 0; i < dn; i++) printf("%d ", demo2[i]);
    printf("\nReversals used: %lld, total cost: %lld\n", reversalCount, reversalCost);

    return 0;
}
