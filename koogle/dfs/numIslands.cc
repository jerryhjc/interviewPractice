Number of Islands 岛屿的数量
 
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:
11110
11010
11000
00000
Answer: 1

Example 2:
11000
11000
00100
00011
Answer: 3    

这道求岛屿数量的题的本质是求矩阵中连续区域的个数，很容易想到需要用深度优先搜索DFS来解，我们需要建立一个visited数组用来记录某个位置是否被访问过，对于一个为‘1’且未被访问过的位置，我们递归进入其上下左右位置上为‘1’的数，将其visited对应值赋为true，继续进入其所有相连的邻位置，这样可以将这个连通区域所有的数找出来，并将其对应的visited中的值赋true，找完次区域后，我们将结果res自增1，然后我们在继续找下一个为‘1’且未被访问过的位置，以此类推直至遍历完整个原数组即可得到最终结果

 int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0; 
        
        vector<vector<bool>> visit(grid.size(), vector<bool>(grid[0].size(), false));              
        int res = 0; 
        
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if(!visit[i][j] && grid[i][j] == '1') {
                    dfs(grid, i, j, visit); 
                    res++; 
                }
            }
        }
        
        return res; 
    }
    
    void dfs(vector<vector<char>>& grid, int i, int j, vector<vector<bool>>& visit) {
        int m = grid.size(); 
        int n = grid[0].size(); 
        if (i < 0 || j < 0 || i >= m || j >= n || visit[i][j] || grid[i][j] == '0') return; 
        
        visit[i][j] = true; 
        dfs(grid, i + 1, j, visit);
        dfs(grid, i - 1, j, visit);
        dfs(grid, i, j + 1, visit);
        dfs(grid, i, j - 1, visit);
    }


///////////////////////////////  

Number of Islands II 岛屿的数量之二  

A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example:
Given m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]].
Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0

那么我们为了解决这种陆地之间会合并的情况，最好能够将每个陆地都标记出其属于哪个岛屿，这样就会方便我们统计岛屿个数。这种群组类问题，很适合使用联合查找 Union Find 来做，又叫并查集 Disjoint Set，LeetCode中使用这种解法的题目还不少呢，比如Friend Circles，Graph Valid Tree，Redundant Connection II 等等。一般来说，UF算法的思路是每个个体先初始化为不同的群组，然后遍历有关联的两个个体，如果发现其getRoot函数的返回值不同，则手动将二者加入一个群组，然后总群组数自减1。这里就要分别说一下root数组，和getRoot函数。两个同群组的个体，通过getRoot函数一定会返回相同的值，但是其在root 数组中的值不一定相同，我们可以类比成getRoot函数返回的是祖先，如果两个人的祖先相同，那么其是属于一个家族的（这里不是指人类共同的祖先哈）。root可以用数组或者HashMap来表示，如果个体是数字的话，那么数组就OK，如果个体是字符串的话，可能就需要用HashMap了。root数组的初始化可以有两种，可以均初始化为-1，或者都初始化为不同的数字，博主一般喜欢初始化为不同的数字。getRoot函数的写法也可用递归或者迭代的方式，可参见博主之前的帖子Redundant Connection II中的讨论部分。这么一说感觉UF算法的东西还蛮多的，啥时候博主写个UF总结贴吧。

那么具体来看这道题吧，此题跟经典的UF使用场景有一点点的区别，因为一般的场景中两个个体之间只有两种关系，属于一个群组或者不属于同一个群组，而这道题里面由于water的存在，就多了一种情况，我们只需要事先检测一下当前位置是不是岛屿就行了，总之问题不大。一般来说我们的root数组都是使用一维数组，方便一些，那么这里就可以将二维数组encode为一维的，于是我们需要一个长度为m*n的一维数组来标记各个位置属于哪个岛屿，我们假设每个位置都是一个单独岛屿，岛屿编号可以用其坐标位置表示，但是我们初始化时将其都赋为-1，这样方便我们知道哪些位置尚未变成岛屿。然后我们开始遍历陆地数组，将其岛屿编号设置为其坐标位置，然后岛屿计数加1，我们此时开始遍历其上下左右的位置，遇到越界或者岛屿标号为-1的情况直接跳过，现在知道我们初始化为-1的好处了吧，遇到是water的地方直接跳过。否则我们用getRoot来查找邻居位置的岛屿编号，同时也用getRoot来查找当前点的编号，这一步就是经典的UF算法的操作了，因为当前这两个land是相邻的，它们是属于一个岛屿，所以其getRoot函数的返回值suppose应该是相等的，但是如果返回值不同，说明我们需要合并岛屿，将两个返回值建立关联，并将岛屿计数cnt减1。当我们遍历完当前点的所有邻居时，该合并的都合并完了，将此时的岛屿计数cnt存入结果中

vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
    vector<int> res; 
    int count = 0; 
    vector<int> roots(m*n, -1); 
    vector<vector<int>> dirs = {{0,-1}, {0, 1}, {-1, 0}, {1, 0}};

    for (auto a : positions) {
        int id = n * a.first + a.second; 
        root[id] = id; 
        count++; 

        for (auto dir : dirs) {
            int x = a.first + dir[0], y = a.second + dir[1], cur_id = n * x + y; 
            if (x < 0 || x >= m || y < 0 || y >= n || roots[cur_id] == -1) continue; 
            int p = findRoot(roots, cur_id), q = findRoot(roots, id); 
            if (p != q) {
                roots[p]  = q; 
                --count;
            } 
        }
    }

    return res;
}

vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
    vector<int> res;
    int cnt = 0;
    vector<int> roots(m * n, -1);
    vector<vector<int>> dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    
    for (auto a : positions) {
        int id = n * a.first + a.second;
        roots[id] = id;
        ++cnt;

        for (auto dir : dirs) {
            int x = a.first + dir[0], y = a.second + dir[1], cur_id = n * x + y;
            if (x < 0 || x >= m || y < 0 || y >= n || roots[cur_id] == -1) continue;
            int p = findRoot(roots, cur_id), q = findRoot(roots, id);
            if (p != q) {
                roots[p] = q;  // merge 
                --cnt;
            }
        }
        res.push_back(cnt);
    }
    return res;
}

int findRoot(vector<int>& roots, int id) {
    if (id == roots[id]) 
        return id; 
    else 
        return findRoot(roots, roots[id]); 
}




711. Number of Distinct Islands II  

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1s (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island is considered to be the same as another if they have the same shape, or have the same shape after rotation (90, 180, or 270 degrees only) or reflection (left/right direction or up/down direction).

Example 1:
11000
10000
00001
00011
Given the above grid map, return 1. 

Notice that:
11
1
and
 1
11
are considered same island shapes. Because if we make a 180 degrees clockwise rotation on the first island, then two islands will have the same shapes.


int numDistinctIslands2(vector<vector<int>>& grid) {
    if(grid.empty()) return 0;
    set<vector<pair<int, int>>> islands;
    
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] == 1) {
                vector<pair<int, int>> island;
                dfs(i, j, i, j, grid, island);
                islands.insert(norm(island));
            }
        }
    }
    return islands.size();
}


void dfs(int sr, int sc, int r, int c, vector<vector<int>>& grid, vector<pair<int, int>>& island) {
    if(r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size() || grid[r][c] == 0) 
        return;

    island.push_back({r - sr, c - sc});
    grid[r][c] = 0;   // similar to visit[i][j] = true;   
    
    dfs(sr, sc, r + 1, c, grid, island);
    dfs(sr, sc, r - 1, c, grid, island);
    dfs(sr, sc, r, c + 1, grid, island);
    dfs(sr, sc, r, c - 1, grid, island);
}


vector<pair<int, int>> norm(vector<pair<int, int>>& island) {
    vector<vector<pair<int, int>>> s(8);
    
    for(auto& p: island) {
        int x = p.first, y = p.second;
        s[0].push_back({x, y});
        s[1].push_back({-x, y});
        s[2].push_back({x, -y});
        s[3].push_back({-x, -y});
        s[4].push_back({y, x});
        s[5].push_back({-y, x});
        s[6].push_back({y, -x});
        s[7].push_back({-y, -x});  
    }
    
    for(auto& l : s) 
        sort(l.begin(), l.end());
    
    for(auto& l: s) {
        for(int i = 1; i < l.size(); i++) {
            l[i] = {l[i].first - l[0].first, l[i].second - l[0].second};
        }
        l[0] = {0,0};
    }
    sort(s.begin(), s.end());
    return s[0];  // 只返回首元素 
}





