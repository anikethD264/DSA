typedef struct {
    int ans[3];
} Answer;

void answerPut(Answer* a, int x) {
    if (x > a->ans[0]) {
        a->ans[2] = a->ans[1];
        a->ans[1] = a->ans[0];
        a->ans[0] = x;
    } else if (x != a->ans[0] && x > a->ans[1]) {
        a->ans[2] = a->ans[1];
        a->ans[1] = x;
    } else if (x != a->ans[0] && x != a->ans[1] && x > a->ans[2]) {
        a->ans[2] = x;
    }
}

int* answerGet(Answer* a, int* returnSize) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (a->ans[i] != 0) {
            count++;
        }
    }

    int* ret = (int*)malloc(count * sizeof(int));
    *returnSize = count;
    int idx = 0;
    for (int i = 0; i < 3; i++) {
        if (a->ans[i] != 0) {
            ret[idx++] = a->ans[i];
        }
    }

    return ret;
}

int* getBiggestThree(int** grid, int gridSize, int* gridColSize,
                     int* returnSize) {
    int m = gridSize, n = gridColSize[0];
    int** sum1 = (int**)malloc((m + 1) * sizeof(int*));
    int** sum2 = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        sum1[i] = (int*)calloc(n + 2, sizeof(int));
        sum2[i] = (int*)calloc(n + 2, sizeof(int));
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            sum1[i][j] = sum1[i - 1][j - 1] + grid[i - 1][j - 1];
            sum2[i][j] = sum2[i - 1][j + 1] + grid[i - 1][j - 1];
        }
    }

    Answer ans = {{0}};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // a single cell is also a rhombus
            answerPut(&ans, grid[i][j]);
            for (int k = i + 2; k < m; k += 2) {
                int ux = i, uy = j;
                int dx = k, dy = j;
                int lx = (i + k) / 2, ly = j - (k - i) / 2;
                int rx = (i + k) / 2, ry = j + (k - i) / 2;
                if (ly < 0 || ry >= n) {
                    break;
                }
                int sum =
                    (sum2[lx + 1][ly + 1] - sum2[ux][uy + 2]) +
                    (sum1[rx + 1][ry + 1] - sum1[ux][uy]) +
                    (sum1[dx + 1][dy + 1] - sum1[lx][ly]) +
                    (sum2[dx + 1][dy + 1] - sum2[rx][ry + 2]) -
                    (grid[ux][uy] + grid[dx][dy] + grid[lx][ly] + grid[rx][ry]);
                answerPut(&ans, sum);
            }
        }
    }

    for (int i = 0; i <= m; i++) {
        free(sum1[i]);
        free(sum2[i]);
    }
    free(sum1);
    free(sum2);

    return answerGet(&ans, returnSize);
}