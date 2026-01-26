/*

Given an array of distinct integers arr, find all pairs of elements with the minimum absolute difference of any two elements.

Return a list of pairs in ascending order(with respect to pairs), each pair [a, b] follows

a, b are from arr
a < b
b - a equals to the minimum absolute difference of any two elements in arr
 

Example 1:

Input: arr = [4,2,1,3]
Output: [[1,2],[2,3],[3,4]]
Explanation: The minimum absolute difference is 1. List all pairs with difference equal to 1 in ascending order.
Example 2:

Input: arr = [1,3,6,10,15]
Output: [[1,3]]
Example 3:

Input: arr = [3,8,-10,23,19,-4,-14,27]
Output: [[-14,-10],[19,23],[23,27]]
 

Constraints:

2 <= arr.length <= 105
-106 <= arr[i] <= 106

  */


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    qsort(arr, arrSize, sizeof(int), cmp);

    int minDiff = INT_MAX;
    for (int i = 1; i < arrSize; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff < minDiff)
            minDiff = diff;
    }

    int count = 0;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] - arr[i - 1] == minDiff)
            count++;
    }

    int** result = (int**)malloc(count * sizeof(int*));
    *returnColumnSizes = (int*)malloc(count * sizeof(int));
    *returnSize = count;

    int idx = 0;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] - arr[i - 1] == minDiff) {
            result[idx] = (int*)malloc(2 * sizeof(int));
            result[idx][0] = arr[i - 1];
            result[idx][1] = arr[i];
            (*returnColumnSizes)[idx] = 2;
            idx++;
        }
    }

    return result;
}
