854. K-Similar Strings  

Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.
Given two anagrams A and B, return the smallest K for which A and B are K-similar.
Example 1:

Input: A = "ab", B = "ba"
Output: 1
Example 2:

Input: A = "abc", B = "bca"
Output: 2

    int kSimilarity(string A, string B) {

        if(A == B)
            return 0;

        int start = next_start(A, B, 0);

        queue<pair<string, pair<int, int>>> q;
        q.push(make_pair(A, make_pair(start, 0)));

        unordered_set<string> visited;
        visited.insert(A);

        while(!q.empty()){
            string curS = q.front().first;
            start = q.front().second.first;
            int curStep = q.front().second.second;
            q.pop();

            for(int i = start + 1 ; i < curS.size() ; i ++)
                if(curS[i] == B[start]){
                    swap(curS[start], curS[i]);
                    if(visited.find(curS) == visited.end()){
                        if(curS == B)
                            return curStep + 1;

                        visited.insert(curS);
                        q.push(make_pair(curS, make_pair(next_start(curS, B, start + 1), curStep + 1)));
                    }
                    swap(curS[start], curS[i]);
                }
        }

        assert(false);
        return -1;
    }

    int next_start(const string& A, const string& B, int start){
        for(int i = start ; i < A.size() ; i ++)
            if(A[i] != B[i])
                return i;
        assert(false);
        return A.size();
    }

///////////////////////////////    

/*
Have to use this stupid level by level generation method.
    from current level, generate new level without repetition.
*/
int kSimilarity(string A, string B) {
    int n = A.size();
    int res = 0;
    if (A == B) return 0; // no swap.
    queue<string> qu;
    qu.push(A);
    while (!qu.empty()) {
        res++;
        // generate new generation, since last generation has no == B
        unordered_set<string> visited;
        int m = qu.size();
        for (int i = 0; i < m; i++) {
            string s = qu.front(); qu.pop();
            int j = res - 1; // at least res-1 char has been matched.

            while (s[j] == B[j]) 
                j++; // it won't match B completely, so, j < n;

            int k = j + 1;
            for (; k < n; k++) {
                if (s[k] != B[k] && s[k] == B[j]) { // find possible swap.
                    s[k] = s[j];
                    s[j] = B[j]; // swap
                    if (s == B) return res; // if found, return; 
                    if (visited.count(s) == 0) { // if not in the queue yet.
                        visited.insert(s);
                        qu.push(s);
                    }
                    s[j] = s[k]; // swap back;
                    s[k] = B[j];
                }
            }
        }
    }
    return res;
}

///////////////////////////// 

 int kSimilarity(string A, string B) {
        if (A==B) return 0;
        int level = 0, n = A.size(), i;
        queue<string> q;
        q.push(A);
        unordered_set<string> visited;
        
        while(!q.empty()) {
            level++;
            for (int sz = q.size(); sz > 0; --sz) {
                string cur = q.front(); q.pop();
                if (visited.count(cur)) continue;
                visited.insert(cur);
                i = 0;
                while (cur[i] == B[i]) ++i;
                for (int j=i+1;j<n; ++j) {
                    if (cur[j] == B[j] || cur[i]!=B[j]) continue;
                    swap(cur[i], cur[j]);
                    if (cur == B) return level;
                    if (!visited.count(cur)) {
                        q.push(cur);
                    }
                    swap(cur[i], cur[j]);
                }
            }
        }
        return -1;
    }

////////////////////////  recursion , best time 

  int kSimilarity(string A, string B) {
      for (int i=0; i<A.size(); i++) {
        if (A[i]==B[i]) continue;
        vector<int> matches;
        for (int j=i+1;j<A.size();j++) { 
          if (A[j]==B[i] && A[j]!=B[j]) {
            matches.push_back(j);
            if (A[i]==B[j]) {
              swap(A[i],A[j]);
              return 1+kSimilarity(A.substr(i+1),B.substr(i+1));
            }
          }
        }
        
        int best=A.size()-1;
        for (int j: matches) {
            swap(A[i],A[j]);
            best = min(best, 1+kSimilarity(A.substr(i+1),B.substr(i+1)));
            swap(A[i],A[j]);
        }
        return best;
      }
      return 0;
    }
