#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int twoSum(int arr[], int lo, int hi, int target, int combo[], int idx) {
    while (lo < hi) {
        int sum = arr[lo] + arr[hi];
        if (sum == target) {
            combo[idx] = arr[lo];
            combo[idx + 1] = arr[hi];
            return 1;
        } else if (sum < target) {
            lo++;
        } else {
            hi--;
        }
    }
    return 0;
}

int kSumRec(int arr[], int n, int start, int k, int target, int combo[], int idx) {
    if (k == 2) {
        return twoSum(arr, start, n - 1, target, combo, idx);
    }
    for (int i = start; i <= n - k; i++) {
        combo[idx] = arr[i];
        if (kSumRec(arr, n, i + 1, k - 1, target - arr[i], combo, idx + 1))
            return 1;
    }
    return 0;
}

int kSum(int arr[], int n, int k, int target, int combo[]) {
    qsort(arr, n, sizeof(int), cmp);
    if (k < 2 || k > n) return 0;
    return kSumRec(arr, n, 0, k, target, combo, 0);
}

int main() {
    int n, k, T;

    printf("Enter n (size of set S): ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Enter %d elements of S, separated by spaces:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Enter k (how many numbers should sum together): ");
    scanf("%d", &k);

    printf("Enter T (target sum): ");
    scanf("%d", &T);

    printf("\nSet S: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nk = %d, T = %d\n\n", k, T);

    int *combo = malloc(k * sizeof(int));
    if (kSum(arr, n, k, T, combo)) {
        printf("Found %d numbers that sum to %d: ", k, T);
        for (int i = 0; i < k; i++) printf("%d ", combo[i]);
        printf("\n");
    } else {
        printf("No combination of %d numbers sums to %d\n", k, T);
    }

    free(arr);
    free(combo);
    return 0;
}
