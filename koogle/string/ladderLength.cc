Word Ladder 词语阶梯  

Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:
Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
Note:

Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

这道词句阶梯的问题给了我们一个单词字典，里面有一系列很相似的单词，然后给了一个起始单词和一个结束单词，每次变换只能改变一个单词，并且中间过程的单词都必须是单词字典中的单词，让我们求出最短的变化序列的长度。这道题还是挺有难度的，我当然是看了别人的解法才写出来的，这里用到了两个高级数据结构unordered_map和queue，即哈希表和队列，其中哈希表是记录单词和目前序列长度之间的映射，而队列的作用是保存每一个要展开的单词。首先把起始单词映射为1，把起始单词排入队列中，开始队列的循环，取出队首词，然后对其每个位置上的字符，用26个字母进行替换，如果此时和结尾单词相同了，就可以返回取出词在哈希表中的值加一。如果替换词在字典中存在但在哈希表中不存在，则将替换词排入队列中，并在哈希表中的值映射为之前取出词加一。如果循环完成则返回0

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    unordered_map<string, int> m;
    queue<string> q;
    m[beginWord] = 1;
    q.push(beginWord);
    while (!q.empty()) {
        string word = q.front(); q.pop();
        for (int i = 0; i < word.size(); ++i) {
            string newWord = word;
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                newWord[i] = ch;
                if (dict.count(newWord) && newWord == endWord) return m[word] + 1;
                if (dict.count(newWord) && !m.count(newWord)) {
                    q.push(newWord);
                    m[newWord] = m[word] + 1;
                }   
            }
        }
    }
    return 0;
}

//////////////////////////////////////  

Word Ladder II 词语阶梯之二
 
Given two words (start and end), and a dictionary, find all shortest transformation sequence(s) from start to end, such that:
Only one letter can be changed at a time
Each intermediate word must exist in the dictionary
For example,

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
Note:
All words have the same length.
All words contain only lowercase alphabetic characters.

核心思想是BFS，大概思路如下：我们的目的是找出所有的路径，我们建立一个路径集paths，用以保存所有路径，然后是起始路径p，在p中先把起始单词放进去。然后定义两个整型变量level，和minLevel，其中level是记录循环中当前路径的长度，minLevel是记录最短路径的长度，这样的好处是，如果某条路径的长度超过了已有的最短路径的长度，那么舍弃，这样会提高运行速度，相当于一种剪枝。还要定义一个set变量words，用来记录已经循环过的路径中的词，然后就是BFS的核心了，循环路径集paths里的内容，取出队首路径，如果该路径长度大于level，说明字典中的有些词已经存入路径了，如果在路径中重复出现，则肯定不是最短路径，所以我们需要在字典中将这些词删去，然后将words清空，对循环对剪枝处理。然后我们取出当前路径的最后一个词，对每个字母进行替换并在字典中查找是否存在替换后的新词，这个过程在之前那道Word Ladder 词语阶梯里面也有。如果替换后的新词在字典中存在，将其加入words中，并在原有路径的基础上加上这个新词生成一条新路径，如果这个新词就是结束词，则此新路径为一条完整的路径，加入结果中，并更新minLevel，若不是结束词，解将新路径加入路径集中继续循环。


 vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> res;
        unordered_set<string> dict(wordList.begin(), wordList.end());
        vector<string> p{beginWord};
        queue<vector<string>> paths;
        paths.push(p);
        int level = 1, minLevel = INT_MAX;
        unordered_set<string> words;
        while (!paths.empty()) {
            auto t = paths.front(); paths.pop();
            if (t.size() > level) {
                for (string w : words) dict.erase(w);
                words.clear();
                level = t.size();
                if (level > minLevel) break;
            }
            string last = t.back();
            for (int i = 0; i < last.size(); ++i) {
                string newLast = last;
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    newLast[i] = ch;
                    if (!dict.count(newLast)) continue;
                    words.insert(newLast);
                    vector<string> nextPath = t;
                    nextPath.push_back(newLast);
                    if (newLast == endWord) {
                        res.push_back(nextPath);
                        minLevel = level;
                    } else paths.push(nextPath);
                }
            }
        }
        return res;
    }










