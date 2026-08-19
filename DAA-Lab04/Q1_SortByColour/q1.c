#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    int colour;
} Item;

void sortByColour(Item arr[], int n) {
    Item *red = malloc(n * sizeof(Item));
    Item *blue = malloc(n * sizeof(Item));
    Item *yellow = malloc(n * sizeof(Item));
    int r = 0, b = 0, y = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i].colour == 0) red[r++] = arr[i];
        else if (arr[i].colour == 1) blue[b++] = arr[i];
        else yellow[y++] = arr[i];
    }

    int idx = 0;
    for (int i = 0; i < r; i++) arr[idx++] = red[i];
    for (int i = 0; i < b; i++) arr[idx++] = blue[i];
    for (int i = 0; i < y; i++) arr[idx++] = yellow[i];

    free(red);
    free(blue);
    free(yellow);
}

const char* colourName(int c) {
    if (c == 0) return "red";
    if (c == 1) return "blue";
    return "yellow";
}

int readColourCode() {
    char buf[20];
    scanf("%19s", buf);
    if (buf[0] == 'r' || buf[0] == 'R' || buf[0] == '0') return 0;
    if (buf[0] == 'b' || buf[0] == 'B' || buf[0] == '1') return 1;
    return 2;
}

int main() {
    int n;
    printf("Enter number of items (n): ");
    scanf("%d", &n);

    Item *arr = malloc(n * sizeof(Item));

    printf("\nEnter the %d items, one at a time.\n", n);
    printf("Items must already be sorted by number (as the problem assumes).\n");
    printf("For colour, type: r (red), b (blue), or y (yellow)\n\n");

    for (int i = 0; i < n; i++) {
        printf("Item %d - number: ", i + 1);
        scanf("%d", &arr[i].number);
        printf("Item %d - colour (r/b/y): ", i + 1);
        arr[i].colour = readColourCode();
    }

    printf("\nBefore sorting by colour:\n");
    for (int i = 0; i < n; i++)
        printf("(%d, %s) ", arr[i].number, colourName(arr[i].colour));
    printf("\n\n");

    sortByColour(arr, n);

    printf("After sorting by colour (numbers stay sorted within each colour):\n");
    for (int i = 0; i < n; i++)
        printf("(%d, %s) ", arr[i].number, colourName(arr[i].colour));
    printf("\n");

    free(arr);
    return 0;
}
