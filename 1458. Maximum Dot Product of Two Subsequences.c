/*Given two arrays nums1 and nums2.

Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same length.

A subsequence of a array is a new array which is formed from the original array by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, [2,3,5] is a subsequence of [1,2,3,4,5] while [1,5,3] is not).

Example 1:

Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
Output: 18
Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from nums2.
Their dot product is (2*3 + (-2)*(-6)) = 18.

Example 2:

Input: nums1 = [3,-2], nums2 = [2,-6,7]
Output: 21
Explanation: Take subsequence [3] from nums1 and subsequence [7] from nums2.
Their dot product is (3*7) = 21.

Example 3:

Input: nums1 = [-1,-1], nums2 = [1,1]
Output: -1
Explanation: Take subsequence [-1] from nums1 and subsequence [1] from nums2.
Their dot product is -1.

Constraints:

1 <= nums1.length, nums2.length <= 500
-1000 <= nums1[i], nums2[i] <= 1000*/

long long maxll(long long a, long long b) {
    return a > b ? a : b;
}

int maxDotProduct(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    static long long dp[501][501];

    for (int i = 0; i <= nums1Size; i++)
        for (int j = 0; j <= nums2Size; j++)
            dp[i][j] = LLONG_MIN;

    for (int i = 1; i <= nums1Size; i++) {
        for (int j = 1; j <= nums2Size; j++) {
            long long prod = (long long)nums1[i - 1] * nums2[j - 1];

            long long best = prod;

            if (dp[i - 1][j - 1] != LLONG_MIN)
                best = maxll(best, prod + dp[i - 1][j - 1]);

            best = maxll(best, dp[i - 1][j]);
            best = maxll(best, dp[i][j - 1]);

            dp[i][j] = best;
        }
    }

    return (int)dp[nums1Size][nums2Size];
}
