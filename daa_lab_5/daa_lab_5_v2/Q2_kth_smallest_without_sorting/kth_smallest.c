#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int randomPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(&arr[randomIndex], &arr[high]);
    return partition(arr, low, high);
}

int quickSelect(int arr[], int low, int high, int k) {
    if (low == high)
        return arr[low];

    int pivotIndex = randomPartition(arr, low, high);

    if (pivotIndex == k)
        return arr[pivotIndex];
    else if (k < pivotIndex)
        return quickSelect(arr, low, pivotIndex - 1, k);
    else
        return quickSelect(arr, pivotIndex + 1, high, k);
}

int main() {
    srand(time(NULL));

    int n, k;
    printf("Enter number of elements (N): ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter K (1 = smallest, N = largest): ");
    scanf("%d", &k);

    if (k < 1 || k > n) {
        printf("Invalid K! Must be between 1 and %d.\n", n);
    } else {
        int result = quickSelect(arr, 0, n - 1, k - 1);
        printf("%d'th smallest element = %d\n", k, result);
    }

    free(arr);
    return 0;
}
