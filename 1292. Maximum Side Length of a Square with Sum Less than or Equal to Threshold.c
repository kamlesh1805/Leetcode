/*
Given a m x n matrix mat and an integer threshold, return the maximum side-length of a square with a sum less than or equal to threshold or return 0 if there is no such square.

 

Example 1:


Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
Output: 2
Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
Example 2:

Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
Output: 0
 

Constraints:

m == mat.length
n == mat[i].length
1 <= m, n <= 300
0 <= mat[i][j] <= 104
0 <= threshold <= 105
  */



int maxSideLength(int** mat, int matSize, int* matColSize, int threshold) {
    int m = matSize;
    int n = matColSize[0];

    int** pre = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        pre[i] = (int*)calloc(n + 1, sizeof(int));
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            pre[i][j] = mat[i-1][j-1]
                      + pre[i-1][j]
                      + pre[i][j-1]
                      - pre[i-1][j-1];
        }
    }

    int left = 1, right = m < n ? m : n, ans = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        int found = 0;

        for (int i = 0; i + mid <= m && !found; i++) {
            for (int j = 0; j + mid <= n; j++) {
                int sum = pre[i+mid][j+mid]
                        - pre[i][j+mid]
                        - pre[i+mid][j]
                        + pre[i][j];
                if (sum <= threshold) {
                    found = 1;
                    break;
                }
            }
        }

        if (found) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    for (int i = 0; i <= m; i++) {
        free(pre[i]);
    }
    free(pre);

    return ans;
}
