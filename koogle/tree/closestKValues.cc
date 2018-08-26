Closest Binary Search Tree Value II 最近的二分搜索树的值之二  

Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.
Note:
Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

还有一种解法是直接在中序遍历的过程中完成比较，当遍历到一个节点时，如果此时结果数组不到k个，我们直接将此节点值加入res中，如果该节点值和目标值的差值的绝对值小于res的首元素和目标值差值的绝对值，说明当前值更靠近目标值，则将首元素删除，末尾加上当前节点值，反之的话说明当前值比res中所有的值都更偏离目标值，由于中序遍历的特性，之后的值会更加的遍历，所以此时直接返回最终结果即可

vector<int> closestKValues(TreeNode* root, double target, int k) {
    vector<int> res;
    inorder(root, target, k, res);
    return res;
}

void inorder(TreeNode *root, double target, int k, vector<int> &res) {
    if (!root) return;
    inorder(root->left, target, k, res);
    if (res.size() < k) res.push_back(root->val);
    else if (abs(root->val - target) < abs(res[0] - target)) {
        res.erase(res.begin());
        res.push_back(root->val);
    } else return;
    inorder(root->right, target, k, res);
}


