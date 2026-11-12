#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int findMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx) mx = arr[i];
    return mx;
}

void findFirstSecondLargest(int arr[], int n, int *first, int *second) {
    if (arr[0] > arr[1]) { *first = arr[0]; *second = arr[1]; }
    else { *first = arr[1]; *second = arr[0]; }
    for (int i = 2; i < n; i++) {
        if (arr[i] > *first) { *second = *first; *first = arr[i]; }
        else if (arr[i] > *second) { *second = arr[i]; }
    }
}

double findMean(int arr[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return (double)sum / n;
}

int cmpInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

double findMedian(int arr[], int n) {
    int *temp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), cmpInt);
    double med;
    if (n % 2 == 0) med = (temp[n/2 - 1] + temp[n/2]) / 2.0;
    else med = temp[n/2];
    free(temp);
    return med;
}

double findStdDev(int arr[], int n) {
    double mean = findMean(arr, n);
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += (arr[i] - mean) * (arr[i] - mean);
    return sqrt(sum / n);
}

int findMode(int arr[], int n) {
    int *temp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), cmpInt);
    int bestVal = temp[0], bestCount = 1, curVal = temp[0], curCount = 1;
    for (int i = 1; i < n; i++) {
        if (temp[i] == curVal) curCount++;
        else { curVal = temp[i]; curCount = 1; }
        if (curCount > bestCount) { bestCount = curCount; bestVal = curVal; }
    }
    free(temp);
    return bestVal;
}

int removeDuplicates(int arr[], int n) {
    int *temp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), cmpInt);
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || temp[i] != temp[i-1]) temp[j++] = temp[i];
    }
    free(temp);
    return j;
}

void reverseArray(int arr[], int n) {
    int l = 0, r = n - 1;
    while (l < r) {
        int t = arr[l]; arr[l] = arr[r]; arr[r] = t;
        l++; r--;
    }
}

int partitionArray(int arr[], int n, int pivotIndex) {
    int pivot = arr[pivotIndex];
    int t = arr[pivotIndex]; arr[pivotIndex] = arr[n-1]; arr[n-1] = t;
    int storeIndex = 0;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] >= pivot) {
            int tmp = arr[i]; arr[i] = arr[storeIndex]; arr[storeIndex] = tmp;
            storeIndex++;
        }
    }
    t = arr[storeIndex]; arr[storeIndex] = arr[n-1]; arr[n-1] = t;
    return storeIndex;
}

int *makeRandomArray(int n) {
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;
    return arr;
}

int main() {
    srand(42);
    FILE *fp = fopen("complexity.csv", "w");
    fprintf(fp, "n,max_time,first_second_time,mean_time,median_time,stddev_time,mode_time,removeDup_time,reverse_time,partition_time\n");

    int sizes[] = {1000, 5000, 10000, 25000, 50000, 100000, 200000, 400000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *base = makeRandomArray(n);
        int *arr = malloc(n * sizeof(int));
        clock_t t1, t2;
        double tMax, tFS, tMean, tMedian, tStd, tMode, tDup, tRev, tPart;

        for (int i = 0; i < n; i++) arr[i] = base[i];
        t1 = clock();
        findMax(arr, n);
        t2 = clock();
        tMax = (double)(t2 - t1) / CLOCKS_PER_SEC;

        int first, second;
        for (int i = 0; i < n; i++) arr[i] = base[i];
        t1 = clock();
        findFirstSecondLargest(arr, n, &first, &second);
        t2 = clock();
        tFS = (double)(t2 - t1) / CLOCKS_PER_SEC;

        for (int i = 0; i < n; i++) arr[i] = base[i];
        t1 = clock();
        findMean(arr, n);
        t2 = clock();
        tMean = (double)(t2 - t1) / CLOCKS_PER_SEC;

        for (int i = 0; i < n; i++) arr[i] = base[i];
        t1 = clock();
        findMedian(arr, n);
        t2 = clock();
        tMedian = (double)(t2 - t1) / CLOCKS_PER_SEC;

        for (int i = 0; i < n; i++) arr[i] = base[i];
        t1 = clock();
        findStdDev(arr, n);
        t2 = clock();
        tStd = (double)(t2 - t1) / CLOCKS_PER_SEC;

        for (int i = 0; i < n; i++) arr[i] = base[i];
        t1 = clock();
        findMode(arr, n);
        t2 = clock();
        tMode = (double)(t2 - t1) / CLOCKS_PER_SEC;

        for (int i = 0; i < n; i++) arr[i] = base[i];
        t1 = clock();
        removeDuplicates(arr, n);
        t2 = clock();
        tDup = (double)(t2 - t1) / CLOCKS_PER_SEC;

        for (int i = 0; i < n; i++) arr[i] = base[i];
        t1 = clock();
        reverseArray(arr, n);
        t2 = clock();
        tRev = (double)(t2 - t1) / CLOCKS_PER_SEC;

        for (int i = 0; i < n; i++) arr[i] = base[i];
        t1 = clock();
        partitionArray(arr, n, n / 2);
        t2 = clock();
        tPart = (double)(t2 - t1) / CLOCKS_PER_SEC;

        fprintf(fp, "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
                n, tMax, tFS, tMean, tMedian, tStd, tMode, tDup, tRev, tPart);

        free(base);
        free(arr);
    }

    fclose(fp);
    printf("Done. Results written to complexity.csv\n");

    int demo[] = {9, 3, 7, 1, 8, 2, 5};
    int dn = 7;
    printf("\nDemo array: ");
    for (int i = 0; i < dn; i++) printf("%d ", demo[i]);
    printf("\nMax: %d\n", findMax(demo, dn));
    int f, sec;
    findFirstSecondLargest(demo, dn, &f, &sec);
    printf("First largest: %d, Second largest: %d\n", f, sec);
    printf("Mean: %.2f\n", findMean(demo, dn));
    printf("Median: %.2f\n", findMedian(demo, dn));
    printf("Std Dev: %.2f\n", findStdDev(demo, dn));
    printf("Mode: %d\n", findMode(demo, dn));
    int dupCount = removeDuplicates(demo, dn);
    printf("Distinct elements count: %d\n", dupCount);
    reverseArray(demo, dn);
    printf("Reversed: ");
    for (int i = 0; i < dn; i++) printf("%d ", demo[i]);
    printf("\n");
    int pivIdx = partitionArray(demo, dn, 3);
    printf("After partition (>=pivot first): ");
    for (int i = 0; i < dn; i++) printf("%d ", demo[i]);
    printf("\nPivot final index: %d\n", pivIdx);

    return 0;
}
