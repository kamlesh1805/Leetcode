/*
  You are given a m x n 2D integer array grid and an integer k. You start at the top-left cell (0, 0) and your goal is to reach the bottom‐right cell (m - 1, n - 1).

There are two types of moves available:

Normal move: You can move right or down from your current cell (i, j), i.e. you can move to (i, j + 1) (right) or (i + 1, j) (down). The cost is the value of the destination cell.

Teleportation: You can teleport from any cell (i, j), to any cell (x, y) such that grid[x][y] <= grid[i][j]; the cost of this move is 0. You may teleport at most k times.

Return the minimum total cost to reach cell (m - 1, n - 1) from (0, 0).

 

Example 1:

Input: grid = [[1,3,3],[2,5,4],[4,3,5]], k = 2

Output: 7

Explanation:

Initially we are at (0, 0) and cost is 0.

Current Position	Move	New Position	Total Cost
(0, 0)	Move Down	(1, 0)	0 + 2 = 2
(1, 0)	Move Right	(1, 1)	2 + 5 = 7
(1, 1)	Teleport to (2, 2)	(2, 2)	7 + 0 = 7
The minimum cost to reach bottom-right cell is 7.

Example 2:

Input: grid = [[1,2],[2,3],[3,4]], k = 1

Output: 9

Explanation:

Initially we are at (0, 0) and cost is 0.

Current Position	Move	New Position	Total Cost
(0, 0)	Move Down	(1, 0)	0 + 2 = 2
(1, 0)	Move Right	(1, 1)	2 + 3 = 5
(1, 1)	Move Down	(2, 1)	5 + 4 = 9
The minimum cost to reach bottom-right cell is 9.

 

Constraints:

2 <= m, n <= 80
m == grid.length
n == grid[i].length
0 <= grid[i][j] <= 104
0 <= k <= 10
  */



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXV 10001

int minCost(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];
    int cells = m * n;
    int *dp = (int*)malloc((k + 1) * cells * sizeof(int));
    for (int i = 0; i < (k + 1) * cells; i++) {
        dp[i] = INT_MAX;
    }

    dp[0] = 0;
    int *best = (int*)malloc(MAXV * sizeof(int));

    for (int t = 0; t <= k; t++) {
        int base = t * cells;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int id = base + r * n + c;
                if (dp[id] == INT_MAX) continue;

                int cost = dp[id];

                if (r + 1 < m) {
                    int nid = base + (r + 1) * n + c;
                    int next = cost + grid[r + 1][c];
                    if (next < dp[nid]) dp[nid] = next;
                }

                if (c + 1 < n) {
                    int nid = base + r * n + (c + 1);
                    int next = cost + grid[r][c + 1];
                    if (next < dp[nid]) dp[nid] = next;
                }
            }
        }

        if (t < k) {
            for (int i = 0; i < MAXV; i++) best[i] = INT_MAX;

            for (int r = 0; r < m; r++) {
                for (int c = 0; c < n; c++) {
                    int id = base + r * n + c;
                    if (dp[id] != INT_MAX) {
                        int v = grid[r][c];
                        if (dp[id] < best[v]) best[v] = dp[id];
                    }
                }
            }
            for (int v = MAXV - 2; v >= 0; v--) {
                if (best[v + 1] < best[v])
                    best[v] = best[v + 1];
            }
            int nextBase = (t + 1) * cells;
            for (int r = 0; r < m; r++) {
                for (int c = 0; c < n; c++) {
                    int v = grid[r][c];
                    int id = nextBase + r * n + c;
                    if (best[v] < dp[id])
                        dp[id] = best[v];
                }
            }
        }
    }

    int ans = INT_MAX;
    int end = (m - 1) * n + (n - 1);
    for (int t = 0; t <= k; t++) {
        int id = t * cells + end;
        if (dp[id] < ans) ans = dp[id];
    }

    free(dp);
    free(best);
    return ans;
}
