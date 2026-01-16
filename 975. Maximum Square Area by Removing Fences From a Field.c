/*2975. Maximum Square Area by Removing Fences From a Field
Medium
Topics
premium lock icon
Companies
Hint
There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing some horizontal and vertical fences given in arrays hFences and vFences respectively.

Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences are from the coordinates (1, vFences[i]) to (m, vFences[i]).

Return the maximum area of a square field that can be formed by removing some fences (possibly none) or -1 if it is impossible to make a square field.

Since the answer may be large, return it modulo 109 + 7.

Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences cannot be removed.

 

Example 1:



Input: m = 4, n = 3, hFences = [2,3], vFences = [2]
Output: 4
Explanation: Removing the horizontal fence at 2 and the vertical fence at 2 will give a square field of area 4.
Example 2:



Input: m = 6, n = 7, hFences = [2], vFences = [4]
Output: -1
Explanation: It can be proved that there is no way to create a square field by removing fences.
 

Constraints:

3 <= m, n <= 109
1 <= hFences.length, vFences.length <= 600
1 < hFences[i] < m
1 < vFences[i] < n
hFences and vFences are unique.*/




int maximizeSquareArea(int m, int n, int* hFences, int hFencesSize,
                       int* vFences, int vFencesSize) {
    const int MOD = 1000000007;

    int cmp(const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    }

    int hSize = hFencesSize + 2;
    int vSize = vFencesSize + 2;

    int* h = (int*)malloc(hSize * sizeof(int));
    int* v = (int*)malloc(vSize * sizeof(int));

    h[0] = 1; 
    h[1] = m;
    for (int i = 0; i < hFencesSize; i++) h[i + 2] = hFences[i];

    v[0] = 1; 
    v[1] = n;
    for (int i = 0; i < vFencesSize; i++) v[i + 2] = vFences[i];

    qsort(h, hSize, sizeof(int), cmp);
    qsort(v, vSize, sizeof(int), cmp);

    int* hDist = (int*)malloc(hSize * hSize * sizeof(int));
    int* vDist = (int*)malloc(vSize * vSize * sizeof(int));
    int hc = 0, vc = 0;

    for (int i = 0; i < hSize; i++)
        for (int j = i + 1; j < hSize; j++)
            hDist[hc++] = h[j] - h[i];

    for (int i = 0; i < vSize; i++)
        for (int j = i + 1; j < vSize; j++)
            vDist[vc++] = v[j] - v[i];

    qsort(hDist, hc, sizeof(int), cmp);
    qsort(vDist, vc, sizeof(int), cmp);

    int i = hc - 1, j = vc - 1;
    while (i >= 0 && j >= 0) {
        if (hDist[i] == vDist[j]) {
            long long d = hDist[i];
            return (int)((d * d) % MOD);
        }
        if (hDist[i] > vDist[j]) i--;
        else j--;
    }

    return -1;
}
