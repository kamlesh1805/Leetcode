/*Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Example 1:

Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
Example 2:

Input: matrix = [["0"]]
Output: 0
Example 3:

Input: matrix = [["1"]]
Output: 1
 

Constraints:

rows == matrix.length
cols == matrix[i].length
1 <= rows, cols <= 200
matrix[i][j] is '0' or '1'.*/


int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) 
{
     if (matrixSize == 0) return 0;

    int cols = matrixColSize[0];
    int heights[cols];
    for (int i = 0; i < cols; i++) heights[i] = 0;

    int stack[cols + 1];
    int maxArea = 0;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == '1')
                heights[j]++;
            else
                heights[j] = 0;
        }

        int top = -1;
        for (int j = 0; j <= cols; j++) {
            int currHeight = (j == cols) ? 0 : heights[j];
            while (top != -1 && currHeight < heights[stack[top]]) {
                int h = heights[stack[top--]];
                int w = (top == -1) ? j : j - stack[top] - 1;
                int area = h * w;
                if (area > maxArea) maxArea = area;
            }
            stack[++top] = j;
        }
    }

    return maxArea;
    
}
