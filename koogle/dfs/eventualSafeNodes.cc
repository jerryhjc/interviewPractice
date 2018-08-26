
LeetCode 802. Find Eventual Safe States  
题目大意：给一个有向图，找出所有不可能进入环的节点。

In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.

Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped at a terminal node in less than K steps.

Which nodes are eventually safe?  Return them as an array in sorted order.

The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.

Example:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Here is a diagram of the above graph.
 


alg: 题目大意：给一个有向图，找出所有不可能进入环的节点。
A node is safe if and only if: itself and all of its neighbors do not have any cycles.
Time complexity: O(V + E)
Space complexity: O(V + E)


 enum State {UNKNOWN, VISITING, SAFE, UNSAFE};

 vector<int> eventualSafeNodes(vector<vector<int>>& graph) {    
    vector<State> states(graph.size(), UNKNOWN);   
    vector<int> res;

    for (int i = 0; i < graph.size(); ++i)      
      if (dfs(graph, i, states) == SAFE)
        res.push_back(i);

    return res;
  }

  State dfs(const vector<vector<int>>& g, int cur, vector<State>& states) {
    if (states[cur] == VISITING)  
      return states[cur] = UNSAFE; 

    if (states[cur] != UNKNOWN)
      return states[cur];

    states[cur] = VISITING;

    for (int next : g[cur])
      if (dfs(g, next, states) == UNSAFE)   // 把所有unsafe的点都连起来 (进入递归), 即unsafe的点形成一个环
        return states[cur] = UNSAFE;

    return states[cur] = SAFE;
  }


////////////////////////////////////  
// dfs + dp; recursion 
  
vector<int> eventualSafeNodes(vector<vector<int>>& graph) {

    vector<int> dp(graph.size(), 0);
    for (int i = 0; i < graph.size(); i++) {
        if (!dp[i])
            dfs(graph, dp, i);
    }
    
    vector<int> res;
    for (int i = 0; i < dp.size(); i++) {
        if (dp[i] == 2)
            res.push_back(i);
    }
    return res;
}


int dfs(vector<vector<int>>& graph, vector<int> &dp, int i) {
    if (dp[i] != 0)      // 若color[i]之前访问过了, 有loop, 则返回 
        return dp[i];
    
    dp[i] = 1;
    int color = 2;
    for (auto adj : graph[i]) {
        if (dfs(graph, dp, adj) == 1)
            color = 1;  // 若有loop, 则iColor = 1 
    }

    dp[i] = color;
    return dp[i];  
}









