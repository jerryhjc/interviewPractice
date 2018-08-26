839. Similar String Groups

Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y.
For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".
Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that "tars" and "arts"are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.
We are given a list A of unique strings.  Every string in A is an anagram of every other string in A.  How many groups are there?

Example 1:
Input: ["tars","rats","arts","star"]
Output: 2
                            
                                
// 把所以单词连成路径，然后找到不同路径下有多少个终点。  
// union find 
int numSimilarGroups(vector<string>& A) {

    unordered_map<string,string> m;
    int n = A.size();

    for (int i = 0; i < n; i++) {
         // Updated on Jun 6th, there is an invalid test case, in the problem description, it says "a list of unique strings", but there are test cases with duplicate strings.
        // In this case, the following line is added.     
        if (m.find(A[i]) != m.end()) 
            continue;
        
        m[A[i]] = A[i];
        for (int j = 0; j < i; j++) {
            if (isSimilar(A[i], A[j]) && m[A[j]] != A[i]) {
                string x = getRoot(A[j], m);
                m[x] = A[i];
            }
        }
    }
    
    int result = 0;
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->first == it->second) result++;
    }
    return result;
}

    
bool isSimilar(string &a, string &b) {
    int n = a.length(), counter = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) counter++;
    }
    return counter == 2;
}

string getRoot(string s, unordered_map<string, string> &map) {
    // string temp = map[s];
    if (map[s] != s) 
        return getRoot(map[s], map);
    else 
        return s;
}



