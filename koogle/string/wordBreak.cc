139. Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".


bool wordBreak(string s, vector<string>& wordDict) {
        set<string> st(wordDict.begin(), wordDict.end()); 
        vector<int> visit(s.size(), -1); 
        
        return dfs(s, st, visit, 0); 
}

bool dfs(string s, set<string>& st, vector<int>& visit, int idx) {
    if (idx == s.size()) return true; 
    // if (st.count(s)) return true; 
    if (visit[idx] != -1) return visit[idx];
    
    for (int i = idx; i < s.size(); ++i) {
        if (st.count(s.substr(idx, i - idx + 1)) && dfs(s, st, visit, i + 1)) {
            visit[idx] = 1; 
            return true; 
        }
        
    }
    visit[idx] = 0; 
    return false; 
    
}


140. Word Break II 

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]

 vector<string> wordBreak(string s, vector<string>& wordDict) {
        string str; 
        vector<string> res; 
        set<string> st(wordDict.begin(), wordDict.end()); 
        vector<bool> visit(s.size() + 1, true);
        
        dfs(s, str, res, st, visit, 0); 
        
        return res; 
    }
    
    void dfs(string s, string& str, vector<string>& res, set<string>& st, vector<bool>& visit, int idx) {
        if (idx == s.size()) {
            res.push_back(str);
            return; 
        }        
        
        for (int i = idx; i < s.size(); ++i) {
            string temp = s.substr(idx, i - idx + 1); 
            if (st.count(temp) && visit[i + 1]) {
               
                // if (i == s.size() - 1) 
                //     str = str + temp; 
                // else 
                //     str = str + temp + " ";           
                    
                
//             if (i == s.size() - 1)     
//                 temp = s.substr(idx, i - idx + 1);
//             else       
//                 temp = s.substr(idx, i - idx + 1) + " ";
//             str = str + temp; 
                
            
            if (i != s.size() - 1)   
                temp = s.substr(idx, i - idx + 1) + " ";
            str = str + temp; 
                
                int oldSize = res.size(); 
                dfs(s, str, res, st, visit, i + 1); 
                if (res.size() == oldSize)
                    visit[i + 1] = false;    
                
                str.erase(str.size() - temp.size(), temp.size());     
            }
        }     
    }
    
