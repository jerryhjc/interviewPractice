310. Minimum Height Trees

For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Example 1 :
Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]
        0
        |
        1
       / \
      2   3 
Output: [1]

Example 2 :
Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
     0  1  2
      \ | /
        3
        |
        4
        |
        5 
Output: [3, 4]

由于LeetCode中的树的题目主要都是针对于二叉树的，而这道题虽说是树但其实本质是想考察图的知识，这道题刚开始在拿到的时候，我最先想到的解法是遍历的点，以每个点都当做根节点，算出高度，然后找出最小的，但是一时半会又写不出程序来，于是上网看看大家的解法，发现大家推崇的方法是一个类似剥洋葱的方法，就是一层一层的褪去叶节点，最后剩下的一个或两个节点就是我们要求的最小高度树的根节点，这种思路非常的巧妙，而且实现起来也不难，跟之前那到课程清单的题一样，我们需要建立一个图g，是一个二维数组，其中g[i]是一个一维数组，保存了i节点可以到达的所有节点。我们开始将所有只有一个连接边的节点(叶节点)都存入到一个队列queue中，然后我们遍历每一个叶节点，通过图来找到和其相连的节点，并且在其相连节点的集合中将该叶节点删去，如果删完后此节点也也变成一个叶节点了，加入队列中，再下一轮删除。那么我们删到什么时候呢，当节点数小于等于2时候停止，此时剩下的一个或两个节点就是我们要求的最小高度树的根节点啦


vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
    if (n == 1) return {0};
    vector<int> res;
    vector<unordered_set<int>> adj(n);
    queue<int> q;

    for (auto edge : edges) {
        adj[edge.first].insert(edge.second);
        adj[edge.second].insert(edge.first);
    }

    for (int i = 0; i < n; ++i) {
        if (adj[i].size() == 1) q.push(i); // q里存的都是叶节点
    }

//当节点数小于等于2时候停止，此时剩下的一个或两个节点就是我们要求的最小高度树的根节点
    while (n > 2) {
        int size = q.size();
        n -= size;
        for (int i = 0; i < size; ++i) {
            int t = q.front(); q.pop();  // t 是叶子节点
            for (auto a : adj[t]) {
                adj[a].erase(t);  // a 是 t 的唯一链接节点 ; 与叶子节点t连接的节点a 删除叶子节点t     
                if (adj[a].size() == 1) q.push(a);
            }
        }
    }

    while (!q.empty()) {
        res.push_back(q.front()); 
        q.pop();
    }

    return res;
}








