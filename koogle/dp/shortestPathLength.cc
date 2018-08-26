847. Shortest Path Visiting All Nodes

An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.
graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.
Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

 
Example 1:
Input: [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]

Example 2:
Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]

// Time complexity: O(n*2^n)
// Space complexity: O(n*2^n)
int shortestPathLength(vector<vector<int>>& graph) {
    const int kAns = (1 << (graph.size())) - 1;    
    queue<pair<int, int>> q;
    unordered_set<int> visited; // (cur_node << 16) | state
    for (int i = 0; i < graph.size(); ++i)
      q.push({i, 1 << i});
    int steps = 0;
    while (!q.empty()) {
      int s = q.size();      
      while (s--) {
        auto p = q.front(); 
        q.pop();
        int n = p.first;
        int state = p.second;
        if (state == kAns) return steps;
        int key = (n << 16) | state;
        if (visited.count(key)) continue;
        visited.insert(key);
        for (int next : graph[n])
          q.push({next, state | (1 << next)});
      }
      ++steps;
    }
    return -1;
}


//////////////////////////////////////////////////// 


int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size();
    
    vector<int> degree(n, 0);
    for (int i = 0; i < n; ++i) {
        degree[i] = graph[i].size();
    }
    
    auto cmp = [&](int l, int r) { return degree[l] < degree[r]; };
    
    for (auto& v : graph) {
        sort(v.begin(), v.end(), cmp); //greedy - search the node with less neighours first
    }
    
    int res = INT_MAX;
    //not sure if this method is always correct, but it passes all the test cases so far...
    for (int i = 0; i < n; ++i) {
        vector<bool> visited(n, false);
        int maxDepth = 0;
        int len = search(graph, i, visited, 0, maxDepth); //len is the length of cycle visiting all nodes, maxDepth is the longest path length from i to a node
        
        res = min(res, len - maxDepth);
        
    }

    return res;
}


int search(vector<vector<int>>& graph, int i, vector<bool>& visited, int depth, int& maxDepth) {
    visited[i] = true;
    
    maxDepth = max(maxDepth, depth);
    int res = 0;
    
    for (auto j : graph[i]) {
        if (!visited[j]) {
            res += 1 + search(graph, j, visited, depth + 1, maxDepth) + 1;
        }
    }
    
    return res;
}


