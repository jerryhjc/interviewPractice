Pacific Atlantic Water Flow 太平洋大西洋水流
 
Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.
Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.
Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

Note:
The order of returned grid coordinates does not matter.
Both m and n are less than 150.
Example:
Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:
[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).

题目给了一个矩阵，代表一个高度，高度高的可以流到同高度或更小的高度那里 
而在矩阵的四周，围绕着太平洋和大西洋（可以看图示，太平洋左边和上边，大西洋下边和右边，也就是这四个边对应的位置是通向海洋的）

现在问说这个矩阵里面的位置，那些的水流可以同时流到大西洋和太平洋？
如果准备一个位置一个位置的去寻找能否有路径能够到达两个海洋，就太naïve了。
我的做法是： 
1、分别处理每个海洋，从海洋边缘（每个海洋两条边）开始，一步步的搜索，即从连接海洋的地方还是搜索，哪些节点的高度高于等于自身（反过来就是可以从那里流到自己），如果是，就标记为true，就这样不断搜索下去。最后所有标记为true的位置就是可以流到对应的海洋。 
2、找这两个矩阵，同为true的输出，就是都能流到两个海洋的位置


这道题给了我们一个二维数组，说是数组的左边和上边是太平洋，右边和下边是大西洋，假设水能从高处向低处流，问我们所有能流向两大洋的点的集合。刚开始我们没有理解题意，以为加括号的点是一条路径，连通两大洋的，但是看来看去感觉也不太对，后来终于明白了，是每一个点单独都路径来通向两大洋。那么就是典型的搜索问题，那么我最开始想的是对于每个点来搜索是否能到达边缘，只不过搜索的目标点不在是一个单点，而是所有的边缘点，找这种思路写出的代码无法通过OJ大数据集，那么我们就要想办法来优化我们的代码，优化的方法跟之前那道Surrounded Regions很类似，都是换一个方向考虑问题，既然从每个点像中间扩散会TLE，那么我们从边缘当作起点开始遍历搜索，然后标记能到达的点位true，分别标记出pacific和atlantic能到达的点，那么最终能返回的点就是二者均为true的点。我们可以先用DFS来遍历二维数组   

// dfs
vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return {};
    vector<pair<int, int>> res;
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        dfs(matrix, pacific, INT_MIN, i, 0);
        dfs(matrix, atlantic, INT_MIN, i, n - 1);
    }
    for (int i = 0; i < n; ++i) {
        dfs(matrix, pacific, INT_MIN, 0, i);
        dfs(matrix, atlantic, INT_MIN, m - 1, i);
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (pacific[i][j] && atlantic[i][j]) {
                res.push_back({i, j});
            }
        }
    }
    return res;
}


void dfs(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int pre, int i, int j) {
    int m = matrix.size(), n = matrix[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || matrix[i][j] < pre) return;
    visited[i][j] = true;
    dfs(matrix, visited, matrix[i][j], i + 1, j);
    dfs(matrix, visited, matrix[i][j], i - 1, j);
    dfs(matrix, visited, matrix[i][j], i, j + 1);
    dfs(matrix, visited, matrix[i][j], i, j - 1);
}


// bfs 
那么BFS的解法也可以做，用queue来辅助，开始把边上的点分别存入queue中，然后对应的map标记true，然后开始BFS遍历，遍历结束后还是找pacific和atlantic均标记为true的点加入res中返回即可

 vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return {};
        vector<pair<int, int>> res;
        int m = matrix.size(), n = matrix[0].size();
        queue<pair<int, int>> q1, q2;
        vector<vector<bool>> pacific(m, vector<bool>(n, false)), atlantic = pacific;
        for (int i = 0; i < m; ++i) {
            q1.push({i, 0}); 
            q2.push({i, n - 1});
            pacific[i][0] = true;
            atlantic[i][n - 1] = true;
        }
        for (int i = 0; i < n; ++i) {
            q1.push({0, i});
            q2.push({m - 1, i});
            pacific[0][i] = true;
            atlantic[m - 1][i] = true;
        }
        bfs(matrix, pacific, q1);
        bfs(matrix, atlantic, q2);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (pacific[i][j] && atlantic[i][j]) {
                    res.push_back({i, j});
                }
            }
        }
        return res;
    }   

    void bfs(vector<vector<int>>& matrix, vector<vector<bool>>& visited, queue<pair<int, int>>& q) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            for (auto dir : dirs) {
                int x = t.first + dir[0], y = t.second + dir[1];
                if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y] || matrix[x][y] < matrix[t.first][t.second]) continue;
                visited[x][y] = true;
                q.push({x, y});
            }
        }
    }



340. Longest Substring with At Most K Distinct Characters    







