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

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

    quickSort(arr, 0, n - 1);

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
