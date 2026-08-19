#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int type;
} Event;

int cmp(const void *a, const void *b) {
    Event *e1 = (Event*)a;
    Event *e2 = (Event*)b;
    if (e1->value != e2->value)
        return e1->value - e2->value;
    return e2->type - e1->type;
}

int findMaxOverlapPoint(int l[], int r[], int n, int *maxCount) {
    Event *events = malloc(2 * n * sizeof(Event));
    for (int i = 0; i < n; i++) {
        events[2 * i].value = l[i];
        events[2 * i].type = 1;
        events[2 * i + 1].value = r[i];
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(Event), cmp);

    int count = 0, best = 0, bestPoint = -1;
    for (int i = 0; i < 2 * n; i++) {
        count += events[i].type;
        if (count > best) {
            best = count;
            bestPoint = events[i].value;
        }
    }

    free(events);
    *maxCount = best;
    return bestPoint;
}

int main() {
    int n;
    printf("Enter number of intervals (n): ");
    scanf("%d", &n);

    int *l = malloc(n * sizeof(int));
    int *r = malloc(n * sizeof(int));

    printf("Enter each interval as: l r\n");
    for (int i = 0; i < n; i++) {
        printf("Interval %d - l r: ", i + 1);
        scanf("%d %d", &l[i], &r[i]);
    }

    printf("\nIntervals:\n");
    for (int i = 0; i < n; i++)
        printf("(%d, %d) ", l[i], r[i]);
    printf("\n\n");

    int maxCount;
    int point = findMaxOverlapPoint(l, r, n, &maxCount);

    printf("Point with maximum overlap: %d\n", point);
    printf("Number of intervals covering it: %d\n", maxCount);

    free(l);
    free(r);
    return 0;
}
