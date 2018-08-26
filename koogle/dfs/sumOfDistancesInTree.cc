834. Sum of Distances in Tree 

An undirected, connected tree with N nodes labelled 0...N-1 and N-1 edges are given.
The ith edge connects nodes edges[i][0] and edges[i][1] together.
Return a list ans, where ans[i] is the sum of the distances between node i and all other nodes.

Example 1:
Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: 
Here is a diagram of the given tree:
  0
 / \
1   2
   /|\
  3 4 5
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.  Hence, answer[0] = 8, and so on.


每个节点保存两个值，一个是其子树的节点个数（包括自身节点也要计数）nodesum[ ]，一个是其子树各点到它的距离 dp[ ]，那么我们假设根节点为 u ，其仅有一个儿子 v ， u 到 v 的距离为 1 ，而 v 有若干儿子节点，那么 dp[v] 表示 v 的子树各点到 v 的距离和，那么各个节点到达 u 的距离便可以这样计算： dp[u] = dp[v] + nodesum[ v ] *1; （式子的理解，v 的一个儿子节点为 f，那么 f 到达 u 的距离为  (sum[ f ->v] + sum [v- > u])*1 ，dp[v] 包含了 sum[f->v]*1，所以也就是式子的分配式推广到各个子节点计算出来的和）。我们已经知道了各个节点到达根节点的距离和，那么从根节点开始递推下来可以得到各个点的距离和。另开一个数组表示每个节点的到其他节点的距离和，那么对于根节点u来说， dissum[u] = dp[u]。以 u 的儿子 v 为例， v 的子节点到 v 不必经过 v->u 这条路径，因此 dissum[u] 多了 nodesum[v] * 1，但是对于不是 v 的子节点的节点，只到达了 u ，因此要到达 v 必须多走 u->v 这条路径，因此 dissum[u] 少了 ( N - nodesum[v] ) * 1) ,所以 dissum[v] = dissum[u] - nodesum[v] * 1 + (N - nodesum[v] ) * 1，按照这个方法递推下去就可以得到各个点的距离和。



  //相当于图来存来处理
      vector<vector<int>> tree;
      vector<int> res;
      vector<int> subc;
      int n;
     
      vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
          //tree.rvec(N,vector<int>(N));
         //init
         n = N;
         tree.resize(N);            //初始化的函数
         res.assign(N,0);
         subc.assign(N,0);
         //build tree
         for(auto e : edges){               //遍历的技巧
             tree[e[0]].push_back(e[1]);
             tree[e[1]].push_back(e[0]);
         }
         set<int> visited1;
         set<int> visited2;
         DFS_POST(0,visited1);         //初始root任何值都行
         DFS_PRE(0,visited2);
         return res;
         
     }

    // calculate from child to root
     void DFS_POST(int root,set<int> &visited){            //传引用保存修改值
         visited.insert(root);
         for(auto i : tree[root]){
             if(visited.find(i) == visited.end() ){  
                 DFS_POST(i,visited);
                 subc[root] += subc[i];
                 res[root] += res[i] + subc[i];    
             }
         }
         subc[root]++;  //加上自身节点
     }


    // calculate from root to child
     void DFS_PRE(int root,set<int> &visited){
         visited.insert(root);
         for(auto i : tree[root]){
             if(visited.find(i) == visited.end()){
                 res[i] = res[root] - subc[i] + n - subc[i];         //算法核心
                 DFS_PRE(i,visited);
             }
         }
     }

///////////////////////////
解题思路

比较简单的一道题目，暴力解决N方，其实每个点的距离和可以由相邻点得到，减去这一侧的点数加上另一侧的点数即可。因此可以先O(N)算出某个点的距离和，再逐个往外算出每个点的距离和，每个点仅需O(1)就能得到，当然要先预处理出这一侧所有点的个数。

复杂度分析
时间复杂度为O(N)
空间复杂度为O(N)


constexpr int kMaxN = 11000;

vector<int> adj[kMaxN], tree[kMaxN];
bool vst[kMaxN];
int cnt[kMaxN];
int sum;
int n;
vector<int> ans;

class Solution {
public:
  vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
    n = N;
    for (int i = 0; i < n; ++i) {
      adj[i].clear();
      tree[i].clear();
    }
    for (int i = 0; i < n - 1; ++i) {
      adj[edges[i][0]].push_back(edges[i][1]);
      adj[edges[i][1]].push_back(edges[i][0]);
    }
    ans.clear();
    ans.resize(n);
    memset(vst, 0, sizeof vst);
    build_tree();
    cal_num(0);
    sum = 0;
    dfs(0, 0);
    work();
    return ans;
  }

  int cal_num(int u) {
    cnt[u] = 1;
    for (int i = 0; i < static_cast<int>(tree[u].size()); ++i) {
      int v = tree[u][i];
      cnt[u] += cal_num(v);
    }
    return cnt[u];
  }

  void build_tree() {
    queue<int> q;
    q.push(0);
    vst[0] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < static_cast<int>(adj[u].size()); ++i) {
        int v = adj[u][i];
        if (!vst[v]) {
          tree[u].push_back(v);
          q.push(v);
          vst[v] = true;
        }
      }
    }
  }

  void dfs(int u, int s) {
    sum += s;
    for (int i = 0; i < static_cast<int>(tree[u].size()); ++i) {
      int v = tree[u][i];
      dfs(v, s + 1);
    }
  }

  void cal_ans(int u, int s) {
    ans[u] = s;
    for (int i = 0; i < static_cast<int>(tree[u].size()); ++i) {
      int v = tree[u][i];
      cal_ans(v, s - cnt[v] + (n - cnt[v]));
    }
  }

  void work() {
    cal_ans(0, sum);
  }
};

Example 1:
Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: 
Here is a diagram of the given tree:
  0
 / \
1   2
   /|\
  3 4 5
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.  Hence, answer[0] = 8, and so on.

///////////////////////////////////

首先想到的用brute force去解这道题:
对于每个节点，我们用BFS就可以求出每个level的点到该节点的距离，边遍历边求和。但是我们要对每个节点都要做一次BFS，时间复杂度为O(n*n)

仔细分析，其实有非常多的重复计算，那么去重就是这道题的分析关键。
那么重复到底在哪里？拿题目中给出的例子来说：
在计算其他节点到N0(node0, 节点0)的距离和的时候：(第一次遍历)
distance(1,2) -> 0 = 1，distance(3,4,5) -> 0 = 2，假设3往下还有(6,7)两个节点，distance(6,7) -> 0 = 3

接下来我们计算其他节点到N2的距离和的时候：(第二次遍历)
distance(3,4,5) -> 2 = 1, distance(6,7) -> 2 = 2
可以看到，在第一次遍历，已经计算，并且知道N2下面有3个点(3,4,5),和两个二重degree(6,7), 第二次遍历，竟然又一次计算N2下面有多少个点，每个点到它的距离是多少，这就是重复的地方。

那么如何去重？这部分是最难想的
在第二次遍历的时候，可以发现，所有N2已经N2往下的节点都靠近了，而除此之外的节点都远离了，所以只要知道N2和N2往下的节点总共有多少个，并且存下来count(2), count(2)个数的节点，距离都要减1，n – count(2)个数的节点，距离都要增加1，最后可以得到公式：
res(2) = res(0) – count(2) + (n – count(2))

所以在第一次遍历的时候，要记录res(0), 和count(i), i from 0 to n – 1，通过这些信息，在第二次遍历的时候，通过刚才的公式，可以得到所有点的结果。










