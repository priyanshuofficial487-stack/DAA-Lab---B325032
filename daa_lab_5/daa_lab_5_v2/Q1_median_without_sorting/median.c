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

void findMedian(int arr[], int n) {
    if (n % 2 == 1) {
        int median = quickSelect(arr, 0, n - 1, n / 2);
        printf("Median = %d\n", median);
    } else {
        int a = quickSelect(arr, 0, n - 1, n / 2 - 1);
        int b = quickSelect(arr, 0, n - 1, n / 2);
        printf("Median = %.2f\n", (a + b) / 2.0);
    }
}

int main() {
    srand(time(NULL));

    int n;
    printf("Enter number of elements (N): ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    findMedian(arr, n);

    free(arr);
    return 0;
}
