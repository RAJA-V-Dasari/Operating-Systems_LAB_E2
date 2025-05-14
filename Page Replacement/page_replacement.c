#include <stdio.h>

void fifo(int frames[], int m, int n, int ref[]) {
    int pageFaults = 0, index = 0;
    printf("FIFO:\n");
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < m; j++) {
            if (frames[j] == ref[i]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            frames[index] = ref[i];
            index = (index + 1) % m;
            pageFaults++;
        }
        printf("Iteration %d:", i + 1);
        for (int k = 0; k < m; k++) {
            if (frames[k] != -1) printf("%d ", frames[k]);
            else printf("  ");
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n\n", pageFaults);
}

void lru(int frames[], int m, int n, int ref[]) {
    int time[m], counter = 0, faults = 0, pos;
    for (int i = 0; i < m; ++i) frames[i] = -1;
    printf("LRU:\n");
    for (int i = 0; i < n; ++i) {
        int found = 0;
        for (int j = 0; j < m; ++j) {
            if (frames[j] == ref[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }
        }

        if (!found) {
            pos = -1;
            for (int j = 0; j < m; ++j) {
                if (frames[j] == -1) {
                    frames[j] = ref[i];
                    time[j] = ++counter;
                    found = 1;
                    faults++;
                    break;
                }
            }

            if (!found) {
                int minTime = time[0], pos = 0;
                for (int j = 1; j < m; j++) {
                    if (time[j] < minTime) {
                        minTime = time[j];
                        pos = j;
                    }
                }
                frames[pos] = ref[i];
                time[pos] = ++counter;
                faults++;
            }
        }

        printf("Iteration %d:", i + 1);
        for (int j = 0; j < m; ++j) {
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("  ");
        }
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n\n", faults);
}

void optimal(int frames[], int m, int n, int ref[]) {
    int pageFaults = 0;
    printf("Optimal:\n");

    for (int i = 0; i < m; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int flag = 0, farthestIdx = -1, farthestDist = -1;

        for (int j = 0; j < m; j++) {
            if (frames[j] == ref[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            pageFaults++;

            int emptySlotIdx = -1;
            for (int j = 0; j < m; j++) {
                if (frames[j] == -1) {
                    emptySlotIdx = j;
                    break;
                }
            }

            if (emptySlotIdx != -1) {
                frames[emptySlotIdx] = ref[i];
            } else {
                for (int j = 0; j < m; j++) {
                    int tempDist = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (frames[j] == ref[k]) {
                            tempDist = k;
                            break;
                        }
                    }

                    if (tempDist == -1) {
                        farthestIdx = j;
                        break;
                    }

                    if (tempDist > farthestDist) {
                        farthestDist = tempDist;
                        farthestIdx = j;
                    }
                }

                frames[farthestIdx] = ref[i];
            }
        }

        printf("Iteration %d: ", i + 1);
        for (int k = 0; k < m; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("  ");
        }
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n\n", pageFaults);
}

int main() {
    int m, n;
    printf("Enter the number of frames: ");
    scanf("%d", &m);
    printf("Enter the length of the reference string: ");
    scanf("%d", &n);

    int ref[n];
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ref[i]);
    }

    int frames[m];
    for (int i = 0; i < m; i++) frames[i] = -1;

    fifo(frames, m, n, ref);
    for (int i = 0; i < m; i++) frames[i] = -1;
    lru(frames, m, n, ref);
    for (int i = 0; i < m; i++) frames[i] = -1;
    optimal(frames, m, n, ref);

    return 0;
}

