The Maze II 迷宫之二
 
There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.
Given the ball's start position, the destination and the maze, find the shortest distance for the ball to stop at the destination. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included). If the ball cannot stop at the destination, return -1.
The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

Example 1
Input 1: a maze represented by a 2D array
0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)

Output: 12
Explanation: One shortest way is : left -> down -> left -> down -> right -> down -> right.
             The total distance is 1 + 1 + 3 + 1 + 2 + 2 + 2 = 12.


这道题是之前那道The Maze的拓展，那道题只让我们判断能不能在终点位置停下，而这道题让我们求出到达终点的最少步数。其实本质都是一样的，难点还是在于对于一滚到底的实现方法，唯一不同的是，这里我们用一个二位数组dists，其中dists[i][j]表示到达(i,j)这个位置时需要的最小步数，我们都初始化为整型最大值，在后在遍历的过程中不断用较小值来更新每个位置的步数值，最后我们来看终点位置的步数值，如果还是整型最大值的话，说明没法在终点处停下来，返回-1，否则就返回步数值。注意在压入栈的时候，我们对x和y进行了判断，只有当其不是终点的时候才压入栈，这样是做了优化，因为如果小球已经滚到终点了，我们就不要让它再滚了，就不把终点位置压入栈，免得它还滚

// bfs 
int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int m = maze.size(), n = maze[0].size();
        vector<vector<int>> dists(m, vector<int>(n, INT_MAX));
        vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
        queue<pair<int, int>> q;
        q.push({start[0], start[1]});
        dists[start[0]][start[1]] = 0;
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            for (auto d : dirs) {
                int x = t.first, y = t.second, dist = dists[t.first][t.second];
                while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
                    x += d[0];
                    y += d[1];
                    ++dist;
                }
                x -= d[0];
                y -= d[1];
                --dist;
                if (dists[x][y] > dist) {
                    dists[x][y] = dist;
                    if (x != destination[0] || y != destination[1]) q.push({x, y});
                }
            }
        }
        int res = dists[destination[0]][destination[1]];
        return (res == INT_MAX) ? -1 : res;
    }

// dfs 
vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    int m = maze.size(), n = maze[0].size();
    vector<vector<int>> dists(m, vector<int>(n, INT_MAX));
    dists[start[0]][start[1]] = 0;
    helper(maze, start[0], start[1], destination, dists);
    int res = dists[destination[0]][destination[1]];
    return (res == INT_MAX) ? -1 : res;
}

void helper(vector<vector<int>>& maze, int i, int j, vector<int>& destination, vector<vector<int>>& dists) {
    if (i == destination[0] && j == destination[1]) return;
    int m = maze.size(), n = maze[0].size();
    for (auto d : dirs) {
        int x = i, y = j, dist = dists[x][y];
        while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
            x += d[0];
            y += d[1];
            ++dist;
        }
        x -= d[0];
        y -= d[1];
        --dist;
        if (dists[x][y] > dist) {
            dists[x][y] = dist;
            helper(maze, x, y, destination, dists);
        }
    }
}
