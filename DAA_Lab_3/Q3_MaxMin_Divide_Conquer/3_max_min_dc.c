#include <stdio.h>

long comparisons = 0;

typedef struct {
    int max;
    int min;
} Pair;

Pair findMaxMin(int arr[], int low, int high) {
    Pair result, left, right;

    if (low == high) {
        result.max = result.min = arr[low];
        return result;
    }

    if (high - low == 1) {
        comparisons++;
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }

    int mid = (low + high) / 2;
    left  = findMaxMin(arr, low, mid);
    right = findMaxMin(arr, mid + 1, high);

    comparisons++;
    result.max = (left.max > right.max) ? left.max : right.max;

    comparisons++;
    result.min = (left.min < right.min) ? left.min : right.min;

    return result;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    comparisons = 0;
    Pair ans = findMaxMin(arr, 0, n - 1);

    printf("\nMaximum element = %d\n", ans.max);
    printf("Minimum element = %d\n", ans.min);
    printf("Total comparisons used = %ld\n", comparisons);
    printf("Upper bound allowed (3n/2) = %.1f\n", 1.5 * n);

    if (comparisons <= (long)(1.5 * n))
        printf("Result: comparisons are within the 3n/2 bound. \n");
    else
        printf("Result: comparisons exceeded the bound (check n).\n");

    return 0;
}
