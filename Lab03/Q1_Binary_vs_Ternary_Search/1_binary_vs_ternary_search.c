#include <stdio.h>

int binaryComparisons = 0;
int ternaryComparisons = 0;

int binarySearch(int arr[], int n, int x) {
    int low = 0, high = n - 1;
    binaryComparisons = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        binaryComparisons++;
        if (arr[mid] == x)
            return mid;

        binaryComparisons++;
        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int ternarySearch(int arr[], int n, int x) {
    int low = 0, high = n - 1;
    ternaryComparisons = 0;

    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        ternaryComparisons++;
        if (arr[mid1] == x) return mid1;

        ternaryComparisons++;
        if (arr[mid2] == x) return mid2;

        ternaryComparisons++;
        if (x < arr[mid1]) {
            high = mid1 - 1;
        } else {
            ternaryComparisons++;
            if (x > arr[mid2]) {
                low = mid2 + 1;
            } else {
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }
    }
    return -1;
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements in SORTED (ascending) order:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int x;
    printf("Enter element to search: ");
    scanf("%d", &x);

    int posB = binarySearch(arr, n, x);
    int posT = ternarySearch(arr, n, x);

    printf("\n--- Binary Search Result ---\n");
    if (posB != -1)
        printf("Element found at index %d\n", posB);
    else
        printf("Element not found\n");
    printf("Comparisons used: %d\n", binaryComparisons);

    printf("\n--- Ternary Search Result ---\n");
    if (posT != -1)
        printf("Element found at index %d\n", posT);
    else
        printf("Element not found\n");
    printf("Comparisons used: %d\n", ternaryComparisons);

    printf("\n--- Conclusion ---\n");
    if (binaryComparisons < ternaryComparisons)
        printf("Binary search used FEWER comparisons -> Binary search is better here.\n");
    else if (binaryComparisons > ternaryComparisons)
        printf("Ternary search used fewer comparisons this time (rare, small n).\n");
    else
        printf("Both used equal comparisons this time.\n");

    return 0;
}
