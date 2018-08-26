Trapping Rain Water II 收集雨水之二
 
Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.
Note:
Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.

Example:
Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]
Return 4.   

这道题是之前那道Trapping Rain Water的拓展，由2D变3D了，感觉很叼。但其实解法跟之前的完全不同了，之前那道题由于是二维的，我们可以用双指针来做，而这道三维的，我们需要用BFS来做，解法思路很巧妙，下面我们就以题目中的例子来进行分析讲解，多图预警，手机流量党慎入：

首先我们应该能分析出，能装水的底面肯定不能在边界上，因为边界上的点无法封闭，那么所有边界上的点都可以加入queue，当作BFS的启动点，同时我们需要一个二维数组来标记访问过的点，访问过的点我们用红色来表示，

我们再想想，怎么样可以成功的装进去水呢，是不是周围的高度都应该比当前的高度高，形成一个凹槽才能装水，而且装水量取决于周围最小的那个高度，有点像木桶原理的感觉，那么为了模拟这种方法，我们采用模拟海平面上升的方法来做，我们维护一个海平面高度mx，初始化为最小值，从1开始往上升，那么我们BFS遍历的时候就需要从高度最小的格子开始遍历，那么我们的queue就不能使用普通队列了，而是使用优先级队列，将高度小的放在队首，最先取出，这样我们就可以遍历高度为1的三个格子，用绿色标记出来了


  int trapRainWater(vector<vector<int>>& heightMap) {
        if (heightMap.empty()) return 0;
        int m = heightMap.size(), n = heightMap[0].size(), res = 0, mx = INT_MIN;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> dir{{0,-1},{-1,0},{0,1},{1,0}};
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    q.push({heightMap[i][j], i * n + j});
                    visited[i][j] = true;
                }
            }
        }
        while (!q.empty()) {
            auto t = q.top(); q.pop();
            int h = t.first, r = t.second / n, c = t.second % n;
            mx = max(mx, h);
            for (int i = 0; i < dir.size(); ++i) {
                int x = r + dir[i][0], y = c + dir[i][1];
                if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y]) continue;
                visited[x][y] = true;
                if (heightMap[x][y] < mx) res += mx - heightMap[x][y];
                q.push({heightMap[x][y], x * n + y});
            }
        }
        return res;
    }




