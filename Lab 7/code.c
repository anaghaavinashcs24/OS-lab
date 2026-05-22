#include <stdio.h>

#define MAX 50

int checkHit(int frames[], int frameSize, int page) {
    for (int i = 0; i < frameSize; i++)
        if (frames[i] == page)
            return 1;
    return 0;
}

void printFrames(int frames[], int frameSize) {
    for (int i = 0; i < frameSize; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
}

int fifo(int pages[], int n, int frameSize) {
    int frames[10], index = 0, faults = 0;

    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    printf("\n\n===== FIFO WORKING =====\n");

    for (int i = 0; i < n; i++) {
        printf("Page %d -> ", pages[i]);

        if (!checkHit(frames, frameSize, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % frameSize;
            faults++;

            printf("FAULT | ");
            printFrames(frames, frameSize);
        } else {
            printf("HIT   | ");
            for (int j = 0; j < frameSize; j++)
                printf("- ");
        }

        printf("\n");
    }

    return faults;
}

int lru(int pages[], int n, int frameSize) {
    int frames[10], time[10];
    int faults = 0, counter = 0;

    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\n\n===== LRU WORKING =====\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int hit = 0;

        printf("Page %d -> ", page);

        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                hit = 1;
                time[j] = ++counter;
                break;
            }
        }

        if (!hit) {
            int pos = 0;

            for (int j = 1; j < frameSize; j++) {
                if (time[j] < time[pos])
                    pos = j;
            }

            frames[pos] = page;
            time[pos] = ++counter;
            faults++;

            printf("FAULT | ");
            printFrames(frames, frameSize);
        } else {
            printf("HIT   | ");
            for (int j = 0; j < frameSize; j++)
                printf("- ");
        }

        printf("\n");
    }

    return faults;
}

int optimal(int pages[], int n, int frameSize) {
    int frames[10];
    int faults = 0;

    for (int i = 0; i < frameSize; i++)
        frames[i] = -1;

    printf("\n\n===== OPTIMAL WORKING =====\n");

    for (int i = 0; i < n; i++) {

        printf("Page %d -> ", pages[i]);

        if (checkHit(frames, frameSize, pages[i])) {
            printf("HIT   | ");
            for (int j = 0; j < frameSize; j++)
                printf("- ");
            printf("\n");
            continue;
        }

        int empty = -1;

        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == -1) {
                empty = j;
                break;
            }
        }

        if (empty != -1) {
            frames[empty] = pages[i];
        } else {
            int farthest = -1, replace = 0;

            for (int j = 0; j < frameSize; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k])
                        break;
                }

                if (k > farthest) {
                    farthest = k;
                    replace = j;
                }
            }

            frames[replace] = pages[i];
        }

        faults++;

        printf("FAULT | ");
        printFrames(frames, frameSize);
        printf("\n");
    }

    return faults;
}

int main() {
    int pages[MAX], n, frameSize;
    int fifoF, lruF, optF;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Choose number of page frames (3 or 4): ");
    scanf("%d", &frameSize);

    if (frameSize != 3 && frameSize != 4) {
        printf("Invalid choice! Only 3 or 4 allowed.\n");
        return 0;
    }

    fifoF = fifo(pages, n, frameSize);
    lruF = lru(pages, n, frameSize);
    optF = optimal(pages, n, frameSize);

    printf("\n\n===== FINAL RESULT =====\n");
    printf("FIFO     : %d faults\n", fifoF);
    printf("LRU      : %d faults\n", lruF);
    printf("OPTIMAL  : %d faults\n", optF);

    printf("\n===== BEST ALGORITHM =====\n");

    if (fifoF <= lruF && fifoF <= optF)
        printf("FIFO is best\n");
    else if (lruF <= fifoF && lruF <= optF)
        printf("LRU is best\n");
    else
        printf("Optimal is best\n");

    printf("\nFrames used: %d\n", frameSize);

    return 0;
}
