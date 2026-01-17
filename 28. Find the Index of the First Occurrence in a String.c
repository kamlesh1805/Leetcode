/*
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

 

Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
 

Constraints:

1 <= haystack.length, needle.length <= 104
haystack and needle consist of only lowercase English characters.
  */

int strStr(char* haystack, char* needle) {
    int i, j, n = 0, m = 0;
    while(haystack[n] != '\0') n++;
    while(needle[m] != '\0') m++;
    if(m == 0) return 0;
    for(i = 0; i <= n - m; i++) {
        for(j = 0; j < m; j++) {
            if(haystack[i + j] != needle[j])
                break;
        }
        if(j == m)
            return i;
    }
    return -1;
}
