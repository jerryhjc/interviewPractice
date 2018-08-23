data structure: 
1. vector: begin(), end(), rbegin(), push_back(xx), pop_back(), size(), empty(), front(), end(), clear(), erase(),  
2. queue: front(), back(), empty(), push(), pop(), size()    while(!q.empty()) 
6. priority_queue: top(), empty(), push(), pop(), size()     
3. stack: top(), empty(), push(), pop(), size() 
4. unordered_map: count(), find(), erase(), empty(), size(), clear(), m[key]++, it->firt, it->second, 
5. unordered_set: insert(), empty(), count(), begin(), end(), size()   
6. string: erase(iterator), erase(pos, len), insert(pos, char/string),   
7. deque:  


for (auto it = vec.begin(); it != vec.end(); ++it)
initialization 

int m = 2, n = 5;
vector<vector<int>> vec(m, vector<int>(n, 0));
vector<vector<int>> num = {{1,4,7,11,15}, {2,5,8,12,19}, {3,6,9,16,22}};
vector<int> vec = {1, 2, 3};
		
///////////////////////////////////// 

239. Sliding Window Maximum
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note: 
You may assume k is always valid, ie: 1 ≤ k ≤ input array size for non-empty array. 


vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	deque<int> dq; 
	vector<int> res; 

	for(int i = 0; i < nums.size(); ++i) {
	//1. 	//remove elements out of window 在out of range 
		if(!dq.empty() && dq.front() == i - k) 
			dq.pop_front(); 

	//2.	//dq is in descending order; dqremove elements 比nums[i]小的
		while(!dq.empty() && nums[dq.back()] < nums[i])
			dq.pop_back(); 

		//push the current element to the deque 
		dq.push_back(i); 

		if(i >= k - 1) //  初始几个k-1个值以后开始push back.                     
			res.push_back(nums[dq.front()]);

	}
	return res; 
}

// better solution:  
// 维护一个大小为k的multiset，每次删去过期的数，取最大数。
//  multiset 自动从小到大排序 

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    multiset<int> history;
    vector<int> result;
    for (int j = 0; j < nums.size(); ++j) {
        if (j >= k) history.erase(history.find(nums[j-k]));
        history.insert(nums[j]);
        if (j >= k-1) result.push_back(*history.rbegin());
    }
    return result;
}




///////////////////////////////////////////// 

backtracking 两种结构 
1. for (int i = 0; i < size; ++i) {
		visit[i] = true;  不可重复  
		helper(..., idx + 1); 
		visit[i] = false; 

	}

2. for (int i = idx; i < size; ++i) {
	2.1 helper(..., idx + 1); 可重复
	2.2 helper(..., i + 1); 不可重复
} 


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


=======================================   

[LeetCode] Permutations 全排列
Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].

这道题是求全排列问题，给的输入数组没有重复项，这跟之前的那道 Combinations 组合项 和类似，解法基本相同，但是不同点在于那道不同的数字顺序只算一种，是一道典型的组合题，而此题是求全排列问题，还是用递归DFS来求解。这里我们需要用到一个visited数组来标记某个数字是否访问过，然后在DFS递归函数从的循环应从头开始，而不是从level开始，这是和 Combinations 组合项 不同的地方，其余思路大体相同




    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res; 
        if (nums.empty()) return res; 
        vector<bool> visit(nums.size(), false); 
        vector<int> vec; 
        helper(res, nums, vec, visit, 0);         
        return res; 
    }
    
    void helper(vector<vector<int>>& res, vector<int> nums, vector<int>& vec, vector<bool>& visit,  int count) {
        if (count == nums.size()) {
            res.push_back(vec); 
            return; 
        }
        
        // if(visit[idx]) return;       
        for (int i = 0; i < nums.size(); ++i) {
            if (!visit[i]) {
            visit[i] = true; 
            vec.push_back(nums[i]);
            helper(res, nums, vec, visit, count+1);
            vec.pop_back(); 
            visit[i] = false; 
            }
        }
    }


[LeetCode] Permutations II 全排列之二
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1].

这道题是之前那道 Permutations 全排列的延伸，由于输入数组有可能出现重复数字，如果按照之前的算法运算，会有重复排列产生，我们要避免重复的产生，在递归函数中要判断前面一个数和当前的数是否相等，如果相等，前面的数必须已经使用了，即对应的visited中的值为1，当前的数字才能使用，否则需要跳过，这样就不会产生重复排列了                        

 vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> vec; 
        vector<vector<int>> res; 
        vector<bool> visit(nums.size(), false);   
        sort(nums.begin(), nums.end());   // 要先排序  
        helper(nums, vec, res, 0, visit);
        return res; 
    }
    
    void helper(vector<int> nums, vector<int>& vec, vector<vector<int>>& res, int idx, vector<bool>& visit) {
        if (idx == nums.size()) {
            res.push_back(vec); 
            return; 
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (visit[i] == false) {
                if(i > 0 && nums[i] == nums[i-1] && visit[i-1] == false ) continue;   // 注意这句跳过重复
                visit[i] = true; 
                vec.push_back(nums[i]); 
                helper(nums, vec, res, idx + 1, visit);
                vec.pop_back();
                visit[i] = false; 
            }
           
        }   
    }


==============================

[LeetCode] Generate Parentheses 生成括号
 
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
For example, given n = 3, a solution set is:
"((()))", "(()())", "(())()", "()(())", "()()()"


vector<string> generateParenthesis(int n) {
        vector<string> vec; 
        string str; 
        if (n == 0) return vec; 
        
        helper(vec, str, n, n);
        return vec; 

    }

    void helper(vector<string>& vec, string str,  int countL, int countR) {
        // if (count < 0) return; 
        // if (n == 0) vec.push_back(str);
        if (countL == 0 & countR == 0) vec.push_back(str); 
        if (countL > countR) return; 
        
        // for (int i = 0; i < n; ++i)
        if (countL > 0 ) {
            // str.push_back('(');   // 错误
            helper(vec, str + '(', countL - 1, countR);
            
            }
        if (countR > 0) {
            // str.push_back(')');   // 错误
            helper(vec, str + ')', countL, countR - 1); 
        }
   
    }


=================================
[LeetCode] Beautiful Arrangement 优美排列

Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed by these N numbers successfully if one of the following is true for the ith position (1 ≤ i ≤ N) in this array:
1. The number at the ith position is divisible by i.
2. i is divisible by the number at the ith position.

    int countArrangement(int N) {
        // int res; 
        int res = 0;  // res 注意要初始化，否则y有bug 
        if (N == 0) return 0; 
        vector<bool> visit(N + 1, false);

        helper(res, N, visit, 1);  // 1 为参数  
       // helper(res, N, visit, 0);
        return res; 
    }
    
    void helper(int& res, int num, vector<bool>& visit, int pos) {
        if (pos > num) { 
            res++;
            return; 
        }
        
        for (int i = 1; i <= num ; ++i) {  // 从1开始循环
           
            // if (visit[i] == false && ((pos + 1) % (i + 1) == 0 || (i + 1) % (pos + 1) == 0)) {
            if (visit[i] == false && ( pos % i == 0 || i % pos  == 0)) {
                visit[i] = true; 
                helper(res, num, visit, pos + 1);
                visit[i] = false; 
            }

        }
        return; 
    }

================================      
784. Letter Case Permutation
Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.  Return a list of all possible strings we could create.
Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]

    vector<string> letterCasePermutation(string S) {
        vector<string> res; 
        int n = S.size();
        // for (int i = 0; i < S.size(); ++i)
        helper(S, res, 0); 
        
        return res; 
    }
    
    void helper(string S, vector<string>& res, int i) {
        if (i == S.size()) { 
            res.push_back(S); 
            return; 
        } 
        
        helper(S, res, i+1);   // 先打印原字符串，然后从最后一个字符backtracking  
        // if (!isalpha(S[i])) return;
        if (isalpha(S[i])) {
        
            if (S[i] <= 127 && S[i] >= 97) S[i] -= 32; 
            else if (S[i] <= 90 && S[i] >= 65) S[i] += 32; 
        
            // res.push_back(S);
            helper(S, res, i + 1); 
        
            if (S[i] <= 127 && S[i] >= 97) S[i] -= 32; 
            else if (S[i] <= 90 && S[i] >= 65) S[i] += 32; 
        } else 
            return;   // 若遇到数字时则返回，不修改数字之后的字符，因为数字之后的字符都已经更改了 
    
    }



==================================

216. Combination Sum III

Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
Note:
All numbers will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: k = 3, n = 7
Output: [[1,2,4]]
Example 2:

Input: k = 3, n = 9
Output: [[1,2,6], [1,3,5], [2,3,4]]

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ret; 
        vector<int> vec; 
        
        if (k == 0) return ret; 
        
        helper(k, n, ret, vec, 1);
        // helper(k, n, ret, vec, 0)
        
        return ret; 
    }
    
    void helper(int k, int n, vector<vector<int>>& ret, vector<int>& vec, int idx) {
        // if (k == 0 && n == 0) {
        if (k == vec.size() && n == 0) {    
            ret.push_back(vec);            
            return;
        }
        
        if (n < 0) return; 
        
        // for (int i = idx; i < k; ++i) {
        for (int i = idx; i <= 9; ++i) {
            
            // vec.push_back(idx); 
            // helper(k, n - idx, ret, vec, idx + 1);
            vec.push_back(i); 
            helper(k, n - i, ret, vec, i + 1);  // 注意下标, 因为数字不能重复使用，所以传入i 
            // helper(k, n - i, ret, vec, idx + 1);  // 注意下标, 若数字可以重复使用，则传入idx
            vec.pop_back(); 
        }
        
    }


[LeetCode] Subsets 子集合
 
Given a set of distinct integers, S, return all possible subsets.
Note:

Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If S = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]


vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> vec; 
    vector<vector<int>> res; 
    sort(nums.begin(), nums.end()); 

    helper(nums, vec, res, 0);
    return res; 
}

void helper(vector<int>& nums, vector<int>& vec, vector<vector<int>>& res, int idx) {
    res.push_back(vec);   // 先push_back

    for (int i = idx; i < nums.size(); ++i) {
        vec.push_back(nums[i]);
        helper(nums, vec, res, i+1);
        vec.pop_back(); 
         // while(i > 0 && i < nums.size() && nums[i] == nums[i - 1] ) ++i;  为什么这一行有bug 
         // while (i + 1 < nums.size() && nums[i] == nums[i + 1]) ++i;
    }
    
}



[LeetCode] Subsets II 子集合之二
Given a collection of integers that might contain duplicates, S, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If S = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> vec; 
    vector<vector<int>> res; 
    sort(nums.begin(), nums.end()); 

    helper(nums, vec, res, 0);
    return res; 
}

void helper(vector<int>& nums, vector<int>& vec, vector<vector<int>>& res, int idx) {
    res.push_back(vec);
    for (int i = idx; i < nums.size(); ++i) {
        vec.push_back(nums[i]);
        helper(nums, vec, res, i+1);
        vec.pop_back(); 
         // while(i > 0 && i < nums.size() && nums[i] == nums[i - 1] ) ++i;  为什么这一行有bug 
         while (i + 1 < nums.size() && nums[i] == nums[i + 1]) ++i;
    }
    
}


=======================================  

[LeetCode] LRU Cache 最近最少使用页面置换缓存器
 

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

 

这道题让我们实现一个LRU缓存器，LRU是Least Recently Used的简写，就是最近最少使用的意思。那么这个缓存器主要有两个成员函数，get和put，其中get函数是通过输入key来获得value，如果成功获得后，这对(key, value)升至缓存器中最常用的位置（顶部），如果key不存在，则返回-1。而put函数是插入一对新的(key, value)，如果原缓存器中有该key，则需要先删除掉原有的，将新的插入到缓存器的顶部。如果不存在，则直接插入到顶部。若加入新的值后缓存器超过了容量，则需要删掉一个最不常用的值，也就是底部的值。具体实现时我们需要三个私有变量，cap, l和m，其中cap是缓存器的容量大小，l是保存缓存器内容的列表，m是哈希表，保存关键值key和缓存器各项的迭代器之间映射，方便我们以O(1)的时间内找到目标项。

然后我们再来看get和put如何实现，get相对简单些，我们在m中查找给定的key，如果存在则将此项移到顶部，并返回value，若不存在返回-1。对于put，我们也是现在m中查找给定的key，如果存在就删掉原有项，并在顶部插入新来项，然后判断是否溢出，若溢出则删掉底部项(最不常用项)。代码如下：  


template<typename T>
class LRUCache {
public: 
	LRUCache(T capacity) {
		cap = capacity; 
	}


	template<typename T> 
	T get(T key) {
		auto it = m.find(key); 
		if (it == m.end()) return -1; 
		l.splice(l.begin(), l, it->second); 
		return it->second->second; 
		// if (!m.count(key)) return -1; 

	}

	void put(T key, T value) {
		auto it = m.find(key); 
		if (it != m.end()) l.erase(it->second); 
		l.push_front(make_pair(key, value));
		m[key] = l.begin(); 

		if(m.size() > cap) {
			T k = l.rbegin()->first; 
			l.pop_back(); 
			m.erase(k); 
		}

	}

private: 
	T cap; 
	list<pair<T, T>> l;  // key, value
	unordered_map<T, list<pair<T, T>>::iterator> m;  // key, iterator 

}; 

---------------------------


class LRUCache {
public: 
	LRUCache (int capacity) {
		cap = capacity; 
	}

	void put(int key, int value) {
		auto it = m.find(key); 
		if (it != m.end()) {
			l.erase(it->second); 
			l.push_front(make_pair(key, value));  
			m[key] = l.begin(); 
		} else {
			// l.push_front(*(it));   // wrong !!!!!!1 
			l.push_front(make_pair(key, value)); 
			m[key] = l.begin();  
			// m.push_back(key, l.begin());   // wrong !!!!!! 

		}

		if (m.size() > cap) {
			int k = l.rbegin()->first;  // first get the key   
			m.erase(k);     //erase element in the m  
			l.pop_back();    // erase element in the l  
		}
	}


	int get(int key) {
		auto it = m.find(key); 
		if (it != m.end()) {
			l.splice(l.begin(), l, it->second);
			return it->second->second; 
		}
		else return -1; 

	}

private: 
	int cap; 
	list<pair<int, int>> l; 
	unordered_map<int, list<pair<int, int>>::iterator> m; 
}; 


list<pair<int, int>> l; 
unordered_map<int, list<pair<init, int>>::iterator> m; 

=================================== 


98. Validate Binary Search Tree 验证二叉搜索树, validate bst 

Given a binary tree, determine if it is a valid binary search tree (BST).  

时间复杂度O(n)，空间复杂度O(logn)
T(n) = 2T(n/2) => O(n)




bool isValidBST(TreeNode *root) {
    return isValidBST(root, LONG_MIN, LONG_MAX);
}

bool isValidBST(TreeNode *root, long mn, long mx) {
    if (!root) return true;
    if (root->val <= mn || root->val >= mx) return false;
    return isValidBST(root->left, mn, root->val) && isValidBST(root->right, root->val, mx);
}



recursive: 
通过中序遍历将所有的节点值存到一个数组里，然后再来判断这个数组是不是有序的
时间复杂度O(n)，空间复杂度O(n)


bool isValidBST(TreeNode* root) {
	if (!root) return true; 
	vector<TreeNode*> vals; 
	inorder(root, vals); 

	for (int i = 0; i < vals.size() - 1; ++i) {
		if (vals[i] >= vals[i+1]) return false; 
	}
	return true; 

}

void inorder(TreeNode* root, vector<TreeNode*>& vals) {
	if (!root) return; 

	inorder(root->left, vals); 
	vals.push_back(root->val); 
	inorder(root->right, vals); 
}


iterative: 
bool isValidBST(TreeNode* root) {

	stack<TreeNode*> s; 
	TreeNode* cur = root, *pre = NULL; 

	while(cur || !s.empty()) {
		while(cur) {
			s.push(cur); 
			cur = cur->left;
		}
		TreeNode* t = s.top(); s.pop(); 
		if (pre && pre->val >= t->val) return false; 
		pre = t; 
		cur = t->right; 

	}
	return true; 
}




Balanced Binary Tree 平衡二叉树  
Given a binary tree, determine if it is height-balanced.
For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

求二叉树是否平衡，根据题目中的定义，高度平衡二叉树是每一个节点的两个字数的深度差不能超过1，那么我们肯定需要一个求各个点深度的函数，然后对每个节点的两个子树来比较深度差，时间复杂度为O(NlgN)，代码如下：



bool isBalanced(TreeNode* root) {
	if(!root) return true; 
	if(abs(height(root->left) - height(root->right)) > 1) return false; 
	return isBalanced(root->left) && isBalanced(root->right); 

}

int height(TreeNode* root) {
	if (!root) return 0; 
	return 1 + max(height(root->left), height(root->right)); 
}

--------------------

int findKthLargest(vector<int>& nums, int k) {
	priority_queue<int> q(nums.begin(), nums.end()); 
	for (int i = 0; i < q.size() - k; ++i) {
		q.pop(); 
	}
	return q.top(); 

}


int findKthLargest(vector<int>& nums, int k) {
	int left = 0, right = nums.size() - 1; 
	while (true) {
		int pos = partition(nums, left, right); 
		if (pos == k - 1) return nums[k-1]; 
		else if (pos > k - 1) right = pos - 1; 
		else  left = pos + 1; 
	}

}


int partition(vector<int>& nums, int left, int right) {
	int pivot = nums[left]; 
	int l = left + 1, r = right; 

	while (l <= r) {
		if (nums[l] < pivot && nums[right] > pivot) {
			swap(nums[l++], nums[r--]); 
		}

		if (nums[l] >= pivot) l++; 
		if (nums[r] <= pivot) r--; 

	}
	swap(nums[left], nums[r]); 
	return r; 

}



string minWindow(string S, string T) {
	if (T.size() > S.size()) return ""; 

	string res = ""; 

	unordered_map<char, int> m; 
	for (int i = 0; i < T.size(); ++i) {
		if (m.count(T[i]))
			m[T[i]]++; 
		else 
			m[T[i]] = 1; 
	}

	int left = 0; 
	int count = 0; 
	int minLen = S.size() + 1; 

	for (int right = 0; right < S.size(); ++i) {
		if (m.count(S[right])) { 
			m[S[right]]--; 
			if (m[S[right]] >= 0)
				++count; 

			while (count == T.size()) {

				if (right - left + 1 > minLen) {
					minLen = right - left + 1; 
					res = S.substr(left, minLen); 
				}

				if (m.count(S[left])) {
					++m[S[left]]; 
					if (m[S[left]] > 0) --count; 
				}
				++left; 

			}	

		}
	}

	return res; 
}



=======================

[LeetCode] Valid Sudoku 验证数独
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

A partially filled sudoku which is valid.
Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.

这道题让我们验证一个方阵是否为数独矩阵，判断标准是看各行各列是否有重复数字，以及每个小的3x3的小方阵里面是否有重复数字，如果都无重复，则当前矩阵是数独矩阵，但不代表待数独矩阵有解，只是单纯的判断当前未填完的矩阵是否是数独矩阵。那么根据数独矩阵的定义，我们在遍历每个数字的时候，就看看包含当前位置的行和列以及3x3小方阵中是否已经出现该数字，那么我们需要三个标志矩阵，分别记录各行，各列，各小方阵是否出现某个数字，其中行和列标志下标很好对应，就是小方阵的下标需要稍稍转换一下，具体代码如下：


bool isValidSudoku(vector<vector<char>>& board) {
	if (board.empty() || board[0].empty()) return false; 

	int m = board.size(), n = board[0].size(); 
	vector<vector<bool>> rowFlag(m, vector<bool>(n, false)); 
	vector<vector<bool>> colFlag(m, vector<bool>(n, false)); 
	vector<vector<bool>> cellFlag(m, vector<bool>(n, false)); 

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			// if (board[i][j] >= "1" && board[i][j] <= "9") {
			if (board[i][j] == '.') continue; 

			int c = board[i][j] - '1'; 
			int x = i / 3 * 3 + c / 3; 
			int y = j / 3 * 3 + c % 3;
			if (rowFlag[i][c] || colFlag[c][j] || cellFlag[x][y])
				return false;  

			rowFlag[i][c] = true; 
			colFlag[c][j] = true; 
			cellFlag[x][y] = true;  	

		}
	}
	return true; 

}


==============================================
[LeetCode] Sudoku Solver 求解数独

Write a program to solve a Sudoku puzzle by filling the empty cells.
Empty cells are indicated by the character '.'.
You may assume that there will be only one unique solution.


   void solveSudoku(vector<vector<char>>& board) {
        if (board.size() == 0 || board[0].size() == 0 || board[0].size() != 9) 
            return;
      
        solveHelper(board);
    }
     
    bool solveHelper(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    for (char k = '1'; k <= '9'; k++) {
                        if (isValid(i, j, k, board)) {
                            board[i][j] = k;
                            if (solveHelper(board) == true) 
                                return true;
                            board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }


    bool isValid(int row, int col, char target, vector<vector<char>>& board) {
        // check the row and column
        for (int i = 0; i < 9; i++) {
            if ((board[row][i] == target) || (board[i][col] == target)) {
                return false;
            }
        }
         
        // check the block
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int x = row / 3 * 3 + i; // nth block * block_size  + offset
                int y = col / 3 * 3 + j;   
                if (board[x][y] == target) {   
                    return false;
                }
            }
        }
        return true;
    }



=====================================================
// common element of two sorted array

vector<int> intersection(vector<int>& num1, vector<int>& num2) {
	vector<int> res; 

	for (int i = 0, j = 0; i < num1.size() && j < num2.size(); ) {
		if (num1[i] < num2[j]) ++i; 
		else if (num1[i] > num2[j]) ++j; 
		else { 
			res.push_back(num1[i]); 
			++i, ++j; 
		}
	}

	return res; 
}

============================= 
// common element of k sorted array

vector<int> Kintersection(vector<vector<int>> nums) {
	vector<int> res; 
	if (nums.size() == 0) return res; 
	if (nums.size() == 1) return nums[0]; 

	res = intersection(nums[0], nums[1]); 
	for (int i = 2; i < nums.size(); ++i) {
		res = intersection(nums[i], res); 

	}

	return res; 
}

vector<int> intersection(vector<int>& num1, vector<int>& num2) {
	vector<int> res; 
	int n1 = num1.size(); 
	int n2 = num2.size();
	int i = 0, j = 0; 

	while (i < n1 && j < n2) {
		if (num1[i] < num2[j]) ++i; 
		else if (num1[i] > num2[j]) ++j; 
		else { 
			res.push_back(num1[i]); 
			++i, ++j; 
		}
	}

	return res; 
}


// common element of three sorted array

vector<int> findCommon(vector<int>& num1, vector<int>& num2, vector<int>& num3) {
	int n1 = num1.size();
	int n2 = num2.size();
	int n3 = num3.size();

	int i = 0, j = 0, k = 0; 
	vector<int> res; 

	while (i < n1 && j < n2 && k < n3) {
		if (num1[i] == num2[j] && num2[j] == num3[k]) {
			res.push_back(num1[i]);
			++i; ++j; ++k; 
		} else if (num1[i] < num2[j]) 
			++i;
		else if (num2[j] < num3[k]) 
			++j; 
		else ++k;  // 因为num1[i] > num2[j] > num3[k] 

	}
}

===================================        

1. Best Time to Buy and Sell Stock 买卖股票的最佳时间 

Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

只需要遍历一次数组，用一个变量记录遍历过数中的最小值，然后每次计算当前值和这个最小值之间的差值最为利润，然后每次选较大的利润来更新。当遍历完成后当前利润即为所求

int maxProfit(vector<int>& prices) {
    int res = 0, buy = INT_MAX;
    for (int price : prices) {
        buy = min(buy, price); // maintain global minimum price
        res = max(res, price - buy);   //  maintain local maximum profit 
    }
    return res;
}


2. Best Time to Buy and Sell Stock II 买股票的最佳时间之二 
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

这道题由于可以无限次买入和卖出。我们都知道炒股想挣钱当然是低价买入高价抛出，那么这里我们只需要从第二天开始，如果当前价格比之前价格高，则把差值加入利润中，因为我们可以昨天买入，今日卖出，若明日价更高的话，还可以今日买入，明日再抛出。以此类推，遍历完整个数组后即可求得最大利润. 这道题的前提是已经知道所有价格。

int maxProfit(vector<int>& prices) {
    int res = 0, n = prices.size();
    for (int i = 0; i < n - 1; ++i) {
        if (prices[i] < prices[i + 1]) {
            res += prices[i + 1] - prices[i];
        }
    }
    return res;
}


3. Best Time to Buy and Sell Stock III 买股票的最佳时间之三
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.
Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

 

这道是买股票的最佳时间系列问题中最难最复杂的一道，前面两道Best Time to Buy and Sell Stock 买卖股票的最佳时间和Best Time to Buy and Sell Stock II 买股票的最佳时间之二的思路都非常的简洁明了，算法也很简单。而这道是要求最多交易两次，找到最大利润，

Since the question asks for at most two transactions. For day i, we can get the maximal profit from [0, i], and the maximal profit from [i, end]. Finding the maximal profit from day [0, i] is relative easier to understand. Use a dp_left[i] stands for maximal profit from day 0 to day i. Getting the best profit from profit from day [i, end] is a bit trickier. If we still scan in forward order, for each element i, we need to scan all its following elements, so the complexity would be O(n ^ 2). If we scan from end in backward order, we need to only scan the array once. Then the maximal profit is the maximal sum of the two arrays given a day.

// int buy = INT_MAX; profit = 0;  
int buy = prices[0]; profit = 0;  
vector<int> profits(prices.size()); 
profits[0] = 0; 

for (int i = 1; i < prices.size(); ++i) {
	buy = min (buy, prices[i]); 
	// profit = max(profit, prices[i] - buy); 
	// profits[i] = profit; 
	profits[i] = max(profits[i-1], prices[i] - buy); 
}

int sell = prices[prices.size() - 1]; 
// int sell = INT_MIN; 
int best = 0; 
for (int i = prices.size() - 2; i >= 0; --i) {
	sell = max(sell, prices[i]); 
	best  = max( best, sell - prices[i] + profits[i]); 

}

return best; 

////////////////////////////////


int maxProfit(vector<int>& prices) {  
	if (prices.size() == 0) return 0; 

	vector<int> profit(prices.size()); 

	int buy = prices[0]; 
	profit[0] = 0; 

	for (int i = 1; i < prices.size(); ++i) {
		profit[i] = max(profit[i-1], prices[i] - buy);
		buy = min(buy, prices[i]);  
	}

	int sell = prices[prices.size() - 1]; 
	int res = 0; 

	for(int i = prices.size() - 2; i >= 0; --i) {
		res = max(res, sell - prices[i] + profit[i]); 
		sell = min(sell, prices[i]); 
	}

	return res; 
}




////////////////////////=========================

[LeetCode] Palindromic Substrings 回文子字符串
 

Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:

Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
 

Example 2:

Input: "aaa"
Output: 
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

Note:

The input string length will not exceed 1000.

     bool isPalindrome(string str) {
        int i = 0, j = str.size() -1; 
        while(i <= j) {
            if (str[i] != str[j]) return false;  
            ++i, --j; 
        }
        return true; 
    }
    
    int countSubstrings(string s) {
        int ret = 0;   // 注意要初始化为0  
        
        for (int i = 0; i < s.size(); ++i) {
            for (int j = 1; j <= s.size() - i ; ++j) {
                string temp = s.substr(i, j);
                if(isPalindrome(temp)) ret++; 
            }
            
        }
        
        return ret;
    }
    
博主看到这个题，下意识的想着应该是用DP来做，哼哼哧哧写了半天，修修补补，终于通过了，但是博主写的DP不是最简便的方法，略显复杂，这里就不贴了。还是直接讲解大神们的解法好了。其实这道题也可以用递归来做，而且思路非常的简单粗暴。就是以字符串中的每一个字符都当作回文串中间的位置，然后向两边扩散，每当成功匹配两个左右两个字符，结果res自增1，然后再比较下一对。注意回文字符串有奇数和偶数两种形式，如果是奇数长度，那么i位置就是中间那个字符的位置，所以我们左右两遍都从i开始遍历；如果是偶数长度的，那么i是最中间两个字符的左边那个，右边那个就是i+1，这样就能cover所有的情况啦，而且都是不同的回文子字符串，

    int countSubstrings(string s) {
        if (s.empty()) return 0;
        int n = s.size(), res = 0;
        for (int i = 0; i < n; ++i) {
            helper(s, i, i, res);
            helper(s, i, i + 1, res);
        }
        return res;
    }

    void helper(string s, int i, int j, int& res) {
        while (i >= 0 && j < s.size() && s[i] == s[j]) {
            --i; ++j; ++res;
        }
    }

======================================  
[LeetCode] Task Scheduler 任务行程表
 

Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1:

Input: tasks = ['A','A','A','B','B','B'], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
 

Note:

The number of tasks is in the range [1, 10000].
The integer n is in the range [0, 100].


这道题让我们安排CPU的任务，规定在两个相同任务之间至少隔n个时间点。说实话，刚开始博主并没有完全理解题目的意思，后来看了大神们的解法才悟出个道理来。下面这种解法参考了大神fatalme的帖子，由于题目中规定了两个相同任务之间至少隔n个时间点，那么我们首先应该处理的出现次数最多的那个任务，先确定好这些高频任务，然后再来安排那些低频任务。如果任务F的出现频率最高，为k次，那么我们用n个空位将每两个F分隔开，然后我们按顺序加入其他低频的任务，来看一个例子：

AAAABBBEEFFGG 3

我们发现任务A出现了4次，频率最高，于是我们在每个A中间加入三个空位，如下：

A---A---A---A

AB--AB--AB--A   (加入B)

ABE-ABE-AB--A   (加入E)

ABEFABE-ABF-A   (加入F，每次尽可能填满或者是均匀填充)

ABEFABEGABFGA   (加入G)

再来看一个例子：

ACCCEEE 2

我们发现任务C和E都出现了三次，那么我们就将CE看作一个整体，在中间加入一个位置即可：

CE-CE-CE

CEACE-CE   (加入A)

注意最后面那个idle不能省略，不然就不满足相同两个任务之间要隔2个时间点了。

这道题好在没有让我们输出任务安排结果，而只是问所需的时间总长，那么我们就想个方法来快速计算出所需时间总长即可。我们仔细观察上面两个例子可以发现，都分成了(mx - 1)块，再加上最后面的字母，其中mx为最大出现次数。比如例子1中，A出现了4次，所以有A---模块出现了3次，再加上最后的A，每个模块的长度为4。例子2中，CE-出现了2次，再加上最后的CE，每个模块长度为3。我们可以发现，模块的次数为任务最大次数减1，模块的长度为n+1，最后加上的字母个数为出现次数最多的任务，可能有多个并列。这样三个部分都搞清楚了，写起来就不难了，我们统计每个大写字母出现的次数，然后排序，这样出现次数最多的字母就到了末尾，然后我们向前遍历，找出出现次数一样多的任务个数，就可以迅速求出总时间长了

     int leastInterval(vector<char>& tasks, int n) {
      int ret = 0; 
      vector<int> vec(26, 0); 
      for (auto c : tasks) 
          vec[c - 'A']++; 
         
      sort(vec.begin(), vec.end());
      int i = 25; int mx = vec[25]; 
      while (i >= 0 && vec[i] == mx) i--; 
         
      int size = tasks.size(); 
        ret = max(size, (mx - 1) * (n + 1) + 25-i);  
         
      return ret; 
    }


//////////////////////////////////////////////////

[LeetCode] Merge Two Binary Trees 合并二叉树
Given two binary trees and imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not.

You need to merge them into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of new tree.

Example 1:

Input: 
	Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
Output: 
Merged tree:
	     3
	    / \
	   4   5
	  / \   \ 
	 5   4   7
 

Note: The merging process must start from the root nodes of both trees.
这道题给了我们两个二叉树，让我们合并成一个，规则是，都存在的结点，就将结点值加起来，否则空的位置就由另一个树的结点来代替。那么根据过往经验，处理二叉树问题的神器就是递归，那么我们来看递归函数如何去写。根据题目中的规则，我们知道如果要处理的相同位置上的两个结点都不存在的话，直接返回即可，如果t1存在，t2不存在，那么我们就以t1的结点值建立一个新结点，然后分别对t1的左右子结点和空结点调用递归函数，反之，如果t1不存在，t2存在，那么我们就以t2的结点值建立一个新结点，然后分别对t2的左右子结点和空结点调用递归函数。如果t1和t2都存在，那么我们就以t1和t2的结点值之和建立一个新结点，然后分别对t1的左右子结点和t2的左右子结点调用递归函数，参见代码如下：


    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        TreeNode *t = new TreeNode(t1->val + t2->val);
        t->left = mergeTrees(t1->left, t2->left);
        t->right = mergeTrees(t1->right, t2->right);
        return t;
    }


581. Shortest Unsorted Continuous Subarray
Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too. 
You need to find the shortest such subarray and output its length.

Example 1:
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
 
Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=. 

这道题给了我们一个数组，让我们求最短的无序连续子数组，根据题目中的例子也不难分析出来是让我们找出数组中的无序的部分。那么我最开始的想法就是要确定无序子数组的起始和结束位置，这样就能知道子数组的长度了。所以我们用一个变量start来记录起始位置，然后我们开始遍历数组，当我们发现某个数字比其前面的数字要小的时候，说明此时数组不再有序，所以我们要将此数字向前移动，移到其应该在的地方，我们用另一个变量j来记录移动到的位置，然后我们考虑要不要用这个位置来更新start的值，当start还是初始值-1时，肯定要更新，因为这是出现的第一个无序的地方，还有就是如果当前位置小于start也要更新，这说明此时的无序数组比之前的更长了。我们举个例子来说明，比如数组[1,3,5,4,2]，第一个无序的地方是数字4，它移动到的正确位置是坐标2，此时start更新为2，然后下一个无序的地方是数字2，它的正确位置是坐标1，所以此时start应更新为1，这样每次用i - start + 1来更新结果res时才能得到正确的结果


  int findUnsortedSubarray(vector<int>& nums) {
        // int ret = 0; 
        vector<int> vec(nums.begin(), nums.end());
        sort(vec.begin(), vec.end()); 
        int i = 0, j = vec.size() - 1; 
        while(i < j) {
            if (nums[i] == vec[i] && nums[j] == vec[j]) {++i; --j;}
            else if(nums[i] == vec[i]) {++i;}
            else if (nums[j] == vec[j]) {--j;}
            else break; 
        }
        if (i < j)
            return j - i + 1; 
        else return 0; 
    }


572. Subtree of Another Tree

[LeetCode] Subtree of Another Tree 另一个树的子树
Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this nodes descendants. The tree scould also be considered as a subtree of itself.

 bool isSubtree(TreeNode* s, TreeNode* t) {
        if (!s) return false; 
        // if (!t) return true;  // 这句不能有
        
        return theSame(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
        
    }
    
    bool theSame(TreeNode* s1, TreeNode* s2) {
        if (!s1 && !s2) return true; 
        if (!s1 || !s2) return false;  // additional key sentence 
        if (s1->val != s2->val) return false; 
        return theSame(s1->left, s2->left) && theSame(s1->right, s2->right);
        
    }

================================================= 
[LeetCode] Subarray Sum Equals K 子数组和为K

Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:
Input:nums = [1,1,1], k = 2
Output: 2

int subarraySum(vector<int>& nums, int k) {
    int res = 0, n = nums.size();
    vector<int> sums = nums;
    for (int i = 1; i < n; ++i) {
        sums[i] = sums[i - 1] + nums[i];
    }
    for (int i = 0; i < n; ++i) {
        if (sums[i] == k) ++res;
        for (int j = i - 1; j >= 0; --j) {
            if (sums[i] - sums[j] == k) ++res;
        }
    }
    return res;
}


// better solution 
  int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m; 
        m[0] = 1;  // 对应[1,1,1] 2 的test case  
        int ret = 0;
        int sum = 0; 
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i]; 
            ret += m[sum - k]; // 这一行一定要在下一行之前，否则有bug: e.g.,  [1] 0  
            m[sum]++;         
        }
        return ret; 
    }

================================= 
[LeetCode] Diameter of Binary Tree 二叉树的直径
 
Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longestpath between any two nodes in a tree. This path may or may not pass through the root.
Example:
Given a binary tree 

          1
         / \
        2   3
       / \     
      4   5    
 
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
Note: The length of path between two nodes is represented by the number of edges between them.

    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0; 
        // 有最长diameter三种可能
        int a = height(root->left) +  height(root->right);
        int b = diameterOfBinaryTree(root->left); 
        int c = diameterOfBinaryTree(root->right); 
        return max(a, max(b, c)); 
    }
    
    int height(TreeNode* root) {
        if (!root) return 0; 
        return 1 + max(height(root->left), height(root->right));  
    }

// better solution 
  int diameterOfBinaryTree(TreeNode* root) {
        int res = 0;
        maxDepth(root, res);
        return res;
    }
    int maxDepth(TreeNode* node, int& res) {
        if (!node) return 0;
        int left = maxDepth(node->left, res);
        int right = maxDepth(node->right, res);
        res = max(res, left + right);
        return max(left, right) + 1;
    }


================================================== 
[LeetCode] Convert BST to Greater Tree 将二叉搜索树BST转为较大树
 

Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

Example:

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13



  TreeNode* convertBST(TreeNode* root) {
        
        deque<int> vec; 
        inorder1(root, vec); 
        for (int i = vec.size() - 2; i >= 0; --i) {
            vec[i] += vec[i+1]; 
        }
        inorder2(root, vec); 
        
        return root; 
        
    }
    
    void inorder2(TreeNode* root, deque<int>& vec) {
        if (!root) return; 
        inorder2(root->left, vec);
        root->val = vec.front(); 
        vec.pop_front(); 
        inorder2(root->right, vec); 

    }
    
    void inorder1(TreeNode* root, deque<int>& vec) {
        if (!root) return; 
        inorder1(root->left, vec); 
        vec.push_back(root->val);
        inorder1(root->right, vec);
        
    }


  ==================================
// better solution 
不用先求出的所有的结点值之和，而是巧妙的将中序遍历左根右的顺序逆过来，变成右根左的顺序，这样就可以反向计算累加和sum，同时更新结点值

  TreeNode* convertBST(TreeNode* root) {
        if (!root) return NULL;
        int sum = 0; 
        helper(root, sum);
  
        return root; 
    }
    
    void helper(TreeNode* root, int& sum) {
        if(!root) return;
        helper(root->right, sum);
    
        sum += root->val; 
        root->val = sum; 
         
        helper(root->left, sum);
    }

-------------------
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
    	if (!root) return NULL;
    // int sum = 0; 
    	convertBST(root->right);
    	sum += root->val; 
    	root->val = sum; 
    	convertBST(root->left);
        return root; 
    }
private:
     int sum = 0; 
};


=================================  

[LeetCode] Target Sum 目标和
You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S.
Example 1:
Input: nums is [1, 1, 1, 1, 1], S is 3. 
Output: 5
Explanation: 
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3
There are 5 ways to assign symbols to make the sum of nums be target 3.

   int findTargetSumWays(vector<int>& nums, int S) {
        int res = 0;
        helper(nums, S, 0, res);
        return res;
    }
    void helper(vector<int>& nums, int S, int start, int& res) {
        if (start >= nums.size()) {
            if (S == 0) ++res;
            return;
        }
        helper(nums, S - nums[start], start + 1, res);
        helper(nums, S + nums[start], start + 1, res);
    }


==================================    

1. Hamming Distance 汉明距离  

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
Given two integers x and y, calculate the Hamming distance.
Note:
0 ≤ x, y < 231.
Example:
Input: x = 1, y = 4
Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different.

这道题让我求两个数字之间的汉明距离，题目中解释的很清楚了，两个数字之间的汉明距离就是其二进制数对应位不同的个数，那么最直接了当的做法就是按位分别取出两个数对应位上的数并异或，我们知道异或的性质上相同的为0，不同的为1，我们只要把为1的情况累加起来就是汉明距离了

// 时间复杂度O(n)，空间复杂度O(1)
int hammingDistance(int x, int y) {
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        if ((x & (1 << i)) ^ (y & (1 << i))) {
            ++res;
        }
    }
    return res;
}

solution 2: 
我们可以一开始直接将两个数字异或起来，然后我们遍历异或结果的每一位，统计为1的个数
    int hammingDistance(int x, int y) {
        int t = x ^ y; 
        int count = 0; 
        for (int i = 0; i < 32; ++i) {
            if ((t >> i) & 1) 
                count++; 
        }
        return count; 
    }


solution 3: 
上面的遍历每一位的方法并不高效，还可以进一步优化，假如数为num, num & (num - 1)可以快速地移除最右边的bit 1， 一直循环到num为0, 总的循环数就是num中bit 1的个数
int hammingDistance(int x, int y) {
        int t = x ^ y; 
        int count = 0; 
            
        while(t) {
	        t  = t & (t-1); 
            count++; 
        }
        return count; 
    }

=============================   

[LeetCode] Find All Numbers Disappeared in an Array 找出数组中所有消失的数字
 Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
Find all the elements of [1, n] inclusive that do not appear in this array.
Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:
Input:
[4,3,2,7,8,2,3,1]
Output:
[5,6]


  vector<int> findDisappearedNumbers(vector<int>& nums) {
        unordered_map<int, int> m; 
        for (auto n : nums) {
            if (m.count(n)) m[n]++; 
            else m[n] = 1; 
        }
        vector<int> res; 
        for (int i = 1; i <= nums.size(); ++i) {
            if (m[i] == 0) res.push_back(i);
        }
        return res; 
    }  

// better solution, 有点绕
   // 若数字i(1 <= i <= n)存在，则index i-1上面的数字设为负数，无论那个数字是否是i             
vector<int> findDisappearedNumbers(vector<int>& nums) {
    vector<int> res; 
    int index = 0; 
    for (int i = 0; i < nums.size();++i) {
        index = abs(nums[i]) - 1; 
        
        if(nums[index] < 0) nums[index] = nums[index]; 
        else nums[index] = -nums[index]; 
    }
        
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0) res.push_back(i+1);
    }
    return res; 
}

=====================================  

[LeetCode] Find All Anagrams in a String 找出字符串中所有的变位词
Given a string s and a non-empty string p, find all the start indices of p anagrams in s.
Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.
The order of output does not matter.
Example 1:
Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

我们可以将上述代码写的更加简洁一些，用两个哈希表，分别记录p的字符个数，和s中前p字符串长度的字符个数，然后比较，如果两者相同，则将0加入结果res中，然后开始遍历s中剩余的字符，每次右边加入一个新的字符，然后去掉左边的一个旧的字符，每次再比较两个哈希表是否相同即可 


 vector<int> findAnagrams(string s, string p) {
        if (s.empty()) return {};
        vector<int> res, m1(256, 0), m2(256, 0);
        for (int i = 0; i < p.size(); ++i) {
            ++m1[s[i]]; ++m2[p[i]];
        }
        if (m1 == m2) res.push_back(0);
        for (int i = p.size(); i < s.size(); ++i) {
            ++m1[s[i]]; 
            --m1[s[i - p.size()]];
            if (m1 == m2) res.push_back(i - p.size() + 1);
        }
        return res;
    }  

============================

[LeetCode] Path Sum III 二叉树的路径和之三
 

You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11

// better solution 

 int pathSum(TreeNode* root, int sum) {
        int res = 0;
        vector<TreeNode*> out;
        helper(root, sum, 0, out, res);
        return res;
    }
    void helper(TreeNode* node, int sum, int curSum, vector<TreeNode*>& out, int& res) {
        if (!node) return;
        curSum += node->val;
        out.push_back(node);
        if (curSum == sum) ++res;
        int t = curSum;
        for (int i = 0; i < out.size() - 1; ++i) {
            t -= out[i]->val;
            if (t == sum) ++res;
        }
        helper(node->left, sum, curSum, out, res);
        helper(node->right, sum, curSum, out, res);
        out.pop_back();
    }

   ========================================= 

 int dfs_next(TreeNode *root, int cur, int target){
        if(root == NULL)
            return 0;
        int sum = 0;
        if(cur + root->val == target){
            sum++;
        }
        sum += dfs_next(root->left, cur+root->val, target);
        sum += dfs_next(root->right, cur+root->val, target);
        
        return sum;
        
    }
    int dfs(TreeNode *root, int cur, int target){
        if(root == NULL)   
            return 0;
        int sum = 0;

        sum += dfs(root->left, 0, target);
        sum += dfs(root->right, 0, target); 

        return sum + dfs_next(root, cur, target);
    }
    int pathSum(TreeNode* root, int target) {

        int t =  dfs(root, 0, target);
        return t;

    }

=====================================    

[LeetCode] Partition Equal Subset Sum 相同子集和分割
 

Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Note:
Both the array size and each of the array element will not exceed 100.

Example 1:

Input: [1, 5, 11, 5]

Output: true

Explanation: The array can be partitioned as [1, 5, 5] and [11].

// 这解法超时了
 bool canPartition(vector<int>& nums) {
        int sum = 0; 
        for(auto a : nums) {
            sum += a; 
        }
        if (sum % 2 == 1) return false; 
        int target = sum / 2; 
        for (int i = 0; i < nums.size(); ++i) {
            if( helper(nums, target, i)) return true; 
        }
        
        return false; 
        
    }
    
    bool helper(vector<int>& nums, int target, int idx) {
        if (target == 0) return true; 
        if(idx >= nums.size()) return false; 
        
        bool ret = helper(nums, target - nums[idx], idx + 1) ||
            helper(nums, target, idx + 1) ;
        
        return ret; 
    }

// 最好的解法，90% 
  bool canPartition(vector<int>& nums) {
        int sum = 0; 
        for(auto a : nums) {
            sum += a; 
        }
        if (sum % 2 == 1) return false; 
        int target = sum / 2; 
        // for (int i = 0; i < nums.size(); ++i) {
            // if( helper(nums, target, i)) return true; 
        // }
        
        sort(nums.begin(), nums.end());  // 先排序
        
        if( helper(nums, target, 0)) return true; 

        return false; 
    }
    
    bool helper(vector<int>& nums, int target, int idx) {
        if (target == 0) return true; 
        if (target < 0) return false;   // 这句话很重要，否则会超时
        if(idx >= nums.size()) return false; 
        
         // int k = idx； // wrong
        int k = idx + 1;  // 目的是为了减少运算, 若要跳过某个元素，则所有该元素都跳过 
        while(k <= nums.size()  && nums[k] == nums[k+1]){
            k++;
        }
         
        bool ret = helper(nums, target - nums[idx], idx + 1) ||  helper(nums, target, k) ;
            // helper(nums, target, idx + 1) ;  // 选择nums[idx] || 不选择nums[idx]       
        return ret; 
    }

====================

[LeetCode] Queue Reconstruction by Height 根据高度重建队列
 
Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers(h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.

Example
Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

这道题给了我们一个队列，队列中的每个元素是一个pair，分别为身高和前面身高不低于当前身高的人的个数，让我们重新排列队列，使得每个pair的第二个参数都满足题意。首先我们来看一种超级简洁的方法，不得不膜拜想出这种解法的大神。首先我们给队列先排个序，按照身高高的排前面，如果身高相同，则第二个数小的排前面。然后我们新建一个空的数组，遍历之前排好序的数组，然后根据每个元素的第二个数字，将其插入到res数组中对应的位置. 

  vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(), people.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first > b.first || (a.first == b.first && a.second < b.second);  // 按照身高从高到低排序, 第二个数字小的排前面
        });
        vector<pair<int, int>> res;
        for (auto a : people) {
            res.insert(res.begin() + a.second, a);
        }
        return res;
    }



[LeetCode] Top K Frequent Elements 前K个高频元素
 
Given a non-empty array of integers, return the k most frequent elements.
For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].
Note:
    You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
    Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

让我们统计前k个高频的数字，那么对于这类的统计数字的问题，首先应该考虑用HashMap来做，建立数字和其出现次数的映射，然后再按照出现次数进行排序。我们可以用堆排序来做，使用一个最大堆来按照映射次数从大到小排列，在C++中使用priority_queue来实现，默认是最大堆

  vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        priority_queue<pair<int, int>> q;
        vector<int> res;
        for (auto a : nums) ++m[a];
        for (auto it : m) q.push({it.second, it.first});
        for (int i = 0; i < k; ++i) {
            res.push_back(q.top().second); q.pop();
        }
        return res;
    }



    unordered_map<int, int> m; 
    priority_queue<pair<int, int>> q; 
    vector<int> res; 

    for (auto n : nums) {
    	m[n]++; 
    }
    for (auto it : m) q.push({it->second, it->first}); 
    for (int i = 0; i < k; ++i) {
    	res.push_back(q.top().second); q.pop(); 
    }

    return res; 



求一个数1的个数的三种方法： 

int count(int n) {
    int res = 0; 
    while(n) {
        n = n & (n -1); 
        res++;
    }
    return res; 
}

int count(int n) {
    int res = 0; 
    for (int i = 0; i< 32; ++i)
        if (n >> i & 1) res++; 
    
    return res; 
}


int count(int n) {
    int res = 0; 
    for (int i = 0; i< 32; ++i)
        if (n & 1 << i) res++; 
    
    return res; 
}

======================================= 

Array, Maximum sum such that no two elements are adjacent  

int FindMaxSum(int arr[], int n)
{
  int incl = arr[0];
  int excl = 0;
  int excl_new;
  int i;
 
  for (i = 1; i < n; i++)
  {
     /* current max excluding i */
     excl_new = (incl > excl)? incl: excl;
 
     /* current max including i */
     incl = excl + arr[i];
     excl = excl_new;
  }
 
   /* return max of incl and excl */
   return ((incl > excl)? incl : excl);
}


==================================
Arrary, Maximum sum such that no elements are adjacent 

    int rob(vector<int> &num) {
        if (num.size() <= 1) return num.empty() ? 0 : num[0];
        vector<int> dp = {num[0], max(num[0], num[1])};
        for (int i = 2; i < num.size(); ++i) {
            dp.push_back(max(num[i] + dp[i - 2], dp[i - 1]));
        }
        return dp.back();
    }

=============================================

Binary tree, Maximum sum such that no elements are adjacent 

int rob(TreeNode* root) {
      
        if (!root) return 0;
        int res = 0;
        if (root->left) {
            res += rob(root->left->left) + rob(root->left->right);
        }
        if (root->right) {
            res += rob(root->right->left) + rob(root->right->right);
        }
        
        res = max(root->val + res, rob(root->left) + rob(root->right)); // 选root, 和不选root
        return res;

    }

// better solution 1. 

    class Solution {
public:
    int rob(TreeNode* root) {
        
        if(m.count(root)) return m[root]; 
      
        if (!root) return 0;
        int res = 0;
        if (root->left) {
            res += rob(root->left->left) + rob(root->left->right);
        }
        if (root->right) {
            res += rob(root->right->left) + rob(root->right->right);
        }
        
        res = max(root->val + res, rob(root->left) + rob(root->right)); // 选root, 和不选root
        m[root] = res; 
        
        return res;  
    }
private: 
    unordered_map<TreeNode*, int> m; 

};


// better solution 2. 
int rob(TreeNode* root) {
    
      unordered_map<TreeNode*, int> m; 
    // if (!root) return 0;
    // int res = 0;
    
    return dfs(root, m); 
    
}

int dfs(TreeNode* root, unordered_map<TreeNode*, int>& m) {
// int dfs(TreeNode* root, unordered_map<TreeNode*, int> m) {  // 不加 & m 会超时, 程序有bug 

	if (!root) return 0; 
	int res = 0; 
	if(m.count(root)) return m[root]; 

	if (root->left) {
	    res += dfs(root->left->left, m) + dfs(root->left->right, m);
	}
	if (root->right) {
	    res += dfs(root->right->left, m) + dfs(root->right->right, m);
	}

	res = max(root->val + res, dfs(root->left, m) + dfs(root->right, m)); // 选root, 和不选root
	m[root] = res; 

	return res;
}

============================================= 

[LeetCode] Coin Change 硬币找零
You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.

int coinChange(vector<int>& coins, int amount) {
    sort(coins.begin(), coins.end());
    int res = INT_MAX;
     
    helper(res, coins, amount, coins.size() - 1, 0);
     
    return res == INT_MAX ? -1 : res;
}
 
void helper(int& res, vector<int>& coins, int amount, int idx, int count){
// void helper(int& res, vector<int>& coins, int* amount, int* idx, int* count){  // error when *, because amount - i * coins[idx], idx - 1, count + i 
    if (idx < 0) return;
    if (amount % coins[idx] == 0) {
        res = min( res, count + amount / coins[idx] );
        return;
    }
     
    for (int i = amount/coins[idx]; i >= 0; --i) { // i=0则不选coins[idx] 
        if (count + i >= res ) break;    // pruing, count + i 存的是 目前为止新count的硬币数目

        helper(res, coins, amount - i * coins[idx], idx - 1, count + i);
}

===================================  
[LeetCode] Count of Smaller Numbers After Self 计算后面较小数字的个数
 
You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].
Example:

Given nums = [5, 2, 6, 1]
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].

这道题给定我们一个数组，让我们计算每个数字右边所有小于这个数字的个数，目测我们不能用brute force，OJ肯定不答应，那么我们为了提高运算效率，首先可以使用用二分搜索法，思路是将给定数组从最后一个开始，用二分法插入到一个新的数组，这样新数组就是有序的，那么此时该数字在新数组中的坐标就是原数组中其右边所有较小数字的个数

// beat 15% 
  vector<int> countSmaller(vector<int>& nums) {
        vector<int> res; 
        
        for (int i = 0; i < nums.size(); ++i) {
            res.push_back(count(nums, i));
        }
        
        return res; 
    }
    
    int count(vector<int>& nums, int i) {
        if (i == nums.size() - 1) return 0; 
        int ct = 0; 
        for (int j = i+1; j < nums.size(); ++j) {
            if (nums[j] < nums[i]) ct++;
        }    
        return ct; 
    
    }

// better solution 
   vector<int> countSmaller(vector<int>& nums) { // binary search 
        vector<int> t, res(nums.size());
        for (int i = nums.size() - 1; i >= 0; --i) {
            int left = 0, right = t.size();
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (t[mid] >= nums[i]) right = mid;
                else left = mid + 1;
            }
            res[i] = right;
            t.insert(t.begin() + right, nums[i]);
        }
        return res;
    }

======================================
[LeetCode] Burst Balloons 打气球游戏
 

Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.
Note: 
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
Example:

Given [3, 1, 5, 8]
Return 167
    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

// vec[i][j]表示打爆区间[i,j]中的所有气球能得到的最多金币
   int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
    
        vector<vector<int>> vec = vector<vector<int>>(n+2, vector<int>(n+2, 0));
        
        return maxCoins(nums, 1, n, vec);
    }

    int maxCoins(const vector<int>& nums, const int i, const int j, vector<vector<int>>& vec) {
        if(i > j) return 0;
        
        if(i == j) return nums[i-1]*nums[i]*nums[i+1];
        
        if(vec[i][j] > 0) return vec[i][j];
        
        int ans = 0;
        for(int k = i; k <= j; ++k)
             ans = max(ans, maxCoins(nums, i, k-1, vec) + nums[i-1]*nums[k]*nums[j+1] + maxCoins(nums, k+1, j, vec));
        
        vec[i][j] = ans;
        
        return vec[i][j];
    }

========================================  

2. Remove Invalid Parentheses 移除非法括号, remove parenthese  

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
Note: The input string may contain letters other than the parentheses ( and ).
Examples:
"()())() -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")( -> [""]


vector<string> removeInvalidParentheses(string s) {
    vector<string> res;
    unordered_map<string, int> visited;  // 用于remove duplicate
    queue<string> q; // 通过queue FIFO 来实现minimum. 因为queue里的string长度最多相差1，所以若某一string是valid, 则比这string长度小1的string肯定不是valid. 要(,)为偶数个，奇数个(,)肯定不valid                   
    q.push(s);              
    ++visited[s];              
    bool found = false;          

    while (!q.empty()) {                                   
        s = q.front(); q.pop();                       
        if (isValid(s)) {                    
            res.push_back(s);               
            found = true;                 
        }                    
        if (found) continue;  // 目的是跳过下面的循环                    

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != '(' && s[i] != ')') continue;  // ignore the letters aren't (,)  
            string t = s.substr(0, i) + s.substr(i + 1);  // remove the ith letter 
            if (visited.find(t) == visited.end()) {   // remove duplicate string 
                q.push(t);      
                ++visited[t];          
            }
        }
    }
    return res;
}


bool isValid(string t) { // ignore the letters aren't (,)  
    int cnt = 0;
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] == '(') ++cnt;
        // if (t[i] == ')' && cnt-- == 0) return false; 
        if (t[i] == ')' && cnt == 0) return false;
        else cnt--;  
    }

    return cnt == 0;
}


=======================
recursion. 

 vector<string> removeInvalidParentheses(string s) {  
        vector<string> res;
      
         if (s.empty()) {
           res.push_back("");
           return res; 
        }
        
        helper(res, s); 
   
          if (res.empty()) {
           res.push_back("");
           return res; 
        }
        
        return res;        
    }
    
    void helper(vector<string>& res, string s) {
        
        string str; 
     
        stack<char> st; 
        int count = 0; 
        
        int countL = 0, countR = 0; 
        
        for (auto ch : s) {
            if (ch == '(') countL++; 
            else if (ch == ')') countR++;             
        }
               
        int L = 0, R = 0;  
        
        for (int i = 0; i < s.size(); ++i) {  
            
             if (s[i] == '(' && countR == 0) {
                continue; 
            }
            
            if (s[i] == ')' && countL == 0) {
                continue; 
            }
            
            if (s[i] == '(' && countR - R == 0) {} 
            else if (s[i] == '(' && L < countR) {   
                L++; 
                
                string temp = s; 
                if ((countL > countR) && (L >= R)) {
                    helper(res, s.substr(0, i) + s.substr(i+1));
                }
                
                // if (countR - R != 0) {
                str.push_back(s[i]); 
                st.push(s[i]);
                count++; 
              
               } 
            
            
            if (s[i] == ')' && R < countL) {
                R++; 
                
                string temp = s; 
                if ((countR > countL) && (R >= L)) {
                    helper(res, s.substr(0, i) + s.substr(i+1));
                }
                                
                if(count == 0) 
                    continue; 
                else {
                    count--; 
                    str.push_back(s[i]); 
                    st.pop();
                }
                
            }  
            
        
            if (s[i] != '(' && s[i] != ')') {
                str.push_back(s[i]);
            }
        } 
    
        if (count == 0 && !std::count(res.begin(), res.end(), str)) { 
            res.push_back(str); 
        } 
        
        // if (count != 0 && countL == countR) res.push_back("");
        // if(count != 0 && res.empty()) res.push_back(""); 

       return;  
        
    }
    
====================================  

[LeetCode] Longest Increasing Subsequence 最长递增子序列
 
Given an unsorted array of integers, find the length of longest increasing subsequence.
For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.
Follow up: Could you improve it to O(n log n) time complexity?

 
这道题让我们求最长递增子串Longest Increasing Subsequence的长度，简称LIS的长度。我最早接触到这道题是在LintCode上，可参见我之前的博客Longest Increasing Subsequence 最长递增子序列，那道题写的解法略微复杂，下面我们来看其他的一些解法。首先来看一种动态规划Dynamic Programming的解法，这种解法的时间复杂度为O(n2)，类似brute force的解法，我们维护一个一维dp数组，其中dp[i]表示以nums[i]为结尾的最长递增子串的长度，对于每一个nums[i]，我们从第一个数再搜索到i，如果发现某个数小于nums[i]，我们更新dp[i]，更新方法为dp[i] = max(dp[i], dp[j] + 1)，即比较当前dp[i]的值和那个小于num[i]的数的dp值加1的大小，我们就这样不断的更新dp数组，到最后dp数组中最大的值就是我们要返回的LIS的长度

// 其中dp[i]表示以nums[i]为结尾的最长递增子串的长度
// 这种解法的时间复杂度为O(n^2)

 int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }


// nlogn time complexity 

int lengthOfLIS(vector<int>& nums) {
        vector<int> dp;
        for (int i = 0; i < nums.size(); ++i) {
            int left = 0, right = dp.size();
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (dp[mid] < nums[i]) left = mid + 1;
                else right = mid;
            }
            if (right >= dp.size()) dp.push_back(nums[i]);
            else dp[right] = nums[i];
        }
        return dp.size();
    }    

================================  
297. Serialize and Deserialize Binary Tree

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Example: 
You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as [1,2,3,null,null,4,5]


   // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        preorderTraverse(root, res);
        return res;
    }
    
    void preorderTraverse(TreeNode* node, string& str) {
        if (!node) {
            str += "N ";
            return;
        }
        str += to_string(node->val) + " ";
        preorderTraverse(node->left, str);
        preorderTraverse(node->right, str);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        string tmp;
        queue<string> q;
        while (getline(ss, tmp, ' ')) {
            q.push(tmp);
        }
        return getTree(q);
    }
    
    TreeNode* getTree(queue<string>& q) {
        string str = q.front();
        q.pop();
        if (str == "N")
            return NULL;
        TreeNode* node = new TreeNode(stoi(str));
        node->left = getTree(q);
        node->right = getTree(q);
        return node;
    }


==========================================  
[LeetCode] Find the Duplicate Number 寻找重复数
 
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate element must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant extra space.
Your runtime complexity should be less than O(n2).
// 不能modify array == 不能排序

这道题给了我们n+1个数，所有的数都在[1, n]区域内，首先让我们证明必定会有一个重复数，这不禁让我想起了小学华罗庚奥数中的抽屉原理(又叫鸽巢原理), 即如果有十个苹果放到九个抽屉里，如果苹果全在抽屉里，则至少有一个抽屉里有两个苹果，这里就不证明了，直接来做题吧。题目要求我们不能改变原数组，即不能给原数组排序，又不能用多余空间，那么哈希表神马的也就不用考虑了，又说时间小于O(n2)，也就不能用brute force的方法，那我们也就只能考虑用二分搜索法了，我们在区别[1, n]中搜索，首先求出中点mid，然后遍历整个数组，统计所有小于等于mid的数的个数，如果个数大于mid，则说明重复值在[mid+1, n]之间，反之，重复值应在[1, mid-1]之间，然后依次类推，直到搜索完成，此时的low就是我们要求的重复值，

// time complexity： nlogn  
  int findDuplicate(vector<int>& nums) {
        int low = 1, high = nums.size() - 1;
        while (low < high) {
            int mid = low + (high - low) * 0.5;
            int cnt = 0;
            for (auto a : nums) {
                if (a <= mid) ++cnt;
            }
            if (cnt <= mid) low = mid + 1;
            else high = mid;
        }
        return low;
    }


其核心思想快慢指针在之前的题目Linked List Cycle II中就有应用，这里应用的更加巧妙一些，由于题目限定了区间[1,n]，所以可以巧妙的利用坐标和数值之间相互转换，而由于重复数字的存在，那么一定会形成环，我们用快慢指针可以找到环并确定环的起始位置，确实是太巧妙了

// time complexity: n 
  int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0, t = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) break;
        }
        while (true) {
            slow = nums[slow];
            t = nums[t];
            if (slow == t) break;
        }
        return slow;
    }


===========================================   
[LeetCode] Move Zeroes 移动零

Given an array nums, write a function to move all 0 to the end of it while maintaining the relative order of the non-zero elements.
For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.

void moveZeroes(vector<int>& nums) {
    int j = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0) {
            swap(nums[j], nums[i]); 
         	j++; 
        }
        else continue; 
    }
}



[LeetCode] Perfect Squares 完全平方数
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.

最后我们来介绍一种递归Recursion的解法，这种方法的好处是写法简洁，但是运算效率不敢恭维。我们的目的是遍历所有比n小的完全平方数，然后对n与完全平方数的差值递归调用函数，目的是不断更新最终结果，知道找到最小的那个. 

// running time very slow
int numSquares(int n) {
    int res = n, num = 2;  // res初始为n, 是因为n个1肯定行
    while (num * num <= n) {
        int a = n / (num * num), b = n % (num * num);
        res = min(res, a + numSquares(b));
        ++num;
    }
    return res;
}

我们还可以用动态规划Dynamic Programming来做，我们建立一个长度为n+1的一维dp数组，将第一个值初始化为0，其余值都初始化为INT_MAX, i从0循环到n，j从1循环到i+j*j <= n的位置，然后每次更新dp[i+j*j]的值，动态更新dp数组，其中dp[i]表示正整数i能少能由多个完全平方数组成，那么我们求n，就是返回dp[n]即可，也就是dp数组的最后一个数字 
// better solution 
// 其中dp[i]表示正整数i能少能由多个完全平方数组成
   int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 1; i + j * j <= n; ++j) {
                dp[i + j * j] = min(dp[i + j * j], dp[i] + 1);
            }
        }
        return dp[n];
    }


==========================================  
add two string


string add(string str1, string str2) {
    if (str1.empty()) return str2;
    if (str2.empty()) return str1;
    
    string res;
    int m = static_cast<int>(str1.size());
    int n = static_cast<int>(str2.size());
    
    int i = m - 1, j = n - 1;
    int remain;
    int carry = 0;
    int a = str1[i], b = str2[j];
    
    while (i >= 0 || j >= 0) {
        remain =  (carry + (a - '0') + (b - '0')) % 10;
        carry = (carry + (a - '0') + (b - '0')) / 10;
       
        res.push_back(remain + '0');
        
        if (i > 0) {i--; a = str1[i]; }
        else {i--; a = '0';}  // 注意增加i--, i一直减下去
        
        if (j > 0) {j--; b = str2[j]; }
        else {j--; b = '0';}
        
//        reverse(res.begin(), res.end());
    }
    reverse(res.begin(), res.end());
    return res;
}



=========================   
bool AreSame(double a, double b) {
    return fabs(a - b) < EPSILON;
}



int fib(int n) { 
    if (n <= 1) return n; 

    // if (n == 1 || n == 2) return 1;
    return fib(n - 1) + fib(n - 2); 
}


int fib(int n) {
    if (n <= 1) return n; 
    int a = 0, b = 1; 
    int res = 0;
    // int temp;  
    for (int i = 2; i <= n; ++i) {
        res = a + b; 
        a = b; 
        b = res;  
    }  
    return res; 
}


===============================

Implement a template boolean IsSameClass() that takes class A and B as template parameters. It should compare class A and B and return false when they are different classes and true if they are the same class. 

template <typename T, typename U> 
struct is_same {
    static const bool value = false; 
};

template <typename T> 
struct is_same {
    static const bool value = true; 
};

template <class A, class B> 
bool IsSameClass() {
    return is_same<A, B>::value; 
}

type <typename A> 
static const bool value = true; 

return is_same<A, B>::value; 

====================================  

How can you make sure a C++ function can be called as e.g. void foo(int, int) but not as any other type like void foo(long, long)?   

template <typename T1, typename T2> 
void foo(T1 a, T2 b) = delete;

======================================


4. replace blank 

void replaceBlank(string str) {
    if (str.empty()) return; 

    int numSpace; 
    int originalSize = str.size(); 
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') ++numSpace; 
    }

    int newSize = originalSize + numSpace * 2;          

    // string newstr(newSize, 0); 
    string newstr; 
    newstr.reserve(newSize); 

    int idx1 = original - 1; 
    int idx2 = newSize - 1; 

    while (idx1 >= 0 && idx2 > idx1) {
        if (str[idx1] == ' ') {
            newstr[idx2--] = '0'; 
            newstr[idx2--] = '2'; 
            newstr[idx2--] = '%'; 
        } else {
            newstr[idx2--] = str[idx1--]; 
        }
    } 

}


for (int i = 0; i < str.size(); ++i) {
    if (str[i] == ' ') str.erase(str.begin() + i); 
    str.insert(i, "%20");  

}


void printReverse(ListNode* head) {
    if (head == NULL) return; 
    stack<ListNode*> st; 
    ListNode* cur = head; 

    while (cur) {
        st.push(cur); 
        cur = cur->next; 
    }

    while(!st.empty()) {
        ListNode* temp = st.top();
        st.pop(); 
        cout << temp->val;  
    }
}


void printReverse(ListNode* head) {
    if (head == NULL) return; 

    if (head->next) {
        printReverse(head->next); 
        cout << head->val; 
    }

}

=================  


for (int i = 0; i <= oldages; ++i) {
    for (int j = 0; j < m[i]; ++j) {
        arr[idx++] = i;   
    }
}

======================================    

[LeetCode] Wiggle Sort 摆动排序
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3] 
For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].

void wiggleSort(vector<int>& nums) {
        sort(nums.begin(), nums.end()); 
        // 1 2 3 4 5   6 
        // 1 6 3  5 4   2
        int i = 0, j = nums.size() - 1; 
        while (i < j) {
            swap(nums[++i], nums[j]); ++i, --j; 
        }   
    } 


==========================================
Queue Reconstruction by Height 根据高度重建队列
Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers(h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.
Note:
The number of people is less than 1,100.
Example
Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]


  static bool comparator(const pair<int, int>& a, const pair<int, int>& b) {
      if (a.first == b.first) return a.second < b.second;   
      return a.first > b.first; 
    }
    
        vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
            
        sort(people.begin(), people.end(), comparator);
            
        vector<pair<int, int>> res;
        for (auto a : people) {
            res.insert(res.begin() + a.second, a);
        }
        return res;
    }

============================================   
Daily Temperatures 日常温度
Given a list of daily temperatures, produce a list that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.
For example, given the list temperatures = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].
Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].

vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size(), 0); 
        stack<int> st; 
        
        for (int i = 0; i < temperatures.size(); ++i) {
            while(!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int t = st.top(); st.pop();
                res[t] = i - t; 
            }
            st.push(i);   
        }   
        return res; 
}

=================================   

Maximum XOR of Two Numbers in an Array 数组中异或值最大的两个数字
 
Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.
Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.
Could you do this in O(n) runtime?

Example:
Input: [3, 10, 5, 25, 2, 8]
Output: 28
Explanation: The maximum result is 5 ^ 25 = 28.

int findMaximumXOR(vector<int>& nums) {
        int res = 0; 
        int mask = 0; 
        // unordered_set<int> st;  wrong
        
        for (int i = 31; i >= 0; --i) {
        // for (int i = 0; i <= 31; ++i) {
            mask = mask | (1 << i); 
            unordered_set<int> st; // 
            for (auto a : nums) {
                st.insert(a & mask);
            }
            
            int temp = res | (1 << i); 
            for (auto a : st) {
                if(st.count(temp ^ a)) {
                    res = temp; 
                    break; 
                } 
            }   
        }    
        return res; 
    }

================================

binary search tree iterator    

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        inorder(root, q); 
    }
    
    void inorder(TreeNode* root, queue<TreeNode*>& q) {
        if (!root) return; 
        inorder(root->left, q); 
        q.push(root); 
        inorder(root->right, q);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !q.empty(); 
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* t = q.front();
        q.pop(); 
        return t->val; 
    }
private: 
    queue<TreeNode*> q; 
};

===================================
Flatten nested list iterator  
Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].


class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        make_queue(nestedList);
    }
    
    void make_queue(vector<NestedInteger>& nestedList) {
        for (int i = 0; i < nestedList.size(); ++i) {
            if (nestedList[i].isInteger()) q.push(nestedList[i].getInteger());
            else {
                make_queue(nestedList[i].getList());
            }
        }
    }

    int next() {
        int res = q.front(); q.pop();
        return res; 
    }

    bool hasNext() {
        return !q.empty(); 
    }
    
private: 
    queue<int> q; 
};


================================   
Meeting Rooms II 会议室之二

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

  int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> m;
        for (auto a : intervals) {
            ++m[a.start];
            --m[a.end];
        }
        int rooms = 0, res = 0;
        for (auto it : m) {
            res = max(res, rooms += it.second);
        }
        return res;
    }  

======================================
Singleton pattern 

#include <iostream>

class Singleton {
    private:
        /* Private constructor to prevent instancing. */
        Singleton();
        Singleton(const Singleton& src); 
        Singleton& operator=(const Singleton& src); 
        ~Singleton(); 

        /* Here will be the instance stored. */
        static Singleton* instance;

    public:
        /* Static access method. */
        static Singleton* getInstance();
};

/* Null, because instance will be initialized on demand. */
// Singleton* Singleton::instance = 0; 
Singleton* Singleton::instance = NULL;   // static variable 初始化也要加variable type

Singleton* Singleton::getInstance() {
    lock();  // thread safe 
    if (instance == NULL) {
        instance = new Singleton();
    }

    return instance;
}

Singleton::Singleton()
{}

int main() {

    //new Singleton(); // Won't work
    Singleton* s = Singleton::getInstance(); // Ok
    Singleton* r = Singleton::getInstance();

    /* The addresses will be the same. */
    std::cout << s << std::endl;
    std::cout << r << std::endl;
}
 

===============================

std::unique_ptr<int> valuePtr(new int(15));   
auto ptr = unique_ptr<int>(new int(15));  
auto ptr = unique_ptr<className>(constructor parameter);    

===================================   
abstract factory pattern  

// C++ program to demonstrate factory method design pattern
#include <iostream>
using namespace std;
 
enum VehicleType {
    VT_TwoWheeler, VT_ThreeWheeler, VT_FourWheeler
};          
                 
// Library classes
class Vehicle {
public:
    virtual void printVehicle() = 0;

    // The answer is, create a static (or factory) method. Let us see below code.
    static Vehicle* Create(VehicleType type);
};

class TwoWheeler : public Vehicle {
public:
    void printVehicle() {
        cout << "I am two wheeler" << endl;
    }
};

class ThreeWheeler : public Vehicle {
public:
    void printVehicle() {
        cout << "I am three wheeler" << endl;
    }
}; 

class FourWheeler : public Vehicle {
    public:
    void printVehicle() {
        cout << "I am four wheeler" << endl;
    }
};
 
// Factory method to create objects of different types.
// Change is required only in this function to create a new object type
Vehicle* Vehicle::Create(VehicleType type) {
    if (type == VT_TwoWheeler)
        return new TwoWheeler();
    else if (type == VT_ThreeWheeler)
        return new ThreeWheeler();
    else if (type == VT_FourWheeler)
        return new FourWheeler();
    else return NULL;
}
 
// Client class
class Client {
public:
 
    // Client doesn't explicitly create objects
    // but passes type to factory method "Create()"
    Client()
    {
        VehicleType type = VT_ThreeWheeler;
        pVehicle = Vehicle::Create(type);
    }
    ~Client() {
        if (pVehicle) {
            delete[] pVehicle;
            pVehicle = NULL;
        }
    }
    Vehicle* getVehicle()  {
        return pVehicle;
    }
 
private:
    Vehicle *pVehicle;
};

 
// Driver program
int main() {
    Client *pClient = new Client();
    Vehicle * pVehicle = pClient->getVehicle();
    pVehicle->printVehicle();
    return 0;
}

==========================================
32. Longest Valid Parentheses    

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Example 1:
Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"

Example 2:
Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"

    int longestValidParentheses(string s) {
//          int res = 0, start = 0;
//     stack<int> m;
//     for (int i = 0; i < s.size(); ++i) {
//         if (s[i] == '(') m.push(i);
//         else if (s[i] == ')') {
//             if (m.empty()) start = i + 1;
//             else {
//                 m.pop(); 
//                 if(m.empty())  
//                     res = max(res, i - start + 1); 
//                 else 
//                     res = max(res, i - m.top());
                
//                 // m.pop();
//             }
//         }
//     }
//     return res;
        
   
   int res = 0; 
        stack<int> st; 
        int idx = 0; 
        for (int i = 0; i < s.size(); ++i) {
            
            if (s[i] == '(') st.push(i); 
            
            if (s[i] == ')' && st.empty()) idx = i + 1;   // (()()
            
            if (s[i] == ')' && !st.empty()) {
                // int t = st.top();   // 传统访问stack有bug, e.g, (()()  
                st.pop(); 
                
                if (st.empty())
                       res = max(res, i - idx + 1); 
                else 
                    res = max(res, i - st.top());
                    // res = max(res, i - t + 1);  // 当(()()时有bug        
            }
        }        
        return res; 
    }

////////////////////////////////  
692. Top K Frequent Words 
Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.


// If you want to "sort" your unordered_map, put them in a vector:
// std::vector<std::pair<char, int>> elems(table.begin(), table.end());
// std::sort(elems.begin(), elems.end(), comp);


 static   bool comparator(const pair<string, int>& a, const pair<string, int>& b) {
     if (a.second == b.second) return a.first < b.first;        
     else return a.second > b.second; 
     
}
    
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> res; 
        
        unordered_map<string, int> m; 
        for (auto word : words) m[word]++; 
        
        vector<pair<string, int>> vec(m.begin(), m.end());
        
        sort(vec.begin(), vec.end(), comparator); 
        
        for (int i= 0; i < k; ++i) {
            res.push_back(vec[i].first); 
        }
        
        return res; 
    }
    



