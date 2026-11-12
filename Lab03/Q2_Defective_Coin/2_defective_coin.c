#include <stdio.h>
#include <math.h>

int weight[100];
int weighings = 0;

int weigh(int idx[], int l1, int r1, int l2, int r2) {
    weighings++;
    int sumLeft = 0, sumRight = 0;
    for (int i = l1; i <= r1; i++) sumLeft += weight[idx[i]];
    for (int i = l2; i <= r2; i++) sumRight += weight[idx[i]];

    if (sumLeft == sumRight) return 0;
    if (sumLeft < sumRight) return -1;
    return 1;
}

int findDefective(int idx[], int low, int high, int possiblyHere) {
    if (!possiblyHere) return -1;

    if (low == high) {

        return idx[low];
    }

    int n = high - low + 1;
    int mid = low + n / 2 - 1;
    int leftover = -1;

    int l1 = low, r1 = mid;
    int l2 = mid + 1, r2 = high;

    if (n % 2 != 0) {
        leftover = idx[high];
        r2 = high - 1;
    }

    int result = weigh(idx, l1, r1, l2, r2);

    if (result == 0) {

        if (leftover != -1) {
            int idxPair[2] = { leftover, idx[l1] };
            weighings++;
            if (weight[idxPair[0]] == weight[idxPair[1]])
                return -1;
            else
                return leftover;
        } else {
            return -1;
        }
    } else if (result == -1) {

        return findDefective(idx, l1, r1, 1);
    } else {

        return findDefective(idx, l2, r2, 1);
    }
}

int main() {
    int n;
    printf("Enter number of coins: ");
    scanf("%d", &n);

    int idx[n];
    for (int i = 0; i < n; i++) {
        idx[i] = i + 1;
        weight[i + 1] = 0;
    }

    int choice;
    printf("Is there a defective (lighter) coin? (1 = Yes, 0 = No): ");
    scanf("%d", &choice);

    if (choice == 1) {
        int defCoin;
        printf("Enter the coin number (1 to %d) that is lighter: ", n);
        scanf("%d", &defCoin);
        weight[defCoin] = -1;
    }

    if (n < 2) {
        printf("\nNeed at least 2 coins to test with a balance scale.\n");
        return 0;
    }

    weighings = 0;
    int result = findDefective(idx, 0, n - 1, 1);

    printf("\n--- Result ---\n");
    if (result == -1)
        printf("No defective coin found. All coins are perfect.\n");
    else
        printf("Defective (lighter) coin is: Coin #%d\n", result);

    printf("Number of weighings used: %d\n", weighings);
    printf("(Expected around log2(%d) = %.2f weighings)\n", n,
           n > 0 ? log2((double)n) : 0);

    return 0;
}
