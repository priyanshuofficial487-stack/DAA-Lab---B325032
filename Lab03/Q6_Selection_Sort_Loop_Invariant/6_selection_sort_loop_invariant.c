#include <stdio.h>

long comparisons = 0;

void selectionSort(int arr[], int n) {

    for (int i = 0; i < n - 1; i++) {
        int smallest = i;

        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[smallest])
                smallest = j;
        }

        if (smallest != i) {
            int temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
        }
    }
}

int isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1])
            return 0;
    return 1;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal array: ");
    printArray(arr, n);

    comparisons = 0;
    selectionSort(arr, n);

    printf("Sorted array:   ");
    printArray(arr, n);

    printf("\nTotal comparisons made: %ld\n", comparisons);
    printf("Expected worst/best-case comparisons n(n-1)/2 = %d\n", n * (n - 1) / 2);

    if (isSorted(arr, n))
        printf("Validation: Array is correctly sorted. Loop invariant held!\n");
    else
        printf("Validation FAILED: Array is not sorted (bug!)\n");

    return 0;
}
