#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int delta;
} Event;

int cmp(const void *a, const void *b) {
    Event *e1 = (Event*)a;
    Event *e2 = (Event*)b;
    return e1->time - e2->time;
}

int findPeakTime(int entry[], int exit_[], int n, int *peakCount) {
    Event *events = malloc(2 * n * sizeof(Event));
    for (int i = 0; i < n; i++) {
        events[2 * i].time = entry[i];
        events[2 * i].delta = 1;
        events[2 * i + 1].time = exit_[i];
        events[2 * i + 1].delta = -1;
    }

    qsort(events, 2 * n, sizeof(Event), cmp);

    int count = 0, best = 0, bestTime = -1;
    for (int i = 0; i < 2 * n; i++) {
        count += events[i].delta;
        if (count > best) {
            best = count;
            bestTime = events[i].time;
        }
    }

    free(events);
    *peakCount = best;
    return bestTime;
}

int main() {
    int n;
    printf("Enter number of persons (n): ");
    scanf("%d", &n);

    int *entry = malloc(n * sizeof(int));
    int *exit_ = malloc(n * sizeof(int));

    printf("Enter entry and exit time for each person (entry exit exit > entry):\n");
    for (int i = 0; i < n; i++) {
        printf("Person %d - entry time: ", i + 1);
        scanf("%d", &entry[i]);
        printf("Person %d - exit time: ", i + 1);
        scanf("%d", &exit_[i]);
    }

    printf("\nPersons (entry, exit):\n");
    for (int i = 0; i < n; i++)
        printf("(%d, %d) ", entry[i], exit_[i]);
    printf("\n\n");

    int peakCount;
    int peakTime = findPeakTime(entry, exit_, n, &peakCount);

    printf("Maximum people present at once: %d\n", peakCount);
    printf("This peak occurs at time: %d\n", peakTime);

    free(entry);
    free(exit_);
    return 0;
}
