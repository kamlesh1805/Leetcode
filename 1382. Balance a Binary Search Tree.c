/*
Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.

A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.

 

Example 1:


Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.
Example 2:


Input: root = [2,1,3]
Output: [2,1,3]
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
1 <= Node.val <= 105

  */


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void inorder(struct TreeNode* root, struct TreeNode** arr, int* size) {
    if (root == NULL) return;

    inorder(root->left, arr, size);
    arr[(*size)++] = root;
    inorder(root->right, arr, size);
}

struct TreeNode* buildBalanced(struct TreeNode** arr, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;
    struct TreeNode* root = arr[mid];

    root->left = buildBalanced(arr, start, mid - 1);
    root->right = buildBalanced(arr, mid + 1, end);

    return root;
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    if (root == NULL) return NULL;

    struct TreeNode* arr[10001];
    int size = 0;

    inorder(root, arr, &size);
    return buildBalanced(arr, 0, size - 1);
}
