Recover Binary Search Tree 复原二叉搜索树  

Two elements of a binary search tree (BST) are swapped by mistake.
Recover the tree without changing its structure.

Example 1:
Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2

void recoverTree(TreeNode* root) {
    vector<int> vec;
    vector<TreeNode*> vec1; 
    dfs(root, vec, vec1); 
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); ++i) {
        vec1[i]->val = vec[i]; 
    }
}

void dfs(TreeNode* node, vector<int>& vec, vector<TreeNode*>& vec1) {
    if (!node) return; 
    dfs(node->left, vec, vec1); 
    vec.push_back(node->val);
    vec1.push_back(node);
    dfs(node->right, vec, vec1);
}

////////////////////////////////////  

Follow up:
A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?


 void recoverTree(TreeNode* root) {
        //中序遍历这树，找到第一个前>后较大的数为first，找第二个前>后的较小的数为second，两个找到了就调换位置。       
        if(root == NULL) return;
        TreeNode* first = NULL;
        TreeNode* second = NULL;
        TreeNode* prev = NULL;
        
        TreeNode* cur = root;
        std::stack<TreeNode*> s{};
        while(!s.empty() || cur != NULL) {
            if(cur != NULL) {
                s.push(cur);
                cur = cur->left;
            }
            else {
                cur = s.top(); s.pop();
                if(prev != NULL && cur->val <= prev->val) {
                    if(first == NULL) 
                        first = prev;
                    second = cur;
                }
                prev = cur;
                cur = cur->right;
            }
        }
        if(first != NULL && second != NULL)
            swap(first->val, second->val);
        
        return;
    }

    



