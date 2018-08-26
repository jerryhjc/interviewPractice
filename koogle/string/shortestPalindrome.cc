214. Shortest Palindrome  

Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: "abcd"
Output: "dcbabcd"


// just brute force is fine
string shortestPalindrome(string s) {
    string r = s;
    std::reverse(r.begin(), r.end());
    
    for (int i = 0; i < s.size(); ++i) {
        // from completely overlapping to not overlapping
        if (r.substr(i) == s.substr(0, s.size()-i)) {
            return r.substr(0, i) + s;
        }
    }
    return r + s;
}

s: abc 
r: cba 
cba + abc


首先我们还是先将其的翻转字符串搞出来，然后比较原字符串s的前缀后翻转字符串t的对应位置的后缀是否相等，起始位置是比较s和t是否相等，如果相等，说明s本身就是回文串，不用添加任何字符，直接返回即可；如果不想等，s去掉最后一位，t去掉第一位，继续比较，以此类推直至有相等，或者循环结束，这样我们就能将两个字符串在正确的位置拼接起来了

 string shortestPalindrome(string s) {
        string t = s;
        reverse(t.begin(), t.end());
        int n = s.size(), i = 0;
        for (i = n; i >= 0; --i) {
            if (s.substr(0, i) == t.substr(n - i)) {
                break;
            }
        }
        return t.substr(0, n - i) + s;
}


