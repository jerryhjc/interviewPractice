Cracking the Safe 破解密码
 
There is a box protected by a password. The password is n digits, where each letter can be one of the first k digits 0, 1, ..., k-1.
You can keep inputting the password, the password will automatically be matched against the last n digits entered.
For example, assuming the password is "345", I can open it when I type "012345", but I enter a total of 6 digits.
Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.

Example 1:
Input: n = 1, k = 2
Output: "01"
Note: "10" will be accepted too.
 
Example 2:
Input: n = 2, k = 2
Output: "00110"
Note: "01100", "10011", "11001" will be accepted too.

// C++ / DFS w/ backtracking 

 string crackSafe(int n, int k) {
        const int total_len = pow(k, n) + n - 1;
        //  const int total_len = pow(k, n); 
        string ans(n, '0');
        unordered_set<string> visited{ans};
        if (dfs(ans, total_len, n, k, visited))
            return ans;
        return "";
    }

    bool dfs(string& ans, const int total_len, const int n, const int k, unordered_set<string>& visited) {
        if (ans.length() == total_len)
            return true;
        
        string node = ans.substr(ans.length() - n + 1, n - 1);
        for (char c = '0'; c < '0' + k; ++c) {
            node.push_back(c);
            if (!visited.count(node)) {
                ans.push_back(c);
                visited.insert(node);
                if (dfs(ans, total_len, n, k, visited)) return true;
                visited.erase(node);
                ans.pop_back();
            }
            node.pop_back();
        }
        
        return false;
    }

///////////////////////////////////  
// C++ / DFS no backtracking

   string crackSafe(int n, int k) {
        const int total_len = pow(k, n) + n - 1;        
        string node(n - 1, '0');
        string ans;
        unordered_set<string> visited;
        dfs(node, k, visited, ans);
        return ans + node;
    }

    void dfs(const string& node, const int k, unordered_set<string>& visited, string& ans) {        
        for (char c = '0'; c < '0' + k; ++c) {
            string next = node + c;            
            if (visited.count(next)) continue;            
            visited.insert(next);                 
            dfs(next.substr(1), k, visited, ans);
            ans.push_back(c);
        }
    }

