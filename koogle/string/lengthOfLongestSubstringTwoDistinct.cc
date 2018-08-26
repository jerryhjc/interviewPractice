Longest Substring with At Most Two Distinct Characters 最多有两个不同字符的最长子串 

我们除了用哈希表来映射字符出现的个数，我们还可以映射每个字符最新的坐标，比如题目中的例子"eceba"，遇到第一个e，映射其坐标0，遇到c，映射其坐标1，遇到第二个e时，映射其坐标2，当遇到b时，映射其坐标3，每次我们都判断当前哈希表中的映射数，如果大于2的时候，那么我们需要删掉一个映射，我们还是从left=0时开始向右找，我们看每个字符在哈希表中的映射值是否等于当前坐标left，比如第一个e，哈希表此时映射值为2，不等于left的0，那么left自增1，遇到c的时候，哈希表中c的映射值是1，和此时的left相同，那么我们把c删掉，left自增1，再更新结果，以此类推直至遍历完整个字符串

int lengthOfLongestSubstringTwoDistinct(string s) {
    int res = 0, left = 0;
    unordered_map<char, int> m;
    for (int i = 0; i < s.size(); ++i) {
        m[s[i]] = i;
        while (m.size() > 2) {
            if (m[s[left]] == left) 
            	m.erase(s[left]);
            
            ++left;
        }
        res = max(res, i - left + 1);
    }
    return res;
}

// follow up 
Longest Substring with At Most K Distinct Characters 最多有K个不同字符的最长子串
 
Given a string, find the length of the longest substring T that contains at most k distinct characters.
For example, Given s = “eceba” and k = 2,
T is "ece" which its length is 3.

这道题是之前那道Longest Substring with At Most Two Distinct Characters的拓展，而且那道题中的解法一和解法二直接将2换成k就行了  


int lengthOfLongestSubstringKDistinct(string s, int k) {
        int res = 0, left = 0;
        unordered_map<char, int> m;
        for (int i = 0; i < s.size(); ++i) {
            ++m[s[i]];
            while (m.size() > k) {
                if (--m[s[left]] == 0) m.erase(s[left]);
                ++left;
            }
            res = max(res, i - left + 1);
        }
        return res;
}




