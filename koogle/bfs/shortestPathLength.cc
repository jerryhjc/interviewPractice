847. Shortest Path Visiting All Nodes

题目大意：求顶点覆盖的最短路径。
An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.
graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.
Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

Example 1:
Input: [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]

Time complexity: O(n*2^n)
Space complexity: O(n*2^n)



int shortestPathLength(vector<vector<int>>& graph) {
    const int n = graph.size();
    const int kAns = (1 << n) - 1;
    queue<pair<int, int>> q;
    vector<vector<int>> visited(n, vector<int>(1 << n));
    for (int i = 0; i < n; ++i)
      q.push({i, 1 << i});
    int steps = 0;
    while (!q.empty()) {
      int s = q.size();
      while (s--) {
        auto p = q.front(); 
        q.pop();
        int node = p.first;
        int state = p.second;
        if (state == kAns) return steps;   
        if (visited[node][state]) continue;
        visited[node][state] = 1;
        for (int next : graph[node])
          q.push({next, state | (1 << next)});
      }
      ++steps;
    }
    return -1;
  }




