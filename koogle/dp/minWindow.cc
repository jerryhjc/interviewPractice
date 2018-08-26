727. Minimum Window Subsequence  

Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.
If there is no such window in S that covers all characters in T, return the empty string "". If there are multiple such minimum-length windows, return the one with the left-most starting index.

Example 1:
Input: 
S = "abcdebdde", T = "bde"
Output: "bcde"
Explanation: 
"bcde" is the answer because it occurs before "bdde" which has the same length.
"deb" is not a smaller window because the elements of T in the window must occur in order.

// brute force 
这道题给了我们两个字符串S和T，让我们找出S的一个长度最短子串W，使得T是W的子序列，如果长度相同，取起始位置靠前的。清楚子串和子序列的区别，那么题意就不难理解，题目中给的例子也很好的解释了题意。我们经过研究可以发现，返回的子串的起始字母和T的起始字母一定相同，这样才能保证最短。那么你肯定会想先试试暴力搜索吧，以S中每个T的起始字母为起点，均开始搜索字符串T，然后维护一个子串长度的最小值。如果是这种思路，那么还是趁早打消念头吧，博主已经替你试过了，OJ不依。原因也不难想，假如S中有大量的连续b，并且如果T也很长的话，这种算法实在是不高效啊。根据博主多年经验，这种玩字符串且还是Hard的题，十有八九都是要用动态规划Dynamic Programming来做的，那么就直接往DP上去想吧。DP的第一步就是设计dp数组，像这种两个字符串的题，一般都是一个二维数组，想想该怎么定义。确定一个子串的两个关键要素是起始位置和长度，那么我们的dp值到底应该是定起始位置还是长度呢？That is a question! 仔细想一想，其实起始位置是长度的基础，因为我们一旦知道了起始位置，那么当前位置减去起始位置，就是长度了，所以我们dp值定为起始位置。那么 dp[i][j] 表示范围S中前i个字符包含范围T中前j个字符的子串的起始位置，注意这里的包含是子序列包含关系。然后就是确定长度了，有时候会使用字符串的原长度，有时候会多加1，看个人习惯吧，这里博主长度多加了个1。

// 优化brute force algorithm ; beat 100% 
// two pointers 
其实这是优化过的暴力搜索的方法，而且居然beat了100%，给跪了好嘛？！而且这双指针的跳跃方式犹如舞蹈般美妙绝伦，比那粗鄙的暴力搜索双指针不知道高到哪里去了？！举个栗子来说吧，比如当 S = "bbbbdde", T = "bde"时，我们知道暴力搜索的双指针在S和T的第一个b匹配上之后，就开始检测S之后的字符能否包含T之后的所有字符，当匹配结束后，S的指针就会跳到第二个b开始匹配，由于有大量的重复b出现，所以每一个b都要遍历一遍，会达到平方级的复杂度，会被OJ无情拒绝。而下面这种修改后的算法会跳过所有重复的b，使得效率大大提升，具体是这么做的，当第一次匹配成功后，我们的双指针往前走，找到那个刚好包含T中字符的位置，比如开始指针 i = 0 时，指向S中的第一个b，指针 j = 0 时指向T中的第一个b，然后开始匹配T，当 i = 6， j = 2 时，此时完全包含了T。暴力搜索解法中此时i会回到1继续找，而这里，我们通过向前再次匹配T，会在 i = 3，j = 0处停下，然后继续向后找，这样S中重复的b就会被跳过，从而达到线性的复杂度  


string minWindow(string S, string T) {
    int m = S.size(), n = T.size(), start = -1, minLen = INT_MAX, i = 0, j = 0;

    while (i < m) {
        if (S[i] == T[j]) {
            if (++j == n) {
                int end = i + 1;
                while (--j >= 0) {
                    while (S[i--] != T[j]);
                }
                ++i; ++j;
                if (end - i < minLen) {
                    minLen = end - i;
                    start = i;
                }
            }
        }
        ++i;
    }
    return (start != -1) ? S.substr(start, minLen) : "";
}






