/*

You are given a 0-indexed array of integers nums of length n, and two positive integers k and dist.

The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.

You need to divide nums into k disjoint contiguous subarrays, such that the difference between the starting index of the second subarray and the starting index of the kth subarray should be less than or equal to dist. In other words, if you divide nums into the subarrays nums[0..(i1 - 1)], nums[i1..(i2 - 1)], ..., nums[ik-1..(n - 1)], then ik-1 - i1 <= dist.

Return the minimum possible sum of the cost of these subarrays.

 

Example 1:

Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
Output: 5
Explanation: The best possible way to divide nums into 3 subarrays is: [1,3], [2,6,4], and [2]. This choice is valid because ik-1 - i1 is 5 - 2 = 3 which is equal to dist. The total cost is nums[0] + nums[2] + nums[5] which is 1 + 2 + 2 = 5.
It can be shown that there is no possible way to divide nums into 3 subarrays at a cost lower than 5.
Example 2:

Input: nums = [10,1,2,2,2,1], k = 4, dist = 3
Output: 15
Explanation: The best possible way to divide nums into 4 subarrays is: [10], [1], [2], and [2,2,1]. This choice is valid because ik-1 - i1 is 3 - 1 = 2 which is less than dist. The total cost is nums[0] + nums[1] + nums[2] + nums[3] which is 10 + 1 + 2 + 2 = 15.
The division [10], [1], [2,2,2], and [1] is not valid, because the difference between ik-1 and i1 is 5 - 1 = 4, which is greater than dist.
It can be shown that there is no possible way to divide nums into 4 subarrays at a cost lower than 15.
Example 3:

Input: nums = [10,8,18,9], k = 3, dist = 1
Output: 36
Explanation: The best possible way to divide nums into 4 subarrays is: [10], [8], and [18,9]. This choice is valid because ik-1 - i1 is 2 - 1 = 1 which is equal to dist.The total cost is nums[0] + nums[1] + nums[2] which is 10 + 8 + 18 = 36.
The division [10], [8,18], and [9] is not valid, because the difference between ik-1 and i1 is 3 - 1 = 2, which is greater than dist.
It can be shown that there is no possible way to divide nums into 3 subarrays at a cost lower than 36.
 

Constraints:

3 <= n <= 105
1 <= nums[i] <= 109
3 <= k <= n
k - 2 <= dist <= n - 2


*/



long long bitSum[100005];
int bitCount[100005];
int sortedUnique[100005];

int cmp(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

long long minimumCost(int* nums, int numsSize, int k, int dist) {
    int* temp = malloc(numsSize * sizeof(int));
    memcpy(temp, nums, numsSize * sizeof(int));
    qsort(temp, numsSize, sizeof(int), cmp);
    int m = 0;
    for (int i = 0; i < numsSize; i++)
        if (i == 0 || temp[i] != temp[i - 1]) sortedUnique[m++] = temp[i];
    free(temp);

    memset(bitSum, 0, (m + 1) * sizeof(long long));
    memset(bitCount, 0, (m + 1) * sizeof(int));

    void update(int r, int v, int c) {
        for (; r <= m; r += r & -r) { bitSum[r] += v; bitCount[r] += c; }
    }

    int getRank(int v) {
        int l = 0, h = m - 1;
        while (l <= h) {
            int mid = l + (h - l) / 2;
            if (sortedUnique[mid] == v) return mid + 1;
            if (sortedUnique[mid] < v) l = mid + 1; else h = mid - 1;
        }
        return -1;
    }

    int maxP = 1; while ((maxP << 1) <= m) maxP <<= 1;
    long long minExtra = LLONG_MAX;
    for (int i = 1; i < numsSize; i++) {
        update(getRank(nums[i]), nums[i], 1);
        if (i > dist + 1) update(getRank(nums[i - dist - 1]), -nums[i - dist - 1], -1);
        if (i >= k - 1) {
            int idx = 0, cc = 0; long long cs = 0;
            for (int p = maxP; p > 0; p >>= 1) {
                if (idx + p <= m && cc + bitCount[idx + p] < k - 1) {
                    idx += p; cc += bitCount[idx]; cs += bitSum[idx];
                }
            }
            if (cc < k - 1) cs += (long long)(k - 1 - cc) * sortedUnique[idx];
            if (cs < minExtra) minExtra = cs;
        }
    }
    return nums[0] + minExtra;
}



