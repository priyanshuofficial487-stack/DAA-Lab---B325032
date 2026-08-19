#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Interval;

int cmp(const void *a, const void *b) {
    Interval *i1 = (Interval*)a;
    Interval *i2 = (Interval*)b;
    return i1->x - i2->x;
}

int mergeIntervals(Interval arr[], int n, Interval result[]) {
    qsort(arr, n, sizeof(Interval), cmp);

    int idx = 0;
    result[idx] = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i].x <= result[idx].y) {
            if (arr[i].y > result[idx].y)
                result[idx].y = arr[i].y;
        } else {
            idx++;
            result[idx] = arr[i];
        }
    }
    return idx + 1;
}

int main() {
    int n;
    printf("Enter number of intervals (n): ");
    scanf("%d", &n);

    Interval *arr = malloc(n * sizeof(Interval));
    Interval *result = malloc(n * sizeof(Interval));

    printf("Enter each interval as: x y\n");
    for (int i = 0; i < n; i++) {
        printf("Interval %d - x y: ", i + 1);
        scanf("%d %d", &arr[i].x, &arr[i].y);
    }

    printf("\nInput intervals:\n");
    for (int i = 0; i < n; i++)
        printf("(%d, %d) ", arr[i].x, arr[i].y);
    printf("\n\n");

    int m = mergeIntervals(arr, n, result);

    printf("Merged intervals:\n");
    for (int i = 0; i < m; i++)
        printf("(%d, %d) ", result[i].x, result[i].y);
    printf("\n");

    free(arr);
    free(result);
    return 0;
}
