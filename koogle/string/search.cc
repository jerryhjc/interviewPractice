[LeetCode] Word Search 词语搜索  
 
Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.

这道题是典型的深度优先遍历DFS的应用，原二维数组就像是一个迷宫，可以上下左右四个方向行走，我们以二维数组中每一个数都作为起点和给定字符串做匹配，我们还需要一个和原数组等大小的visited数组，是bool型的，用来记录当前位置是否已经被访问过，因为题目要求一个cell只能被访问一次。如果二维数组board的当前字符和目标字符串word对应的字符相等，则对其上下左右四个邻字符分别调用DFS的递归函数，只要有一个返回true，那么就表示可以找到对应的字符串，否则就不能找到，具体看代码实现如下：


bool exist(vector<vector<char>> &board, string word) {
	if (word.empty()) return true; 
	if (board.empty() || board[0].empty()) return false; 

	int m = board.size(); 
	int n = board[0].size(); 

	vector<vector<bool>> visit(m, vector<bool>(n, false));

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (search(board, word, 0, i, j, visit)) return true; 
		}
	}

	return false; 
}

bool search(vector<vector<char>>& board, string word, int idx, int i, int j, vector<vector<bool>>& visit) {
	if (idx == word.size()) return true; 

	int m = board.size(), n = board[0].size(); 
	if (i >= m || j >= n || i < 0 || j < 0 || visit[i][j] || board[i][j] != word[idx]) 
		return false; 

	visit[i][j] = true; 

	bool ret = search(board, word, idx + 1, i - 1, j, visit) || 
		search(board, word, idx + 1, i + 1, j, visit) ||
		search(board, word, idx + 1, i, j + 1, visit) ||
		search(board, word, idx + 1, i, j - 1, visit); 


	visit[i][j] = false; 

	return ret; 

}

===============================
[LeetCode] Word Search II 词语搜索之二

Given a 2D board and a list of words from the dictionary, find all words in the board.
Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].

Note:
You may assume that all inputs are consist of lowercase letters a-z.

  struct TrieNode {
        TrieNode *child[26];
        string str;
        TrieNode() : str("") {
            for (auto &a : child) a = NULL;
        }
    };
    
    struct Trie {
        TrieNode *root;
        Trie() : root(new TrieNode()) {}
        void insert(string s) {
            TrieNode *p = root;
            for (auto &a : s) {
                int i = a - 'a';
                if (!p->child[i]) p->child[i] = new TrieNode();
                p = p->child[i];
            }
            p->str = s;
        }
    };

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> res;
        if(board.size() == 0 || board[0].size() == 0 || words.size() == 0) return res;
        int m = board.size();
        int n = board[0].size();
        Trie *T = new Trie();
        vector<vector<bool>> visited(m,vector<bool>(n,false));

        for(auto w:words){
            T->insert(w);
        }

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                search(board,T->root,i,j,visited,res);
            }
        }
        return res;
    }
    
    void search(vector<vector<char>> &board, TrieNode *p, int i, int j, vector<vector<bool>> &visited, vector<string> &res) {
         if( i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || visited[i][j]) return;
        
        p = p->child[board[i][j]-'a'];
        if (!p) return; 
        
        if(!p->str.empty()) {
            res.push_back(p->str);
            p->str.clear();
        }
       
        visited[i][j]=true;
        
        search(board,p,i+1,j,visited,res);
        search(board,p,i-1,j,visited,res);
        search(board,p,i,j+1,visited,res);
        search(board,p,i,j-1,visited,res);
        
        visited[i][j]=false;       
    }


