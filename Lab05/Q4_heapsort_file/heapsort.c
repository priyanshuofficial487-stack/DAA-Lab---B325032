#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void generateRandomFile(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not create %s\n", filename);
        exit(1);
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int value = rand() % 1000;
        fprintf(fp, "%d\n", value);
    }

    fclose(fp);
    printf("Generated %d random numbers into %s\n", n, filename);
}

int* readFromFile(const char *filename, int n) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open %s\n", filename);
        exit(1);
    }

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);

    fclose(fp);
    return arr;
}

void writeToFile(const char *filename, int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not create %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < n; i++)
        fprintf(fp, "%d\n", arr[i]);

    fclose(fp);
    printf("Sorted numbers written to %s\n", filename);
}

int main() {
    int n;
    printf("Enter number of random elements to generate (N): ");
    scanf("%d", &n);

    generateRandomFile(INPUT_FILE, n);

    int *arr = readFromFile(INPUT_FILE, n);

    heapSort(arr, n);

    writeToFile(OUTPUT_FILE, arr, n);

    if (n <= 50) {
        printf("Sorted elements:\n");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }

    free(arr);
    return 0;
}
