#include <stdio.h>

void bestFit(int b[], int m, int f[], int n) {
    int a[n], temp[m];
    for (int i = 0; i < m; i++) temp[i] = b[i];
    for (int i = 0; i < n; i++) a[i] = -1;

    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (temp[j] >= f[i]) {
                if (idx == -1 || temp[idx] > temp[j]) idx = j;
            }
        }
        if (idx != -1) {
            a[i] = idx;
            temp[idx] -= f[i];
        }
    }

    printf("\nBest Fit:\n");
    for (int i = 0; i < n; i++) {
        if (a[i] != -1)
            printf("Block %d (%d) - File %d (%d)\n", a[i] + 1, b[a[i]], i + 1, f[i]);
        else
            printf("File %d (%d) -> Not Allocated\n", i + 1, f[i]);
    }
}

void firstFit(int b[], int m, int f[], int n) {
    int a[n], temp[m];
    for (int i = 0; i < m; i++) temp[i] = b[i];
    for (int i = 0; i < n; i++) a[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (temp[j] >= f[i]) {
                a[i] = j;
                temp[j] -= f[i];
                break;
            }
        }
    }

    printf("\nFirst Fit:\n");
    for (int i = 0; i < n; i++) {
        if (a[i] != -1)
            printf("Block %d (%d) - File %d (%d)\n", a[i] + 1, b[a[i]], i + 1, f[i]);
        else
            printf("File %d (%d) -> Not Allocated\n", i + 1, f[i]);
    }
}

void worstFit(int b[], int m, int f[], int n) {
    int a[n], temp[m];
    for (int i = 0; i < m; i++) temp[i] = b[i];
    for (int i = 0; i < n; i++) a[i] = -1;

    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 0; j < m; j++) {
            if (temp[j] >= f[i]) {
                if (idx == -1 || temp[idx] < temp[j]) idx = j;
            }
        }
        if (idx != -1) {
            a[i] = idx;
            temp[idx] -= f[i];
        }
    }

    printf("\nWorst Fit:\n");
    for (int i = 0; i < n; i++) {
        if (a[i] != -1)
            printf("Block %d (%d) - File %d (%d)\n", a[i] + 1, b[a[i]], i + 1, f[i]);
        else
            printf("File %d (%d) -> Not Allocated\n", i + 1, f[i]);
    }
}

int main() {
    int m, n;
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    printf("Enter the number of files: ");
    scanf("%d", &n);

    int b[m], f[n];
    printf("Enter the sizes of %d blocks: ", m);
    for (int i = 0; i < m; i++) scanf("%d", &b[i]);
    printf("Enter the sizes of %d files: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &f[i]);

    bestFit(b, m, f, n);
    firstFit(b, m, f, n);
    worstFit(b, m, f, n);

    return 0;
}
