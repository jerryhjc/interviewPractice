44. Wildcard Matching

Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

对p中第一个*之前的内容，我们可以直接跟s的内容匹配，如果已经发生匹配失败则返回false。如果p中没有*则直接返回s是否已扫描完。
p中连续出现的*可以视为一个。如果*是p的最后一个字符，则可以把s剩下的内容跟*匹配。
此外的情况需要递归。

Input:
s = "acdcb"
p = "a*c?b"
Output: false   

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".

// 超时了  
// bool isMatch(string s, string p) {
//     return isMatch_recur(s, p, 0, 0);
// }

// bool isMatch_recur(const string &s, const string &p, int si, int pi) {
//     // match s and p sequentially until finding a "*" or reaching end of p
//     while (pi < p.size() && p[pi] != '*') {
//         if (si == s.size() || (p[pi] != '?' && p[pi] != s[si])) return false;
//         ++pi, ++si;
//     }
//     if(pi == p.size()) return si == s.size();
    
//     // skip continuous * in p and treat them as a single *
//     while (pi <p.size() && p[pi]=='*') ++pi;
//     if(pi==p.size()) return true;
    
//     for(int i = si; i<s.size(); ++i) {   // then do recursion
//         if(isMatch_recur(s, p, i, pi)) return true;
//     }
    
//     return false;
// }

注意到递归只发生在*出现的地方，且递归内部所实现的是匹配一段被*分隔的串。
我们假设p=p1*p2*...*pn，p1, pn可以为空。我们首先通过去掉p1和pn。
因此我们实际上做的事情是寻找p2, p3, …，p(n－1)在s中的匹配。并要求对应的子串不相交且保持一样的先后顺序。我们假定p和s有一个匹配，而p2在s中出现的位置包括l1, l2, ... 假设在匹配中p2出现的位置在lm，事实上我们也可以把p2放在l1, l2，...l(m-1)并得到匹配。因此当已经匹配完一个完整的字符串后，不能再发生回退。
我们可以简单修改上面的递归算法来达到避免不必要的回退的目的：我们纪录每层的递归长度并且如果发现递归回退时返回false.


// 通过修改 time 99%, 和上面解法比较                     
bool isMatch(string s, string p) {         
    int l = 0;             
    return isMatch_recur(s, p, 0, 0, l);         
}

bool isMatch_recur(const string &s, const string &p, int si, int pi, int &rec_level) {
    int cur_level = rec_level;            
       
    // match s and p sequentially until finding a "*" or reaching end of p
    while (pi < p.size() && p[pi] != '*') {
        if (si == s.size() || (p[pi] != '?' && p[pi] != s[si])) return false;
        ++pi, ++si;
    }
    if(pi == p.size()) return si == s.size();
    
    // skip continuous * in p and treat them as a single *
    while (pi <p.size() && p[pi]=='*') ++pi;
    if(pi==p.size()) return true;
    
    // recursion
    ++rec_level;
    for(int i = si; i<s.size(); ++i) { 
        if(isMatch_recur(s, p, i, pi, rec_level)) return true;
        if(rec_level>cur_level+1) return false;
    }
    
    return false;
}


