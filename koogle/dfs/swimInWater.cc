778. Swim in Rising Water  

On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).
Now rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.
You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?

Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation:
 0  1  2  3  4
24 23 22 21  5
12 13 14 15 16
11 17 18 19 20
10  9  8  7  6

The final route is marked in bold.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.

这道题给了我们一个二维数组，可以看作一个水池，这里不同数字的高度可以看作台阶的高度，只有当水面升高到台阶的高度时，我们才能到达该台阶，起始点在左上角位置，问我们水面最低升到啥高度就可以到达右下角的位置。这是一道蛮有意思的题目。对于这种类似迷宫遍历的题，一般都是DFS或者BFS。而如果有极值问题存在的时候，一般都是优先考虑BFS的，但是这道题比较特别，有一个上升水面的设定，我们可以想象一下，比如洪水爆发了，大坝垮了，那么愤怒汹涌的水流冲了出来，地势低洼处就会被淹没，而地势高的地方，比如山峰啥的，就会绕道而过。这里也是一样，随着水面不断的上升，低于水平面的地方就可以到达，直到水流到了右下角的位置停止。因为水流要向周围低洼处蔓延，所以BFS仍是一个不错的选择，由于水是向低洼处蔓延的，而低洼处的位置又是不定的，所以我们希望每次取出最低位置进行遍历，那么使用最小堆就是一个很好的选择，这样高度低的就会被先处理。在每次取出高度最小的数字时，我们用此高度来更新结果res，如果当前位置已经是右下角了，则我们直接返回结果res，否则就遍历当前位置的周围位置，如果未越界且未被访问过，则标记已经访问过，并且加入队列


class cmp{
public:
    bool operator()(vector<int>& a, vector<int>& b) {
        return a[2] > b[2];
    }
};


int swimInWater(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0; 
    int res; 
    int m = grid.size(), n = grid[0].size(); 
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;  
    vector<vector<int>> dirs = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}}; 
    pq.push({0, 0, grid[0][0]}); 
    vector<vector<bool>> visited(m, vector<bool>(n, false); 

    while(!pq.empty()) {
        auto t = pq.top(); pq.pop(); 
        res = max(res, t[2]); 
        if(t[0] == m - 1 && t[1] == n - 1) return res; 

        for (auto a : dirs) {
            auto temp = t; 
            temp[0] += a[0]; 
            temp[1] += a[1];  
            if (temp[0] < 0 || temp[1] < 0 || temp[0] >= m || temp[1] >= n || visited[temp[0]][temp[1]]) continue; 

            visited[temp[0]][temp[1]] = true; 
            temp[2] = grid[temp[0]][temp[1]]; 
            pq.push(temp);  

        }
    }
    return -1; 
 
}


//////////////////////////////////////////////////

我们也可以使用DP+DFS来做，这里使用一个二维dp数组，其中 dp[i][j] 表示到达 (i, j) 位置所需要的最低水面高度，均初始化为整型数最大值，我们的递归函数函数需要知道当前的位置 (x, y)，还有当前的水高cur，同时传入grid数组和需要不停更新的dp数组，如果当前位置越界了，或者是当前水高和 grid[x][y] 中的较大值大于等于 dp[x][y] 了，直接跳过，因为此时的dp值更小，不需要被更新了。否则 dp[x][y] 更新为较大值，然后对周围四个位置调用递归函数继续更新dp数组，最终返回右下位置的dp值即可

// 递归的时间慢 2% 
vector<vector<int>> dirs{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    helper(grid, 0, 0, grid[0][0], dp);
    return dp[n - 1][n - 1];
}

void helper(vector<vector<int>>& grid, int x, int y, int cur, vector<vector<int>>& dp) {
    int n = grid.size();
    if (x < 0 || x >= n || y < 0 || y >= n || max(cur, grid[x][y]) >= dp[x][y]) 
        return;
    
    dp[x][y] = max(cur, grid[x][y]);

    for (auto dir : dirs) {
        helper(grid, x + dir[0], y + dir[1], dp[x][y], dp);
    }
}



// https://www.youtube.com/watch?v=dmP65LPl9wQ&frags=pl%2Cwn 

// struct pos {
// 	pos(int a, int b, int c) : val(a), x(a), y(b) {};
// 	int val, x, y;  
// 	bool operator<(const pos& d) const {return val > d.val};  
// }; 

// vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; 

// bool isValid(int x, int y, int n) {
// 	return (x >= 0 && x < n && y >= 0 && y < n); 
// } 


// int swimInWater(vector<vector<int>>& grid) {
// 	int n = grid.size(); 
// 	priority_queue<pos> pq; 
// 	pq.push(pos(grid[0][0], 0, 0)); 
// 	vector<vector<int>> done(n, vector<n, -1>); 
// 	done[0][0] = grid[0][0]; 

// 	while(done[n-1][n-1] == -1) {
// 		auto p = pq.top(); 
// 		pq.pop(); 
// 		for (auto a : dirs) {
// 			int a = p.x + a[0]; 
// 			int b = p.y + a[1]; 
// 			if (isValid(a, b, n) && done[a][b] == -1) {
// 				int c = max(grid[a][b], p.val); 
// 				pq.push(pos(c, a, b)); 
// 				done[a][b] = c; 
// 			}
// 		}
// 	}

// 	return done[n-1][n-1]; 
// }



