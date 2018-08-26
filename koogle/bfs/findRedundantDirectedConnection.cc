Redundant Connection II 冗余的连接之二  

In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.
The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.
Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

这道题是之前那道Redundant Connection的拓展，那道题给的是无向图，只需要删掉组成环的最后一条边即可，归根到底就是检测环就行了。而这道题给我们的是有向图，那么整个就复杂多了，因为有多种情况存在. 

第一种：无环，但是有结点入度为2的结点（结点3）
[[1,2], [1,3], [2,3]]

第二种：有环，没有入度为2的结点
[[1,2], [2,3], [3,4], [4,1], [1,5]]

第三种：有环，且有入度为2的结点（结点1）
[[1,2],[2,3],[3,1],[1,4]]

对于这三种情况的处理方法各不相同，首先对于第一种情况，我们返回的产生入度为2的后加入的那条边[2, 3]，而对于第二种情况，我们返回的是刚好组成环的最后加入的那条边[4, 1]，最后对于第三种情况我们返回的是组成环，且组成入度为2的那条边[3, 1]。

明白了这些，我们先来找入度为2的点，如果有的话，那么我们将当前产生入度为2的后加入的那条边标记为second，前一条边标记为first。然后我们来找环，为了方便起见，找环使用联合查找Union Find的方法，可参见Redundant Connection中的解法三。当我们找到了环之后，如果first不存在，说明是第二种情况，我们返回刚好组成环的最后加入的那条边。如果first存在，说明是第三种情况，我们返回first。如果没有环存在，说明是第一种情况，我们返回second

    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();                       
        vector<int> root(n + 1, 0), first, second;
        
        for (auto& edge : edges) {
            if (root[edge[1]] == 0) {
                root[edge[1]] = edge[0];
            } else {   
                first = {root[edge[1]], edge[1]};
                second = edge;
                edge[1] = 0;     
            }
        }
        
        for (int i = 0; i <= n; ++i) 
            root[i] = i;
        
        for (auto& edge : edges) {
            if (edge[1] == 0) 
                continue;
            int x = find(root, edge[0]), y = find(root, edge[1]);
            if (x == y) 
                return first.empty() ? edge : first;
            root[x] = y;
        }

        return second;
    }


    int find(vector<int>& root, int i) {
    	// while (root[i] != 0)  // 有问题  
        while (i != root[i]) {
            i = root[i];
            // root[i] == i;   // 有问题 
        }
    	return i;
	}

//////////////////////////////////////  

Redundant Connection 冗余的连接   

In this problem, a tree is an undirected graph that is connected and has no cycles.
The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.
The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.
Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]

这道题给我们了一个无向图，让我们删掉组成环的最后一条边，其实这道题跟之前那道Graph Valid Tree基本没什么区别  

其实这道题最好的解法使用Union Find来做，论坛上清一色的都是用这种解法来做的，像博主用DFS和BFS这么清新脱俗的方法还真不多:) 其实Union Find的核心思想并不是很难理解，首先我们建立一个长度为(n+1)的数组root，由于这道题并没有明确的说明n是多少，只是说了输入的二位数组的长度不超过1000，那么n绝对不会超过2000，我们加1的原因是由于结点值是从1开始的，而数组是从0开始的，我们懒得转换了，就多加一位得了。我们将这个数组都初始化为-1，有些人喜欢初始化为i，都可以。开始表示每个结点都是一个单独的组，所谓的Union Find就是要让结点之间建立关联，比如若root[1] = 2，就表示结点1和结点2是相连的，root[2] = 3表示结点2和结点3是相连的，如果我们此时新加一条边[1, 3]的话，我们通过root[1]得到2，再通过root[2]得到3，说明结点1有另一条路径能到结点3，这样就说明环是存在的；如果没有这条路径，那么我们要将结点1和结点3关联起来，让root[1] = 3即可


vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size(); 
    vector<int> root(n + 1, 0);
    // vector<int> root(2001, -1);
    for (auto edge : edges) {
        int x = find(root, edge[0]), y = find(root, edge[1]);
        if (x == y) return edge;   
        root[x] = y;  // merge x and y    
    }
    return {};
}

// iterative 版本   
int find(vector<int>& root, int i) {
    while (root[i] != 0) {
    // while (root[i] != i) {  // 有问题, 注意和上文比较   
        i = root[i];
    }
    return i;
}


// recursion 版本, get the root of i 
int find(vector<int>& root, int i) {
        // return i == root[i] ? i : find(root, root[i]);
    if (i != root[i]) 
        return find(root, root[i]); 
    return i; 
}



/////////////////////////////////////////////////////////////////  
// bfs 

既然递归能做，一般来说迭代也木有问题。但是由于BFS的遍历机制和DFS不同，所以没法采用利用变量pre来避免上面所说的死循环(不是很确定，可能是博主没想出来，有做出来的请在评论区贴上代码)，所以我们采用一个集合来记录遍历过的结点，如果该结点已经遍历过了，那么直接跳过即可，否则我们就把该结点加入queue和集合，继续循环

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    unordered_map<int, unordered_set<int>> m;
    for (auto edge : edges) {
        queue<int> q{{edge[0]}};
        unordered_set<int> s{{edge[0]}};
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            if (m[t].count(edge[1])) return edge;
            for (int num : m[t]) {
                if (s.count(num)) continue;
                q.push(num);
                s.insert(num);
            }
        }
        m[edge[0]].insert(edge[1]);
        m[edge[1]].insert(edge[0]);
    }
    return {};
}


/////////////////////////////////////////////////
// dfs 

这道题给我们了一个无向图，让我们删掉组成环的最后一条边，其实这道题跟之前那道Graph Valid Tree基本没什么区别，三种解法都基本相同。博主觉得老题稍微变一下就是一道新题，而onsite遇到原题的概率很小，大多情况下都会稍稍变一下，所以举一反三的能力真的很重要，要完全吃透一道题也不太容易，需要多下功夫。我们首先来看递归的解法，这种解法的思路是，每加入一条边，就进行环检测，一旦发现了环，就返回当前边。对于无向图，我们还是用邻接表来保存，建立每个结点和其所有邻接点的映射，由于两个结点之间不算有环，所以我们要避免这种情况 1->{2}, 2->{1}的死循环，所以我们用一个变量pre记录上一次递归的结点，比如上一次遍历的是结点1，那么在遍历结点2的邻接表时，就不会再次进入结点1了，这样有效的避免了死循环，使其能返回正确的结果

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    unordered_map<int, unordered_set<int>> m;
    for (auto edge : edges) {
        if (hasCycle(edge[0], edge[1], m, -1)) return edge;
        m[edge[0]].insert(edge[1]);
        m[edge[1]].insert(edge[0]);
    }
    return {};
}

bool hasCycle(int cur, int target, unordered_map<int, unordered_set<int>>& m, int pre) {
    if (m[cur].count(target)) return true;
    for (int num : m[cur]) {
        if (num == pre) continue;
        if (hasCycle(num, target, m, cur)) return true;
    }
    return false;
}





