Binary Tree Postorder Traversal 二叉树的后序遍历

由于后序遍历的顺序是左-右-根，而先序遍历的顺序是根-左-右，二者其实还是很相近的，我们可以先在先序遍历的方法上做些小改动，使其遍历顺序变为根-右-左，然后翻转一下，就是左-右-根啦，翻转的方法我们使用反向Q，哦不，是反向加入结果res，每次都在结果res的开头加入结点值，而改变先序遍历的顺序就只要该遍历一下入栈顺序，先左后右，这样出栈处理的时候就是先右后左啦，

vector<int> postorderTraversal(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
    stack<TreeNode*> s;
    s.push(root); 

    while (!s.empty()) {
        TreeNode *t = s.top(); s.pop();
        res.insert(res.begin(), t->val);
        if (t->left) s.push(t->left);
        if (t->right) s.push(t->right);
    }
    return res;
}


