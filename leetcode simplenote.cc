
soulmachine.gitbooks.io/algorithm-essentials/cpp/dfs/unique-paths.html

1. Two Sum 两数之和

Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution.
Example:
Given nums = [2, 7, 11, 15], target = 9,
Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

这道题一看就知道用暴力搜索肯定没问题，而且猜到OJ肯定不会允许用暴力搜索这么简单的方法，于是去试了一下，果然是Time Limit Exceeded，这个算法的时间复杂度是O(n^2)。那么只能想个O(n)的算法来实现，整个实现步骤为：先遍历一遍数组，建立map数据，然后再遍历一遍，开始查找，找到则记录index

 vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            m[nums[i]] = i;
        }
        for (int i = 0; i < nums.size(); ++i) {
            int t = target - nums[i];
            if (m.count(t) && m[t] != i) {
                res.push_back(i);
                res.push_back(m[t]);
                break;
            }
        }
        return res;
    }


2. Add Two Numbers 两个数字相加  

You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

就是建立一个新链表，然后把输入的两个链表从头往后撸，每两个相加，添加一个新节点到新链表后面，就是要处理下进位问题。还有就是最高位的进位问题要最后特殊处理一下

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *res = new ListNode(-1);
    ListNode *cur = res;
    int carry = 0;

    while (l1 || l2) {
        int n1 = l1 ? l1->val : 0;
        int n2 = l2 ? l2->val : 0;
        int sum = n1 + n2 + carry;
        carry = sum / 10;
        cur->next = new ListNode(sum % 10);
        cur = cur->next;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }
    if (carry) cur->next = new ListNode(1);
    return res->next;
}


3. Longest Substring Without Repeating Characters 最长无重复子串

Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.



int lengthOfLongestSubstring(string s) {
        vector<int> m(256, -1);
        int res = 0, left = -1;
        for (int i = 0; i < s.size(); ++i) {
            left = max(left, m[s[i]]);
            m[s[i]] = i;
            res = max(res, i - left);
        }
        return res;
    }


下面这种解法使用了set，核心算法和上面的很类似，把出现过的字符都放入set中，遇到set中没有的字符就加入set中并更新结果res，如果遇到重复的，则从左边开始删字符，直到删到重复的字符停止

 int lengthOfLongestSubstring(string s) {
        set<char> t;
        int res = 0, left = 0, right = 0;
        while (right < s.size()) {
            if (t.find(s[right]) == t.end()) {
                t.insert(s[right++]);
                res = max(res, (int)t.size());
            }  else {
                t.erase(s[left++]);
            }
        }
        return res;
    }



4. Median of Two Sorted Arrays 两个有序数组的中位数

There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).


而且限制了时间复杂度为O(log (m+n))，看到这个时间复杂度，自然而然的想到了应该使用二分查找法来求解. 这里我们需要定义一个函数来找到第K个元素，由于两个数组长度之和的奇偶不确定，因此需要分情况来讨论，对于奇数的情况，直接找到最中间的数即可，偶数的话需要求最中间两个数的平均值。下面重点来看如何实现找到第K个元素，首先我们需要让数组1的长度小于或等于数组2的长度，那么我们只需判断如果数组1的长度大于数组2的长度的话，交换两个数组即可，然后我们要判断小的数组是否为空，为空的话，直接在另一个数组找第K个即可。还有一种情况是当K = 1时，表示我们要找第一个元素，只要比较两个数组的第一个元素，返回较小的那个即可。 


    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        return (findKth(nums1, nums2, (m + n + 1) / 2) + findKth(nums1, nums2, (m + n + 2) / 2)) / 2.0;
    }
    
    int findKth(vector<int> nums1, vector<int> nums2, int k) {
        int m = nums1.size(), n = nums2.size();
        if (m > n) return findKth(nums2, nums1, k);
        if (m == 0) return nums2[k - 1];
        if (k == 1) return min(nums1[0], nums2[0]);
        int i = min(m, k / 2), j = min(n, k / 2);
        if (nums1[i - 1] > nums2[j - 1]) {
            return findKth(nums1, vector<int>(nums2.begin() + j, nums2.end()), k - j);
        } else {
            return findKth(vector<int>(nums1.begin() + i, nums1.end()), nums2, k - i);
        }
        return 0;
    }




5. Longest Palindromic Substring 最长回文串

我们维护一个二维数组dp，其中dp[i][j]表示字符串区间[i, j]是否为回文串，当i = j时，只有一个字符，肯定是回文串，如果i = j + 1，说明是相邻字符，此时需要判断s[i]是否等于s[j]，如果i和j不相邻，即i - j >= 2时，除了判断s[i]和s[j]相等之外，dp[j + 1][i - 1]若为真，就是回文串


可以写出递推式如下：

dp[i, j] = 1 , if i == j
         = s[i] == s[j] , if j = i + 1
         = s[i] == s[j] && dp[i + 1][j - 1] , if j > i + 1      


   string longestPalindrome(string s) {
        int dp[s.size()][s.size()] = {0}, left = 0, right = 0, len = 0;

        for (int i = 0; i < s.size(); ++i) {
            for (int j = 0; j < i; ++j) {

                dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j + 1][i - 1]));

                if (dp[j][i] && len < i - j + 1) {
                    len = i - j + 1;
                    left = j;
                    right = i;
                }
            }

            dp[i][i] = 1;
        }
        return s.substr(left, right - left + 1);
    }



6. ZigZag Converesion 之字型转换字符串

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR". 


 string convert(string str, int n) {
        // void printZigZagConcat(string str, int n)

    // Corner Case (Only one row)
    if (n == 1) {
        return str;      
        // return;
    }   
 
    // Find length of string
    int len = str.length();
 
    // Create an array of strings for all n rows
    string arr[n];
 
    // Initialize index for array of strings arr[]
    int row = 0;
    bool down; // True if we are moving down in rows, 
               // else false
 
    // Travers through given string
    for (int i = 0; i < len; ++i) {
        // append current character to current row
        arr[row].push_back(str[i]);
 
        // If last row is reached, change direction to 'up'
        if (row == n-1)
          down = false;
 
        // If 1st row is reached, change direction to 'down'
        else if (row == 0)
          down = true;
 
        // If direction is down, increment, else decrement
        (down)? (row++): (row--);
    }
 
     string ret;

    // Print concatenation of all rows
    for (int i = 0; i < n; ++i)
        ret = ret + arr[i];
    
    return ret;    
}


7. Reverse Integer 翻转整数

Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321  

solution 1: 

 int reverse(int x) {
        int res = 0;
        while (x != 0) {
            if (abs(res) > INT_MAX / 10) return 0;
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res;
    }


solution 2: 
用long long型变量保存计算结果，最后返回的时候判断是否在int返回内 


int reverse(int x) {
    long long res = 0;
    while (x != 0) {
        res = 10 * res + x % 10;
        x /= 10;
    }
    return (res > INT_MAX || res < INT_MIN) ? 0 : res;
}


8. String to Integer (atoi) 字符串转为整数
          
Implement atoi to convert a string to an integer.

包括符号，自然数，小数点的出现位置，判断他们是否是数字。个人以为这道题也应该有这么多种情况。但是这题只需要考虑数字和符号的情况：

1. 若字符串开头是空格，则跳过所有空格，到第一个非空格字符，如果没有，则返回0.
2. 若第一个非空格字符是符号+/-，则标记sign的真假，这道题还有个局限性，那就是在c++里面，+-1和-+1都是认可的，都是-1，而在此题里，则会返回0.
3. 若下一个字符不是数字，则返回0. 完全不考虑小数点和自然数的情况，不过这样也好，起码省事了不少。
4. 如果下一个字符是数字，则转为整形存下来，若接下来再有非数字出现，则返回目前的结果。
5. 还需要考虑边界问题，如果超过了整形数的范围，则用边界值替代当前值。


   int myAtoi(string str) {

        if (str.empty()) 
        	return 0;

        int sign = 1, base = 0, i = 0, n = str.size();

        while (i < n && str[i] == ' ') 
        	++i;

        if (str[i] == '+' || str[i] == '-') {
            sign = (str[i++] == '+') ? 1 : -1;
        }

        while (i < n && str[i] >= '0' && str[i] <= '9') {

            if (base > INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }

            base = 10 * base + (str[i++] - '0');
        }
        return base * sign;
    }



9. Palindrome Number 验证回文数字

Determine whether an integer is a palindrome. Do this without extra space.

solution: 翻转数字再比较

public bool IsPalindrome(int x) {
	if (x < 0) return false;

	int result = 0;
	int original = x;

	while(x != 0)
	{
		result = result * 10 + x % 10;
		x /= 10;
	}

	return result == original;
}


10. Regular Expression Matching 正则表达式匹配  
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true



这道求正则表达式匹配的题和那道 Wildcard Matching 通配符匹配的题很类似，不同点在于*的意义不同，在之前那道题中，*表示可以代替任意个数的字符，而这道题中的*表示之前那个字符可以有0个，1个或是多个，就是说，字符串a*b，可以表示b或是aaab，即a的个数任意，这道题的难度要相对之前那一道大一些，分的情况的要复杂一些，需要用递归Recursion来解，大概思路如下：

- 若p为空，若s也为空，返回true，反之返回false
- 若p的长度为1，若s长度也为1，且相同或是p为'.'则返回true，反之返回false
- 若p的第二个字符不为*，若此时s为空返回false，否则判断首字符是否匹配，且从各自的第二个字符开始调用递归函数匹配
- 若p的第二个字符为*，若s不为空且字符匹配，调用递归函数匹配s和去掉前两个字符的p，若匹配返回true，否则s去掉首字母
- 返回调用递归函数匹配s和去掉前两个字符的p的结果


我们也可以用DP来解，定义一个二维的DP数组，其中dp[i][j]表示s[0,i)和p[0,j)是否match，然后有下面三种情况(下面部分摘自这个帖子)：

1.  dp[i][j] = dp[i - 1][j - 1], if p[j - 1] != '*' && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
2.  dp[i][j] = dp[i][j - 2], if p[j - 1] == '*' and the pattern repeats for 0 times;
3.  dp[i][j] = dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'), if p[j - 1] == '*' and the pattern repeats for at least 1 times.


bool isMatch(string s, string p) {

    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int i = 0; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1 && p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
            } else {
                dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
            }
        }
    }

    return dp[m][n];
}


11. Container With Most Water 装最多水的容器  

我们需要定义i和j两个指针分别指向数组的左右两端，然后两个指针向中间搜索，每移动一次算一个值和结果比较取较大的，容器装水量的算法是找出左右两个边缘中较小的那个乘以两边缘的距离. 

int maxArea(vector<int>& height) {
    int res = 0, i = 0, j = height.size() - 1;

    while (i < j) {
        res = max(res, min(height[i], height[j]) * (j - i));
        height[i] < height[j] ? ++i : --j;
    }

    return res;
}


12. Integer to Roman 整数转化成罗马数字 

Given an integer, convert it to a roman numeral.
Input is guaranteed to be within the range from 1 to 3999.

本题由于限制了输入数字范围这一特殊性，故而还有一种利用贪婪算法的解法，建立一个数表，每次通过查表找出当前最大的数，减去再继续查表。

string intToRoman(int num) {

    string res = "";
    vector<int> val{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    vector<string> str{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    for (int i = 0; i < val.size(); ++i) {
        while (num >= val[i]) {
            num -= val[i];
            res += str[i];
        }
    }

    return res;
}


13. Roman to Integer 罗马数字转化成整数

我们需要用到map数据结构，来将罗马数字的字母转化为对应的整数值，因为输入的一定是罗马数字，那么我们只要考虑两种情况即可：
第一，如果当前数字是最后一个数字，或者之后的数字比它小的话，则加上当前数字
第二，其他情况则减去这个数字

int romanToInt(string s) {
    int res = 0;
    unordered_map<char, int> m{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

    for (int i = 0; i < s.size(); ++i) {
        int val = m[s[i]];
        if (i == s.size() - 1 || m[s[i+1]] <= m[s[i]]) res += val;
        else res -= val;
    }

    return res;
}


14. Longest Common Prefix 最长共同前缀 

Write a function to find the longest common prefix string amongst an array of strings.

string longestCommonPrefix(vector<string>& strs) {

    string res = "";

    if (strs.empty()) return res;

    for (int j = 0; j < strs[0].size(); ++j) {
        char c = strs[0][j];
        for (int i = 1; i < strs.size(); ++i) {
            if (j >= strs[i].size() || strs[i][j] != c) {
                return res;
            }
        }
        res.push_back(c);
    }

    return res;
}


15. 3Sum 三数之和 

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
The solution set must not contain duplicate triplets.


我们还是要首先对原数组进行排序，然后开始遍历排序后的数组，这里注意不是遍历到最后一个停止，而是到倒数第三个就可以了，然后我们还要加上重复就跳过的处理，对于遍历到的数，我们用0减去这个数得到一个sum，我们只需要再之后找到两个数之和等于sum即可，这样一来问题又转化为了求two sum，这时候我们一次扫描，找到了等于sum的两数后，加上当前遍历到的数字，按顺序存入结果中即可，然后还要注意跳过重复数字。


   vector<vector<int>> threeSum(vector<int>& nums) {

        vector<vector<int>> res;
        sort(nums.begin(), nums.end());

        for (int k = 0; k < nums.size(); ++k) {

            if (nums[k] > 0) break;
            if (k > 0 && nums[k] == nums[k - 1]) continue;
            int target = 0 - nums[k];
            int i = k + 1, j = nums.size() - 1;

            while (i < j) {
                if (nums[i] + nums[j] == target) {
                    res.push_back({nums[k], nums[i], nums[j]});
                    while (i < j && nums[i] == nums[i + 1]) ++i;
                    while (i < j && nums[j] == nums[j - 1]) --j;
                    ++i; --j;
                } else if (nums[i] + nums[j] < target) 
               		++i;
                else 
                	--j;
            }
        }
        return res;
    }


16. 3Sum Closest 最近三数之和

Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.          
    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).


那么这道题让我们返回这个最接近于给定值的值，即我们要保证当前三数和跟给定值之间的差的绝对值最小，所以我们需要定义一个变量diff用来记录差的绝对值，然后我们还是要先将数组排个序，然后开始遍历数组，思路跟那道三数之和很相似，都是先确定一个数，然后用两个指针left和right来滑动寻找另外两个数，每确定两个数，我们求出此三数之和，然后算和给定值的差的绝对值存在newDiff中，然后和diff比较并更新diff和结果closest即可 

int threeSumClosest(vector<int>& nums, int target) {

    int closest = nums[0] + nums[1] + nums[2];
    int diff = abs(closest - target);
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 2; ++i) {
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            int newDiff = abs(sum - target);
            if (diff > newDiff) {
                diff = newDiff;
                closest = sum;
            }
            if (sum < target) ++left;
            else --right;
        }
    }
    return closest;
}


17. Letter Combinations of a Phone Number 电话号码的字母组合

Given a digit string, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.


我们用递归Recursion来解，我们需要建立一个字典，用来保存每个数字所代表的字符串，然后我们还需要一个变量level，记录当前生成的字符串的字符个数

  vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.empty()) return res;
        string dict[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        letterCombinationsDFS(digits, dict, 0, "", res);
        return res;
    }

    void letterCombinationsDFS(string digits, string dict[], int level, string out, vector<string> &res) {

        if (level == digits.size()) 
        	res.push_back(out);
        else {
            string str = dict[digits[level] - '2'];
            for (int i = 0; i < str.size(); ++i) {

                out.push_back(str[i]);
                letterCombinationsDFS(digits, dict, level + 1, out, res);
                out.pop_back();
            }
        }
    }


这道题我们也可以用迭代Iterative来解

vector<string> letterCombinations(string digits) {

    vector<string> res;
    if (digits.empty()) return res;
    string dict[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    res.push_back("");

    for (int i = 0; i < digits.size(); ++i) {
        int n = res.size();
        string str = dict[digits[i] - '2'];

        for (int j = 0; j < n; ++j) {
            string tmp = res.front();
            res.erase(res.begin());

            for (int k = 0; k < str.size(); ++k) {
                res.push_back(tmp + str[k]);
            }
        }
    }
    return res;
}


18. 4Sum 四数之和

Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
The solution set must not contain duplicate quadruplets.
For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

为了避免重复项，我们使用了STL中的set，其特点是不能有重复，如果新加入的数在set中原本就存在的话，插入操作就会失败. 解法的思路跟3Sum 三数之和基本没啥区别，就是多加了一层for循环，其他的都一样


vector<vector<int> > fourSum(vector<int> &nums, int target) {
    set<vector<int> > res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < int(nums.size() - 3); ++i) {
        for (int j = i + 1; j < int(nums.size() - 2); ++j) {
            int left = j + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target) {
                    vector<int> out;
                    out.push_back(nums[i]);
                    out.push_back(nums[j]);
                    out.push_back(nums[left]);
                    out.push_back(nums[right]);
                    res.insert(out);
                    ++left; --right;
                } else if (sum < target) ++left;
                else --right;
            }
        }
    }
    return vector<vector<int> > (res.begin(), res.end());
}


19. Remove Nth Node From End of List 移除链表倒数第N个节点  

如何找到倒数第N个节点，由于只允许一次遍历，所以我们不能用一次完整的遍历来统计链表中元素的个数，而是遍历到对应位置就应该移除了。那么我们需要用两个指针来帮助我们解题，pre和cur指针。首先cur指针先向前走N步，如果此时cur指向空，说明N为链表的长度，则需要移除的为首元素，那么此时我们返回head->next即可，如果cur存在，我们再继续往下走，此时pre指针也跟着走，直到cur为最后一个元素时停止，此时pre指向要移除元素的前一个元素，我们再修改指针跳过需要移除的元素即可. 

最后一个元素是倒数第1个，第一个元素是第0个. 

ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (!head->next) return NULL;
    ListNode *pre = head, *cur = head;
    for (int i = 0; i < n; ++i) cur = cur->next;
    if (!cur) return head->next; // it means delete head 
    while (cur->next) {
        cur = cur->next;
        pre = pre->next;
    }
    pre->next = pre->next->next;
    return head;
}


20. Valid Parentheses 验证括号 
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

这里我们需要用一个栈，我们开始遍历输入字符串，如果当前字符为左半边括号时，则将其压入栈中，如果遇到右半边括号时，若此时栈为空，则直接返回false，如不为空，则取出栈顶元素，若为对应的左半边括号，则继续循环，反之返回false


bool isValid(string s) {
    stack<char> parentheses;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') parentheses.push(s[i]);
        else {
            if (parentheses.empty()) return false;
            if (s[i] == ')' && parentheses.top() != '(') return false;
            if (s[i] == ']' && parentheses.top() != '[') return false;
            if (s[i] == '}' && parentheses.top() != '{') return false;
            parentheses.pop();
        }
    }
    return parentheses.empty();
}


21. Generate Parentheses 生成括号

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()"
如果在某次递归时，左括号的个数大于右括号的个数，说明此时生成的字符串中右括号的个数大于左括号的个数，即会出现')('这样的非法串，所以这种情况直接返回，不继续处理。

vector<string> generateParenthesis(int n) {
    // Write your code here
    vector<string> res;
    string out;
    dfs(n, 0, 0, out, res);
    return res;
}

void dfs(int n, int left, int right, string &out, vector<string> &res) {
    if (left < n) { //Keep 塞左括号
        out.push_back('(');
        dfs(n, left + 1, right, out, res);
        out.pop_back();
    }

    if (right < left) { //避免出现右括号多余左括号的情况
        out.push_back(')');
        dfs(n, left, right + 1, out, res);
        out.pop_back();
    }

    if (out.size() == n * 2)
        res.push_back(out);
}


22. Merge Two Sorted Lists 混合插入有序链表 

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

具体思想就是新建一个链表，然后比较两个链表中的元素值，把较小的那个链到新链表中，由于两个输入链表的长度可能不同，所以最终会有一个链表先完成插入所有元素，则直接另一个未完成的链表直接链入新链表的末尾。


    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dummy = new ListNode(-1), *cur = dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1 : l2;
        return dummy->next;
    }


recursion: 
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}


23. Merge k Sorted Lists 合并k个有序链表  

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity. 

最小堆这种数据结构，我们首先把k个链表的首元素都加入最小堆中，它们会自动排好序。然后我们每次取出最小的那个元素加入我们最终结果的链表中，然后把取出元素的下一个元素再加入堆中，下次仍从堆中取出最小的元素做相同的操作，以此类推，直到堆中没有元素了，此时k个链表也合并为了一个链表，返回首节点即可

struct cmp {
bool operator () (ListNode *a, ListNode *b) {
    return a->val > b->val;
}
};


ListNode *mergeKLists(vector<ListNode *> &lists) {  
    priority_queue<ListNode*, vector<ListNode*>, cmp> q;  // EleType, vector<EleType>, cmp  
    for (int i = 0; i < lists.size(); ++i) {
        if (lists[i]) q.push(lists[i]);
    }
    ListNode *head = NULL, *pre = NULL, *tmp = NULL;
    while (!q.empty()) {
        tmp = q.top();
        q.pop();
        if (!pre) head = tmp;
        else pre->next = tmp;
        pre = tmp;
        if (tmp->next) q.push(tmp->next);
    }
    return head;
}   


24. Swap Nodes in Pairs 成对交换节点 

Given a linked list, swap every two adjacent nodes and return its head.
For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.

对于迭代实现，还是需要建立dummy节点，注意在连接节点的时候，最好画个图，以免把自己搞晕了

ListNode* swapPairs(ListNode* head) {
    ListNode *dummy = new ListNode(-1), *pre = dummy;
    dummy->next = head;
    while (pre->next && pre->next->next) {
        ListNode *t = pre->next->next;
        pre->next->next = t->next;
        t->next = pre->next;
        pre->next = t;
        pre = t->next;
    }
    return dummy->next;
}


recursion: 

ListNode* swapPairs(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode *t = head->next;  // 注意顺序 head->next 在右
    head->next = swapPairs(head->next->next);  // head->next 在左，类似swap 
    t->next = head;
    return t;
}


25. Reverse Nodes in k-Group 每k个一组翻转链表

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
You may not alter the values in the nodes, only nodes itself may be changed.
Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5
For k = 2, you should return: 2->1->4->3->5
For k = 3, you should return: 3->2->1->4->5

以每k个为一组来翻转链表，实际上是把原链表分成若干小段，然后分别对其进行翻转，那么肯定总共需要两个函数，一个是用来分段的，一个是用来翻转的，我们就以题目中给的例子来看，对于给定链表1->2->3->4->5，一般在处理链表问题时，我们大多时候都会在开头再加一个dummy node，因为翻转链表时头结点可能会变化，为了记录当前最新的头结点的位置而引入的dummy node，那么我们加入dummy node后的链表变为-1->1->2->3->4->5，如果k为3的话，我们的目标是将1,2,3翻转一下，那么我们需要一些指针，pre和next分别指向要翻转的链表的前后的位置，然后翻转后pre的位置更新到如下新的位置


ListNode *reverseKGroup(ListNode *head, int k) {
    if (!head || k == 1) return head;
    ListNode *dummy = new ListNode(-1);
    ListNode *pre = dummy, *cur = head;
    dummy->next = head;
    int i = 0;
    while (cur) {
        ++i;
        if (i % k == 0) {
            pre = reverseOneGroup(pre, cur->next);
            cur = pre->next;
        } else {
            cur = cur->next;
        }
    }
    return dummy->next;
}

ListNode *reverseOneGroup(ListNode *pre, ListNode *next) {  // pre为要翻转链表的前节点，next为要翻转链表的后节点
    ListNode *last = pre->next;
    ListNode *cur = last->next;
    while(cur != next) {
        last->next = cur->next;
        cur->next = pre->next;
        pre->next = cur;
        cur = last->next;
    }
    return last; // last 为reverse后链表最后一个节点
}



26. Remove Duplicates from Sorted Array 有序数组中去除重复项 

Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array A = [1,1,2],

Your function should return length = 2, and A is now [1,2].

我们使用快慢指针来记录遍历的坐标，最开始时两个指针都指向第一个数字，如果两个指针指的数字相同，则快指针向前走一步，如果不同，则两个指针都向前走一步，这样当快指针走完整个数组后，慢指针当前的坐标加1就是数组中不同数组的个数


int removeDuplicates(int A[], int n) {
    if (n <= 1) return n;
    int pre = 0, cur = 0;
    while (cur < n) {
        if (A[cur] == A[pre]) ++cur;
        else A[++pre] = A[cur++];
    }
    return pre + 1;
}


27. Remove Element 移除元素 

Given an array and a value, remove all instances of that value in place and return the new length.

The order of elements can be changed. It doesnot matter what you leave beyond the new length 


这道题让我们移除一个数组中和给定值相同的数字，并返回新的数组的长度。是一道比较容易的题，我们只需要一个变量用来计数，然后遍历原数组，如果当前的值和给定值不同，我们就把当前值覆盖计数变量的位置，并将计数变量加1

int removeElement(vector<int>& nums, int val) {
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] != val) nums[res++] = nums[i];
    }
    return res;
}


28. Implement strStr() 实现strStr()函数

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

我们在一个字符串中找另一个字符串第一次出现的位置，那我们首先要做一些判断，如果子字符串为空，则返回0，如果子字符串长度大于母字符串长度，则返回-1。然后我们开始遍历母字符串，我们并不需要遍历整个母字符串，而是遍历到剩下的长度和子字符串相等的位置即可，这样可以提高运算效率。然后对于每一个字符，我们都遍历一遍子字符串，一个一个字符的对应比较，如果对应位置有不等的，则跳出循环，如果一直都没有跳出循环，则说明子字符串出现了，则返回起始位置即可，

int strStr(string haystack, string needle) {
    if (needle.empty()) return 0;
    int m = haystack.size(), n = needle.size();
    if (m < n) return -1;
    for (int i = 0; i <= m - n; ++i) {
        int j = 0;   // 注意
        for (j = 0; j < n; ++j) {
            if (haystack[i + j] != needle[j]) break;
        }
        if (j == n) return i;
    }
    return -1;
}


29. Divide Two Integers 两数相除 

Divide two integers without using multiplication, division and mod operator.
If it is overflow, return MAX_INT. 

如果被除数大于或等于除数，则进行如下循环，定义变量t等于除数，定义计数p，当t的两倍小于等于被除数时，进行如下循环，t扩大一倍，p扩大一倍，然后更新res和m。这道题的OJ给的一些test case非常的讨厌，因为输入的都是int型，比如被除数是-2147483648，在int范围内，当除数是-1时，结果就超出了int范围，需要返回INT_MAX，所以对于这种情况我们就在开始用if判定，将其和除数为0的情况放一起判定，返回INT_MAX。然后我们还要根据被除数和除数的正负来确定返回值的正负，这里我们采用长整型long来完成所有的计算，最后返回值乘以符号即可

int divide(int dividend, int divisor) {

    if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
    long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;
    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
    if (n == 1) return sign == 1 ? m : -m;

    while (m >= n) {
        long long t = n, temp = 1;
        while (m >= (t << 1)) {
            t <<= 1;
            temp <<= 1;
        }
        res += temp;
        m -= t;
    }
    return sign == 1 ? res : -res;
}


recursion: 
int divide(int dividend, int divisor) {

    long long res = 0;
    long long m = abs((long long)dividend), n = abs((long long)divisor);
    if (m < n) return 0;
    long long t = n, p = 1;

    while (m > (t << 1)) {
        t <<= 1;
        p <<= 1;
    }
c
    res += p + divide(m - t, n);
    if ((dividend < 0) ^ (divisor < 0)) res = -res;
    return res > INT_MAX ? INT_MAX : res;
}


30.  Substring with Concatenation of All Words 串联所有单词的子串  

You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).


这道题让我们求串联所有单词的子串，就是说给定一个长字符串，再给定几个长度相同的单词，让我们找出串联给定所有单词的子串的起始位置，还是蛮有难度的一道题。这道题我们需要用到两个哈希表，第一个哈希表先把所有的单词存进去，然后从开头开始一个个遍历，停止条件为当剩余字符个数小于单词集里所有字符的长度。这时候我们需要定义第二个哈希表，然后每次找出给定单词长度的子串，看其是否在第一个哈希表里，如果没有，则break，如果有，则加入第二个哈希表，但相同的词只能出现一次，如果多了，也break。如果正好匹配完给定单词集里所有的单词，则把i存入结果中

// 解法有点像 no.28
vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> res;
    if (s.empty() || words.empty()) return res;
    int n = words.size(), m = words[0].size();
    unordered_map<string, int> m1;
    for (auto &a : words) 
        ++m1[a];

    for (int i = 0; i <= (int)s.size() - n * m; ++i) {  // 注意等号
        unordered_map<string, int> m2;
        int j = 0;  // 注意
        for (j = 0; j < n; ++j) {
            string t = s.substr(i + j * m, m);
            if (m1.find(t) == m1.end()) break;
            ++m2[t];
            if (m2[t] > m1[t]) break;
        }
        if (j == n) res.push_back(i);
    }
    return res;
}


31. Next Permutation 下一个排列  

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1


这道题让我们求下一个排列顺序，有题目中给的例子可以看出来，如果给定数组是降序，则说明是全排列的最后一种情况，则下一个排列就是最初始情况，可以参见之前的博客 Permutations 全排列。我们再来看下面一个例子，有如下的一个数组

1　　2　　7　　4　　3　　1

下一个排列为：

1　　3　　1　　2　　4　　7

那么是如何得到的呢，我们通过观察原数组可以发现，如果从末尾往前看，数字逐渐变大，到了2时才减小的，然后我们再从后往前找第一个比2大的数字，是3，那么我们交换2和3，再把此时3后面的所有数字转置一下即可，步骤如下：

1　　2　　7　　4　　3　　1

1　　2　　7　　4　　3　　1

1　　3　　7　　4　　2　　1

1　　3　　1　　2　　4　　7


void nextPermutation(vector<int> &num) {
    int i, j, n = num.size(); // 注意 i, j declare here
    for (i = n - 2; i >= 0; --i) {
        if (num[i + 1] > num[i]) {
            for (j = n - 1; j > i; --j) {
                if (num[j] > num[i]) break;
            }
            swap(num[i], num[j]);
            reverse(num.begin() + i + 1, num.end());
            return;
        }
    }
    reverse(num.begin(), num.end());
}


32. Longest Valid Parentheses 最长有效括号

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
 

这道求最长有效括号比之前那道 Valid Parentheses 验证括号难度要大一些，这里我们还是借助栈来求解，需要定义个start变量来记录合法括号串的起始位置，我们遍历字符串，如果遇到左括号，则将当前下标压入栈，如果遇到右括号，如果当前栈为空，则将下一个坐标位置记录到start，如果栈不为空，则将栈顶元素取出，此时若栈为空，则更新结果和i - start + 1中的较大值，否则更新结果和i - 栈顶元素中的较大值

int longestValidParentheses(string s) {
    int res = 0, start = 0;
    stack<int> m;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') m.push(i);
        else if (s[i] == ')') {
            if (m.empty()) start = i + 1;
            else {
                m.pop();  // 先pop了, 下一句判断是否empty才有意义, corner case: ()()
                res = m.empty() ? max(res, i - start + 1) : max(res, i - m.top());  
                // i-m.top(): 因为先pop了要匹配的'(', top()实际是要匹配的'('之前的那个字符  
            }
        }
    }
    return res;
}



33. Search in Rotated Sorted Array 在旋转有序数组中搜索 

Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.

这道题让在旋转数组中搜索一个给定值，若存在返回坐标，若不存在返回-1。我们还是考虑二分搜索法，但是这道题的难点在于我们不知道原数组在哪旋转了，我们还是用题目中给的例子来分析，对于数组[0 1 2 4 5 6 7] 共有下列七种旋转方法：

0　　1　　2　　 4　　5　　6　　7

7　　0　　1　　 2　　4　　5　　6

6　　7　　0　　 1　　2　　4　　5

5　　6　　7　　 0　　1　　2　　4

4　　5　　6　　7　　0　　1　　2

2　　4　　5　　6　　7　　0　　1

1　　2　　4　　5　　6　　7　　0

二分搜索法的关键在于获得了中间数后，判断下面要搜索左半段还是右半段，我们观察上面红色的数字都是升序的，由此我们可以观察出规律，如果中间的数小于最右边的数，则右半段是有序的，若中间数大于最右边数，则左半段是有序的，我们只要在有序的半段里用首尾两个数组来判断目标值是否在这一区域内，这样就可以确定保留哪半边了


int search(int A[], int n, int target) {
    if (n == 0) return -1;
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (A[mid] == target) return mid;
        else if (A[mid] < A[right]) {
            if (A[mid] < target && target <= A[right]) left = mid + 1;
            else right = mid - 1;
        } else {
            if (A[left] <= target && target < A[mid]) right = mid - 1;
            else left = mid + 1;
        }
    }

    return -1;
}


34. Search for a Range 搜索一个范围  

Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithms runtime complexity must be in the order of O(log n).
If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

这道题让我们在一个有序整数数组中寻找相同目标值的起始和结束位置，而且限定了时间复杂度为O(logn)，这是典型的二分查找法的时间复杂度，所以这道题我们也需要用此方法，我们的思路是首先对原数组使用二分查找法，找出其中一个目标值的位置，然后向两边搜索找出起始和结束的位置. 使用两次二分查找法，第一次找到左边界，第二次调用找到右边界即可


vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res(2, -1);
    int left = 0, right = nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }

    if (nums[right] != target) return res;
    res[0] = right;
    right = nums.size();

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target) left = mid + 1;
        else right= mid;
    }

    res[1] = left - 1;
    return res;
}

solution 2: 
vector<int> searchRange(vector<int>& nums, int target) {

    vector<int> ret; 
    if(nums.size() == 0) {
         ret.push_back(-1);
        ret.push_back(-1);
        return ret; 
    }
    
    if(nums.size() == 1 && nums[0] == target) {
        ret.push_back(0);
        ret.push_back(0);
        return ret; 
        
    } else if(nums.size() == 1 && nums[0] != target) {
        ret.push_back(-1);
        ret.push_back(-1);
        return ret; 
        
    }
    
    
    int low = 0; 
    int high = nums.size(); 
    
    while(low < high) {  // 找下限
        int mid = low + (high - low)/2; 
        
        if(nums[mid] == target)
            high = mid; 
        else if(nums[mid] > target)
            high = mid; 
        else if(nums[mid] < target)
            low = mid + 1; 
    }
   
    if(nums[high] == target)
        ret.push_back(high);
    else
        ret.push_back(-1);
    
    low = 0; 
    high = nums.size(); 
    
    while(low + 1 < high) {  // 找上限
        int mid = low + (high - low)/2; 
        
        if(nums[mid] == target)
            low = mid; 
        else if(nums[mid] > target)
            high = mid; 
        else if(nums[mid] < target)
            low = mid + 1; 
    }
    
    if(nums[low] == target)
        ret.push_back(low);
    else
        ret.push_back(-1);
    
    return ret; 
}


35. Search Insert Position 搜索插入位置 

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0


int searchInsert(vector<int>& nums, int target) {
        if (nums.back() < target) return nums.size();
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        return right;
    }


37. Sudoku Solver 求解数独

Write a program to solve a Sudoku puzzle by filling the empty cells.
Empty cells are indicated by the character '.'.
You may assume that there will be only one unique solution.


    void solveSudoku(vector<vector<char> > &board) {
        if (board.empty() || board.size() != 9 || board[0].size() != 9) return;
        solveSudokuDFS(board, 0, 0);
    }

    bool solveSudokuDFS(vector<vector<char> > &board, int i, int j) {
        if (i == 9) return true;
        if (j >= 9) return solveSudokuDFS(board, i + 1, 0); // 再扫一列
        if (board[i][j] == '.') {
            for (int k = 1; k <= 9; ++k) {
                board[i][j] = (char)(k + '0');
                if (isValid(board, i , j)) {
                    if (solveSudokuDFS(board, i, j + 1)) return true;  // 先扫一排
                }
                board[i][j] = '.';
            }
        } else {
            return solveSudokuDFS(board, i, j + 1);
        }
        return false;
    }
    
    bool isValid(vector<vector<char> > &board, int i, int j) {
        for (int col = 0; col < 9; ++col) {
            if (col != j && board[i][j] == board[i][col]) return false;
        }
        for (int row = 0; row < 9; ++row) {
            if (row != i && board[i][j] == board[row][j]) return false;
        }
        for (int row = i / 3 * 3; row < i / 3 * 3 + 3; ++row) {
            for (int col = j / 3 * 3; col < j / 3 * 3 + 3; ++col) {
                if ((row != i || col != j) && board[i][j] == board[row][col]) return false;
            }
        }
        return true;
    }



38. Count and Say 计数和读法

The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.

逐个构建序列——根据第i-1个序列构建后第i个。理解题目意思后便知道在扫描前一个序列ret时，需要一个计数变量count记录当前字符重复的次数，以及需要一个字符变量prev记录上一个字符的值。当ret[i] = prev，则先不写入结果，而增加count。当ret[i] != prev时，说明prev的重复结束，需要将count和prev都写入结果，然后重置count为1，prev为ret[i]。


 string countAndSay(int n) {
        if(n<1) return "";
        string ret = "1";
        for(int i=2; i<=n; i++) {
            string temp = "";
            int count = 1;
            char prev = ret[0];
            for(int j=1; j<ret.size(); j++) {
                if(ret[j]==prev)
                    count++;
                else {
                    temp += to_string(count);
                    temp += prev;
                    // temp.push_back(prev);
                    count = 1;
                    prev = ret[j];
                }
            }
            temp += to_string(count);
            temp.push_back(prev);
            ret = temp;
        }
        return ret;
    }


39. Combination Sum 组合之和

Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:

All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
 

For example, given candidate set 2,3,6,7 and target 7, 
A solution set is: 
[7] 
[2, 2, 3] 

这里我们新加入三个变量，start记录当前的递归到的下标，out为一个解，res保存所有已经得到的解，每次调用新的递归函数时，此时的target要减去当前数组的的数


vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    vector<vector<int> > res;
    vector<int> out;
    sort(candidates.begin(), candidates.end());
    combinationSumDFS(candidates, target, 0, out, res);
    return res;
}

void combinationSumDFS(vector<int> &candidates, int target, int start, vector<int> &out, vector<vector<int> > &res) {
    if (target < 0) return;
    else if (target == 0) res.push_back(out);
    else {
        for (int i = start; i < candidates.size(); ++i) {
            out.push_back(candidates[i]);
            combinationSumDFS(candidates, target - candidates[i], i, out, res); // 一个数字可以使用多次, 所以i不用加一
            out.pop_back();
        }
    }
}



40. Combination Sum II 组合之和之二         


Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:

All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
 

For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
A solution set is: 
[1, 7] 
[1, 2, 5] 
[2, 6] 
[1, 1, 6] 

只需要改动一点点即可，之前那道题给定数组中的数字可以重复使用，而这道题不能重复使用，只需要在之前的基础上修改两个地方即可，首先在递归的for循环里加上if (i > start && num[i] == num[i - 1]) continue; 这样可以防止res中出现重复项，然后就在递归调用combinationSum2DFS里面的参数换成i+1，这样就不会重复使用数组中的数字了. 

vector<vector<int> > combinationSum2(vector<int> &num, int target) {
    vector<vector<int> > res;
    vector<int> out;
    sort(num.begin(), num.end());
    combinationSum2DFS(num, target, 0, out, res);
    return res;
}

void combinationSum2DFS(vector<int> &num, int target, int start, vector<int> &out, vector<vector<int> > &res) {
    if (target < 0) return;
    else if (target == 0) res.push_back(out);
    else {
        for (int i = start; i < num.size(); ++i) {
            if (i > start && num[i] == num[i - 1]) continue; // 防止重复项
            out.push_back(num[i]);
            combinationSum2DFS(num, target - num[i], i + 1, out, res); // 一个数字只能使用一次，所以i+1
            out.pop_back();
        }
    }
}


41. First Missing Positive 首个缺失的正数 

Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.

solution 1:  
这道题让我们找缺失的首个正数，由于限定了O(n)的时间，所以一般的排序方法都不能用，最开始我没有看到还限制了空间复杂度，所以想到了用哈希表来解，这个思路很简单，第一遍遍历数组把所有的数都存入哈希表中，并且找出数组的最大值，下次循环从1开始递增找数字，哪个数字找不到就返回哪个数字，如果一直找到了最大的数字，则返回最大值+1，

solution 2: 
但是上面的解法不是O(1)的时间复杂度，所以我们需要另想一种解法，既然不能建立新的数组，那么我们只能覆盖原有数组，我们的思路是把1放在数组第一个位置A[0]，2放在第二个位置A[1]，即需要把A[i]放在A[A[i] - 1]上，那么我们遍历整个数组，如果A[i] != i + 1, 而A[i]为整数且不大于n，另外A[i]不等于A[A[i] - 1]的话，我们将两者位置调换，如果不满足上述条件直接跳过，最后我们再遍历一遍数组，如果对应位置上的数不正确则返回正确的数


int firstMissingPositive(int A[], int n) {
    int i = 0;
    while (i < n) {
        if (A[i] != i + 1 && A[i] > 0 && A[i] <= n && A[i] != A[A[i] - 1]) {
            swap(A[i], A[A[i] - 1]);
        } else {
            ++i;
        }
    }
    for (i = 0; i < n; ++i) {
        if (A[i] != i + 1) return i + 1;
    }
    return n + 1;
}


42. Trapping Rain Water 收集雨水 

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.


solution 1: 
这种方法是基于动态规划Dynamic Programming的，我们维护一个一维的dp数组，这个DP算法需要遍历两遍数组，第一遍遍历dp[i]中存入i位置左边的最大值，然后开始第二遍遍历数组，第二次遍历时找右边最大值，然后和左边最大值比较取其中的较小值，然后跟当前值A[i]相比，如果大于当前值，则将差值存入结果

// a b c: a 值是index b 的左边最大值，c 值是index b 的右边最大值. 对每个index都要维护a, b 值。  
// 
int trap(vector<int>& height) {
    int res = 0, mx = 0; // 初始化左边最大值为0
    int n = height.size();
    vector<int> dp(n, 0);
    for (int i = 0; i < n; ++i) {
        dp[i] = mx; // 第一遍遍历dp[i]中存入i位置左边的最大值
        mx = max(mx, height[i]);  // mx维护当前height的最大值
    }

    mx = 0; // 初始化右边最大值为0
    for (int i = n - 1; i >= 0; --i) {
        dp[i] = min(dp[i], mx);  // 2. 和左边最大值a比较,  第二遍遍历dp[i]中存入比较后的较小值
        mx = max(mx, height[i]);  // 1. 更新从右边遍历时的最大值c
        if (dp[i] > height[i]) res += dp[i] - height[i];  // 3. 和当前b 比较
    }
    return res;
}


solution 2: 
最后我们来看一种只需要遍历一次即可的解法，这个算法需要left和right两个指针分别指向数组的首尾位置，从两边向中间扫描，在当前两指针确定的范围内，先比较两头找出较小值，如果较小值是left指向的值，则从左向右扫描，如果较小值是right指向的值，则从右向左扫描，若遇到的值比当较小值小，则将差值存入结果，如遇到的值大，则重新确定新的窗口范围，以此类推直至left和right指针重合

int trap(vector<int>& height) {

    int res = 0, l = 0, r = height.size() - 1;
    while (l < r) {
        int mn = min(height[l], height[r]);
        if (mn == height[l]) {
            ++l;
            while (l < r && height[l] < mn) {
                res += mn - height[l++];
            }
        } else {
            --r;
            while (l < r && height[r] < mn) {
                res += mn - height[r--];
            }
        }
    }
    return res;
}


43. Multiply Strings 字符串相乘  

Given two numbers represented as strings, return multiplication of the numbers as a string.
Note: The numbers can be arbitrarily large and are non-negative.

做过Plus One，Add Binary等题后，这类按位运算的题就是一个葫芦里的药了。按照最原始的按位相乘，最后移位相加的法则来计算。

注意：
1. m位的数字乘以n位的数字的结果最大为m+n位：
999*99 < 1000*100 = 100000，最多为3+2 = 5位数。
2. 先将字符串逆序便于从最低位开始计算。


string multiply(string num1, string num2) {

    if(num1.empty() || num2.empty()) return "";
    reverse(num1.begin(),num1.end());
    reverse(num2.begin(),num2.end());
    string ret(num1.size()+num2.size(),'0');
    
    for(int j=0; j<num2.size(); j++) {
        int carry = 0;
        int val = num2[j] - '0';
        for(int i=0; i<num1.size(); i++) {
            carry += ((num1[i]-'0')*val + (ret[i+j]-'0'));
            ret[i+j] = carry%10 + '0';
            carry /= 10;
        }
        if(carry!=0) ret[num1.size()+j] = carry + '0';  // line 17
    }
    reverse(ret.begin(),ret.end());
    
    int count = 0; 
    while(count < ret.size()-1 && ret[count]=='0') count++;  //line 22
    ret.erase(0,count);
    return ret;

}

总结：
题目虽然不难。要完全写对也不容易。
1. 首先要注意num1[i] * num2[j]的结果应该加到ret[i+j]的位置上。
2. 其次要注意line 17不能遗漏最高位的进位，由于此时ret中该位为0，所以只需要将carry转为字符即可。
3. 最容易遗漏的corner case是line 22-24。如999*0 = 0000，此时需要去掉开始的0，但又需要保留最后一个0。


44. Wildcard Matching 外卡匹配  

Implement wildcard pattern matching with support for '?' and '*'.
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).
The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false

外卡匹配和正则匹配最大的区别就是在星号的使用规则上，对于正则匹配来说，星号不能单独存在，前面必须要有一个字符，而星号存在的意义就是表明前面这个字符的个数可以是任意个，包括0个，那么就是说即使前面这个字符并没有在s中出现过也无所谓，只要后面的能匹配上就可以了。而外卡匹配就不是这样的，外卡匹配中的星号跟前面的字符没有半毛钱关系，如果前面的字符没有匹配上，那么直接返回false了，根本不用管星号。而星号存在的作用是可以表示任意的字符串，当然只是当匹配字符串缺少一些字符的时候起作用，当匹配字符串包含目标字符串没有的字符时，将无法成功匹配。


bool isMatch(string s, string p) {

    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; ++i) {
        if (p[i - 1] == '*') dp[0][i] = dp[0][i - 1];
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1]; // dp[i-1][j] 无法理解; dp[i-1][j]对应的corner case: s = "aa", p = "*".  
            } else {
                dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && dp[i - 1][j - 1];
            }
        }
    }

    return dp[m][n];
}


45. Jump Game II 跳跃游戏之二 

Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)


这题是之前那道Jump Game 跳跃游戏 的延伸，那题是问能不能到达最后一个数字，而此题只让我们求到达最后一个位置的最少跳跃数，貌似是默认一定能到达最后位置的? 此题的核心方法还是利用动态规划Dynamic Programming的思想来解，我们需要两个变量cur和pre分别来保存当前的能到达的最远位置和之前能到达的最远位置，只要cur未达到最后一个位置则循环继续，pre记录cur的值，如果当前位置i小于等于pre，则更新cur然后i自增1。更新cur的方法是比较当前的cur和i + A[i]之中的较大值，等i循环到pre的值时，跳跃的步数加一，如果题目中未说明是否能到达末尾，我们还可以判断此时pre和cur是否相等，如果相等说明cur没有更新，即无法到达末尾位置，返回-1

int jump(int A[], int n) {
    int res = 0, i = 0, cur = 0;
    while (cur < n - 1) {
        int pre = cur;
        while (i <= pre) {
            cur = max(cur, i + A[i]);
            ++i;
        }
        ++res;
        // if (pre == cur) return -1; // May not need this
    }
    return res;
}

solution 2 : better time

int jump(vector<int>& nums) {
     int ret = 0;
    int last = 0;
    int curr = 0;
    int n=nums.size();
    for (int i = 0; i < n; ++i) {
        if (i > last) {
            last = curr;
            ++ret;
        }
        curr = max(curr, i+nums[i]);
    }
    return ret;
}



46. Permutations 全排列 

Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].

这道题是求全排列问题，给的输入数组没有重复项，这跟之前的那道 Combinations 组合项 和类似，解法基本相同，但是不同点在于那道不同的数字顺序只算一种，是一道典型的组合题，而此题是求全排列问题，还是用递归DFS来求解。这里我们需要用到一个visited数组来标记某个数字是否访问过，然后在DFS递归函数从的循环应从头开始，而不是从level开始，这是和 Combinations 组合项 不同的地方，其余思路大体相同

vector<vector<int> > permute(vector<int> &num) {
    vector<vector<int> > res;
    vector<int> out;
    vector<int> visited(num.size(), 0);
    permuteDFS(num, 0, visited, out, res);
    return res;
}

void permuteDFS(vector<int> &num, int level, vector<int> &visited, vector<int> &out, vector<vector<int> > &res) {
    if (level == num.size()) res.push_back(out);
    else {
        for (int i = 0; i < num.size(); ++i) { // 注意从0开始循环，combinationSum 从start开始循环
            if (visited[i] == 0) {
                visited[i] = 1;
                out.push_back(num[i]);
                permuteDFS(num, level + 1, visited, out, res);
                out.pop_back();
                visited[i] = 0;
            }
        }
    }
}


47. Permutations II 全排列之二 

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], and [2,1,1].

这道题是之前那道 Permutations 全排列的延伸，由于输入数组有可能出现重复数字，如果按照之前的算法运算，会有重复排列产生，我们要避免重复的产生，在递归函数中要判断前面一个数和当前的数是否相等，如果相等，前面的数必须已经使用了，即对应的visited中的值为1，当前的数字才能使用，否则需要跳过，这样就不会产生重复排列了



    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int> > res;
        vector<int> out;
        vector<int> visited(num.size(), 0);
        sort(num.begin(), num.end());
        permuteUniqueDFS(num, 0, visited, out, res);
        return res;
    }
    void permuteUniqueDFS(vector<int> &num, int level, vector<int> &visited, vector<int> &out, vector<vector<int> > &res) {
        if (level >= num.size()) res.push_back(out);
        else {
            for (int i = 0; i < num.size(); ++i) {
                if (visited[i] == 0) {
                    if (i > 0 && num[i] == num[i - 1] && visited[i - 1] == 0) continue; // 关键
                    visited[i] = 1;
                    out.push_back(num[i]);
                    permuteUniqueDFS(num, level + 1, visited, out, res);
                    out.pop_back();
                    visited[i] = 0;
                }
            }
        }
    }


48. Rotate Image 旋转图像

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?  

最后再来看一种方法，这种方法首先对原数组取其转置矩阵，然后把每行的数字翻转可得到结果，如下所示(其中蓝色数字表示翻转轴)：

1  2  3　　　 　　 1  4  7　　　　　    7  4  1

4  5  6　　-->　　 2  5  8　　 -->  　 8  5  2　　

7  8  9 　　　 　　3  6  9　　　　      9  6  3


void rotate(vector<vector<int> > &matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
        reverse(matrix[i].begin(), matrix[i].end());
    }
}


49. Group Anagrams 群组错位词  

这道题让我们群组给定字符串集中所有的错位词，所谓的错位词就是两个字符串中字母出现的次数都一样，只是位置不同，比如abc，bac, cba等它们就互为错位词，那么我们如何判断两者是否是错位词呢，我们发现如果把错位词的字符顺序重新排列，那么会得到相同的结果，所以重新排序是判断是否互为错位词的方法，由于错位词重新排序后都会得到相同的字符串，我们以此作为key，将所有错位词都保存到字符串数组中，建立key和字符串数组之间的映射，最后再存入结果res中即可


vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res;
    unordered_map<string, vector<string>> m;

    for (string str : strs) {
        string t = str;
        sort(t.begin(), t.end());
        m[t].push_back(str);
    }

    for (auto a : m) {
        res.push_back(a.second);
    }
    return res;
}


50. Pow(x, n) 求x的n次方  

Implement pow(x, n).  

我们可以用递归来折半计算，每次把n缩小一半，这样n最终会缩小到0，任何数的0次方都为1，这时候我们再往回乘，如果此时n是偶数，直接把上次递归得到的值算个平方返回即可，如果是奇数，则还需要乘上个x的值。还有一点需要引起我们的注意的是n有可能为负数，对于n是负数的情况，我们可以先用其绝对值计算出一个结果再取其倒数即可  

solution 1: recursion
double myPow(double x, int n) {
    if (n < 0) return 1 / power(x, -n);
    return power(x, n);
}

double power(double x, int n) {
    if (n == 0) return 1;
    double half = power(x, n / 2);
    if (n % 2 == 0) return half * half;
    return x * half * half;
}

solution 2: iterative  
double myPow(double x, int n) {
    double res = 1.0;
    for (int i = n; i != 0; i /= 2) {
        if (i % 2 != 0) res *= x;
        x *= x;
    }
    return n < 0 ? 1 / res : res;
}


51. N-Queens N皇后问题  

Given an integer n, return all distinct solutions to the n-queens puzzle 

Each solution contains a distinct board configuration of the n-queens placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],


vector<vector<string> > solveNQueens(int n) {
    vector<vector<string> > res;
    vector<int> pos(n, -1);
    solveNQueensDFS(pos, 0, res);
    return res;
}

void solveNQueensDFS(vector<int> &pos, int row, vector<vector<string> > &res) {
    int n = pos.size();
    if (row == n) {
        vector<string> out(n, string(n, '.'));
        for (int i = 0; i < n; ++i) {
            out[i][pos[i]] = 'Q';
        }
        res.push_back(out);
    } else {
        for (int col = 0; col < n; ++col) {
            if (isValid(pos, row ,col)) {
                pos[row] = col;
                solveNQueensDFS(pos, row + 1, res);
                pos[row] = -1;
            }
        }
    }
}

bool isValid(vector<int> &pos, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (col == pos[i] || abs(row - i) == abs(col - pos[i])) {
            return false;
        }
    }
    return true;
}


52. N-Queens II N皇后问题之二 

Follow up for N-Queens problem.
Now, instead outputting board configurations, return the total number of distinct solutions.

都是要用回溯法Backtracking来解，如果理解了之前那道题的思路，此题只要做很小的改动即可，不再需要求出具体的皇后的摆法，只需要每次生成一种解法时，计数器加一即可  


int totalNQueens(int n) {
    int res = 0;
    vector<int> pos(n, -1);
    totalNQueensDFS(pos, 0, res);
    return res;
}

void totalNQueensDFS(vector<int> &pos, int row, int &res) {
    int n = pos.size();
    if (row == n) ++res;
    else {
        for (int col = 0; col < n; ++col) {
            if (isValid(pos, row, col)) {
                pos[row] = col;
                totalNQueensDFS(pos, row + 1, res);
                pos[row] = -1;
            }
        }
    }
}

bool isValid(vector<int> &pos, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (col == pos[i] || abs(row - i) == abs(col - pos[i])) {
            return false;
        }
    }
    return true;
}


53. Maximum Subarray 最大子数组  

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

定义两个变量res和curSum，其中res保存最终要返回的结果，即最大的子数组之和，curSum初始值为0，每遍历一个数字num，比较curSum + num和num中的较大值存入curSum，然后再把res和curSum中的较大值存入res，以此类推直到遍历完整个数组，可得到最大子数组的值存在res中


int maxSubArray(vector<int>& nums) {
    int res = INT_MIN, curSum = 0;
    for (int num : nums) {
        curSum = max(curSum + num, num);
        res = max(res, curSum);
    }
    return res;
}


54. Spiral Matrix I

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
For example,
Given the following matrix:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].

与Rotate Image那题类似，一层一层处理。但这题有两个注意点：
1. m和n可以不同，所以对于第i层来说，最后一行为lastRow = m-1-i，而最后一列为lastCol = n-1-i。所以层数由min(m,n)决定。
2. 当min(m,n)为奇数时，最后一层为一行或一列，需要特殊处理。

vector<int> spiralOrder(vector<vector<int> > &matrix) {

    vector<int> ret;
    if(matrix.empty() || matrix[0].empty()) return ret;
    int m = matrix.size(), n = matrix[0].size();
    int nlvl = (min(m,n)+1)/2;

    for(int i=0; i<nlvl; i++) {
        int lastRow = m-1-i;
        int lastCol = n-1-i;

        if(lastRow==i) {    // one row remain
            for(int j=i; j<=lastCol; j++)
                ret.push_back(matrix[i][j]);
        }
        else if(lastCol==i) {   // one col remain
            for(int j=i; j<=lastRow; j++)
                ret.push_back(matrix[j][i]);
        }   
        else {
            for(int j=i; j<lastCol; j++) 
                ret.push_back(matrix[i][j]);
            for(int j=i; j<lastRow; j++)
                ret.push_back(matrix[j][lastCol]);
            for(int j=lastCol; j>i; j--)
                ret.push_back(matrix[lastRow][j]);
            for(int j=lastRow; j>i; j--)
                ret.push_back(matrix[j][i]);
        }
    }
    return ret;
}


55. Jump Game 跳跃游戏  

Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.
A = [3,2,1,0,4], return false.

其中dp[i]表示走道i位置时剩余的最大步数

这道题说的是有一个非负整数的数组，每个数字表示在当前位置的基础上最多可以走的步数，求判断能不能到达最后一个位置，开始我以为是必须刚好到达最后一个位置，超过了不算，其实是理解题意有误，因为每个位置上的数字表示的是最多可以走的步数而不是像玩大富翁一样摇骰子摇出几一定要走几步。那么我们可以用动态规划Dynamic Programming来解，我们维护一个一位数组dp，其中dp[i]表示走道i位置时剩余的最大步数，那么递推公式为：dp[i] = max(dp[i - 1], A[i - 1]) - 1，如果当某一个时刻dp数组的值为负了，说明无法抵达当前位置，则直接返回false，最后我们判断dp数组最后一位是否为非负数即可知道是否能抵达该位置

bool canJump(int A[], int n) {
    vector<int> dp(n, 0);
    for (int i = 1; i < n; ++i) {
        dp[i] = max(dp[i - 1], A[i - 1]) - 1;

        if (dp[i] < 0) 
            return false;
    }
    return dp[n - 1] >= 0;
}


56. Merge Intervals 合并区间 

Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

这次题目要求我们合并区间，之前那题明确了输入区间集是有序的，而这题没有，所有我们首先要做的就是给区间集排序，由于我们要排序的是个结构体，所以我们要定义自己的comparator，才能用sort来排序，我们以start的值从小到大来排序，排完序我们就可以开始合并了，首先把第一个区间存入结果中，然后从第二个开始遍历区间集，如果结果中最后一个区间和遍历的当前区间无重叠，直接将当前区间存入结果中，如果有重叠，将结果中最后一个区间的end值更新为结果中最后一个区间的end和当前end值之中的较大值，然后继续遍历区间集，以此类推可以得到最终结果


static bool comp(const Interval &a, const Interval &b) {
    return (a.start < b.start);
}

vector<Interval> merge(vector<Interval> &intervals) {
    vector<Interval> res;
    if (intervals.empty()) return res;
    sort(intervals.begin(), intervals.end(), comp);
    res.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); ++i) {
        if (res.back().end >= intervals[i].start) {
            res.back().end = max(res.back().end, intervals[i].end);
        } else {
            res.push_back(intervals[i]);
        }
    }
    return res;
}


57. Insert Interval 插入区间  

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].


这道题让我们在一系列非重叠的区间中插入一个新的区间，可能还需要和原有的区间合并，那么我们需要对给区间集一个一个的遍历比较，那么会有两种情况，重叠或是不重叠，不重叠的情况最好，直接将新区间插入到对应的位置即可，重叠的情况比较复杂，有时候会有多个重叠，我们需要更新新区间的范围以便包含所有重叠，而且最后处理的时候还需要删除原区间集中所有和新区间重叠的区间，然后插入新区间即可。具体思路如下：

- 对区间集中每个区间进行遍历

　　- 如果新区间的末尾小于当前区间的开头，则跳出循环

　　- 如果新区间的开头大于当前区间的末尾，不作处理

　　- 如果新区间和当前区间有重叠，则更新新区间的开头为两者最小值，新区间的末尾为两者最大值，重叠数加一

　　- 指针移向下一个区间

- 如果重叠数大于0，则删除掉所有的重叠区间

- 插入新区间到对应的位置


vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
    vector<Interval> res = intervals;
    int i = 0, overlap = 0, n = res.size();
    while (i < n) {
        if (newInterval.end < res[i].start) break;  
        else if (newInterval.start > res[i].end) {} 
        else {
            newInterval.start = min(newInterval.start, res[i].start);
            newInterval.end = max(newInterval.end, res[i].end);
            ++overlap;
        }
        ++i;
    }
    if (overlap > 0) res.erase(res.begin() + i - overlap, res.begin() + i);
    res.insert(res.begin() + i - overlap, newInterval);
    return res;
}

solution 2: 

vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
    vector<Interval> res = intervals;
    vector<Interval>::iterator it = res.begin();
    int overlap = 0;
    while(it != res.end()) {
        if(newInterval.end < it->start) break;
        else if(newInterval.start > it->end) {}   
        else {
            newInterval.start = min(newInterval.start, it->start);
            newInterval.end   = max(newInterval.end, it->end);
            ++overlap;
        }
        ++it;
    }
    
    if(overlap != 0) it = res.erase(it-overlap, it);
    res.insert(it, newInterval);
    return res;
}


58. Length of Last Word 求末尾单词的长度 

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example, 
Given s = "Hello World",
return 5.

这道题难度不是很大。先对输入字符串做预处理，去掉开头和结尾的空格，然后用一个计数器来累计非空格的字符串的长度，遇到空格则将计数器清零


int lengthOfLastWord(const char *s) {
    int len = strlen(s);
    int left = 0;
    int right = len - 1;
    int count = 0;
    while (s[left] == ' ') ++left;
    while (s[right] == ' ') --right;
    for (int i = left; i <= right; ++i) {
        if (s[i] == ' ') count = 0;
        else ++count;
    }
    return count;
}

59. Spiral Matrix II

II比I简单，一样的按层访问法。由于是正方形矩阵，当n为奇数时，最后只会剩下一个数字即matrix[n/2][n/2]，最后不要忘记补填上这个数字。

vector<vector<int> > generateMatrix(int n) {

    vector<vector<int>> ret(n,vector<int>(n,0));
    int nlvl = n/2;
    int val = 1;
    for(int i=0; i<nlvl; i++) {
        int last = n-1-i;
        for(int j=i; j<last; j++) 
            ret[i][j] = val++;
        for(int j=i; j<last; j++)
            ret[j][last] = val++;
        for(int j=last; j>i; j--)
            ret[last][j] = val++;
        for(int j=last; j>i; j--)
            ret[j][i] = val++;
    }

    if(n % 2 == 1) ret[n/2][n/2] = val;
    return ret;
}


60. Permutation Sequence 序列排序 

DFS 超时

int num = 0;

string getPermutation(int n, int k) {
    if( n <= 0) return "";
    string result;

    vector<bool> flag(n+1, false);
    dfs(n, 0, k, flag, "", result);
    return result;
}

void dfs(int n, int step, int k, vector<bool> &flag, string path, string &result) {
    if( step == n ) {
        num++;
        if( num == k )
            result = path;
        return;
    }
    
    for(int i=1; i <= n; ++i) {
        if( !flag[i] ) {
            flag[i] = true;
            string nextpath(path);
            nextpath.append(1, '0' + i);
            dfs( n, step+1, k, flag, nextpath, result);
            flag[i] = false;
        }
        if( result.size() > 0)
            return;
    }
}

    
61. Rotate List 旋转链表 

Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

solution 1: 
这道旋转链表的题和之前那道 Rotate Array 旋转数组 很类似，但是比那道要难一些，因为链表的值不能通过下表来访问，只能一个一个的走，我刚开始拿到这题首先想到的就是用快慢指针来解，快指针先走k步，然后两个指针一起走，当快指针走到末尾时，慢指针的下一个位置是新的顺序的头结点，这样就可以旋转链表了，自信满满的写完程序，放到OJ上跑，以为能一次通过，结果跪在了各种特殊情况，首先一个就是当原链表为空时，直接返回NULL，还有就是当k大于链表长度和k远远大于链表长度时该如何处理，我们需要首先遍历一遍原链表得到链表长度n，然后k对n取余，这样k肯定小于n


ListNode *rotateRight(ListNode *head, int k) {
    if (!head) return NULL;
    int n = 0;
    ListNode *cur = head;
    while (cur) {
        ++n;
        cur = cur->next;
    }
    k %= n;
    ListNode *fast = head, *slow = head;
    for (int i = 0; i < k; ++i) {
        if (fast) fast = fast->next;
    }
    if (!fast) return head;
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    fast->next = head;
    fast = slow->next;
    slow->next = NULL;
    return fast;
}

solution 2: 
原理是先遍历整个链表获得链表长度n，然后此时把链表头和尾链接起来，在往后走n - k % n个节点就到达新链表的头结点前一个点，这时断开链表即可


ListNode *rotateRight(ListNode *head, int k) {
    if (!head) return NULL;
    int n = 1;
    ListNode *cur = head;
    while (cur->next) {
        ++n;
        cur = cur->next;
    }
    cur->next = head;
    int m = n - k % n;
    for (int i = 0; i < m; ++i) {
        cur = cur->next;
    }
    ListNode *newhead = cur->next;
    cur->next = NULL;
    return newhead;
}


62. Unique Paths 不同的路径

solution 1: 
// 深搜，小集合可以过，大集合会超时
// 时间复杂度O(n^4)，空间复杂度O(n)

int uniquePaths(int m, int n) {
    if (m < 1 || n < 1) return 0; // 终止条件

    if (m == 1 && n == 1) return 1; // 收敛条件

    return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
}


// 深搜 + 缓存，即备忘录法
// 时间复杂度O(n^2)，空间复杂度O(n^2)

solution 2: 

vector<vector<int> > f;  // 缓存

int uniquePaths(int m, int n) {
    // f[x][y] 表示 从(0,0)到(x,y)的路径条数
    f = vector<vector<int> >(m, vector<int>(n, 0));
    f[0][0] = 1;
    return dfs(m - 1, n - 1);
}

int dfs(int x, int y) {
    if (x < 0 || y < 0) return 0; // 数据非法，终止条件

    if (x == 0 && y == 0) return f[0][0]; // 回到起点，收敛条件

    if (f[x][y] > 0) {
        return f[x][y];
    } else {
        return f[x][y] = dfs(x - 1, y) +  dfs(x, y - 1);
    }
}


solution 3:
既然可以用备忘录法自顶向下解决，也一定可以用动规自底向上解决。
设状态为f[i][j]，表示从起点(1,1)到达(i,j)的路线条数，则状态转移方程为：

f[i][j]=f[i-1][j]+f[i][j-1]


// Unique Paths
// 动规，滚动数组
// 时间复杂度O(n^2)，空间复杂度O(n)

int uniquePaths(int m, int n) {
    vector<int> f(n, 0);
    f[0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            // 左边的f[j]，表示更新后的f[j]，与公式中的f[i][j]对应
            // 右边的f[j]，表示老的f[j]，与公式中的f[i-1][j]对应
            f[j] = f[j] + f[j - 1];
        }
    }
    return f[n - 1];
}

63. Unique Paths II 不同的路径之二

Now consider if some obstacles are added to the grids. How many unique paths would there be?
An obstacle and empty space is marked as 1 and 0 respectively in the grid.

There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.
Note: m and n will be at most 100.

在路径中加了一些障碍物，还是用动态规划Dynamic Programming来解，不同的是当遇到为1的点，将该位置的dp数组中的值清零，其余和之前那道题并没有什么区别


solution 1： 
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

    if (obstacleGrid.empty() || obstacleGrid[0].empty() || obstacleGrid[0][0] == 1) return 0;
    vector<vector<int> > dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 0));
    for (int i = 0; i < obstacleGrid.size(); ++i) {
        for (int j = 0; j < obstacleGrid[i].size(); ++j) {
            if (obstacleGrid[i][j] == 1) dp[i][j] = 0;
            else if (i == 0 && j == 0) dp[i][j] = 1;
            else if (i == 0 && j > 0) dp[i][j] = dp[i][j - 1];
            else if (i > 0 && j == 0) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp.back().back();
}


solution 2: 
// 深搜 + 缓存，即备忘录法

vector<vector<int> > f;  // 缓存

int uniquePathsWithObstacles(const vector<vector<int> >& obstacleGrid) {
    const int m = obstacleGrid.size();
    const int n = obstacleGrid[0].size();
    if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) return 0;

    f = vector<vector<int> >(m, vector<int>(n, 0));
    f[0][0] = obstacleGrid[0][0] ? 0 : 1;
    return dfs(obstacleGrid, m - 1, n - 1);
}

// @return 从 (0, 0) 到 (x, y) 的路径总数
int dfs(const vector<vector<int> >& obstacleGrid, int x, int y) {
    if (x < 0 || y < 0) return 0; // 数据非法，终止条件

    // (x,y)是障碍
    if (obstacleGrid[x][y]) return 0;

    if (x == 0 and y == 0) return f[0][0]; // 回到起点，收敛条件

    if (f[x][y] > 0) {
        return f[x][y];
    } else {
        return f[x][y] = dfs(obstacleGrid, x - 1, y) + 
            dfs(obstacleGrid, x, y - 1);
    }
}


64. Minimum Path Sum 最小路径和

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

设状态为f[i][j]，表示从起点(0,0)到达(i,j)的最小路径和，则状态转移方程为：
f[i][j]=min(f[i-1][j], f[i][j-1])+grid[i][j]


solution 1: DFS
vector<vector<int> > f;  // 缓存

int minPathSum(vector<vector<int> > &grid) {
    const int m = grid.size();
    const int n = grid[0].size();
    this->f = vector<vector<int> >(m, vector<int>(n, -1));
    return dfs(grid, m-1, n-1);
}

int dfs(const vector<vector<int> > &grid, int x, int y) {
    if (x < 0 || y < 0) return INT_MAX; // 越界，终止条件，注意，不是0

    if (x == 0 && y == 0) return grid[0][0]; // 回到起点，收敛条件

    return min(getOrUpdate(grid, x - 1, y),
            getOrUpdate(grid, x, y - 1)) + grid[x][y];
}

int getOrUpdate(const vector<vector<int> > &grid, int x, int y) {
    if (x < 0 || y < 0) return INT_MAX; // 越界，注意，不是0
    if (f[x][y] >= 0) return f[x][y];
    else return f[x][y] = dfs(grid, x, y);
}


solution 2: DP 

int minPathSum(vector<vector<int> > &grid) {
    if (grid.size() == 0) return 0;
    const int m = grid.size();
    const int n = grid[0].size();

    int f[m][n];
    f[0][0] = grid[0][0];

    for (int i = 1; i < m; i++) {
        f[i][0] = f[i - 1][0] + grid[i][0];
    }

    for (int i = 1; i < n; i++) {
        f[0][i] = f[0][i - 1] + grid[0][i];
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            f[i][j] = min(f[i - 1][j], f[i][j - 1]) + grid[i][j];
        }
    }
    return f[m - 1][n - 1];
}


65. Valid Number 验证数字 

Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.

只要设计好Finite Automata Machine之后，写程序就可以很优雅，很简单了。
但是，问题是要构造一个Finite Automata也是十分麻烦的事情，我画了一张A4纸，像蜘蛛网一样的，故此就不贴出来了，也搞了一两个小时，要多练练automata才能快起来吧

注释一下本题分多少状态吧：
0初始无输入或者只有space的状态
1输入了数字之后的状态
2前面无数字，只输入了Dot的状态
3输入了符号状态
4前面有数字和有dot的状态
5'e' or 'E'输入后的状态
6输入e之后输入Sign的状态
7输入e后输入数字的状态
8前面有有效数输入之后，输入space的状态
共9种状态了，难设计的是6,7,8状态。
分好之后就好办了，设计出根据输入进行状态转换就OK了。

这里的输入可以分：
INVALID,  // 0 Include: Alphas, '(', '&' ans so on
SPACE,  // 1
SIGN, // 2 '+','-'
DIGIT,  // 3 numbers
DOT, // 4 '.'
EXPONENT,  // 5 'e' 'E'
然后就是画蜘蛛网吧，什么状态可以转换到什么状态的。

bool isNumber(const char *s) {
        enum InputType {
            INVALID,        // 0 Include: Alphas, '(', '&' ans so on
            SPACE,      // 1
            SIGN,       // 2 '+','-'
            DIGIT,      // 3 numbers
            DOT,            // 4 '.'
            EXPONENT,       // 5 'e' 'E'
        };
        int transTable[][6] = {
        //0INVA,1SPA,2SIG,3DI,4DO,5E
            -1,  0,  3,  1,  2, -1,//0初始无输入或者只有space的状态
            -1,  8, -1,  1,  4,  5,//1输入了数字之后的状态
            -1, -1, -1,  4, -1, -1,//2前面无数字，只输入了Dot的状态
            -1, -1, -1,  1,  2, -1,//3输入了符号状态
            -1,  8, -1,  4, -1,  5,//4前面有数字和有dot的状态
            -1, -1,  6,  7, -1, -1,//5'e' or 'E'输入后的状态
            -1, -1, -1,  7, -1, -1,//6输入e之后输入Sign的状态
            -1,  8, -1,  7, -1, -1,//7输入e后输入数字的状态
            -1,  8, -1, -1, -1, -1,//8前面有有效数输入之后，输入space的状态
        };
        int state = 0;
        while (*s)
        {
            InputType input = INVALID;
            if (*s == ' ') input = SPACE;
            else if (*s == '+' || *s == '-') input = SIGN;
            else if (isdigit(*s)) input = DIGIT;
            else if (*s == '.') input = DOT;
            else if (*s == 'e' || *s == 'E') input = EXPONENT;
            state = transTable[state][input];
            if (state == -1) return false;
            ++s;
        }
        return state == 1 || state == 4 || state == 7 || state == 8;
    }



66. Plus One 加一运算

Given a non-negative number represented as an array of digits, plus one to the number.
The digits are stored such that the most significant digit is at the head of the list.

将一个数字的每个位上的数字分别存到一个一维向量中，最高位在最开头，我们需要给这个数字加一，即在末尾数字加一，如果末尾数字是9，那么则会有进位问题，而如果前面位上的数字仍为9，则需要继续向前进位。具体算法如下：首先判断最后一位是否为9，若不是，直接加一返回，若是，则该位赋0，再继续查前一位，同样的方法，知道查完第一位。如果第一位原本为9，加一后会产生新的一位，那么最后要做的是，查运算完的第一位是否为0，如果是，则在最前头加一个1. 

vector<int> plusOne(vector<int> &digits) {

    int n = digits.size();
    for (int i = n - 1; i >= 0; --i) {
        if (digits[i] == 9) digits[i] = 0;
        else {
            digits[i] += 1;
            return digits;
        }
    }

    if (digits.front() == 0) 
        digits.insert(digits.begin(), 1);
    return digits;
}

solution 2: 
我们也可以使用跟之前那道Add Binary类似的做法，我们将carry初始化为1，然后相当于digits加了一个0，处理方法跟之前那道题一样

vector<int> plusOne(vector<int>& digits) {

    if (digits.empty()) return digits;
    int carry = 1, n = digits.size();

    for (int i = n - 1; i >= 0; --i) {
        if (carry == 0) return digits;
        int sum = digits[i] + carry;
        digits[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry == 1) digits.insert(digits.begin(), 1);
    return digits;
}


67. Add Binary 二进制数相加

Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".

下面这种写法又巧妙又简洁，用了两个指针分别指向a和b的末尾，然后每次取出一个字符，转为数字，若无法取出字符则按0处理，然后定义进位carry，初始化为0，将三者加起来，对2取余即为当前位的数字，对2取商即为当前进位的值，记得最后还要判断下carry，如果为1的话，要在结果最前面加上一个1. 

string addBinary(string a, string b) {

    string res = "";
    int m = a.size() - 1, n = b.size() - 1, carry = 0;

    while (m >= 0 || n >= 0) {
        int p = m >= 0 ? a[m--] - '0' : 0;
        int q = n >= 0 ? b[n--] - '0' : 0;
        int sum = p + q + carry;
        res = to_string(sum % 2) + res;
        carry = sum / 2;
    }

    return carry == 1 ? "1" + res : res;
}


68. Text Justification 文本左右对齐 

Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly Lcharacters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.



69. Sqrt(x) 求平方根 

Implement int sqrt(int x).
Compute and return the square root of x.

这道题要求我们求平方根，我们能想到的方法就是算一个候选值的平方，然后和x比较大小，为了缩短查找时间，我们采用二分搜索法来找平方根，由于求平方的结果会很大，可能会超过int的取值范围，所以我们都用long long来定义变量，这样就不会越界.

int sqrt(int x) {

    long long left = 0, right = (x / 2) + 1; // long long 避免会溢出; right多加1是corner case: 1 
    while (left <= right) {
        long long mid = (left + right) / 2;
        long long sq = mid * mid;
        if (sq == x) return mid;
        else if (sq < x) left = mid + 1;
        else right = mid - 1;
    }

    return right;
}

70. Climbing Stairs 爬梯子问题

这个爬梯子问题最开始看的时候没搞懂是让干啥的，后来看了别人的分析后，才知道实际上跟斐波那契数列非常相似，假设梯子有n层，那么如何爬到第n层呢，因为每次只能怕1或2步，那么爬到第n层的方法要么是从第n-1层一步上来的，要不就是从n-2层2步上来的，所以递推公式非常容易的就得出了：dp[n] = dp[n-1] + dp[n-2]。 由于斐波那契额数列的求解可以用递归，所以我最先尝试了递归，拿到OJ上运行，显示Time Limit Exceeded，就是说运行时间超了，因为递归计算了很多分支，效率很低，这里需要用动态规划 (Dynamic Programming) 来提高效率

int climbStairs(int n) {
    if (n <= 1) return 1;

    vector<int> dp(n);
    dp[0] = 1; dp[1] = 2;

    for (int i = 2; i < n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp.back();
}


71. Simplify Path 简化路径

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

这道题让简化给定的路径，光根据题目中给的那一个例子还真不太好总结出规律，应该再加上两个例子 path = "/a/./b/../c/", => "/a/c"和path = "/a/./b/c/", => "/a/b/c"， 这样我们就可以知道中间是"."的情况直接去掉，是".."时删掉它上面挨着的一个路径，而下面的边界条件给的一些情况中可以得知，如果是空的话返回"/"，如果有多个"/"只保留一个。那么我们可以把路径看做是由一个或多个"/"分割开的众多子字符串，把它们分别提取出来一一处理即可


string simplifyPath(string path) {

    vector<string> v;
    int i = 0;

    while (i < path.size()) {
        while (path[i] == '/' && i < path.size()) ++i;
        if (i == path.size()) break;
        int start = i;
        while (path[i] != '/' && i < path.size()) ++i;
        int end = i - 1;
        string s = path.substr(start, end - start + 1);
        if (s == "..") {
            if (!v.empty()) v.pop_back(); 
        } else if (s != ".") {
            v.push_back(s);
        }
    }

    if (v.empty()) return "/";
    string res;

    for (int i = 0; i < v.size(); ++i) {
        res += '/' + v[i];
    }
    return res;
}


72. Edit Distance 编辑距离 

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:
a) Insert a character
b) Delete a character
c) Replace a character


设状态为f[i][j]，表示A[0,i]和B[0,j]之间的最小编辑距离。设A[0,i]的形式是str1c，B[0,j]的形式是str2d，
1. 如果c==d，则f[i][j]=f[i-1][j-1]；
2. 如果c!=d，
    i.   如果将c替换成d，则f[i][j]=f[i-1][j-1]+1；
    ii.  如果在c后面添加一个d，则f[i][j]=f[i][j-1]+1；
    iii. 如果将c删除，则f[i][j]=f[i-1][j]+1；

int minDistance(const string &word1, const string &word2) {

    const size_t n = word1.size();
    const size_t m = word2.size();
    // 长度为n的字符串，有n+1个隔板
    int f[n + 1][m + 1];
    for (size_t i = 0; i <= n; i++)
        f[i][0] = i;

    for (size_t j = 0; j <= m; j++)
        f[0][j] = j;

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            if (word1[i - 1] == word2[j - 1])
                f[i][j] = f[i - 1][j - 1];
            else {
                int mn = min(f[i - 1][j], f[i][j - 1]);
                f[i][j] = 1 + min(f[i - 1][j - 1], mn);
            }
        }
    }
    return f[n][m];
}


73. Set Matrix Zeroes 矩阵赋零 
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

click to show follow up.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?

这道题的要求是用O(1)的空间，那么我们就不能新建数组，我们考虑就用原数组的第一行第一列来记录各行各列是否有0.

- 先扫描第一行第一列，如果有0，则将各自的flag设置为true
- 然后扫描除去第一行第一列的整个数组，如果有0，则将对应的第一行和第一列的数字赋0
- 再次遍历除去第一行第一列的整个数组，如果对应的第一行和第一列的数字有一个为0，则将当前值赋0
- 最后根据第一行第一列的flag来更新第一行第一列


 void setZeroes(vector<vector<int> > &matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        int m = matrix.size(), n = matrix[0].size();
        bool rowZero = false, colZero = false;
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) colZero = true;
        }
        for (int i = 0; i < n; ++i) {
            if (matrix[0][i] == 0) rowZero = true;
        } 
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[0][j] == 0 || matrix[i][0] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (rowZero) {
            for (int i = 0; i < n; ++i) matrix[0][i] = 0;
        }
        if (colZero) {
            for (int i = 0; i < m; ++i) matrix[i][0] = 0;
        }
    }


74. Search a 2D Matrix 搜索一个二维矩阵 

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row. 

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.

如果我们按S型遍历该二维数组，可以得到一个有序的一维数组，那么我们只需要用一次二分查找法，而关键就在于坐标的转换，如何把二维坐标和一维坐标转换是关键点，把一个长度为n的一维数组转化为m*n的二维数组(m*n = n)后，那么原一维数组中下标为i的元素将出现在二维数组中的[i/n][i%n]的位置

bool searchMatrix(const vector<vector<int>>& matrix, int target) {

    if (matrix.empty()) return false;
    const size_t  m = matrix.size();
    const size_t n = matrix.front().size();

    int first = 0;
    int last = m * n;

    while (first < last) {
        int mid = first + (last - first) / 2;
        int value = matrix[mid / n][mid % n];  // 记住 

        if (value == target)
            return true;
        else if (value < target)
            first = mid + 1;
        else
            last = mid;
    }

    return false;
}

75. Sort Colors 颜色排序

Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
Note:
You are not suppose to use the library sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?

two pass algorithm 
- 首先遍历一遍原数组，分别记录0,1,2的个数
- 然后更新原数组，按个数分别赋上0，1，2

solution 1: 
void sortColors(int A[], int n) {
    int count[3] = {0}, idx = 0;
    for (int i = 0; i < n; ++i) ++count[A[i]];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            A[idx++] = i;
        }
    }
}

solution 2: 
void sortColors(int A[], int n) {int red = 0, blue = n - 1;
    for (int i = 0; i <= blue; ++i) {
        if (A[i] == 0) {
            swap(A[i], A[red++]);
        } else if (A[i] == 2) {
            swap(A[i--], A[blue--]);
        } 
    }
}


76. Minimum Window Substring 最小窗口子串 

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
For example,
S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the emtpy string "".
If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.


这道题的要求是要在O(n)的时间度里实现找到这个最小窗口字串，那么暴力搜索Brute Force肯定是不能用的，我们可以考虑哈希表，其中key是T中的字符，value是该字符出现的次数。

- 我们最开始先扫描一遍T，把对应的字符及其出现的次数存到哈希表中。
- 然后开始遍历S，遇到T中的字符，就把对应的哈希表中的value减一，直到包含了T中的所有的字符，纪录一个字串并更新最小字串值。
- 将子窗口的左边界向右移，略掉不在T中的字符，如果某个在T中的字符出现的次数大于哈希表中的value，则也可以跳过该字符。


string minWindow(string S, string T) {
    if (T.size() > S.size()) return "";
    string res = "";
    int left = 0, count = 0, minLen = S.size() + 1;
    unordered_map<char, int> m;

    for (int i = 0; i < T.size(); ++i) {
        if (m.find(T[i]) != m.end()) ++m[T[i]];
        else m[T[i]] = 1;
    }

    for (int right = 0; right < S.size(); ++right) {

        if (m.find(S[right]) != m.end()) {
            --m[S[right]];
            if (m[S[right]] >= 0) ++count;
            while (count == T.size()) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    res = S.substr(left, minLen);
                }
                if (m.find(S[left]) != m.end()) {
                    ++m[S[left]];
                    if (m[S[left]] > 0) --count;
                }
                ++left;
            }
        }
    }
    return res;
}


77. Combinations 组合项 

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

DFS: 
vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> out;
        helper(n, k, 1, out, res);
        return res;
    }
    void helper(int n, int k, int level, vector<int>& out, vector<vector<int>>& res) {
        if (out.size() == k) res.push_back(out);
        for (int i = level; i <= n; ++i) {
            out.push_back(i);
            helper(n, k, i + 1, out, res);
            out.pop_back();
        }
    }


iterative:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> out(k, 0);
        int i = 0;
        while (i >= 0) {
            ++out[i];
            if (out[i] > n) --i;
            else if (i == k - 1) res.push_back(out);
            else {
                ++i;
                out[i] = out[i - 1];
            }
        }
        return res;
    }



78. Subsets 子集合 

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

比如对于题目中给的例子[1,2,3]来说，最开始是空集，那么我们现在要处理1，就在空集上加1，为[1]，现在我们有两个自己[]和[1]，下面我们来处理2，我们在之前的子集基础上，每个都加个2，可以分别得到[2]，[1, 2]，那么现在所有的子集合为[], [1], [2], [1, 2]，同理处理3的情况可得[3], [1, 3], [2, 3], [1, 2, 3], 再加上之前的子集就是所有的子集合了

vector<vector<int> > subsets(vector<int> &S) {

    vector<vector<int> > res(1);
    sort(S.begin(), S.end());
    for (int i = 0; i < S.size(); ++i) {
        int size = res.size();
        for (int j = 0; j < size; ++j) {
            res.push_back(res[j]);
            res.back().push_back(S[i]);
        }
    }
    return res;
}


solution 2: 每个元素，都有两种选择，选或者不选 
// Subsets
// 增量构造法，深搜，时间复杂度O(2^n)，空间复杂度O(n)

    vector<vector<int> > subsets(vector<int> &S) {
        sort(S.begin(), S.end());  // 输出要求有序
        vector<vector<int> > result;
        vector<int> path;
        subsets(S, path, 0, result);
        return result;
    }

    static void subsets(const vector<int> &S, vector<int> &path, int step,
            vector<vector<int> > &result) {
        if (step == S.size()) {
            result.push_back(path);
            return;
        }
        // 不选S[step]
        subsets(S, path, step + 1, result);
        // 选S[step]
        path.push_back(S[step]);
        subsets(S, path, step + 1, result);
        path.pop_back();
    }


79. Word Search 词语搜索 

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

这道题是典型的深度优先遍历DFS的应用，原二维数组就像是一个迷宫，可以上下左右四个方向行走，我们以二维数组中每一个数都作为起点和给定字符串做匹配，我们还需要一个和原数组等大小的visited数组，是bool型的，用来记录当前位置是否已经被访问过，因为题目要求一个cell只能被访问一次。如果二维数组board的当前字符和目标字符串word对应的字符相等，则对其上下左右四个邻字符分别调用DFS的递归函数，只要有一个返回true，那么就表示可以找到对应的字符串，否则就不能找到


bool exist(vector<vector<char> > &board, string word) {
    if (word.empty()) return true;
    if (board.empty() || board[0].empty()) return false;
    vector<vector<bool> > visited(board.size(), vector<bool>(board[0].size(), false));
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (search(board, word, 0, i, j, visited)) return true;
        }
    }
    return false;
}


bool search(vector<vector<char> > &board, string word, int idx, int i, int j, vector<vector<bool> > &visited) {
    if (idx == word.size()) return true;
    if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || visited[i][j] || board[i][j] != word[idx]) return false;
    visited[i][j] = true;
    bool res = search(board, word, idx + 1, i - 1, j, visited) 
             || search(board, word, idx + 1, i + 1, j, visited)
             || search(board, word, idx + 1, i, j - 1, visited)
             || search(board, word, idx + 1, i, j + 1, visited);
    visited[i][j] = false;
    return res;
}


80. Remove Duplicates from Sorted Array II 有序数组中去除重复项之二  

加一个变量记录一下元素出现的次数即可。这题因为是已经排序的数组，所以一个变量即可解决。如果是没有排序的数组，则需要引入一个hashmap来记录出现次数。

// Remove Duplicates from Sorted Array II
// Time complexity: O(n), Space Complexity: O(1)
// 将index = 2改为index = 3，就变成了允许重复最多3次。

int removeDuplicates(vector<int>& nums) {
    if (nums.size() <= 2) return nums.size();

    int index = 2;
    for (int i = 2; i < nums.size(); i++){
        if (nums[i] != nums[index - 2])
            nums[index++] = nums[i];
    }

    return index;
}



81. Search in Rotated Sorted Array II 在旋转有序数组中搜索之二 

Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?
Would this affect the run-time complexity? How and why?
Write a function to determine if a given target is in the array.


这道是之前那道 Search in Rotated Sorted Array 在旋转有序数组中搜索 的延伸，现在数组中允许出现重复数字，这个也会影响我们选择哪半边继续搜索，由于之前那道题不存在相同值，我们在比较中间值和最右值时就完全符合之前所说的规律：如果中间的数小于最右边的数，则右半段是有序的，若中间数大于最右边数，则左半段是有序的。而如果可以有重复值，就会出现来面两种情况，[3 1 1] 和 [1 1 3 1]，对于这两种情况中间值等于最右值时，目标值3既可以在左边又可以在右边，那怎么办么，对于这种情况其实处理非常简单，只要把最右值向左一位即可继续循环，如果还相同则继续移，直到移到不同值为止

 bool search(int A[], int n, int target) {
        if (n == 0) return false;
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (A[mid] == target) return true;
            else if (A[mid] < A[right]) {
                if (A[mid] < target && A[right] >= target) left = mid + 1;
                else right = mid - 1;
            } else if (A[mid] > A[right]){
                if (A[left] <= target && A[mid] > target) right = mid - 1;
                else left = mid + 1;
            } else --right;
        }
        return false;
    }



82. Remove Duplicates from Sorted List II 移除有序链表中的重复项之二

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

由于链表开头可能会有重复项，被删掉的话头指针会改变，而最终却还需要返回链表的头指针。所以需要定义一个新的节点，然后链上原链表，然后定义一个前驱指针和一个现指针，每当前驱指针指向新建的节点，现指针从下一个位置开始往下遍历，遇到相同的则继续往下，直到遇到不同项时，把前驱指针的next指向下面那个不同的元素。如果现指针遍历的第一个元素就不相同，则把前驱指针向下移一位. 


ListNode *deleteDuplicates(ListNode *head) {

    if (!head || !head->next) return head;
    
    ListNode *start = new ListNode(0);
    start->next = head;
    ListNode *pre = start;

    while (pre->next) {
        ListNode *cur = pre->next;
        while (cur->next && cur->next->val == cur->val) cur = cur->next;
        if (cur != pre->next) pre->next = cur->next;
        else pre = pre->next;
    }

    return start->next;
}


83. Remove Duplicates from Sorted List 移除有序链表中的重复项 

Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.

移除有序链表中的重复项需要定义个指针指向该链表的第一个元素，然后第一个元素和第二个元素比较，如果重复了，则删掉第二个元素，如果不重复，指针指向第二个元素。这样遍历完整个链表，则剩下的元素没有重复项。

ListNode *deleteDuplicates(ListNode *head) {
    if (!head || !head->next) return head;
    
    ListNode *start = head;

    while (start && start->next) {
        if (start->val == start->next->val) {
            ListNode *tmp = start->next;
            start->next = start->next->next;
            delete tmp;
        } else start = start->next;
    }

    return head;
}


84. Largest Rectangle in Histogram 直方图中最大的矩形 

就是遍历数组，每找到一个局部峰值，然后向前遍历所有的值，算出共同的矩形面积，每次对比保留最大值，

int largestRectangleArea(vector<int> &height) {
    int res = 0;
    for (int i = 0; i < height.size(); ++i) {
        if (i + 1 < height.size() && height[i] <= height[i + 1]) {
            continue;
        }
        int minH = height[i];
        for (int j = i; j >= 0; --j) {
            minH = min(minH, height[j]);
            int area = minH * (i - j + 1);
            res = max(res, area);
        }
    }
    return res;
}


85. Maximal Rectangle 最大矩形  

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area. 

此题是之前那道的 Largest Rectangle in Histogram 直方图中最大的矩形 的扩展，这道题的二维矩阵每一层向上都可以看做一个直方图，输入矩阵有多少行，就可以形成多少个直方图，对每个直方图都调用 Largest Rectangle in Histogram 直方图中最大的矩形 中的方法，就可以得到最大的矩形面积


int maximalRectangle(vector<vector<char> > &matrix) {
    int res = 0;
    vector<int> height;

    for (int i = 0; i < matrix.size(); ++i) {
        height.resize(matrix[i].size());
        for (int j = 0; j < matrix[i].size(); ++j) {
            height[j] = matrix[i][j] == '0' ? 0 : (1 + height[j]);
        }
        res = max(res, largestRectangleArea(height));
    }
    return res;
}

int largestRectangleArea(vector<int> &height) {
    int res = 0;
    for (int i = 0; i < height.size(); ++i) {
        if (i + 1 < height.size() && height[i] <= height[i + 1]) {
            continue;
        }
        int minH = height[i];
        for (int j = i; j >= 0; --j) {
            minH = min(minH, height[j]);
            int area = minH * (i - j + 1);
            res = max(res, area);
        }
    }
    return res;
}


86. Partition List 划分链表 

Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.


solution 1: 
这道题要求我们划分链表，把所有小于给定值的节点都移到前面，大于该值的节点顺序不变，相当于一个局部排序的问题。那么可以想到的一种解法是首先找到第一个大于或等于给定值的节点，用题目中给的例子来说就是先找到4，然后再找小于3的值，每找到一个就将其取出置于4之前即可. 

ListNode *partition(ListNode *head, int x) {

    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *pre = dummy, *cur = head;;

    while (pre->next && pre->next->val < x) pre = pre->next;
    cur = pre;
    while (cur->next) {
        if (cur->next->val < x) {
            ListNode *tmp = cur->next;
            cur->next = tmp->next;
            tmp->next = pre->next;
            pre->next = tmp;
            pre = pre->next;
        } else {
            cur = cur->next;
        }
    }
    return dummy->next;
}


solution 2: 
就是将所有小于给定值的节点取出组成一个新的链表，此时原链表中剩余的节点的值都大于或等于给定值，只要将原链表直接接在新链表后即可

ListNode *partition(ListNode *head, int x) {

    if (!head) return head;
    ListNode *dummy = new ListNode(-1);
    ListNode *newDummy = new ListNode(-1);
    dummy->next = head;
    ListNode *cur = dummy, *p = newDummy;

    while (cur->next) {
        if (cur->next->val < x) {
            p->next = cur->next;
            p = p->next;
            cur->next = cur->next->next;
            p->next = NULL;
        } else {
            cur = cur->next;
        }
    }
    p->next = dummy->next;
    return newDummy->next;
}


87. Scramble String 爬行字符串  

Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string"rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string"rgtae".

简单的说，就是s1和s2是scramble的话，那么必然存在一个在s1上的长度l1，将s1分成s11和s12两段，同样有s21和s22.那么要么s11和s21是scramble的并且s12和s22是scramble的；要么s11和s22是scramble的并且s12和s21是scramble的。

bool isScramble(string s1, string s2) {

    if (s1.size() != s2.size()) return false;
    if (s1 == s2) return true;
    string str1 = s1, str2 = s2;
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    if (str1 != str2) return false;

    for (int i = 1; i < s1.size(); ++i) {
        string s11 = s1.substr(0, i);
        string s12 = s1.substr(i);
        string s21 = s2.substr(0, i);
        string s22 = s2.substr(i);
        if (isScramble(s11, s21) && isScramble(s12, s22)) return true;
        s21 = s2.substr(s1.size() - i);
        s22 = s2.substr(0, s1.size() - i);
        if (isScramble(s11, s21) && isScramble(s12, s22)) return true;
    }
    return false;
}

首先想到的是递归（即深搜），对两个string进行分割，然后比较四对字符串。代码虽然简单，但是复杂度比较高。有两种加速策略，一种是剪枝，提前返回；一种是加缓存，缓存中间结果，即memorization（翻译为记忆化搜索）。
剪枝可以五花八门，要充分观察，充分利用信息，找到能让节点提前返回的条件。例如，判断两个字符串是否互为scamble，至少要求每个字符在两个字符串中出现的次数要相等，如果不相等则返回false。
加缓存，可以用数组或HashMap。本题维数较高，用HashMap，map和unordered_map均可。
既然可以用记忆化搜索，这题也一定可以用动规。设状态为f[n][i][j]，表示长度为n，起点为s1[i]和起点为s2[j]两个字符串是否互为scramble，则状态转移方程为

f[n][i][j]} =  (f[k][i][j] && f[n-k][i+k][j+k]) 
            || (f[k][i][j+n-k] && f[n-k][i+k][j])


根字符串有关的题十有八九可以用DP来做，那么难点就在于如何找出递推公式


88. Merge Sorted Array 混合插入有序数组  

由于合并后A数组的大小必定是m+n，所以从最后面开始往前赋值，先比较A和B中最后一个元素的大小，把较大的那个插入到m+n-1的位置上，再依次向前推。如果A中所有的元素都比B小，那么前m个还是A原来的内容，没有改变。如果A中的数组比B大的，当A循环完了，B中还有元素没加入A，直接用个循环把B中所有的元素覆盖到A剩下的位置

void merge(int A[], int m, int B[], int n) {

    int count = m + n - 1;
    --m; --n;
    while (m >= 0 && n >= 0) A[count--] = A[m] > B[n] ? A[m--] : B[n--];
    while (n >= 0) A[count--] = B[n--];
}


89. Gray Code 格雷码 

The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note:

For a given n, a gray code sequence is not uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.
For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.

镜面排列: n位元的格雷码可以从n-1位元的格雷码以上下镜射后加上新位元的方式快速的得到, 代码思路和(78. Subsets)很像 


vector<int> grayCode(int n) {

    vector<int> res{0};
    for (int i = 0; i < n; ++i) {
        int size = res.size();
        for (int j = size - 1; j >= 0; --j) {
            res.push_back(res[j] | (1 << i));   // 1 << 0 == 01; 1 << 1 == 10; 1 << 2 == 100
        }
    }
    return res;
}

90. Subsets II 子集合之二

Given a collection of integers that might contain duplicates, S, return all possible subsets.

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

recursion : 
代码只需在原有的基础上增加一句话，while (S[i] == S[i + 1]) ++i; 这句话的作用是跳过树中为X的叶节点，因为它们是重复的子集，应被抛弃

    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > res;
        vector<int> out;
        sort(S.begin(), S.end());
        getSubsets(S, 0, out, res);
        return res;
    }

    void getSubsets(vector<int> &S, int pos, vector<int> &out, vector<vector<int> > &res) {
        res.push_back(out);
        for (int i = pos; i < S.size(); ++i) {
            out.push_back(S[i]);
            getSubsets(S, i + 1, out, res);
            out.pop_back();
            while (S[i] == S[i + 1]) ++i;
        }
    }

iterative: 
我们先来看非递归解法，拿题目中的例子[1 2 2]来分析，根据之前 Subsets 子集合 里的分析可知，当处理到第一个2时，此时的子集合为[], [1], [2], [1, 2]，而这时再处理第二个2时，如果在[]和[1]后直接加2会产生重复，所以只能在上一个循环生成的后两个子集合后面加2，发现了这一点，题目就可以做了，我们用last来记录上一个处理的数字，然后判定当前的数字和上面的是否相同，若不同，则循环还是从0到当前子集的个数，若相同，则新子集个数减去之前循环时子集的个数当做起点来循环，这样就不会产生重复 

vector<vector<int> > subsetsWithDup(vector<int> &S) {
    vector<vector<int> > res(1);  // one empty element, 即 {}
    sort(S.begin(), S.end());
    int size = 1, last = S[0];
    for (int i = 0; i < S.size(); ++i) {
        if (last != S[i]) {
            last = S[i];
            size = res.size();
        }

        int newSize = res.size();
        for (int j = newSize - size; j < newSize; ++j) {
            res.push_back(res[j]);
            res.back().push_back(S[i]);
        }
    }
    return res;
}



91. Decode Ways 解码方法

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
The number of ways decoding "12" is 2.

比如说一位数时不能为0，两位数不能大于26，其十位上的数也不能为0，出去这些限制条件，根爬梯子基本没啥区别，也勉强算特殊的斐波那契数列，当然需要用动态规划Dynamci Programming来解。建立一位dp数组，长度比输入数组长多多2，全部初始化为1，因为斐波那契数列的前两项也为1，然后从第三个数开始更新，对应数组的第一个数。对每个数组首先判断其是否为0，若是将改为dp赋0，若不是，赋上一个dp值，此时相当如加上了dp[i - 1], 然后看数组前一位是否存在，如果存在且满足前一位不是0，且和当前为一起组成的两位数不大于26，则当前dp值加上dp[i - 2], 至此可以看出来跟斐波那契数组的递推式一样

dp[i] 表示长度为i-1的string的decoding ways 

int numDecodings(string s) {
        if (s.empty() || (s.size() > 1 && s[0] == '0')) return 0;
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        for (int i = 1; i < dp.size(); ++i) {
            dp[i] = (s[i - 1] == '0') ? 0 : dp[i - 1];  // 一位数时不能为0
            if (i > 1 && (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6'))) {
                dp[i] += dp[i - 2];  // 起始就是: dp[i] = dp[i-1] + dp[i-2]
            }
        }
        return dp.back();
    }


92. Reverse Linked List II 倒置链表之二 

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.

对于链表的问题，根据以往的经验一般都是要建一个dummy node，连上原链表的头结点，这样的话就算头结点变动了，我们还可以通过dummy->next来获得新链表的头结点。这道题的要求是只通过一次遍历完成

// Reverse Linked List II
// 迭代版，时间复杂度O(n)，空间复杂度O(1)
ListNode *reverseBetween(ListNode *head, int m, int n) {

    ListNode *dummy = new ListNode(-1);
    dummy.next = head;

    ListNode *prev = dummy;
    for (int i = 0; i < m-1; ++i)
        prev = prev->next;
    ListNode* const head2 = prev;

    prev = head2->next;
    ListNode *cur = prev->next;
    for (int i = m; i < n; ++i) {
        prev->next = cur->next;
        cur->next = head2->next;
        head2->next = cur;  // 头插法
        cur = prev->next;
    }

    return dummy->next;
}


93. Restore IP Addresses 复原IP地址              

一是只要遇到字符串的子序列或配准问题首先考虑动态规划DP，二是只要遇到需要求出所有可能情况首先考虑用递归

IP地址由32位二进制数组成，为便于使用，常以XXX.XXX.XXX.XXX形式表现，每组XXX代表小于或等于255的10进制数。所以说IP地址总共有四段，每一段可能有一位，两位或者三位，范围是[0, 255]，题目明确指出输入字符串只含有数字，所以当某段是三位时，我们要判断其是否越界（>255)，还有一点很重要的是，当只有一位时，0可以成某一段，如果有两位或三位时，像 00， 01， 001， 011， 000等都是不合法. 这道题其实也可以看做是字符串的分段问题，在输入字符串中加入三个点，将字符串分为四段，每一段必须合法，求所有可能的情况. 


必须要走到底部才能判断解是否合法，深搜。
// Restore IP Addresses
// 时间复杂度O(n^4)，空间复杂度O(n)
vector<string> restoreIpAddresses(const string& s) {
    vector<string> result;
    vector<string> ip; // 存放中间结果
    dfs(s, ip, result, 0);
    return result;
}

/**
 * @brief 解析字符串
 * @param[in] s 字符串，输入数据
 * @param[out] ip 存放中间结果
 * @param[out] result 存放所有可能的IP地址
 * @param[in] start 当前正在处理的 index
 * @return 无
 */
void dfs(string s, vector<string>& ip, vector<string> &result,
        size_t start) {
    if (ip.size() == 4 && start == s.size()) {  // 找到一个合法解
        result.push_back(ip[0] + '.' + ip[1] + '.' + ip[2] + '.' + ip[3]);
        return;
    }

    if (s.size() - start > (4 - ip.size()) * 3)
        return;  // 剪枝
    if (s.size() - start < (4 - ip.size()))
        return;  // 剪枝

    int num = 0;
    for (size_t i = start; i < start + 3 && i < s.size(); i++) {
        num = num * 10 + (s[i] - '0');

        if (num < 0 || num > 255) continue;  // 剪枝

        ip.push_back(s.substr(start, i - start + 1));
        dfs(s, ip, result, i + 1);
        ip.pop_back();

        if (num == 0) break;  // 不允许前缀0，但允许单个0
    }
}


94. Binary Tree Inorder Traversal 二叉树的中序遍历  

Given a binary tree, return the inorder traversal of its nodes values.  

recursion: 
vector<int> inorderTraversal(TreeNode *root) {
    vector<int> res;
    inorder(root, res);
    return res;
}

void inorder(TreeNode *root, vector<int> &res) {
    if (!root) return;
    if (root->left) inorder(root->left, res);
    res.push_back(root->val);
    if (root->right) inorder(root->right, res);
}

iterative: 
需要用栈来做，思路是从根节点开始，先将根节点压入栈，然后再将其所有左子结点压入栈，然后取出栈顶节点，保存节点值，再将当前指针移到其右子节点上，若存在右子节点，则在下次循环时又可将其所有左子结点压入栈中
// 使用栈，时间复杂度O(n)，空间复杂度O(n)
vector<int> inorderTraversal(TreeNode *root) {

    vector<int> res;
    stack<TreeNode*> s;
    TreeNode *p = root;

    while (p || !s.empty()) {
        while (p) {
            s.push(p);
            p = p->left;
        }
        p = s.top();
        s.pop();
        res.push_back(p->val);
        p = p->right;
    }

    return res;
}


// Morris中序遍历，时间复杂度O(n)，空间复杂度O(1)
vector inorderTraversal(TreeNode *root) {
        vector result;
        TreeNode *cur = root, *prev = nullptr;

        while (cur != nullptr) {
            if (cur->left == nullptr) {
                result.push_back(cur->val);
                prev = cur;
                cur = cur->right;
            } else {
                /* 查找前驱 */
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur)
                    node = node->right;

                if (node->right == nullptr) { /* 还没线索化，则建立线索 */
                    node->right = cur;
                    /* prev = cur; 不能有这句，cur还没有被访问 */
                    cur = cur->left;
                } else {    /* 已经线索化，则访问节点，并删除线索  */
                    result.push_back(cur->val);
                    node->right = nullptr;
                    prev = cur;
                    cur = cur->right;
                }
            }
        }
        return result;
    }


95. Unique Binary Search Trees II 独一无二的二叉搜索树之二  

Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3


vector<TreeNode *> generateTrees(int n) {
    if (n == 0) return {};
    return *generateTreesDFS(1, n);
}

vector<TreeNode*> *generateTreesDFS(int start, int end) {

    vector<TreeNode*> *subTree = new vector<TreeNode*>();

    if (start > end) 
        subTree->push_back(NULL);
    else {
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> *leftSubTree = generateTreesDFS(start, i - 1);
            vector<TreeNode*> *rightSubTree = generateTreesDFS(i + 1, end);
            for (int j = 0; j < leftSubTree->size(); ++j) {
                for (int k = 0; k < rightSubTree->size(); ++k) {
                    TreeNode *node = new TreeNode(i);
                    node->left = (*leftSubTree)[j];
                    node->right = (*rightSubTree)[k];
                    subTree->push_back(node);
                }
            }
        }
    }
    return subTree;
}


96. Unique Binary Search Trees 独一无二的二叉搜索树 

Given n, how many structurally unique BSTs (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BSTs.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

就跟斐波那契数列一样，我们把n = 0 时赋为1，因为空树也算一种二叉搜索树，那么n = 1时的情况可以看做是其左子树个数乘以右子树的个数，左右字数都是空树，所以1乘1还是1。那么n = 2时，由于1和2都可以为跟，分别算出来，再把它们加起来即

int numTrees(int n) {

    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] += dp[j] * dp[i - j - 1];
        }
    }
    return dp[n];
}

97. Interleaving String 交织相错的字符串 

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.


首先，这道题的大前提是字符串s1和s2的长度和必须等于s3的长度，如果不等于，肯定返回false。那么当s1和s2是空串的时候，s3必然是空串，则返回true。所以直接给dp[0][0]赋值true，然后若s1和s2其中的一个为空串的话，那么另一个肯定和s3的长度相等，则按位比较，若相同且上一个位置为True，赋True，其余情况都赋False，这样的二维数组dp的边缘就初始化好了。下面只需要找出递推公式来更新整个数组即可，我们发现，在任意非边缘位置dp[i][j]时，它的左边或上边有可能为True或是False，两边都可以更新过来，只要有一条路通着，那么这个点就可以为True。那么我们得分别来看，如果左边的为True，那么我们去除当前对应的s2中的字符串s2[j - 1] 和 s3中对应的位置的字符相比（计算对应位置时还要考虑已匹配的s1中的字符），为s3[j - 1 + i], 如果相等，则赋True，反之赋False。 而上边为True的情况也类似，所以可以求出递推公式为：

dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i - 1 + j]) || (dp[i][j - 1] && s2[j - 1] == s3[j - 1 + i]);

其中dp[i][j] 表示的是 s2 的前 i 个字符和 s1 的前 j 个字符是否匹配 s3 的前 i+j 个字符

bool isInterleave(string s1, string s2, string s3) {

    if (s1.size() + s2.size() != s3.size()) return false;
    int n1 = s1.size();
    int n2 = s2.size();
    vector<vector<bool> > dp(n1 + 1, vector<bool> (n2 + 1, false)); 
    dp[0][0] = true;
    for (int i = 1; i <= n1; ++i) {
        dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
    }
    for (int i = 1; i <= n2; ++i) {
        dp[0][i] = dp[0][i - 1] && (s2[i - 1] == s3[i - 1]);
    }
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i - 1 + j]) || (dp[i][j - 1] && s2[j - 1] == s3[j - 1 + i]);
        }
    }
    return dp[n1][n2];
}


98. Validate Binary Search Tree 验证二叉搜索树

// 时间复杂度O(n)，空间复杂度O(\logn)
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
bool isValidBST(TreeNode *root) {
    if (!root) return true;
    vector<int> vals;
    inorder(root, vals);
    for (int i = 0; i < vals.size() - 1; ++i) {
        if (vals[i] >= vals[i + 1]) return false;
    }
    return true;
}

void inorder(TreeNode *root, vector<int> &vals) {
    if (!root) return;
    inorder(root->left, vals);
    vals.push_back(root->val);
    inorder(root->right, vals);
}


iterative: 
bool isValidBST(TreeNode* root) {
    stack<TreeNode*> s;
    TreeNode *p = root, *pre = NULL;

    while (p || !s.empty()) {
        while (p) {
            s.push(p);
            p = p->left;
        }
        TreeNode *t = s.top(); s.pop();
        if (pre && t->val <= pre->val) return false;
        pre = t;
        p = t->right;
    }
    return true;
}


99. Recover Binary Search Tree 复原二叉搜索树  

Two elements of a binary search tree (BST) are swapped by mistake.
Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?


binary search tree 空间复杂度要求为O(1) 要想到morris tree. 

其中有两个的顺序被调换了，题目要求上说O(n)的解法很直观，这种解法需要用到递归，用中序遍历树，并将所有节点存到一个一维向量中，把所有节点值存到另一个一维向量中，然后对存节点值的一维向量排序，在将排好的数组按顺序赋给节点。这种最一般的解法可针对任意个数目的节点错乱的情况

void recoverTree(TreeNode *root) {
    vector<TreeNode*> list;
    vector<int> vals;
    inorder(root, list, vals);
    sort(vals.begin(), vals.end());

    for (int i = 0; i < list.size(); ++i) {
        list[i]->val = vals[i];
    }
}

void inorder(TreeNode *root, vector<TreeNode*> &list, vector<int> &vals) {
    if (!root) return;

    inorder(root->left, list, vals);
    list.push_back(root);
    vals.push_back(root->val);
    inorder(root->right, list, vals);
}

这道题的真正符合要求的解法应该用的Morris遍历，这是一种非递归且不使用栈，空间复杂度为O(1)的遍历方法


100. Same Tree 判断相同树  

Given two binary trees, write a function to check if they are equal or not.
Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

判断两棵树是否相同和之前的判断两棵树是否对称都是一样的原理，利用深度优先搜索DFS来递归

// 递归版，时间复杂度O(n)，空间复杂度O(logn)
bool isSameTree(TreeNode *p, TreeNode *q) {
    if (!p && !q) return true;
    if ((p && !q) || (!p && q) || (p->val != q->val)) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}


// 迭代版，时间复杂度O(n)，空间复杂度O(logn)
bool isSameTree(TreeNode *p, TreeNode *q) {
    stack<TreeNode*> s;
    s.push(p);
    s.push(q);

    while(!s.empty()) {
        p = s.top(); s.pop();
        q = s.top(); s.pop();

        if (!p && !q) continue;
        if (!p || !q) return false;
        if (p->val != q->val) return false;

        s.push(p->left);
        s.push(q->left);

        s.push(p->right);
        s.push(q->right);
    }
    return true;
}


101. Symmetric Tree 判断对称树 
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center). 
For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3


recursive: // 时间复杂度O(n)，空间复杂度O(logn)
bool isSymmetric(TreeNode *root) {
    if (!root) return true;
    return isSymmetric(root->left, root->right);
}

bool isSymmetric(TreeNode *left, TreeNode *right) {
    if (!left && !right) return true;
    if (left && !right || !left && right || left->val != right->val) return false;
    return isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
}

iterative: // queue 版本
bool isSymmetric(TreeNode *root) {
    if (!root) return true;
    queue<TreeNode*> q1, q2;
    q1.push(root->left);
    q2.push(root->right);
    
    while (!q1.empty() && !q2.empty()) {
        TreeNode *node1 = q1.front();
        TreeNode *node2 = q2.front();
        q1.pop();
        q2.pop();
        if((node1 && !node2) || (!node1 && node2)) return false;
        if (node1) {
            if (node1->val != node2->val) return false;
            q1.push(node1->left);
            q1.push(node1->right);
            q2.push(node2->right);
            q2.push(node2->left);
        }
    }
    return true;
}

iterative: // stack 版本
bool isSymmetric (TreeNode* root) {
    if (!root) return true;

    stack<TreeNode*> s;
    s.push(root->left);
    s.push(root->right);

    while (!s.empty ()) {
        auto p = s.top (); s.pop();
        auto q = s.top (); s.pop();

        if (!p && !q) continue;
        if (!p || !q) return false;
        if (p->val != q->val) return false;

        s.push(p->left);
        s.push(q->right);

        s.push(p->right);
        s.push(q->left);
    }

    return true;
}


102. Binary Tree Level Order Traversal 二叉树层序遍历  

Given a binary tree, return the level order traversal of its nodes values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7
 

return its level order traversal as:

[
  [3],
  [9,20],
  [15,7]
] 

层序遍历二叉树是典型的广度优先搜索BFS的应用，但是这里稍微复杂一点的是，我们要把各个层的数分开，存到一个二维向量里面，大体思路还是基本相同的，建立一个queue，然后先把根节点放进去，这时候找根节点的左右两个子节点，这时候去掉根节点，此时queue里的元素就是下一层的所有节点，用一个for循环遍历它们，然后存到一个一维向量里，遍历完之后再把这个一维向量存到二维向量里

//时间复杂度O(n)，空间复杂度O(1)
vector<vector<int> > levelOrder(TreeNode *root) {
    vector<vector<int> > res;
    if (root == NULL) return res;

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        vector<int> oneLevel;
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            TreeNode *node = q.front();
            q.pop();
            oneLevel.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(oneLevel);
    }
    return res;
}


// 递归版，时间复杂度O(n)，空间复杂度O(n)
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int> > res;
    levelorder(root, 0, res);
    return res;
}

void levelorder(TreeNode *root, int level, vector<vector<int> > &res) {
    if (!root) return;
    if (res.size() == level) res.push_back({});
    res[level].push_back(root->val);
    if (root->left) levelorder(root->left, level + 1, res);
    if (root->right) levelorder(root->right, level + 1, res);
}


103. Binary Tree Zigzag Level Order Traversal 二叉树的之字形层序遍历 

Given a binary tree, return the zigzag level order traversal of its nodes values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7

return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

广度优先遍历，用一个bool记录是从左到右还是从右到左，每一层结束就翻转一下。使用queue比two stacks要更好更快

recursive:// 时间复杂度O(n)，空间复杂度O(n)
vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
    vector<vector<int>> result;
    traverse(root, 1, result, true);
    return result;
}

void traverse(TreeNode *root, size_t level, vector<vector<int>> &result,
        bool left_to_right) {
    if (!root) return;

    if (level > result.size())
        result.push_back({});

    if (left_to_right)
        result[level-1].push_back(root->val);
    else
        result[level-1].insert(result[level-1].begin(), root->val);

    traverse(root->left, level+1, result, !left_to_right);
    traverse(root->right, level+1, result, !left_to_right);
}


iterative: // 广度优先遍历，用一个bool记录是从左到右还是从右到左，每一层结束就翻转一下。
// 迭代版，时间复杂度O(n)，空间复杂度O(n)
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
      vector<vector<int>> result;
    queue<TreeNode*> current, next;
    bool left_to_right = true;
    
    if(root == nullptr) {
        return result;
    } else {
        current.push(root);
    }

    while (!current.empty()) {
        vector<int> level; // elments in one level
        while (!current.empty()) {
            TreeNode* node = current.front();
            current.pop();
            level.push_back(node->val);
            if (node->left != nullptr) next.push(node->left);
            if (node->right != nullptr) next.push(node->right);
        }
        if (!left_to_right) reverse(level.begin(), level.end());
        result.push_back(level);
        left_to_right = !left_to_right;
        swap(next, current);
    }
    return result;
    
}


104. Maximum Depth of Binary Tree 二叉树的最大深度

// 时间复杂度O(n)，空间复杂度O(logn)
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

iterative:
我们也可以使用层序遍历二叉树，然后计数总层数，即为二叉树的最大深度

int maxDepth(TreeNode* root) {
    if (!root) return 0;
    int res = 0;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        ++res;
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            TreeNode *t = q.front(); q.pop();
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
    }
    return res;
}


105. Construct Binary Tree from Preorder and Inorder Traversal 由先序和中序遍历建立二叉树  

106. Construct Binary Tree from Inorder and Postorder Traversal 由中序和后序遍历建立二叉树 

107. Binary Tree Level Order Traversal II 二叉树层序遍历之二 

Given a binary tree, return the bottom-up level order traversal of its nodes values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},

    3
   / \
  9  20
    /  \
   15   7
 

return its bottom-up level order traversal as:

[
  [15,7],
  [9,20],
  [3]
]

iterative:
从底部层序遍历其实还是从顶部开始遍历，只不过最后存储的方式有所改变
vector<vector<int>> levelOrderBottom(TreeNode *root) {
    vector<vector<int> > res;
    if (root == NULL) return res;

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        vector<int> oneLevel;
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            TreeNode *node = q.front();
            q.pop();
            oneLevel.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.insert(res.begin(), oneLevel);  // add more line
    }
    return res;
}

recursive:
核心就在于我们需要一个二维数组，和一个变量level，当level递归到上一层的个数，我们新建一个空层，继续往里面加数字
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int> > res;
    levelorder(root, 0, res);
    return vector<vector<int> > (res.rbegin(), res.rend()); // add more line
}
void levelorder(TreeNode *root, int level, vector<vector<int> > &res) {
    if (!root) return;
    if (res.size() == level) res.push_back({});
    res[level].push_back(root->val);
    if (root->left) levelorder(root->left, level + 1, res);
    if (root->right) levelorder(root->right, level + 1, res);
}


108. Convert Sorted Array to Binary Search Tree 将有序数组转为二叉搜索树  

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.  

是一种始终满足左<根<右的特性，如果将二叉搜索树按中序遍历的话，得到的就是一个有序数组了。那么反过来，我们可以得知，根节点应该是有序数组的中间点，从中间点分开为左右两个有序数组，在分别找出其中间点作为原中间点的左右两个子节点，这不就是是二分查找法的核心思想么。所以这道题考的就是二分查找法. 
// 二分法，时间复杂度O(n)，空间复杂度O(logn)
TreeNode *sortedArrayToBST(vector<int> &num) {
    return sortedArrayToBST(num, 0 , num.size() - 1);
}

TreeNode *sortedArrayToBST(vector<int> &num, int left, int right) {
    if (left > right) return NULL;
    int mid = (left + right) / 2;
    TreeNode *cur = new TreeNode(num[mid]);
    cur->left = sortedArrayToBST(num, left, mid - 1);
    cur->right = sortedArrayToBST(num, mid + 1, right);
    return cur;
}


109. Convert Sorted List to Binary Search Tree 将有序链表转为二叉搜索树  

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.  

由于二分查找法每次需要找到中点，而链表的查找中间点可以通过快慢指针来操作. 找到中点后，要以中点的值建立一个数的根节点，然后需要把原链表断开，分为前后两个链表，都不能包含原中节点，然后再分别对这两个链表递归调用原函数，分别连上左右子节点即可. 
// bottom-up，时间复杂度O(n)，空间复杂度O(logn)

solution 1:
TreeNode *sortedListToBST(ListNode *head) {
    if (!head) return NULL;
    if (!head->next) return new TreeNode(head->val);
    ListNode *slow = head;
    ListNode *fast = head;
    ListNode *last = slow;
    while (fast->next && fast->next->next) {
        last = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    last->next = NULL;  // fast 是mid point 之前那个值
    TreeNode *cur = new TreeNode(slow->val);  // slow is the middle value
    if (head != slow) cur->left = sortedListToBST(head);
    cur->right = sortedListToBST(fast);
    return cur;
}


solution 2:
// 自底向上
TreeNode *sortedListToBST(ListNode *head) {
    int len = 0;
    ListNode *p = head;
    while (p) {
        len++;
        p = p->next;
    }
    return sortedListToBST(head, 0, len - 1);
}

TreeNode* sortedListToBST(ListNode*& list, int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;
    TreeNode *leftChild = sortedListToBST(list, start, mid - 1);
    TreeNode *parent = new TreeNode(list->val);
    parent->left = leftChild;
    list = list->next;
    parent->right = sortedListToBST(list, mid + 1, end);
    return parent;
}


110. Balanced Binary Tree 平衡二叉树  

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

solution 1: 
高度平衡二叉树是每一个节点的两个字数的深度差不能超过1，那么我们肯定需要一个求各个点深度的函数，然后对每个节点的两个子树来比较深度差，时间复杂度为O(N*N)

bool isBalanced(TreeNode *root) {
    if (!root) return true;
    if (abs(getDepth(root->left) - getDepth(root->right)) > 1) return false;
    return isBalanced(root->left) && isBalanced(root->right);    
}

int getDepth(TreeNode *root) {
    if (!root) return 0;
    return 1 + max(getDepth(root->left), getDepth(root->right));
}


solution 2: 
上面那个方法正确但不是很高效，因为每一个点都会被上面的点计算深度时访问一次，我们可以进行优化。方法是如果我们发现子树不平衡，则不计算具体的深度，而是直接返回-1。那么优化后的方法为：对于每一个节点，我们通过递归获得左右子树的深度，如果子树是平衡的，则返回真实的深度，若不平衡，直接返回-1，此方法时间复杂度O(N)，空间复杂度O(Height)=O(logN)

bool isBalanced (TreeNode* root) {
    return balancedHeight (root) >= 0;
}

/**
 * Returns the height of `root` if `root` is a balanced tree,
 * otherwise, returns `-1`.
 */
int balancedHeight (TreeNode* root) {
    if (root == nullptr) return 0;  // 终止条件

    int left = balancedHeight (root->left);
    int right = balancedHeight (root->right);

    if (left < 0 || right < 0 || abs(left - right) > 1) return -1;  // 剪枝

    return max(left, right) + 1; // 三方合并
}

111. Minimum Depth of Binary Tree 二叉树的最小深度  

Given a binary tree, find its minimum depth.

int minDepth(TreeNode *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    
    if (root->left == NULL) 
        return minDepth(root->right) + 1;
    else if (root->right == NULL) 
        return minDepth(root->left) + 1;
    else 
        return 1 + min(minDepth(root->left), minDepth(root->right));
}


112. Path Sum 二叉树的路径和  

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum. 

这道求二叉树的路径需要用深度优先算法DFS的思想来遍历每一条完整的路径，也就是利用递归不停找子节点的左右子节点，而调用递归函数的参数只有当前节点和sum值。首先，如果输入的是一个空节点，则直接返回false，如果如果输入的只有一个根节点，则比较当前根节点的值和参数sum值是否相同，若相同，返回true，否则false。 这个条件也是递归的终止条件。下面我们就要开始递归了，由于函数的返回值是Ture/False，我们可以同时两个方向一起递归，中间用或||连接，只要有一个是True，整个结果就是True。递归左右节点时，这时候的sum值应该是原sum值减去当前节点的值. 

// 时间复杂度O(n)，空间复杂度O(logn)
bool hasPathSum(TreeNode *root, int sum) {
    if (root == NULL) return false;
    if (root->left == NULL && root->right == NULL && root->val == sum ) return true;
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}


113. Path Sum II 二叉树路径之和之二 
Given a binary tree and a sum, find all root-to-leaf paths where each path sum equals the given sum. 
For example:

Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return

[
   [5,4,11,2],
   [5,8,4,5]
]

还是需要用深度优先搜索DFS，只不过数据结构相对复杂一点，需要用到二维的vector，而且每当DFS搜索到新节点时，都要保存该节点。而且每当找出一条路径之后，都将这个保存为一维vector的路径保存到最终结果二位vector中。并且，每当DFS搜索到子节点，发现不是路径和时，返回上一个结点时，需要把该节点从一维vector中移除. 


vector<vector<int> > pathSum(TreeNode *root, int sum) {
    vector<vector<int>> res;
    vector<int> out;
    helper(root, sum, out, res);
    return res;
}

void helper(TreeNode* node, int sum, vector<int>& out, vector<vector<int>>& res) {
    if (!node) return;
    out.push_back(node->val);
    if (sum == node->val && !node->left && !node->right) {
        res.push_back(out);
    }
    helper(node->left, sum - node->val, out, res);
    helper(node->right, sum - node->val, out, res);
    out.pop_back();
}


114. Flatten Binary Tree to Linked List 将二叉树展开成链表 
Given a binary tree, flatten it to a linked list in-place.

For example,
         1
        / \
       2   5
      / \   \
     3   4   6
 
The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

这道题要求把二叉树展开成链表，根据展开后形成的链表的顺序分析出是使用先序遍历，那么只要是数的遍历就有递归和非递归的两种方法来求解，这里我们也用两种方法来求解。首先来看递归版本的，思路是先利用DFS的思路找到最左子节点，然后回到其父节点，把其父节点和右子节点断开，将原左子结点连上父节点的右子节点上，然后再把原右子节点连到新右子节点的右子节点上，然后再回到上一父节点做相同操作
// 递归版1，时间复杂度O(n)，空间复杂度O(logn)
void flatten(TreeNode *root) {
    if (!root) return;
    if (root->left) flatten(root->left);
    if (root->right) flatten(root->right);
    TreeNode *tmp = root->right;
    root->right = root->left;
    root->left = NULL;

    while (root->right) 
        root = root->right;
    root->right = tmp;
}

iterative: preorder, inorder, 


115. Distinct Subsequences 不同的子序列 

Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"
Return 3.


若原字符串和子序列都为空时，返回1，因为空串也是空串的一个子序列。若原字符串不为空，而子序列为空，也返回1，因为空串也是任意字符串的一个子序列。而当原字符串为空，子序列不为空时，返回0，因为非空字符串不能当空字符串的子序列。理清这些，二维数组dp的边缘便可以初始化了，下面只要找出递推式，就可以更新整个dp数组了。我们通过观察上面的二维数组可以发现，当更新到dp[i][j]时，dp[i][j] >= dp[i][j - 1] 总是成立，再进一步观察发现，当 T[i - 1] == S[j - 1] 时，dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1]，若不等， dp[i][j] = dp[i][j - 1]，所以，综合以上，递推式为：

dp[i][j] = dp[i][j - 1] + (T[i - 1] == S[j - 1] ? dp[i - 1][j - 1] : 0)

dp[i][j] 表示T[0, i-1] 在 S[0, j-1]里出现的次数. 

int numDistinct(string S, string T) {
    int dp[T.size() + 1][S.size() + 1];
    for (int i = 0; i <= S.size(); ++i) dp[0][i] = 1;    
    for (int i = 1; i <= T.size(); ++i) dp[i][0] = 0;    

    for (int i = 1; i <= T.size(); ++i) {
        for (int j = 1; j <= S.size(); ++j) {
            dp[i][j] = dp[i][j - 1] + (T[i - 1] == S[j - 1] ? dp[i - 1][j - 1] : 0);
        }
    }
    return dp[T.size()][S.size()];
}


116. Populating Next Right Pointers in Each Node 每个节点的右向指针 

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:
You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,

         1
       /  \
      2    3
     / \  / \
    4  5  6  7
 
After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL

由于是完全二叉树，所以若节点的左子结点存在的话，其右子节点必定存在，所以左子结点的next指针可以直接指向其右子节点，对于其右子节点的处理方法是，判断其父节点的next是否为空，若不为空，则指向其next指针指向的节点的左子结点，若为空则指向NULL

void connect(TreeLinkNode *root) {
    if (!root) return;
    if (root->left) root->left->next = root->right;

    if (root->right) {
        if(root->next)
            root->right->next = root->next->left; 
        else 
            root->right->next = NULL;
    }
    connect(root->left);
    connect(root->right);
}


题目中要求用O(1)的空间复杂度，所以我们来看下面这种碉堡了的方法。用两个指针start和cur，其中start标记每一层的起始节点，cur用来遍历该层的节点，设计思路之巧妙. 

void connect(TreeLinkNode *root) {
    if (!root) return;
    TreeLinkNode *start = root, *cur = NULL;
    while (start->left) {
        cur = start;
        while (cur) {
            cur->left->next = cur->right;
            if (cur->next) cur->right->next = cur->next->left;
            cur = cur->next;
        }
        start = start->left;
    }
}


117. Populating Next Right Pointers in Each Node II 每个节点的右向指针之二 

要处理一个节点，可能需要最右边的兄弟节点，首先想到用广搜。但广搜不是常数空间的，本题要求常数空间。
// 时间复杂度O(n)，空间复杂度O(1)
void connect(TreeLinkNode *root) {
    if (root == nullptr) return;

    TreeLinkNode* dummy = new TreeLinkNode(-1);
    for (TreeLinkNode *curr = root, *prev = dummy; curr; curr = curr->next) {

        if (curr->left != nullptr){
            prev->next = curr->left;
            prev = prev->next;
        }
        if (curr->right != nullptr){
            prev->next = curr->right;
            prev = prev->next;
        }
    }
    connect(dummy->next);
}

iterative: 
// 时间复杂度O(n)，空间复杂度O(1) 
void connect(TreeLinkNode *root) {
    if(!root)   return;
        TreeLinkNode* l = NULL;
        TreeLinkNode* r = NULL;
        TreeLinkNode* curr = root;
    
        while(curr){
            if(curr->left){
                if(l) {r->next = curr->left;
                       r = r->next; }
                else {r = curr->left;
                      l = r;}
            }

            if(curr->right){
                if(l) {r->next=curr->right;
                       r = r->next;}
                else {r = curr->right;
                      l = r;}
            }

            curr = curr->next;
            if(!curr){
                curr = l;
                l = r = NULL;
            }
        }
}


118. Pascals Triangle 杨辉三角 

Given numRows, generate the first numRows of Pascal triangle.
For example, given numRows = 5,

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]

每一行的首个和结尾一个数字都是1，从第三行开始，中间的每个数字都是上一行的左右两个数字之和。 

vector<vector<int> > generate(int numRows) {
    vector<vector<int> > res;
    if (numRows <= 0) return res;
    // res.assign(numRows, vector<int>(1));  // 只是开辟了一个空间, 并没有赋1
    res.assign(numRows, vector<int>{1});  // 首赋值1


    for (int i = 1; i < numRows; ++i) {
        for (int j = 1; j < i; ++j) {
            res[i].push_back(res[i-1][j] + res[i-1][j-1]);
        }
        res[i].push_back(1);  // 尾赋值1
    }
    return res;
}


119. Pascal Triangle II 杨辉三角之二 
Given an index k, return the kth row of the Pascal triangle.

For example, given k = 3,
Return [1,3,3,1].

// k start from 0
vector<int> getRow(int k) {
    vector<vector<int> > res;   
    vector<int> out;
    int row = k + 1;

    if (row <= 0) return out;

    res.assign(row, vector<int>{1});  // 首赋值1

    for (int i = 1; i < row; ++i) {
        for (int j = 1; j < i; ++j) {
            res[i].push_back(res[i-1][j] + res[i-1][j-1]);
        }
        res[i].push_back(1);  // 尾赋值1
    }
    return res[row-1];
}

120. Triangle 三角形 
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.

设状态为f(i, j)，表示从从位置(i,j)出发，到位置(0,0)间路径的最小和，则状态转移方程为 
f(i, j) = min{f(i+1, j), f(i+1, j+1)} + (i, j)
// solution: 从低向高计算
// 时间复杂度O(n^2)，空间复杂度O(1)
int minimumTotal (vector<vector<int>>& triangle) {
    for (int i = triangle.size() - 2; i >= 0; --i)
        for (int j = 0; j <= i; ++j)
            triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);

    return triangle [0][0];
}


121. Best Time to Buy and Sell Stock 买卖股票的最佳时间 

Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

只需要遍历一次数组，用一个变量记录遍历过数中的最小值，然后每次计算当前值和这个最小值之间的差值最为利润，然后每次选较大的利润来更新。当遍历完成后当前利润即为所求

int maxProfit(vector<int>& prices) {
    int res = 0, buy = INT_MAX;
    for (int price : prices) {
        buy = min(buy, price);
        res = max(res, price - buy);
    }
    return res;
}

122. Best Time to Buy and Sell Stock II 买股票的最佳时间之二 

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


123. Best Time to Buy and Sell Stock III 买股票的最佳时间之三

Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).


允许两次买卖，但同一时间只允许持有一支股票。也就意味着这两次买卖在时间跨度上不能有重叠（当然第一次的卖出时间和第二次的买入时间可以是同一天）。既然不能有重叠可以将整个序列以任意坐标i为分割点，分割成两部分：

prices[0:n-1] => prices[0:i] + prices[i:n-1]

对于这个特定分割来说，最大收益为两段的最大收益之和。每一段的最大收益当然可以用I的解法来做。而III的解一定是对所有0<=i<=n-1的分割的最大收益中取一个最大值。为了增加计算效率，考虑采用dp来做bookkeeping。目标是对每个坐标i：

1. 计算A[0:i]的收益最大值：用minPrice记录i左边的最低价格，用maxLeftProfit记录左侧最大收益
2. 计算A[i:n-1]的收益最大值：用maxPrices记录i右边的最高价格，用maxRightProfit记录右侧最大收益。
3. 最后这两个收益之和便是以i为分割的最大收益。将序列从左向右扫一遍可以获取1，从右向左扫一遍可以获取2。相加后取最大值即为答案。


int maxProfit(vector<int> &prices) {

    if(prices.empty()) return 0;
    int n = prices.size();
    vector<int> leftProfit(n,0);
    
    int maxLeftProfit = 0, minPrice = prices[0];
    for(int i=1; i<n; i++) {
        if(prices[i]<minPrice)
            minPrice = prices[i];
        else
            maxLeftProfit = max(maxLeftProfit, prices[i]-minPrice);
        leftProfit[i] = maxLeftProfit;
    }
    
    int ret = leftProfit[n-1];
    int maxRightProfit = 0, maxPrice = prices[n-1];
    for(int i=n-2; i>=0; i--) {
        if(prices[i]>maxPrice)
            maxPrice = prices[i];
        else
            maxRightProfit = max(maxRightProfit, maxPrice-prices[i]);
        ret = max(ret, maxRightProfit + leftProfit[i]);
    }
    
    return ret;
}


124. Binary Tree Maximum Path Sum 求二叉树的最大路径和

Given a binary tree, find the maximum path sum.
The path may start and end at any node in the tree.

Given the below binary tree,
       1
      / \
     2   3

Return 6.

// 时间复杂度O(n)，空间复杂度O(logn)
int maxPathSum(TreeNode *root) {
    int res = root->val;
    maxPathSumDFS(root, res);
    return res;
}

//maxPathSumDFS return value: 从root到某个node的max value.
// max path sum 只是在maxPathSumDFS中顺带计算出来的
int maxPathSumDFS(TreeNode *root, int &res) {
    if (!root) return 0;
    int left = maxPathSumDFS(root->left, res);
    int right = maxPathSumDFS(root->right, res);

    int top = root->val;
    if(left > 0) 
        top += left; 
    if(right > 0)
        top += right; 

    res = max(res, top);
    return max(left, right) > 0 ? max(left, right) + root->val : root->val; // 注意，最后return的时候，只返回一个方向上的值，为什么？这是因为在递归中，只能向父节点返回，不可能存在L->root->R的路径，只可能是L->root或R->root。
}


125. Valid Palindrome 验证回文字符串
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

但是这里，加入了空格和非字母数字的字符，增加了些难度，但其实原理还是很简单：只需要建立两个指针，left和right, 分别从字符的开头和结尾处开始遍历整个字符串，如果遇到非字母数字的字符就跳过，继续往下找，直到找到下一个字母数字或者结束遍历，如果遇到大写字母，就将其转为小写。等左右指针都找到字母数字时，比较这两个字符，若相等，则继续比较下面两个分别找到的字母数字，若不相等，直接返回false. 

//时间复杂度为O(n)

bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1 ;
    while (left < right) {
        if (!isAlphaNum(s[left])) ++left;
        else if (!isAlphaNum(s[right])) --right;
        else if ((s[left] + 32 - 'a') %32 != (s[right] + 32 - 'a') % 32) return false;
        else {
            ++left; --right;
        }
    }
    return true;
}

126. Word Ladder II 词语阶梯之二  

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



127. Word Ladder 词语阶梯 

Given two words (beginWord and endWord), and a dictionary, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the dictionary

Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.

这里用到了两个高级数据结构unordered_map和queue，即哈希表和队列，其中哈希表是记录单词和目前序列长度之间的映射，而队列的作用是保存每一个要展开的单词。首先把起始单词映射为1，把起始单词排入队列中，开始队列的循环，取出队首词，然后对其每个位置上的字符，用26个字母进行替换，如果此时和结尾单词相同了，就可以返回取出词在哈希表中的值加一。如果替换词在字典中存在但在哈希表中不存在，则将替换词排入队列中，并在哈希表中的值映射为之前取出词加一。如果循环完成则返回0，


int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    unordered_map<string, int> m;
    queue<string> q;  
    //程序正确性证明: 因为queue里的string是按照哈希值从小到大排列, 所以可以保证从queue先计算的值是最小的.

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


128. Longest Consecutive Sequence 求最长连续序列  
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
Your algorithm should run in O(n) complexity.

若是O(nlogn)则可以先排序. 给定了O(n)复杂度限制，我们的思路是，使用一个集合set存入所有的数字，然后遍历数组中的每个数字，如果其在集合中存在，那么将其移除，然后分别用两个变量pre和next算出其前一个数跟后一个数，然后在集合中循环查找，如果pre在集合中，那么将pre移除集合，然后pre再自减1，直至pre不在集合之中，对next采用同样的方法，那么next-pre-1就是当前数字的最长连续序列，更新res即可
// Time Complexity: O(n)，Space Complexity: O(n)
int longestConsecutive(vector<int>& nums) {
    int res = 0;
    unordered_set<int> s(nums.begin(), nums.end());
    for (int val : nums) {
        s.erase(val);
        int pre = val - 1, next = val + 1;
        while (s.count(pre)) s.erase(pre--);
        while (s.count(next)) s.erase(next++);
        res = max(res, next - pre - 1);
    }
    return res;
}


129. Sum Root to Leaf Numbers 求根到叶节点数字之和  

Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
An example is the root-to-leaf path 1->2->3 which represents the number 123.
Find the total sum of all root-to-leaf numbers.

    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.
// 时间复杂度O(n)，空间复杂度O(logn)
这道题由于不是单纯的把各个节点的数字相加，而是每到一个新的数字，要把原来的数字扩大10倍之后再相加 

int sumNumbers(TreeNode *root) {
    return sumNumbersDFS(root, 0);
}

int sumNumbersDFS(TreeNode *root, int sum) {
    if (!root) return 0;
    sum = sum * 10 + root->val;
    if (!root->left && !root->right) return sum;
    return sumNumbersDFS(root->left, sum) + sumNumbersDFS(root->right, sum);
}

130. Surrounded Regions 包围区域  

Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:
X X X X
X X X X
X X X X
X O X X

将包住的O都变成X，但不同的是边缘的O不算被包围，普遍的做法是扫面矩阵的四条边，如果有O，则用DFS遍历，将所有连着的O都变成另一个字符$. 然后把X变成O, 把$变成O. 


void solve(vector<vector<char> >& board) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if ((i == 0 || i == board.size() - 1 || j == 0 || j == board[i].size() - 1) && board[i][j] == 'O')
                solveDFS(board, i, j);
        }
    }

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] == 'O') board[i][j] = 'X';
            if (board[i][j] == '$') board[i][j] = 'O';
        }
    }
}

void solveDFS(vector<vector<char> > &board, int i, int j) {
    if (board[i][j] == 'O') {
        board[i][j] = '$';
        if (i > 0 && board[i - 1][j] == 'O') 
            solveDFS(board, i - 1, j);
        if (j < board[i].size() - 1 && board[i][j + 1] == 'O') 
            solveDFS(board, i, j + 1);
        if (i < board.size() - 1 && board[i + 1][j] == 'O') 
            solveDFS(board, i + 1, j);
        // if (j > 0 && board[i][j - 1] == 'O')  also works, but time out for large data 
        if (j > 1 && board[i][j - 1] == 'O') 
            solveDFS(board, i, j - 1);
    }
}


131. Palindrome Partitioning 拆分回文串

Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return
  [
    ["aa","b"],
    ["a","a","b"]
  ]

这又是一道需要用DFS来解的题目，既然题目要求找到所有可能拆分成回文数的情况，那么肯定是所有的情况都要遍历到，对于每一个子字符串都要分别判断一次是不是回文数，那么肯定有一个判断回文数的子函数，还需要一个DFS函数用来递归，再加上原本的这个函数，总共需要三个函数来求解。  

vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> out;
    partitionDFS(s, 0, out, res);
    return res;
}

void partitionDFS(string s, int start, vector<string> &out, vector<vector<string>> &res) {
    if (start == s.size()) {
        res.push_back(out);
        return;
    }

    for (int i = start; i < s.size(); ++i) {
        if (isPalindrome(s, start, i)) {
            out.push_back(s.substr(start, i - start + 1));
            partitionDFS(s, i + 1, out, res);
            out.pop_back();
        }
    }
}

bool isPalindrome(string s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) return false;
        ++start;
        --end;
    }
    return true;
}


132. Palindrome Partitioning II 拆分回文串之二  
Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.


//超时
 int minCut(string s) {
        vector<vector<string>> res;
    vector<string> out;
    partitionDFS(s, 0, out, res);
    // return res;
    int count = INT_MAX; 
    for(auto r : res)
        count = min(count, static_cast<int>(r.size())); 
        
    return count-1; 
        
    }
    
void partitionDFS(string s, int start, vector<string> &out, vector<vector<string>> &res) {
    if (start == s.size()) {
        res.push_back(out);
        return;
    }

    for (int i = start; i < s.size(); ++i) {
        if (isPalindrome(s, start, i)) {
            out.push_back(s.substr(start, i - start + 1));
            partitionDFS(s, i + 1, out, res);
            out.pop_back();
        }
    }
}

bool isPalindrome(string s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) return false;
        ++start;
        --end;
    }
    return true;
}

solution 2: 

所以要转换成一维DP。如果每次，从i往右扫描，每找到一个回文就算一次DP的话，就可以转换为f(i)=区间[i, n-1]之间最小的cut数，n为字符串长度，则状态转移方程为: f(i) = min{f(j+1) + 1}, i <= j < n. 
一个问题出现了，就是如何判断[i,j]是否是回文？每次都从i到j比较一遍？太浪费了，这里也是一个DP问题。
定义状态 P[i][j] = true if [i,j]为回文，那么: P[i][j] = str[i] == str[j] && P[i+1][j-1]

递推公式为：dp[i] = min(dp[i], 1+dp[j+1] ) i<= j <n，那么还有个问题，是否对于i到j之间的子字符串s[i][j]每次都判断一下是否是回文串，其实这个也可以用DP来简化，其DP递推公式为P[i][j] = s[i] == s[j] && P[i+1][j-1]，其中P[i][j] = true if [i,j]为回文. dp[i]表示区间[i, n-1]之间最小的cut数, 所以dp[0] 要初始化为len - 1, 即[0, n-1]之间有n-1的cut. P[i][j] 表示[i,j]是否为回文    

int minCut(string s) {
    int len = s.size();
    bool P[len][len];
    int dp[len + 1];
    for (int i = 0; i <= len; ++i) {
        dp[i] = len - i - 1; // len = 6, dp[0,1,2,3,4,5,6] = 5,4,3,2,1,0,-1
    }
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            P[i][j] = false;
        }
    }
    for (int i = len - 1; i >= 0; --i) {
        for (int j = i; j < len; ++j) {
            if (s[i] == s[j] && (j - i <= 1 || P[i + 1][j - 1])) {
                P[i][j] = true;
                dp[i] = min(dp[i], dp[j + 1] + 1); // "+ 1" 表示[i, j]之间是palindrome, 但可能[i,jj]之间也是palindrome, where jj > j, 所以要用min 
            }
        }
    }
    return dp[0];
}


133. Clone Graph 无向图的复制  

Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors. 

这道题目的难点在于如何处理每个节点的neighbors，由于在深度拷贝每一个节点后，还要将其所有neighbors放到一个vector中，而如何避免重复拷贝呢？这道题好就好在所有节点值不同，所以我们可以使用哈希表来对应节点值和新生成的节点。对于图的遍历的两大基本方法是深度优先搜索DFS和广度优先搜索BFS  

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    unordered_map<int, UndirectedGraphNode*> umap;
    return clone(node, umap);
}

UndirectedGraphNode *clone(UndirectedGraphNode *node, unordered_map<int, UndirectedGraphNode*> &umap) {
    if (!node) return node;
    if (umap.count(node->label)) return umap[node->label];
    UndirectedGraphNode *newNode = new UndirectedGraphNode(node->label);
    umap[node->label] = newNode;
    for (int i = 0; i < node->neighbors.size(); ++i) {
        (newNode->neighbors).push_back(clone(node->neighbors[i], umap));
    }
    return newNode;
}


134.  Gas Station 加油站问题 

There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas stations index if you can travel around the circuit once, otherwise return -1.
Note:
The solution is guaranteed to be unique.


我们首先要知道能走完整个环的前提是gas的总量要大于cost的总量，这样才会有起点的存在。假设开始设置起点start = 0, 并从这里出发，如果当前的gas值大于cost值，就可以继续前进，此时到下一个站点，剩余的gas加上当前的gas再减去cost，看是否大于0，若大于0，则继续前进。当到达某一站点时，若这个值小于0了，则说明从起点到这个点中间的任何一个点都不能作为起点，则把起点设为下一个点，继续遍历。当遍历完整个环时，当前保存的起点即为所求  

int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int total = 0, sum = 0, start = 0;
    for (int i = 0; i < gas.size(); ++i) {
        total += gas[i] - cost[i];
        sum += gas[i] - cost[i];
        if (sum < 0) {
            start = i + 1;
            sum = 0;
        }
    }
    if (total < 0) return -1;
    else return start;
}


135. Candy 分糖果问题  

There are N children standing in a line. Each child is assigned a rating value.
You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

这道题看起来很难，其实解法并没有那么复杂，当然我也是看了别人的解法才做出来的，先来看看两遍遍历的解法，首先初始化每个人一个糖果，然后这个算法需要遍历两遍，第一遍从左向右遍历，如果右边的小盆友的等级高，等加一个糖果，这样保证了一个方向上高等级的糖果多。然后再从右向左遍历一遍，如果相邻两个左边的等级高，而左边的糖果又少的话，则左边糖果数为右边糖果数加一。最后再把所有小盆友的糖果数都加起来返回即可。


int candy(vector<int>& ratings) {
    int res = 0;
    vector<int> num(ratings.size(), 1);
    for (int i = 0; i < (int)ratings.size() - 1; ++i) {
        if (ratings[i + 1] > ratings[i]) num[i + 1] = num[i] + 1;
    }
    for (int i = (int)ratings.size() - 1; i > 0; --i) {
        if (ratings[i - 1] > ratings[i]) num[i - 1] = max(num[i] + 1, num[i - 1]);
    }
    for (int i = 0; i < num.size(); ++i) {
        res += num[i];
    }
    return res;
}


136. Single Number 单独的数字 

Given an array of integers, every element appears twice except for one. Find that single one.  

由于数字在计算机是以二进制存储的，每位上都是0或1，如果我们把两个相同的数字异或，0与0异或是0,1与1异或也是0，那么我们会得到0。根据这个特点，我们把数组中所有的数字都异或起来，则每对相同的数字都会得0，然后最后剩下来的数字就是那个只有1次的数字. 

int singleNumber(vector<int>& nums) {
    int res = 0;
    for (auto num : nums) res ^= num;
    return res;
}


137. Single Number II 单独的数字之二

Given an array of integers, every element appears three times except for one. Find that single one.
Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

这道题是之前那道 Single Number 单独的数字 的延伸，那道题的解法就比较独特，是利用计算机按位储存数字的特性来做的，这道题就是除了一个单独的数字之外，数组中其他的数字都出现了三次，那么还是要利用位操作 Bit Operation 来解此题。我们可以建立一个32位的数字，来统计每一位上1出现的个数，我们知道如果某一位上为1的话，那么如果该整数出现了三次，对3去余为0，我们把每个数的对应位都加起来对3取余，最终剩下来的那个数就是单独的数字。

int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        int sum = 0;
        for (int j = 0; j < nums.size(); ++j) {
            sum += (nums[j] >> i) & 1;
        }
        res |= (sum % 3) << i;
    }
    return res;
}


138. Copy List with Random Pointer 拷贝带有随机指针的链表 

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.


RandomListNode *copyRandomList(RandomListNode *head) {
    if (!head) return NULL;

     //insert nodes
    RandomListNode *cur = head;
    while (cur) {
        RandomListNode *node = new RandomListNode(cur->label);
        node->next = cur->next;
        cur->next = node;
        cur = node->next;
    }

    // copy random pointer 
    cur = head;
    while (cur) {
        if (cur->random) {
            cur->next->random = cur->random->next;
        }
        cur = cur->next->next;
    }

    //decouple two links
    cur = head;
    RandomListNode *res = head->next;
    while (cur) {
        RandomListNode *tmp = cur->next;
        cur->next = tmp->next;
        if(tmp->next) tmp->next = tmp->next->next;
        cur = cur->next;
    }
    return res;
}


139. Word Break 拆分词句 

Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].
Return true because "leetcode" can be segmented as "leet code".


// solution 1: 深搜，超时
// 时间复杂度O(2^n)，空间复杂度O(n)

bool wordBreak(string s, unordered_set<string> &dict) {
    return dfs(s, dict, 0, 1);
}

bool dfs(const string &s, unordered_set<string> &dict,
    size_t start, size_t cur) {
    if (cur == s.size()) {
        return dict.find(s.substr(start, cur-start)) != dict.end();
    }
    if (dfs(s, dict, start, cur+1)) return true; // no cut
    if (dict.find(s.substr(start, cur-start)) != dict.end()) // cut here
        if (dfs(s, dict, cur+1, cur+1)) return true;
    return false;
}


设状态为f(i)，表示s[0,i)是否可以分词，则状态转移方程为: 
f(i) = any_of(f(j) && s[j,i] in dict), 0 <= j < i

//solution 2: 动规，时间复杂度O(n^2)，空间复杂度O(n)
bool wordBreak(string s, unordered_set<string> &dict) {
    // 长度为n的字符串有n+1个隔板s.size();
    vector<bool> res(s.size() + 1, false);
    res[0] = true;  // 空字符串
    for (int i = 0; i < s.size() + 1; ++i) {
        for (int j = 0; j < i; ++j) {
            if (res[j] && dict.find(s.substr(j, i-j)) != dict.end()) {
                res[i] = true;
                break;
            }
        }
    }
    return res[len];
}


140. Word Break II 拆分词句之二  

Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.
Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].
A solution is ["cats and dog", "cat sand dog"].

这道题是之前那道Word Break 拆分词句的拓展，那道题只让我们判断给定的字符串能否被拆分成字典中的词，而这道题加大了难度，让我们求出所有可以拆分成的情况，就像题目中给的例子所示。可以用DFS的套路来解题，但是不是一般的brute force，我们必须进行剪枝优化，因为按照惯例OJ的最后一个test case都是巨长无比的，很容易就Time Limit Exceeded。那么如何进行剪枝优化呢，可以参见网友水中的鱼的博客，定义一个一位数组possible，其中possible[i] = true表示在[i, n]区间上有解，n为s的长度，如果某个区间之前被判定了无解，下次循环时就会跳过这个区间，从而大大减少了运行时间. 


vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
    vector<string> res;
    string out;
    vector<bool> possible(s.size() + 1, true);
    wordBreakDFS(s, wordDict, 0, possible, out, res);
    return res;
}


void wordBreakDFS(string &s, unordered_set<string> &wordDict, int start, vector<bool> &possible, string &out, vector<string> &res) {
    if (start == s.size()) {
        res.push_back(out.substr(0, out.size() - 1));
        return;
    }

    for (int i = start; i < s.size(); ++i) {
        string word = s.substr(start, i - start + 1);
        if (wordDict.find(word) != wordDict.end() && possible[i + 1]) { // eliminate unnecessory search
            out.append(word).append(" ");
            int oldSize = res.size();
            wordBreakDFS(s, wordDict, i + 1, possible, out, res);
            if (res.size() == oldSize) possible[i + 1] = false; // if no solution, set the possible to false
            out.resize(out.size() - word.size() - 1);
        }
    }

    // 有大量重复计算
    // for (int i = start; i < s.size(); ++i) {
    //     string word = s.substr(start, i - start + 1);
    //     if (wordDict.find(word) != wordDict.end() && possible[i + 1]) { // eliminate unnecessory search
    //         out.append(word).append(" ");
    //         wordBreakDFS(s, wordDict, i + 1, possible, out, res);
    //         out.resize(out.size() - word.size() - 1);
    //     }
    // }

}


141. Linked List Cycle 单链表中的环 

Given a linked list, determine if it has a cycle in it.
Follow up:
Can you solve it without using extra space? 

这道题是快慢指针的经典应用。只需要设两个指针，一个每次走一步的慢指针和一个每次走两步的快指针，如果链表里有环的话，两个指针最终肯定会相遇. 

bool hasCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}


142. Linked List Cycle II 单链表中的环之二

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
Follow up:
Can you solve it without using extra space?

 还是要设快慢指针，不过这次要记录两个指针相遇的位置，当两个指针相遇了后，让其一指针从链表头开始 

ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (!fast || !fast->next) return NULL;
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return fast;
}


143. Reorder List 链表重排序 

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes values.
For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.

这道链表重排序问题可以拆分为以下三个小问题：
1. 使用快慢指针来找到链表的中点，并将链表从中点处断开，形成两个独立的链表。
2. 将第二个链翻转。
3. 将第二个链表的元素间隔地插入第一个链表中。

void reorderList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return;

    ListNode *slow = head, *fast = head, *prev = nullptr;
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = nullptr; // cut at middle

    slow = reverseList(slow);

    // merge two lists
    ListNode *curr = head;
    while (curr->next) {
        ListNode *tmp = curr->next;
        curr->next = slow;
        slow = slow->next;
        curr->next->next = tmp;
        curr = tmp;
    }
    curr->next = slow;
}


ListNode* reverseList(ListNode* head) {
    if (!head) return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *cur = head;
    while (cur->next) {
        ListNode *tmp = cur->next;
        cur->next = tmp->next;
        tmp->next = dummy->next;
        dummy->next = tmp;
    }
    return dummy->next;
}


144. Binary Tree Preorder Traversal 二叉树的先序遍历 

Given a binary tree, return the preorder traversal of its nodes values.
For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3

return [1,2,3].
Note: Recursive solution is trivial, could you do it iteratively?

要用到stack来辅助运算。由于先序遍历的顺序是"根-左-右", 算法为：
1. 把根节点push到栈中
2. 循环检测栈是否为空，若不空，则取出栈顶元素，保存其值，然后看其右子节点是否存在，若存在则push到栈中。再看其左子节点，若存在，则push到栈中。

vector<int> preorderTraversal(TreeNode *root) {
    vector<int> res;
    stack<TreeNode*> s;
    if (!root) return res;
    s.push(root);

    while (!s.empty()) {
        TreeNode *p = s.top();
        res.push_back(p->val);
        s.pop();
        if (p->right) s.push(p->right); // 先右
        if (p->left) s.push(p->left);   // 再左
    }
    return res;
}


145. Binary Tree Postorder Traversal 二叉树的后序遍历

Given a binary tree, return the postorder traversal of its nodes values.
For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [3,2,1].
Note: Recursive solution is trivial, could you do it iteratively?

求二叉树的后序遍历的非递归方法，跟前序，中序，层序一样都需要用到栈，后续的顺序是左-右-根，所以当一个节点值被取出来时，它的左右子节点要么不存在，要么已经被访问过了。 

vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    if (!root) return res;
    stack<TreeNode*> s;
    s.push(root);
    TreeNode *head = root;

    while (!s.empty()) {
        TreeNode *top = s.top();
        if ((!top->left && !top->right) || top->left == head || top->right == head) {
            res.push_back(top->val);
            s.pop();
            head = top;
        } else {
            if (top->right) s.push(top->right);
            if (top->left) s.push(top->left);
        }
    }
    return res;
}


146. LRU Cache 最近最少使用页面置换缓存器

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

这个缓存器主要有两个成员函数，get和set，其中get函数是通过输入key来获得value，如果成功获得后，这对(key, value)升至缓存器中最常用的位置（顶部），如果key不存在，则返回-1。而set函数是插入一对新的(key, value)，如果原缓存器中有该key，则需要先删除掉原有的，将新的插入到缓存器的顶部。如果不存在，则直接插入到顶部。若加入新的值后缓存器超过了容量，则需要删掉一个最不常用的值，也就是底部的值。具体实现时我们需要三个私有变量，cap, l和m，其中cap是缓存器的容量大小，l是保存缓存器内容的列表，m是哈希表，保存关键值key和缓存器各项的迭代器之间映射，方便我们以O(1)的时间内找到目标项。

然后我们再来看get和set如何实现，get相对简单些，我们在m中查找给定的key，如果存在则将此项移到顶部，并返回value，若不存在返回-1。对于set，我们也是现在m中查找给定的key，如果存在就删掉原有项，并在顶部插入新来项，然后判断是否溢出，若溢出则删掉底部项(最不常用项)。

class LRUCache{
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if (it == m.end()) return -1;
        l.splice(l.begin(), l, it->second);
        return it->second->second;
    }
    
    void set(int key, int value) {
        auto it = m.find(key);
        if (it != m.end()) l.erase(it->second);
        l.push_front(make_pair(key, value));
        m[key] = l.begin();
        if (m.size() > cap) {
            int k = l.rbegin()->first;
            l.pop_back();
            m.erase(k);
        }
    }
    
private:
    int cap;
    list<pair<int, int> > l;
    unordered_map<int, list<pair<int, int> >::iterator> m;
};


147. Insertion Sort List 链表插入排序 

Sort a linked list using insertion sort.

链表的插入排序实现原理很简单，就是一个元素一个元素的从原链表中取出来，然后按顺序插入到新链表中，时间复杂度为O(n2)，是一种效率并不是很高的算法，但是空间复杂度为O(1)，以高时间复杂度换取了低空间复杂度。

ListNode *insertionSortList(ListNode *head) {
    ListNode *res = new ListNode(-1);
    ListNode *cur = res;

    while (head) {
        ListNode *next = head->next;
        cur = res;
        while (cur->next && cur->next->val <= head->val) {
            cur = cur->next;
        }
        head->next = cur->next;
        cur->next = head;
        head = next;
    }
    return res->next;
}


148. Sort List 链表排序 

Sort a linked list in O(n log n) time using constant space complexity.

常见排序方法有很多，插入排序，选择排序，堆排序，快速排序，冒泡排序，归并排序，桶排序等等。。它们的时间复杂度不尽相同，而这里题目限定了时间必须为O(nlgn)，符合要求只有快速排序，归并排序，堆排序，而根据单链表的特点，最适于用归并排序。

ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode *slow = head, *fast = head, *pre = head;
    while (fast && fast->next) {
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    pre->next = NULL;
    return merge(sortList(head), sortList(slow));
}
ListNode* merge(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->val < l2->val) {
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        l2->next = merge(l1, l2->next);
        return l2;
    }
}


149. Max Points on a Line 共线点个数  

Given n points on a 2D plane, find the maximum number of points that lie on the same straight line. 

令我惊奇的是，这道题的OJ居然容忍brute force的方法通过，那么我感觉下面这种O(n^3)的解法之所以能通过OJ，可能还有一个原因就是用了比较高效的判断三点共线的方法。一般来说判断三点共线有三种方法，斜率法，周长法，面积法(请参见这个帖子)。而其中通过判断叉积为零的面积法是坠好的。比如说有三个点A(x1, y1)、B(x2, y2)、C(x3, y3). 
行列式:
x1 y1 1
x2 y2 1  = 0
x3 y3 1

int maxPoints(vector<Point>& points) {
    int res = 0;
    for (int i = 0; i < points.size(); ++i) {
        int duplicate = 1;
        for (int j = i + 1; j < points.size(); ++j) {
            int cnt = 0;
            long long x1 = points[i].x, y1 = points[i].y;
            long long x2 = points[j].x, y2 = points[j].y;
            if (x1 == x2 && y1 == y2) {
                ++duplicate; 
                continue;
            }

            for (int k = 0; k < points.size(); ++k) {
                int x3 = points[k].x, y3 = points[k].y;
                if (x1 * y2 + x2 * y3 + x3 * y1 - x3 * y2 - x2 * y1 - x1 * y3 == 0) {
                    ++cnt;
                }
            }
            res = max(res, cnt);
        }
        res = max(res, duplicate);
    }
    return res;
}


150. Evaluate Reverse Polish Notation 计算逆波兰表达式 

Evaluate the value of an arithmetic expression in Reverse Polish Notation.
Valid operators are +, -, *, /. Each operand may be an integer or another expression.
Some examples:

  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

从前往后遍历数组，遇到数字则压入栈中，遇到符号，则把栈顶的两个数字拿出来运算，把结果再压入栈中，直到遍历完整个数组，栈顶数字即为最终答案.

int evalRPN(vector<string> &tokens) {
    if (tokens.size() == 1) 
        return atoi(tokens[0].c_str());

    stack<int> s;
    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens[i] != "+" && tokens[i] != "-" && tokens[i] != "*" && tokens[i] != "/") {
            s.push(atoi(tokens[i].c_str())); // c++ string to integer 
            // s.push(stoi(tokens[i])); // c++ string to integer: stoi. integer to string: to_string
        } else {
            int m = s.top();
            s.pop();
            int n = s.top();
            s.pop();
            if (tokens[i] == "+") s.push(n + m);
            if (tokens[i] == "-") s.push(n - m);
            if (tokens[i] == "*") s.push(n * m);
            if (tokens[i] == "/") s.push(n / m);
        }
    }
    return s.top();
}


151. Reverse Words in a String 翻转字符串中的单词

Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the". 

solution 1: 
先整个字符串整体翻转一次，然后再分别翻转每一个单词（或者先分别翻转每一个单词，然后再整个字符串整体翻转一次），此时就能得到我们需要的结果了

solution 2: 

下面我们来看使用字符串流类stringstream的解法，我们先把字符串装载入字符串流中，然后定义一个临时变量tmp，然后把第一个单词赋给s，这里需要注意的是，如果含有非空格字符，那么每次>>操作就会提取连在一起的非空格字符，那么我们每次将其加在s前面即可；如果原字符串为空，那么就不会进入while循环；如果原字符串为许多空格字符连在一起，那么第一个>>操作就会提取出这些空格字符放入s中，然后不进入while循环，这时候我们只要判断一下s的首字符是否为空格字符，是的话就将s清空即可

void reverseWords(string &s) {
    istringstream is(s);
    string tmp;
    is >> s;  // >>操作就会提取连在一起的非空格字符, 存到s中
    while(is >> tmp) s = tmp + " " + s; // >>操作就会提取连在一起的非空格字符, 存到tmp中
    if(!s.empty() && s[0] == ' ') s = "";
}


152. Maximum Product Subarray 求最大子数组乘积 

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

这个求最大子数组乘积问题是由最大子数组之和问题演变而来，但是却比求最大子数组之和要复杂，因为在求和的时候，遇到0，不会改变最大值，遇到负数，也只是会减小最大值而已。而在求最大子数组乘积的问题中，遇到0会使整个乘积为0，而遇到负数，则会使最大乘积变成最小乘积，正因为有负数和0的存在，使问题变得复杂了不少. 


仔细研读代码后，发现算法设计的很精妙。首先定义了两个变量maxIdx和minIdx，分别用于保存当前时刻的最大值和最小值，然后在遍历每一个数字的时候，更新当前的最大值和最小值，最终可以得到最大子数组乘积。

最开始时，设置当前当前最大值和最小值均为1，最终最大值为数组第一个数字，还要定义一个oldMaxIdx变量来保存之前最大值，然后最每一个遍历的数字根据其正负分别做不同的处理：
1. 当遍历到一个正数时，此时的最大值等于之前的最大值乘以这个正数，此时的最小值等于它本身再乘以这个正数。
2. 当遍历到一个负数时，此时的最大值等于之前最小值乘以这个负数，这时候问题就来了，挖掘技术哪家强？哈哈，言归正传，这时候问题就来了，当之前的最小值是负数时，负负得正没有问题，当之前的最小值是正数时，在乘以一个负数，当前最大值就变成负数了，这怎么办，没关系，在下次循环时，会和1比较取大的，负数就被舍弃了，程序继续正常执行。此时的最小值等于之前最大值（肯定是正数）乘以这个负数，还是负数。
3. 在每遍历完一个数时，都要更新最终的最大值。

如果这里改成去最小值的话，就是求最小子数组乘积，并且时间复杂度是醉人的O(n)

int maxProduct (int A[], int n) {
    if (n == 0) return 0;
    
    int maxIdx = 1, minIdx = 1;
    int out = A[0];
    for (int i = 0; i < n; ++i) {
        int oldMaxIdx = max (maxIdx, 1);
        if (A[i] > 0) {
            maxIdx = oldMaxIdx * A[i];
            minIdx *= A[i];
        } else {
            maxIdx = minIdx * A[i];
            minIdx = oldMaxIdx * A[i];
        }
        out = max (out, maxIdx);
    }
    return out;
}


153. Find Minimum in Rotated Sorted Array 寻找旋转有序数组的最小值 

Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
Find the minimum element.

You may assume no duplicate exists in the array.

从左向右扫描，扫描到的第一个逆序的位置，肯定是原始数组中第一个元素，时间复杂度O(n)。

不过本题依旧可以用二分查找，最关键的是要判断那个“断层”是在左边还是右边。 若A[mid] < A[right]，则区间[mid,right]一定递增，断层一定在左边; 若A[mid] > A[right]，则区间[left,mid]一定递增，断层一定在右边
// solution 类似 No.33  
int findMin(vector<int>& num) {
     int n = num.size(); 
     int left = 0, right = n - 1;
    
    if (num[left] > num[right]) {
        // while (left <= right) {
        while (left < right) {
            int mid = (left + right) / 2;
            if (num[mid] < num[right]) 
                right = mid;
            else 
                left = mid + 1;
        }
        return min(num[left], num[right]);
    }
    return num[0]; 
}


154. Find Minimum in Rotated Sorted Array II 寻找旋转有序数组的最小值之二 

Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
Find the minimum element.
The array may contain duplicates.

若A[mid] < A[right]，则区间[mid,right]一定递增，断层一定在左边
若A[mid] > A[right]，则区间[left,mid]一定递增，断层一定在右边
若A[mid] == A[right] 确定不了，这个时候，断层既可能在左边，也可能在右边，所以我们不能扔掉一半，不过这时，我们可以--right扔掉一个 

int findMin(vector<int>& num) {
    int n = num.size(); 
    int left = 0, right = n - 1;
    
    while (left < right) {
        int mid = (left + right) / 2;
        if (num[mid] < num[right]) 
            right = mid;
        else if(num[mid] > num[right]) 
            left = mid + 1;
        else 
            --right;  // num[mid] == num[right]时
    }
    return min(num[left], num[right]);
}


155. Min Stack 最小栈 

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

这道最小栈跟原来的栈相比就是多了一个功能，可以返回该栈的最小值。使用两个栈来实现，一个栈来按顺序存储push进来的数据，另一个用来存出现过的最小值. 

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {}
    
    void push(int x) {
        s1.push(x);
        if (s2.empty() || x <= s2.top()) s2.push(x);
    }
    
    void pop() {
        if (s1.top() == s2.top()) s2.pop();
        s1.pop();
    }
    
    int top() {
        return s1.top();
    }
    
    int getMin() {
        return s2.top(); // s2 keeps the minimum 
    }
    
private:
    stack<int> s1, s2;
};


156. Binary Tree Upside Down 二叉树的上下颠倒 

Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.

For example:
Given a binary tree {1,2,3,4,5},
    1
   / \
  2   3
 / \
4   5

return the root of the binary tree [4,5,2,#,#,3,1].

   4
  / \
 5   2
    / \
   3   1  

这道题让我们把一棵二叉树上下颠倒一下，而且限制了右节点要么为空要么一定会有对应的左节点。上下颠倒后原来二叉树的最左子节点变成了根节点，其对应的右节点变成了其左子节点，其父节点变成了其右子节点，相当于顺时针旋转了一下。 

对于一个根节点来说，我们的目标是将其左子节点变为根节点，右子节点变为左子节点，原根节点变为右子节点，那么我们首先判断这个根节点是否存在，且其有没有左子节点，如果不满足这两个条件的话，直接返回即可，不需要翻转操作。那么我们不停的对左子节点调用递归函数，直到到达最左子节点开始翻转，翻转好最左子节点后，开始回到上一个左子节点继续翻转即可，直至翻转完整棵树. 

TreeNode *upsideDownBinaryTree(TreeNode *root) {
    if (!root || !root->left) return root;
    TreeNode *l = root->left, *r = root->right;
    TreeNode *res = upsideDownBinaryTree(l);
    l->left = r;  // 递归中上一层的l, 
    l->right = root;
    root->left = NULL;
    root->right = NULL;
    return res;
}


157. Read N Characters Given Read4 用Read4来读取N个字符  

The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.
By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.
Note:
The read function will only be called once for each test case.


这道题给了我们一个Read4函数，每次可以从一个文件中最多读出4个字符，如果文件中的字符不足4个字符时，返回准确的当前剩余的字符数。现在让我们实现一个最多能读取n个字符的函数。思路是我们每4个读一次，然后把读出的结果判断一下，如果为0的话，说明此时的buf已经被读完，跳出循环，直接返回res和n之中的较小值。否则一直读入，直到读完n个字符，循环结束，最后再返回res和n之中的较小值. 

int read(char *buf, int n) {
    int res = 0;
    for (int i = 0; i <= n / 4; ++i) {
        int cur = read4(buf + res);  // read 4 chars at a time and store in buf. 
        if (cur == 0) break;
        res += cur;
    }
    return min(res, n);
}

158. Read N Characters Given Read4 II - Call multiple times 用Read4来读取N个字符之二 - 多次调用

The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.
By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times.

那道题说read函数只能调用一次，而这道题说read函数可以调用多次，那么难度就增加了. 

buf = "ab", [read(1),read(2)]，返回 ["a","b"]
那么第一次调用read(1)后，从buf中读出一个字符，那么就是第一个字符a，然后又调用了一个read(2)，想取出两个字符，但是buf中只剩一个b了，所以就把取出的结果就是b。再来看一个例子：

buf = "a", [read(0),read(1),read(2)]，返回 ["","a",""]
第一次调用read(0)，不取任何字符，返回空，第二次调用read(1)，取一个字符，buf中只有一个字符，取出为a，然后再调用read(2)，想取出两个字符，但是buf中没有字符了，所以取出为空。

貌似是用两个变量readPos和writePos来记录读取和写的位置，i从0到n开始循环，如果此时读和写的位置相同，那么我们调用read4函数，将结果赋给writePos，把readPos置零，如果writePos为零的话，说明buf中没有东西了，返回当前的坐标i。然后我们用内置的buff变量的readPos位置覆盖输入字符串buf的i位置，如果完成遍历，返回n. 

int readPos = 0, writePos = 0;  // define global variables to record previous R/W postion, and prepare for the next R/W. 
char buff[4];

int read(char *buf, int n) {
    for (int i = 0; i < n; ++i) {
        if (readPos == writePos) {
            writePos = read4(buff); // first read 4 chars at a time and store in buff. 
            readPos = 0;  // read resets to 0. 
            if (writePos == 0) return i;
        }
        buf[i] = buff[readPos++]; // second, assign buff to buf. 
    }
    return n;
}


159. Longest Substring with At Most Two Distinct Characters 最多有两个不同字符的最长子串  

Given a string S, find the length of the longest substring T that contains at most two distinct characters.
For example,
Given S = “eceba”,
T is “ece” which its length is 3.

让我们求最多有两个不同字符的最长子串。那么我们首先想到的是用哈希表来做，哈希表记录每个字符的出现次数，然后如果哈希表中的映射数量超过两个的时候，我们需要删掉一个映射. 

int lengthOfLongestSubstringTwoDistinct(string s) {
    int res = 0, left = 0;
    unordered_map<char, int> m;   // unordered_map不对key排序 
    for (int i = 0; i < s.size(); ++i) {
        ++m[s[i]];
        while (m.size() > 2) {   // 把2换成k, 则可以拓展at most k distinct characters. 
            if (--m[s[left]] == 0) m.erase(s[left]);
            ++left;
        }
        res = max(res, i - left + 1);
    }
    return res;
}

160. Intersection of Two Linked Lists 求两个链表的交点  

Write a program to find the node at which the intersection of two singly linked lists begins.
For example, the following two linked lists:
A:          a1 → a2
                    ↘
                     c1 → c2 → c3
                    ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.

*If the two linked lists have no intersection at all, return null.
*The linked lists must retain their original structure after the function returns.
*You may assume there are no cycles anywhere in the entire linked structure.
*Your code should preferably run in O(n) time and use only O(1) memory.

solution 1: 
// 分别遍历两个链表，得到分别对应的长度。然后求长度的差值，把较长的那个链表向后移动这个差值的个数，然后一一比较即可
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (!headA || !headB) return NULL;
    int lenA = getLength(headA), lenB = getLength(headB);
    if (lenA < lenB) {
        for (int i = 0; i < lenB - lenA; ++i) headB = headB->next;
    } else {
        for (int i = 0; i < lenA - lenB; ++i) headA = headA->next;
    }
    while (headA && headB && headA != headB) {
        headA = headA->next;
        headB = headB->next;
    }
    return (headA && headB) ? headA : NULL;
}

int getLength(ListNode* head) {
    int cnt = 0;
    while (head) {
        ++cnt;
        head = head->next;
    }
    return cnt;
}

solution 2: 
让两条链表分别从各自的开头开始往后遍历，当其中一条遍历到末尾时，我们跳到另一个条链表的开头继续遍历。两个指针最终会相等，而且只有两种情况，一种情况是在交点处相遇，另一种情况是在各自的末尾的空节点处相等。为什么一定会相等呢，因为两个指针走过的路程相同，是两个链表的长度之和，所以一定会相等. 

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (!headA || !headB) return NULL;
    ListNode *a = headA, *b = headB;

    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}


161. One Edit Distance 一个编辑距离 

Given two strings S and T, determine if they are both one edit distance apart.

这道题是之前那道Edit Distance的拓展，然而这道题并没有那道题难，这道题只让我们判断两个字符串的编辑距离是否为1，那么我们只需分下列三种情况来考虑就行了：
1. 两个字符串的长度之差大于1，那么直接返回False
2. 两个字符串的长度之差等于1，那么长的那个字符串去掉一个字符，剩下的应该和短的字符串相同
3. 两个字符串的长度之差等于0，那么两个字符串对应位置的字符只能有一处不同。

只需要对比两个字符串对应位置上的字符，如果遇到不同的时候，这时我们看两个字符串的长度关系，如果相等，那么我们比较当前位置后的字串是否相同，如果s的长度大，那么我们比较s的下一个位置开始的子串，和t的当前位置开始的子串是否相同，反之如果t的长度大，那么我们比较t的下一个位置开始的子串，和s的当前位置开始的子串是否相同。如果循环结束，都没有找到不同的字符，那么此时我们看两个字符串的长度是否相差1. 

bool isOneEditDistance(string s, string t) {
    for (int i = 0; i < min(s.size(), t.size()); ++i) {
        if (s[i] != t[i]) {
            if (s.size() == t.size()) return s.substr(i + 1) == t.substr(i + 1);
            else if (s.size() < t.size()) return s.substr(i) == t.substr(i + 1);
            else return s.substr(i + 1) == t.substr(i);
        }
    }
    return abs(s.size() - t.size()) == 1;
}


162. Find Peak Element 求数组的局部峰值 

A peak element is an element that is greater than its neighbors.
Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.
The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
You may imagine that num[-1] = num[n] = -∞.
For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

solution 1: 
我们要考虑使用类似于二分查找法来缩短时间，由于只是需要找到任意一个峰值，那么我们在确定二分查找折半后中间那个元素后，和紧跟的那个元素比较下大小，如果大于，则说明峰值在前面，如果小于则在后面。这样就可以找到一个峰值了. 

public int findPeakElement(int[] nums) {
    int left = 0, right = nums.length - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < nums[mid + 1]) left = mid + 1;
        else right = mid;
    }
    return right;
}

solution 2: 
由于题目中说明了局部峰值一定存在，那么实际上可以从第二个数字开始往后遍历

int findPeakElement(vector<int>& nums) {
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] < nums[i - 1]) return i - 1;
    }
    return nums.size() - 1;
}


163. Missing Ranges 缺失区间  

Given a sorted integer array where the range of elements are [0, 99] inclusive, return its missing ranges.
For example, given [0, 1, 3, 50, 75], return [“2”, “4->49”, “51->74”, “76->99”] 

这道题让我们求缺失区间，跟之前那道Summary Ranges很类似，这道题让我们求缺失的空间，给了一个空间的范围[lower upper]，缺失的空间的范围需要在给定的空间范围内。我们首先将lower赋给l，然后开始遍历nums数组，如果i小于nums长度且当前数字小于等于upper，我们让r等于当前数字，否则如果当i等于nums的长度时或者当前数字大于upper时，将r赋为upper+1。然后判断l和r的值，若相同，l自增1，否则当r大于l时，说明缺失空间存在，我们看l和r是否差1，如果是，说明只缺失了一个数字，若不是，则说明缺失了一个区间，我们分别加上数字或者区间即可. 

vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
    vector<string> res;
    int l = lower;
    for (int i = 0; i <= nums.size(); ++i) {
        int r = (i < nums.size() && nums[i] <= upper) ? nums[i] : upper + 1;
        if (l == r) ++l;
        else if (r > l) {
            res.push_back(r - l == 1 ? to_string(l) : to_string(l) + "->" + to_string(r - 1));
            l = r + 1;
        }
    }
    return res;
}


164. Maximum Gap 求最大间距  
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
Try to solve it in linear time/space.
Return 0 if the array contains less than 2 elements.
You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.

遇到这类问题肯定先想到的是要给数组排序，但是题目要求是要线性的时间和空间，那么只能用桶排序或者基排序。这里我用桶排序Bucket Sort来做，首先找出数组的最大值和最小值，然后要确定每个桶的容量，即为(最大值 - 最小值) / 个数 + 1，在确定桶的个数，即为(最大值 - 最小值) / 桶的容量 + 1，然后需要在每个桶中找出局部最大值和最小值，而最大间距的两个数不会在同一个桶中，而是一个桶的最小值和另一个桶的最大值之间的间距。

int maximumGap(vector<int> &numss) {
    if (numss.empty()) return 0;
    int mx = INT_MIN, mn = INT_MAX, n = numss.size();
    //遍历一遍，找出最大最小值
    for (int d : numss) {
        mx = max(mx, d);
        mn = min(mn, d);
    }
    // 每个桶的长度len,向上取整所以加+  
    int size = (mx - mn) / n + 1;
    int bucket_nums = (mx - mn) / size + 1;
    vector<int> bucket_min(bucket_nums, INT_MAX);
    vector<int> bucket_max(bucket_nums, INT_MIN);
    set<int> s;
    //桶的个数:(maxNum - minNum) / len + 1,
    //每个桶里面存储属于该桶的最大值和最小值即可，注意这里的最大最小值是局部的  
    for (int d : numss) {
        int idx = (d - mn) / size;
        bucket_min[idx] = min(bucket_min[idx], d);
        bucket_max[idx] = max(bucket_max[idx], d);
        s.insert(idx);
    }
    int pre = 0, res = 0;
    for (int i = 1; i < n; ++i) {
        if (!s.count(i)) continue;
        res = max(res, bucket_min[i] - bucket_max[pre]);
        pre = i;
    }
    return res;
}


165. Compare Version Numbers 版本比较 

Compare two version numbers version1 and version1.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

Here is an example of version numbers ordering:
0.1 < 1.1 < 1.2 < 13.37

// 我们可以一位一位的累加
int compareVersion(string version1, string version2) {
    int n1 = version1.size(), n2 = version2.size();
    int i = 0, j = 0, d1 = 0, d2 = 0;
    while (i < n1 || j < n2) {
        while (i < n1 && version1[i] != '.') {
            d1 = d1 * 10 + version1[i++] - '0';
        }
        while (j < n2 && version2[j] != '.') {
            d2 = d2 * 10 + version2[j++] - '0';
        }
        if (d1 > d2) return 1;
        else if (d1 < d2) return -1;
        d1 = d2 = 0;
        ++i; ++j;
    }
    return 0;
}


166. Fraction to Recurring Decimal 分数转循环小数 

Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
If the fractional part is repeating, enclose the repeating part in parentheses.

For example,
Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".

这道题还是比较有意思的，开始还担心万一结果是无限不循环小数怎么办，百度之后才发现原来可以写成分数的都是有理数，而有理数要么是有限的，要么是无限循环小数，无限不循环的叫无理数，例如圆周率pi或自然数e等，小学数学没学好，汗！由于还存在正负情况，处理方式是按正数处理，符号最后在判断，那么我们需要把除数和被除数取绝对值，那么问题就来了：由于整型数INT的取值范围是-2147483648～2147483647，而对-2147483648取绝对值就会超出范围，所以我们需要先转为long long型再取绝对值。那么怎么样找循环呢，肯定是再得到一个数字后要看看之前有没有出现这个数。为了节省搜索时间，我们采用哈希表来存数每个小数位上的数字。还有一个小技巧，由于我们要算出小数每一位，采取的方法是每次把余数乘10，再除以除数，得到的商即为小数的下一位数字。等到新算出来的数字在之前出现过，则在循环开始出加左括号，结束处加右括号。 

string fractionToDecimal(int numerator, int denominator) {
    int s1 = numerator >= 0 ? 1 : -1;
    int s2 = denominator >= 0 ? 1 : -1;
    long long num = abs( (long long)numerator );
    long long den = abs( (long long)denominator );
    long long out = num / den;
    long long rem = num % den;
    unordered_map<long long, int> m;
    string res = to_string(out);

    if (s1 * s2 == -1 && (out > 0 || rem > 0)) 
        res = "-" + res;
    if (rem == 0) 
        return res;
    res += ".";
    string s = "";
    int pos = 0;
    while (rem != 0) {
        if (m.find(rem) != m.end()) {
            s.insert(m[rem], "(");
            s += ")";
            return res + s;
        }
        m[rem] = pos;
        s += to_string((rem * 10) / den);
        rem = (rem * 10) % den;
        ++pos;
    }
    return res + s;
}


167. Two Sum II - Input array is sorted 两数之和之二 - 输入数组有序

Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution.
Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2

//solution 1:
vector<int> twoSum(vector<int>& numbers, int target) {
    int l = 0, r = numbers.size() - 1;
    while (l < r) {
        int sum = numbers[l] + numbers[r];
        if (sum == target) return {l + 1, r + 1};
        else if (sum < target) ++l;
        else --r;
    }
    return {};
}

//solution 2:
vector<int> twoSum(vector<int>& numbers, int target) {
    for (int i = 0; i < numbers.size(); ++i) {
        int t = target - numbers[i], left = i + 1, right = numbers.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (numbers[mid] == t) return {i + 1, mid + 1};
            else if (numbers[mid] < t) left = mid + 1;
            else right = mid;
        }
    }
    return {};
}


168. Excel Sheet Column Title 求Excel表列名称 

Given a positive integer, return its corresponding column title as appear in an Excel sheet.
For example:
    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB 

此题和Excel Sheet Column Number 求Excel表列序号是一起的，但是我在这题上花的时间远比上面一道多，起始原理都一样，就是一位一位的求，此题从低位往高位求，每进一位，则把原数缩小26倍，再对26取余，之后减去余数，再缩小26倍，以此类推，可以求出各个位置上的字母。最后只需将整个字符串翻转一下即可。

string convertToTitle(int n) {
    string res = "";
    while (n) {
        if (n % 26 == 0) {
            res += 'Z';
            n -= 26;
        }
        else {
            res += n%26 - 1 + 'A';
            n -= n%26;
        }
        n /= 26;
    }
    reverse(res.begin(), res.end());
    return res;
}


169. Majority Element 求众数 

Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
You may assume that the array is non-empty and the majority element always exist in the array.

一种是用哈希表，这种方法需要O(n)的时间和空间，另一种是用一种叫摩尔投票法 Moore Voting，需要O(n)的时间和O(1)的空间，比前一种方法更好。这种投票法先将第一个数字假设为众数，然后把计数器设为1，比较下一个数和此数是否相等，若相等则计数器加一，反之减一。然后看此时计数器的值，若为零，则将当前值设为候选众数。以此类推直到遍历完整个数组，当前候选众数即为该数组的众数. 

int majorityElement(vector<int>& nums) {
    int res = 0, cnt = 0;
    for (int num : nums) {
        if (cnt == 0) {res = num; ++cnt;}
        else (num == res) ? ++cnt : --cnt;
    }
    return res;
}

下面这种解法利用到了位操作Bit Manipulation来解，将中位数按位来建立，从0到31位，每次统计下数组中该位上0和1的个数，如果1多，那么我们将结果res中该位变为1，最后累加出来的res就是中位数了，相当赞的方法，这种思路尤其在这道题的延伸Majority Element II中有重要的应用，

int majorityElement(vector<int>& nums) {
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        int ones = 0, zeros = 0;
        for (int num : nums) {
            if ((num & (1 << i)) != 0) ++ones;
            else ++zeros;
        }
        if (ones > zeros) res |= (1 << i);
    }
    return res;
}


170. Two Sum III - Data structure design 两数之和之三 - 数据结构设计 

Design and implement a TwoSum class. It should support the following operations:add and find.
add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

For example,
add(1); add(3); add(5);
find(4) -> true
find(7) -> false

我们先来看用哈希表的解法，我们把每个数字和其出现的次数建立映射，然后我们遍历哈希表，对于每个值，我们先求出此值和目标值之间的差值t，然后我们需要分两种情况来看，如果当前值不等于差值t，那么只要哈希表中有差值t就返回True，或者是当差值t等于当前值时，如果此时哈希表的映射次数大于1，则表示哈希表中还有另一个和当前值相等的数字，二者相加就是目标值. 

class TwoSum {
public:
    void add(int number) {
        ++m[number];
    }

    bool find(int value) {
        for (auto a : m) {
            int t = value - a.first;
            if ((t != a.first && m.count(t)) || (t == a.first && a.second > 1)) {
                return true;
            }
        }
        return false;
    }
private:
    unordered_map<int, int> m;
};


171. Excel Sheet Column Number 求Excel表列序号 

Given a column title as appear in an Excel sheet, return its corresponding column number.
For example:
    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 

这题实际上相当于一种二十六进制转十进制的问题  

int titleToNumber(string s) {
    int n = s.size();
    int res = 0;
    int tmp = 1;
    for (int i = n; i >= 1; --i) {
        res += (s[i - 1] - 'A' + 1) * tmp; 
        tmp *= 26;
    }
    return res;
}

172. Factorial Trailing Zeroes 求阶乘末尾零的个数 

Given an integer n, return the number of trailing zeroes in n!.
Note: Your solution should be in logarithmic time complexity.

是让求一个数的阶乘末尾0的个数，也就是要找乘数中10的个数，而10可分解为2和5，而我们可知2的数量又远大于5的数量，那么此题即便为找出5的个数。仍需注意的一点就是，像25,125，这样的不只含有一个5的数字需要考虑进去 

int trailingZeroes(int n) {
    int res = 0;
    while (n) {
        res += n / 5;
        n /= 5;  // corner case: 25, 125
    }
    return res;
}

173. Binary Search Tree Iterator 二叉搜索树迭代器 

Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

这道题主要就是考二叉树的中序遍历的非递归形式，需要额外定义一个栈来辅助，二叉搜索树的建树规则就是左<根<右，用中序遍历即可从小到大取出所有节点

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        while (root) {
            s.push(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *n = s.top();
        s.pop();
        int res = n->val;
        if (n->right) {
            n = n->right;
            while (n) {
                s.push(n);
                n = n->left;
            }
        }
        return res;
    }

private:
    stack<TreeNode*> s;
};


174. Dungeon Game 地牢游戏 

The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

Write a function to determine the knights minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 (K)  -3  3
-5      -10 1
10      30  -5 (P)

Notes:
The knights health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.

如果按我的那种算法走的路径为 1 -> 0 -> -2 -> 0 -> -3, 这样的话骑士的起始血量要为5，而正确的路径应为 1 -> -3 -> 3 -> 0 -> -3, 这样骑士的骑士血量只需为3。无奈只好上网看大神的解法，发现统一都是用动态规划Dynamic Programming来做，建立一个和迷宫大小相同的二维数组用来表示当前位置出发的起始血量，最先初始化的是公主所在的房间的起始生命值，然后慢慢向第一个房间扩散，不断的得到各个位置的最优的起始生命值。递归方程为: 递归方程是dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j]).  

int calculateMinimumHP(vector<vector<int> > &dungeon) {

    int m = dungeon.size();
    int n = dungeon[0].size();
    int dp[m][n];
    dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);

    for (int i = m - 2; i >= 0; --i) {
        dp[i][n - 1] = max(1, dp[i + 1][n - 1] - dungeon[i][n - 1]);
    }

    for (int j = n - 2; j >= 0; --j) {
        dp[m - 1][j] = max(1, dp[m - 1][j + 1] - dungeon[m - 1][j]);
    }

    for (int i = m - 2; i >= 0; --i) {
        for (int j = n - 2; j >= 0; --j) {
            dp[i][j] = max(1, min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]);
        }
    }
    return dp[0][0];
}


179. Largest Number 最大组合数 

Given a list of non negative integers, arrange them such that they form the largest number.
For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.
Note: The result may be very large, so you need to return a string instead of an integer.

这种解法对于两个数字a和b来说，如果将其都转为字符串，如果ab > ba，则a排在前面，比如9和34，由于934>349，所以9排在前面，再比如说30和3，由于303<330，所以3排在30的前面。按照这种规则对原数组进行排序后，将每个数字转化为字符串再连接起来就是最终结果。

string largestNumber(vector<int>& nums) {
    string res;
    sort(nums.begin(), nums.end(), [](int a, int b) {
       return to_string(a) + to_string(b) > to_string(b) + to_string(a); 
    });
    for (int i = 0; i < nums.size(); ++i) {
        res += to_string(nums[i]);
    }
    return res[0] == '0' ? "0" : res;
}


186. Reverse Words in a String II 翻转字符串中的单词之二 

Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.
The input string does not contain leading or trailing spaces and the words are always separated by a single space.
For example,
Given s = "the sky is blue",
return "blue is sky the".
Could you do it in-place without allocating extra space?

void reverseWords(string &s) {
    int left = 0, right;
    for (int i = 0; i <= s.size(); i++) {
        if (s[i] == ' ' || i == s.size()) {
            right = i;
            reverse(s.begin() + left, s.begin() + right); // reverse函数[a, b）, reverse a to b-1的数 
            left = i + 1;
        }
    }
    reverse(s.begin(), s.end());
}


187. Repeated DNA Sequences 求重复的DNA序列  

All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,
Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].

// 如果我们不需要考虑节省内存空间，那我们可以直接将10个字符组成字符串存入set中
vector<string> findRepeatedDnaSequences(string s) {
    set<string> res, st;
    for (int i = 0; i + 9 < s.size(); ++i) {
        string t = s.substr(i, 10);
        if (st.count(t)) res.insert(t);
        else st.insert(t);
    }
    return vector<string>{res.begin(), res.end()};
}


188. Best Time to Buy and Sell Stock IV 买卖股票的最佳时间之四

Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

这道题实际上是之前那道 Best Time to Buy and Sell Stock III 买股票的最佳时间之三的一般情况的推广，还是需要用动态规划Dynamic programming来解决，具体思路如下：
这里我们需要两个递推公式来分别更新两个变量local和global，参见网友Code Ganker的博客，我们其实可以求至少k次交易的最大利润。我们定义local[i][j]为在到达第i天时最多可进行j次交易并且最后一次交易在最后一天卖出的最大利润，此为局部最优。然后我们定义global[i][j]为在到达第i天时最多可进行j次交易的最大利润，此为全局最优。它们的递推式为：

local[i][j] = max(global[i - 1][j - 1] + max(diff, 0), local[i - 1][j] + diff)
global[i][j] = max(local[i][j], global[i - 1][j])，

其中局部最优值是比较前一天并少交易一次的全局最优加上大于0的差值，和前一天的局部最优加上差值后相比，两者之中取较大值，而全局最优比较局部最优和前一天的全局最优。
但这道题还有个坑，就是如果k的值远大于prices的天数，比如k是好几百万，而prices的天数就为若干天的话，上面的DP解法就非常的没有效率，应该直接用Best Time to Buy and Sell Stock II 买股票的最佳时间之二的方法来求解，所以实际上这道题是之前的二和三的综合体，

int maxProfit(int k, vector<int> &prices) {
    if (prices.empty()) 
        return 0;
    if (k >= prices.size()) 
        return solveMaxProfit(prices);

    int g[k + 1] = {0};
    int l[k + 1] = {0};
    for (int i = 0; i < prices.size() - 1; ++i) {
        int diff = prices[i + 1] - prices[i];
        for (int j = k; j >= 1; --j) {
            l[j] = max(g[j - 1] + max(diff, 0), l[j] + diff);
            g[j] = max(g[j], l[j]);
        }
    }
    return g[k];
}

int solveMaxProfit(vector<int> &prices) {
    int res = 0;
    for (int i = 1; i < prices.size(); ++i) {
        if (prices[i] - prices[i - 1] > 0) {
            res += prices[i] - prices[i - 1];
        }
    }
    return res;
}


189. Rotate Array 旋转数组 

Rotate an array of n elements to the right by k steps.
For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].
Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
Hint:
Could you do it in-place with O(1) extra space?

// 我们先来看一种O(n)的空间复杂度的方法，我们复制一个和nums一样的数组，然后利用映射关系i -> (i+k)%n来交换数字
void rotate(vector<int>& nums, int k) {
    vector<int> t = nums;
    for (int i = 0; i < nums.size(); ++i) {
        nums[(i + k) % nums.size()] = t[i];
    }
}

// 先把前n-k个数字翻转一下，再把后k个数字翻转一下，最后再把整个数组翻转一下
void rotate(vector<int>& nums, int k) {
    if (nums.empty() || (k %= nums.size()) == 0) return;
    int n = nums.size();
    reverse(nums.begin(), nums.begin() + n - k);
    reverse(nums.begin() + n - k, nums.end());
    reverse(nums.begin(), nums.end());
}


190. Reverse Bits 翻转位 

Reverse bits of a given 32 bits unsigned integer.
For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?           

// 那么对于这道题，我们只需要把要翻转的数从右向左一位位的取出来，然后加到新生成的数的最低位即可 
uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;

    for (int i = 0; i < 32; ++i) {
        if (n & 1 == 1) {
            res = (res << 1) + 1;
        } else {
            res = res << 1;
        }
        n = n >> 1;
    }
    return res;
}


191. Number of 1 Bits 位1的个数 

Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).
For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.

int hammingWeight(uint32_t n) {
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        res += (n & 1);
        n = n >> 1;
    }
    return res;
}


198. House Robber 打家劫舍
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police. 

// solution 1:
int rob(vector<int> &num) {
    if (num.size() <= 1) return num.empty() ? 0 : num[0];
    //initialize
    vector<int> dp = {num[0], max(num[0], num[1])};

    for (int i = 2; i < num.size(); ++i) {
        dp.push_back(max(num[i] + dp[i - 2], dp[i - 1]));
    }
    return dp.back();
}

// 核心思想还是用DP，分别维护两个变量a和b，然后按奇偶分别来更新a和b，这样就可以保证组成最大和的数字不相邻
int rob(vector<int> &num) {
    int a = 0, b = 0;
    for (int i = 0; i < num.size(); ++i) {
        if (i % 2 == 0) {
            a += num[i];
            a = max(a, b);
        } else {
            b += num[i];
            b = max(a, b);
        }
    }
    return max(a, b);
}


199. Binary Tree Right Side View 二叉树的右侧视图

Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].

这道题要求我们打印出二叉树每一行最右边的一个数字，实际上是求二叉树层序遍历的一种变形，我们只需要保存每一层最右边的数字即可，这道题只要在之前那道题上稍加修改即可得到结果，还是需要用到数据结构队列queue，遍历每层的节点时，把下一层的节点都存入到queue中，每当开始新一层节点的遍历之前，先把新一层最后一个节点值存到结果中. 

vector<int> rightSideView(TreeNode *root) {
    vector<int> res;
    if (!root) return res;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        res.push_back(q.back()->val);
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            TreeNode *node = q.front();
            q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return res;
}


200. Number of Islands 岛屿的数量  

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:
11110
11010
11000
00000
Answer: 1

Example 2:
11000
11000
00100
00011
Answer: 3

这道求岛屿数量的题的本质是求矩阵中连续区域的个数，很容易想到需要用深度优先搜索DFS来解，我们需要建立一个visited数组用来记录某个位置是否被访问过，对于一个为‘1’且未被访问过的位置，我们递归进入其上下左右位置上为‘1’的数，将其visited对应值赋为true，继续进入其所有相连的邻位置，这样可以将这个连通区域所有的数找出来，并将其对应的visited中的值赋true，找完次区域后，我们将结果res自增1，然后我们在继续找下一个为‘1’且未被访问过的位置，以此类推直至遍历完整个原数组即可得到最终结果.    


int numIslands(vector<vector<char> > &grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int m = grid.size(), n = grid[0].size(), res = 0;
    vector<vector<bool> > visited(m, vector<bool>(n, false));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                numIslandsDFS(grid, visited, i, j);
                ++res;
            }
        }
    }
    return res;
}

void numIslandsDFS(vector<vector<char> > &grid, vector<vector<bool> > &visited, int x, int y) {
    if (x < 0 || x >= grid.size()) return;
    if (y < 0 || y >= grid[0].size()) return;
    if (grid[x][y] != '1' || visited[x][y]) return;

    visited[x][y] = true;
    numIslandsDFS(grid, visited, x - 1, y);
    numIslandsDFS(grid, visited, x + 1, y);
    numIslandsDFS(grid, visited, x, y - 1);
    numIslandsDFS(grid, visited, x, y + 1);
}


201. Bitwise AND of Numbers Range 数字范围位相与    

Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
For example, given the range [5, 7], you should return 4.


仔细观察我们可以得出，最后的数是该数字范围内所有的数的左边共同的部分，我们再来看一个范围[26, 30]，它们的二进制如下：
11010　　11011　　11100　　11101　　11110
发现了规律后，我们只要写代码找到左边公共的部分即可，我们可以从建立一个32位都是1的mask，然后每次向左移一位，比较m和n是否相同，不同再继续左移一位，直至相同，然后把m和mask相与就是最终结果

int rangeBitwiseAnd(int m, int n) {
    int d = INT_MAX;
    while ((m & d) != (n & d)) {
        d <<= 1;
    }
    return m & d;
}

还有另一种解法，不需要用mask，直接平移m和n，每次向右移一位，直到m和n相等，记录下所有平移的次数i，然后再把m左移i位即为最终结果. 

int rangeBitwiseAnd(int m, int n) {
    int i = 0;
    while (m != n) {
        m >>= 1;
        n >>= 1;
        ++i;
    }
    return (m << i);
}


202. Happy Number 快乐数

Write an algorithm to determine if a number is "happy".
A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

我们可以用set来记录所有出现过的数字，然后每出现一个新数字，在set中查找看是否存在，若不存在则加入表中，若存在则跳出循环，并且判断此数是否为1，若为1返回true，不为1返回false

bool isHappy(int n) {
    set<int> s;
    while (n != 1) {
        int t = 0;
        while (n) {
            t += (n % 10) * (n % 10);
            n /= 10;
        }
        n = t;
        if (s.count(n)) break;
        else s.insert(n);
    }
    return n == 1;
}

203. Remove Linked List Elements 移除链表元素  

Remove all elements from a linked list of integers that have value val.
Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5

我们只需定义几个辅助指针，然后遍历原链表，遇到与给定值相同的元素，将该元素的前后连个节点连接起来，然后删除该元素即可，要注意的是还是需要在链表开头加上一个dummy node. 

ListNode* removeElements(ListNode* head, int val) {
    ListNode *dummy = new ListNode(-1), *pre = dummy;
    dummy->next = head;

    while (pre->next) {
        if (pre->next->val == val) {
            ListNode *t = pre->next;
            pre->next = t->next;
            t->next = NULL;
            delete t;
        } else {
            pre = pre->next;
        }
    }
    return dummy->next;
}


204. Count Primes 质数的个数     

Count the number of prime numbers less than a non-negative number, n  

这道题给定一个非负数n，让我们求小于n的质数的个数，题目中给了充足的提示，解题方法就在第二个提示埃拉托斯特尼筛法Sieve of Eratosthenes中，这个算法的过程如下图所示，我们从2开始遍历到根号n，先找到第一个质数2，然后将其所有的倍数全部标记出来，然后到下一个质数3，标记其所有倍数，一次类推，直到根号n，此时数组中未被标记的数字就是质数。我们需要一个n-1长度的bool型数组来记录每个数字是否被标记，长度为n-1的原因是题目说是小于n的质数个数，并不包括n。 然后我们用两个for循环来实现埃拉托斯特尼筛法

int countPrimes(int n) {
    vector<bool> num(n - 1, true);
    num[0] = false;
    int res = 0, limit = sqrt(n);

    for (int i = 2; i <= limit; ++i) {
        if (num[i - 1]) {
            for (int j = i * i; j < n; j += i) {
                num[j - 1] = false;
            }
        }
    }

    for (int j = 0; j < n - 1; ++j) {  // j < n is wrong, corner case: n = 2; 
        if (num[j]) ++res;
    }
    return res;
}


205. Isomorphic Strings 同构字符串  

Given two strings s and t, determine if they are isomorphic.
Two strings are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.
Given "foo", "bar", return false.
Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.

这道题让我们求同构字符串，就是说原字符串中的每个字符可由另外一个字符替代，可以被其本身替代，相同的字符一定要被同一个字符替代，且一个字符不能被多个字符替代，即不能出现一对多的映射。根据一对一映射的特点，我们需要用两个哈希表分别来记录原字符串和目标字符串中字符出现情况，由于ASCII码只有256个字符，所以我们可以用一个256大小的数组来代替哈希表，并初始化为0，我们遍历原字符串，分别从源字符串和目标字符串取出一个字符，然后分别在两个哈希表中查找其值，若不相等，则返回false，若想等，将其值更新为i + 1. 

bool isIsomorphic(string s, string t) {
    int m1[256] = {0}, m2[256] = {0}, n = s.size();

    for (int i = 0; i < n; ++i) {
        if (m1[s[i]] != m2[t[i]]) 
            return false;

        m1[s[i]] = i + 1;
        m2[t[i]] = i + 1;
    }
    return true;
}


206. Reverse Linked List 倒置链表 

Reverse a singly linked list. 

// solution 1;
ListNode* reverseList(ListNode* head) {
    if (!head) return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *cur = head;
    while (cur->next) {
        ListNode *tmp = cur->next;
        cur->next = tmp->next;
        tmp->next = dummy->next;
        dummy->next = tmp;
    }
    return dummy->next;
}

// solution 2; 
下面我们来看递归解法，代码量更少，递归解法的思路是，不断的进入递归函数，直到head指向最后一个节点，p指向之前一个节点，然后调换head和p的位置，再返回上一层递归函数，再交换p和head的位置，每次交换后，head节点后面都是交换好的顺序，直到p为首节点，然后再交换，首节点就成了为节点，此时整个链表也完成了翻转

ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode *p = head;
    head = reverseList(p->next);
    p->next->next = p;
    p->next = NULL;
    return head;
}


207. Course Schedule 课程清单

There are a total of n courses you have to take, labeled from 0 to n - 1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:
2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.


Hints:
1. This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
2. There are several ways to represent a graph. For example, the input prerequisites is a graph represented by a list of edges. Is this graph representation appropriate?
3. Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
4. Topological sort could also be done via BFS.

我们开始先根据输入来建立这个有向图，并将入度数组也初始化好。然后我们定义一个queue变量，将所有入度为0的点放入队列中，然后开始遍历队列，从graph里遍历其连接的点，每到达一个新节点，将其入度减一，如果此时该点入度为0，则放入队列末尾。直到遍历完队列中所有的值，若此时还有节点的入度不为0，则说明环存在，返回false，反之则返回true

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int> > graph(numCourses, vector<int>(0));
    vector<int> in(numCourses, 0);
    for (auto a : prerequisites) {
        graph[a[1]].push_back(a[0]);
        ++in[a[0]];
    }
    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (in[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (auto a : graph[t]) {
            --in[a];
            if (in[a] == 0) q.push(a);
        }
    }
    for (int i = 0; i < numCourses; ++i) {
        if (in[i] != 0) return false;
    }
    return true;
}


下面我们来看DFS的解法，也需要建立有向图，还是用二维数组来建立，和BFS不同的是，我们像现在需要一个一维数组visit来记录访问状态，大体思路是，先建立好有向图，然后从第一个门课开始，找其可构成哪门课，暂时将当前课程标记为已访问，然后对新得到的课程调用DFS递归，直到出现新的课程已经访问过了，则返回false，没有冲突的话返回true，然后把标记为已访问的课程改为未访问

bool canFinish(int numCourses, vector<vector<int> >& prerequisites) {
    vector<vector<int> > graph(numCourses, vector<int>(0));
    vector<int> visit(numCourses, 0);
    for (auto a : prerequisites) {
        graph[a[1]].push_back(a[0]);
    }
    for (int i = 0; i < numCourses; ++i) {
        if (!canFinishDFS(graph, visit, i)) return false;
    }
    return true;
}

bool canFinishDFS(vector<vector<int> > &graph, vector<int> &visit, int i) {
    if (visit[i] == -1) return false;
    if (visit[i] == 1) return true;
    visit[i] = -1;
    for (auto a : graph[i]) {
        if (!canFinishDFS(graph, visit, a)) return false;
    }
    visit[i] = 1;
    return true;
}


208. Implement Trie (Prefix Tree) 实现字典树(前缀树)

Implement a trie with insert, search, and startsWith methods.

字典树主要有如下三点性质：
1. 根节点不包含字符，除根节点意外每个节点只包含一个字符。
2. 从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串。
3. 每个节点的所有子节点包含的字符串不相同。

字母树的插入（Insert）、删除（ Delete）和查找（Find）都非常简单，用一个一重循环即可，即第i 次循环找到前i 个字母所对应的子树，然后进行相应的操作。实现这棵字母树，我们用最常见的数组保存（静态开辟内存）即可，当然也可以开动态的指针类型（动态开辟内存）。至于结点对儿子的指向，一般有三种方法：
1、对每个结点开一个字母集大小的数组，对应的下标是儿子所表示的字母，内容则是这个儿子对应在大数组上的位置，即标号；
2、对每个结点挂一个链表，按一定顺序记录每个儿子是谁；
3、使用左儿子右兄弟表示法记录这棵树。
三种方法，各有特点。第一种易实现，但实际的空间要求较大；第二种，较易实现，空间要求相对较小，但比较费时；第三种，空间要求最小，但相对费时且不易写。

我们先来看第一种实现方法，这种方法实现起来简单直观，字母的字典树每个节点要定义一个大小为26的子节点指针数组，然后用一个标志符用来记录到当前位置为止是否为一个词，初始化的时候讲26个子节点都赋为空。那么insert操作只需要对于要插入的字符串的每一个字符算出其的位置，然后找是否存在这个子节点，若不存在则新建一个，然后再查找下一个。查找词和找前缀操作跟insert操作都很类似，不同点在于若不存在子节点，则返回false。查找次最后还要看标识位，而找前缀直接返回true即可

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode *child[26];
    bool isWord;
    TrieNode() : isWord(false){
        for (auto &a : child) a = NULL;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string s) {
        TrieNode *p = root;
        for (auto &a : s) {
            int i = a - 'a';
            if (!p->child[i]) p->child[i] = new TrieNode();
            p = p->child[i];
        }
        p->isWord = true;
    }

    // Returns if the word is in the trie.
    bool search(string key) {
        TrieNode *p = root;
        for (auto &a : key) {
            int i = a - 'a';
            if (!p->child[i]) return false;
            p = p->child[i];
        }
        return p->isWord;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *p = root;
        for (auto &a : prefix) {
            int i = a - 'a';
            if (!p->child[i]) return false;
            p = p->child[i];
        }
        return true;
    }

private:
    TrieNode* root;
};


209. Minimum Size Subarray Sum 最短子数组之和 

Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there is not one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

// solution 1: O(n)
定义两个指针left和right，分别记录子数组的左右的边界位置，然后我们让right向右移，直到子数组和大于等于给定值或者right达到数组末尾，此时我们更新最短距离，并且将left像右移一位，然后再sum中减去移去的值，然后重复上面的步骤，直到right到达末尾，且left到达临界位置，即要么到达边界，要么再往右移动，和就会小于给定值

int minSubArrayLen(int s, vector<int>& nums) {
    if (nums.empty()) return 0;
    int left = 0, right = 0, sum = 0, len = nums.size(), res = len + 1;
    while (right < len) {
        while (sum < s && right < len) {
            sum += nums[right++];
        }
        while (sum >= s) {
            res = min(res, right - left); // 不是right - left + 1, 因为上面的while loop
            sum -= nums[left++];
        }
    }
    return res == len + 1 ? 0 : res;
}

//solution 2: O(nlgn)的解法，
这个解法要用到二分查找法，思路是，我们建立一个比原数组长一位的sums数组，其中sums[i]表示nums数组中[0, i - 1]的和，然后我们对于sums中每一个值sums[i]，用二分查找法找到子数组的右边界位置，使该子数组之和大于sums[i] + s，然后我们更新最短长度的距离即可 

int minSubArrayLen(int s, vector<int>& nums) {
    int res = INT_MAX, n = nums.size();
    vector<int> sums(n + 1, 0);

    for (int i = 1; i < n + 1; ++i) 
        sums[i] = sums[i - 1] + nums[i - 1];

    for (int i = 0; i < n; ++i) {
        int left = i + 1, right = n, t = sums[i] + s;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (sums[mid] < t) left = mid + 1;
            else right = mid - 1;
        }
        if (left == n + 1) break;
        res = min(res, left - i);
    }
    return res == INT_MAX ? 0 : res;
}


210. Course Schedule II 课程清单之二 

There are a total of n courses you have to take, labeled from 0 to n - 1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:
2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

那道题只让我们判断是否能完成所有课程，即检测有向图中是否有环，而这道题我们得找出要上的课程的顺序，即有向图的拓扑排序，这样一来，难度就增加了，但是由于我们有之前那道的基础，而此题正是基于之前解法的基础上稍加修改，我们从queue中每取出一个数组就将其存在结果中，最终若有向图中有环，则结果中元素的个数不等于总课程数，那我们将结果清空即可. 

vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<int> res;
    vector<vector<int> > graph(numCourses, vector<int>(0));
    vector<int> in(numCourses, 0);

    for (auto &a : prerequisites) {
        graph[a.second].push_back(a.first);
        ++in[a.first];
    }

    queue<int> q;

    for (int i = 0; i < numCourses; ++i) {
        if (in[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int t = q.front();
        res.push_back(t);
        q.pop();
        for (auto &a : graph[t]) {
            --in[a];
            if (in[a] == 0) q.push(a);
        }
    }

    if (res.size() != numCourses) 
        res.clear();

    return res;
}


211. Add and Search Word - Data structure design 添加和查找单词-数据结构设计 

Design a data structure that supports the following two operations:
void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

For example:
addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.


class WordDictionary {
public:
    struct TrieNode {
    public:
        TrieNode *child[26];
        bool isWord;
        TrieNode() : isWord(false) {
            for (auto &a : child) a = NULL;
        }
    };
    
    WordDictionary() {
        root = new TrieNode();
    }
    
    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode *p = root;
        for (auto &a : word) {
            int i = a - 'a';
            if (!p->child[i]) p->child[i] = new TrieNode();
            p = p->child[i];
        }
        p->isWord = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return searchWord(word, root, 0);
    }
    
    bool searchWord(string &word, TrieNode *p, int i) {
        if (i == word.size()) return p->isWord;
        if (word[i] == '.') {
            for (auto &a : p->child) {
                if (a && searchWord(word, a, i + 1)) return true;
            }
            return false;
        } else {
            return p->child[word[i] - 'a'] && searchWord(word, p->child[word[i] - 'a'], i + 1);
        }
    }
    
private:
    TrieNode *root;
};


212. Word Search II 词语搜索之二 

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
You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
If the current candidate does not exist in all words prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.

在这题中只要实现字典树中的insert功能就行了，查找单词和前缀就没有必要了，然后DFS的思路跟之前那道Word Search 词语搜索基本相同


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

vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
    vector<string> res;
    if (words.empty() || board.empty() || board[0].empty()) return res;
    vector<vector<bool> > visit(board.size(), vector<bool>(board[0].size(), false));
    Trie T;
    for (auto &a : words) T.insert(a);
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (T.root->child[board[i][j] - 'a']) {
                search(board, T.root->child[board[i][j] - 'a'], i, j, visit, res);
            }
        }
    }
    return res;
}

void search(vector<vector<char> > &board, TrieNode *p, int i, int j, vector<vector<bool> > &visit, vector<string> &res) { 
    if (!p->str.empty()) {
        res.push_back(p->str);
        p->str.clear();
    }
    int d[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    visit[i][j] = true;
    for (auto &a : d) {
        int nx = a[0] + i, ny = a[1] + j;
        if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && !visit[nx][ny] && p->child[board[nx][ny] - 'a']) {
            search(board, p->child[board[nx][ny] - 'a'], nx, ny, visit, res);
        }
    }
    visit[i][j] = false;
}


213. House Robber II 打家劫舍之二  

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

这道题是之前那道House Robber 打家劫舍的拓展，现在房子排成了一个圆圈，则如果抢了第一家，就不能抢最后一家，因为首尾相连了，所以第一家和最后一家只能抢其中的一家，或者都不抢，那我们这里变通一下，如果我们把第一家和最后一家分别去掉，各算一遍能抢的最大值，然后比较两个值取其中较大的一个即为所求。那我们只需参考之前的House Robber 打家劫舍中的解题方法，然后调用两边取较大值

int rob(vector<int>& nums) {
    if (nums.size() <= 1) return nums.empty() ? 0 : nums[0];
    return max(rob(nums, 0, nums.size() - 1), rob(nums, 1, nums.size()));
}

int rob(vector<int> &nums, int left, int right) {
    if (right - left <= 1) return nums[left];
    vector<int> dp(right, 0);
    dp[left] = nums[left];
    dp[left + 1] = max(nums[left], nums[left + 1]);
    for (int i = left + 2; i < right; ++i) {
        dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
    }
    return dp.back();
}


214. Shortest Palindrome 最短回文串  

Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
For example:
Given "aacecaaa", return "aaacecaaa".
Given "abcd", return "dcbabcd".

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


215. Kth Largest Element in an Array 数组中第k大的数字

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.
Note: 
You may assume k is always valid, 1 ≤ k ≤ arrays length.

// solution 1
这道题让我们求数组中第k大的数字，怎么求呢，当然首先想到的是给数组排序，然后求可以得到第k大的数字。先看一种利用c++的STL中的集成的排序方法，不用我们自己实现，这样的话这道题只要两行就完事了

int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
}

// solution 2
int findKthLargest(vector<int>& nums, int k) {
    int left = 0, right = nums.size() - 1;
    while (true) {
        int pos = partition(nums, left, right);
        if (pos == k - 1) return nums[pos];
        else if (pos > k - 1) right = pos - 1;
        else left = pos + 1;
    }
}

int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[left], l = left + 1, r = right;
    while (l <= r) {
        if (nums[l] < pivot && nums[r] > pivot) {
            swap(nums[l++], nums[r--]);
        }
        if (nums[l] >= pivot) ++l;
        if (nums[r] <= pivot) --r;
    }
    swap(nums[left], nums[r]);
    return r;
}


216. Combination Sum III 组合之和之三 

Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
Ensure that numbers within the set are sorted in ascending order.

Example 1:
Input: k = 3, n = 7

Output:
[[1,2,4]]

Example 2:
Input: k = 3, n = 9

Output:
[[1,2,6], [1,3,5], [2,3,4]]

这道题题是组合之和系列的第三道题，跟之前两道Combination Sum 组合之和，Combination Sum II 组合之和之二都不太一样，那两道的联系比较紧密，变化不大，而这道跟它们最显著的不同就是这道题的个数是固定的，为k。个人认为这道题跟那道Combinations 组合项更相似一些，但是那道题只是排序，对k个数字之和又没有要求。所以实际上这道题是它们的综合体，两者杂糅到一起就是这道题的解法了，n是k个数字之和，如果n小于0，则直接返回，如果n正好等于0，而且此时out中数字的个数正好为k，说明此时是一个正确解，将其存入结果res中. 

vector<vector<int> > combinationSum3(int k, int n) {
    vector<vector<int> > res;
    vector<int> out;
    combinationSum3DFS(k, n, 1, out, res);
    return res;
}

void combinationSum3DFS(int k, int n, int level, vector<int> &out, vector<vector<int> > &res) {
    if (n < 0) return;
    if (n == 0 && out.size() == k) res.push_back(out);
    for (int i = level; i <= 9; ++i) {
        out.push_back(i);
        combinationSum3DFS(k, n - i, i + 1, out, res);
        out.pop_back();
    }
}


217. Contains Duplicate 包含重复值  

Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct. 

这道题不算难题，就是使用一个哈希表，遍历整个数组，如果哈希表里存在，返回false，如果不存在，则将其放入哈希表中. 

bool containsDuplicate(vector<int>& nums) {
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); ++i) {
        if (m.find(nums[i]) != m.end()) return true;
        ++m[nums[i]];
    }
    return false;
}      


218.  The Skyline Problem 天际线问题 

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ]. 

-The number of buildings in any input list is guaranteed to be in the range [0, 10000].
-The input list is already sorted in ascending order by the left x position Li.
-The output list must be sorted by the x position.
-There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]

类似的题，也就只有 Merge Intervals 合并区间了吧，但是与那题不同的是，这道题不是求被合并成的空间，而是求轮廓线的一些关键的转折点，这就比较复杂了，我们通过仔细观察题目中给的那个例子可以发现，要求的红点都跟每个小区间的左右区间点有密切的关系，而且进一步发现除了每一个封闭区间的最右边的结束点是楼的右边界点，其余的都是左边界点，而且每个红点的纵坐标都是当前重合处的最高楼的高度。这里用到了multiset数据结构，其好处在于其中的元素是按堆排好序的，插入新元素进去还是有序的，而且执行删除元素也可方便的将所有相同的元素删掉。这里为了区分左右边界，将左边界的高度存为负数，这样遇到左边界就存入堆中，遇到右边界就删掉，然后看当前状态有无改变，改变了话就把左边界和当前的高度存入结果中

vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int, int> > h, res;
    multiset<int> m;
    int pre = 0, cur = 0;

    for (auto &a : buildings) {
        h.push_back({a[0], -a[2]});
        h.push_back({a[1], a[2]});
    }

    sort(h.begin(), h.end());
    m.insert(0);

    for (auto &a : h) {
        if (a.second < 0) m.insert(-a.second);
        else m.erase(m.find(a.second));
        cur = *m.rbegin();
        if (cur != pre) {
            res.push_back({a.first, cur});
            pre = cur;
        }
    }
    return res;
}


219. Contains Duplicate II 包含重复值之二  

Given an array of integers and an integer k, find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k. 

这道题是之前那道Contains Duplicate 包含重复值的延伸，不同之处在于那道题只要我们判断下数组中是否有重复值，而这道题限制了数组中只许有一组重复的数字，而且他们坐标差不能超过k。那么我们首先需要一个哈希表，来记录每个数字和其坐标的映射，然后我们需要一个变量d来记录第一次出现重复数字的坐标差。由于题目要求只能有一组重复的数字，所以我们在遇到重复数字时，首先判断d是否已经存了值，如果d已经有值了，说明之前有过了重复数字，则直接返回false即可。如果没有，则此时给d附上值。在网上看到有些解法在这里就直接判断d和k的关系然后返回结果了，其实这样是不对的。因为题目要求只能有一组重复数，就是说如果后面又出现了重复数，就没法继续判断了。所以正确的做法应该是扫描完整个数组后在判断，先看d有没有存入结果，如果没有，则说明没出现过重复数， 返回false即可。如果d有值，再跟k比较，返回对应的结果

bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); ++i) {
        if (m.find(nums[i]) != m.end() && i - m[nums[i]] <= k) return true;
        else m[nums[i]] = i;
    }
    return false;
}


220. Contains Duplicate III 包含重复值之三  

Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k. 

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    map<long long, int> m;
    int j = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (i - j > k) m.erase(nums[j++]);
        auto a = m.lower_bound((long long)nums[i] - t);
        if (a != m.end() && abs(a->first - nums[i]) <= t) return true;
        m[nums[i]] = i;
    }
    return false;
}


221. Maximal Square 最大正方形  

Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1s and return its area.       
For example, given the following matrix:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.

// solution 1: 我们先来看一种brute force的方法，这种方法的机理就是就是把数组中每一个点都当成正方形的左顶点来向右下方扫描，来寻找最大正方形。具体的扫描方法是，确定了左顶点后，再往下扫的时候，正方形的竖边长度就确定了，只需要找到横边即可，这时候我们使用直方图的原理，从其累加值能反映出上面的值是否全为1，之前也有一道关于直方图的题Largest Rectangle in Histogram 直方图中最大的矩形 。通过这种方法我们就可以找出最大的正方形

int maximalSquare(vector<vector<char> >& matrix) {
    int res = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        vector<int> v(matrix[i].size(), 0);
        for (int j = i; j < matrix.size(); ++j) {
            for (int k = 0; k < matrix[j].size(); ++k) {
                if (matrix[j][k] == '1') ++v[k];
            }
            res = max(res, getSquareArea(v, j - i + 1));
        }
    }
    return res;
}

int getSquareArea(vector<int> &v, int k) {
    if (v.size() < k) return 0;
    int count = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] != k) count = 0; 
        else ++count;
        if (count == k) return k * k;
    }
    return 0;
}


// solution 2: 
我们还可以进一步的优化时间复杂度到O(n2)，做法是使用DP，简历一个二维dp数组，其中dp[i][j]表示到达(i, j)位置所能组成的最大正方形的边长。我们首先来考虑边界情况，也就是当i或j为0的情况，那么在首行或者首列中，必定有一个方向长度为1，那么就无法组成长度超过1的正方形，最多能组成长度为1的正方形，条件是当前位置为1。边界条件处理完了，再来看一般情况的递推公式怎么办，对于任意一点dp[i][j]，由于该点是正方形的右下角，所以该点的右边，下边，右下边都不用考虑，关心的就是左边，上边，和左上边。这三个位置的dp值suppose都应该算好的，还有就是要知道一点，只有当前(i, j)位置为1，dp[i][j]才有可能大于0，否则dp[i][j]一定为0。当(i, j)位置为1，此时要看dp[i-1][j-1], dp[i][j-1]，和dp[i-1][j]这三个位置，我们找其中最小的值，并加上1，就是dp[i][j]的当前值了，这个并不难想，毕竟不能有0存在，所以只能取交集，最后再用dp[i][j]的值来更新结果res的值即可

int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;
    int m = matrix.size(), n = matrix[0].size(), res = 0;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 || j == 0) dp[i][j] = matrix[i][j] - '0';
            else if (matrix[i][j] == '1') {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
            }
            res = max(res, dp[i][j]);
        }
    }
    return res * res;
}


222. Count Complete Tree Nodes 求完全二叉树的节点个数 

Given a complete binary tree, count the number of nodes.
Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

int countNodes(TreeNode* root) {
    int hLeft = 0, hRight = 0;
    TreeNode *pLeft = root, *pRight = root;

    while (pLeft) {
        ++hLeft;
        pLeft = pLeft->left;
    }

    while (pRight) {
        ++hRight;
        pRight = pRight->right;
    }

    if (hLeft == hRight) return pow(2, hLeft) - 1;
    return countNodes(root->left) + countNodes(root->right) + 1;
}


223. Rectangle Area 矩形面积  

Find the total area covered by two rectilinear rectangles in a2D plane.
Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
Assume that the total area is never beyond the maximum possible value of int. 

尝试先找出所有的不相交的情况，只有四种，一个矩形在另一个的上下左右四个位置不重叠，这四种情况下返回两个矩形面积之和。其他所有情况下两个矩形是有交集的，这时候我们只要算出长和宽，即可求出交集区域的大小，然后从两个巨型面积之和中减去交集面积就是最终答案。求交集区域的长和宽也不难，由于交集都是在中间，所以横边的左端点是两个矩形左顶点横坐标的较大值，右端点是两个矩形右顶点的较小值，同理，竖边的下端点是两个矩形下顶点纵坐标的较大值，上端点是两个矩形上顶点纵坐标的较小值

int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    int sum = (C - A) * (D - B) + (H - F) * (G - E);
    if (E >= C || F >= D || B >= H || A >= G) 
        return sum;
    return 
        sum - ((min(G, C) - max(A, E)) * (min(D, H) - max(B, F)));
}


224. Basic Calculator 基本计算器 

Implement a basic calculator to evaluate a simple expression string.
The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
You may assume that the given expression is always valid.

Some examples:
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23

int calculate(string s) {
    int res = 0, sign = 1, n = s.size();
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c >= '0') {
            int num = 0;
            while (i < n && s[i] >= '0') {
                num = 10 * num + s[i++] - '0';
            }
            res += sign * num;
            --i;
        } else if (c == '+') {
            sign = 1;
        } else if (c == '-') {
            sign = -1;
        } else if (c == '(') {
            st.push(res);
            st.push(sign);
            res = 0;
            sign = 1;
        } else if (c == ')') {
            res *= st.top(); st.pop();
            res += st.top(); st.pop();
        }
    }
    return res;
}


225. Implement Stack using Queues 用队列来实现栈 

Implement the following operations of a stack using queues.
push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
Notes:

You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue -- which means only push to back, pop from front, size, and is empty operations are valid.

只要实现对了push函数，后面三个直接调用队列的函数即可。这种方法的原理就是每次把新加入的数插到前头，这样队列保存的顺序和栈的顺序是相反的，它们的取出方式也是反的，那么反反得正，就是我们需要的顺序了。我们需要一个辅助队列tmp，把s的元素也逆着顺序存入tmp中，此时加入新元素x，再把tmp中的元素存回来，这样就是我们要的顺序了，其他三个操作也就直接调用队列的操作即可

class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        queue<int> tmp;
        while (!q.empty()) {
            tmp.push(q.front());
            q.pop();
        }
        q.push(x);
        while (!tmp.empty()) {
            q.push(tmp.front());
            tmp.pop();
        }
    }

    // Removes the element on top of the stack.
    void pop() {
        q.pop();
    }

    // Get the top element.
    int top() {
        return q.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return q.empty();
    }
    
private:
    queue<int> q;
};


226. Invert Binary Tree 翻转二叉树  

Invert a binary tree.
     4
   /   \
  2     7
 / \   / \
1   3 6   9
to

     4
   /   \
  7     2
 / \   / \
9   6 3   1

// solution 1: 
// 交换当前左右节点，并直接调用递归即可
TreeNode* invertTree(TreeNode* root) {
    if (!root) return NULL;
    TreeNode *tmp = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(tmp);
    return root;
}

// solution 2:
非递归的方法也不复杂，跟二叉树的层序遍历一样，需要用queue来辅助，先把根节点排入队列中，然后从队中取出来，交换其左右节点，如果存在则分别将左右节点在排入队列中，以此类推直到队列中木有节点了停止循环，返回root即可

TreeNode* invertTree(TreeNode* root) {
    if (!root) return NULL;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front(); q.pop();
        TreeNode *tmp = node->left;
        node->left = node->right;
        node->right = tmp;
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return root;
}


227. Basic Calculator II 基本计算器之二  

Implement a basic calculator to evaluate a simple expression string.
The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.
You may assume that the given expression is always valid.

Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5
Note: Do not use the eval built-in library function.

这道题是之前那道Basic Calculator 基本计算器的拓展，不同之处在于那道题的计算符号只有加和减，而这题加上了乘除，那么就牵扯到了运算优先级的问题，好在这道题去掉了括号，还适当的降低了难度，估计再出一道的话就该加上括号了。不管那么多，这道题先按木有有括号来处理，由于存在运算优先级，我们采取的措施是使用一个栈保存数字，如果该数字之前的符号是加或减，那么把当前数字压入栈中，注意如果是减号，则加入当前数字的相反数，因为减法相当于加上一个相反数。如果之前的符号是乘或除，那么从栈顶取出一个数字和当前数字进行乘或除的运算，再把结果压入栈中，那么完成一遍遍历后，所有的乘或除都运算完了，再把栈中所有的数字都加起来就是最终结果了

int calculate(string s) {
    int res = 0, d = 0;
    char sign = '+';
    stack<int> nums;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] >= '0') {
            d = d * 10 + s[i] - '0';
        }
        if ((s[i] < '0' && s[i] != ' ') || i == s.size() - 1) {
            if (sign == '+') nums.push(d);
            if (sign == '-') nums.push(-d);
            if (sign == '*' || sign == '/') {
                // int tmp = sign == '*' ? nums.top() * d : nums.top() / d;
                if(sign == '*')
                    int tmp = nums.top() * d; 
                else 
                    int tmp = nums.top() / d; 
                nums.pop();
                nums.push(tmp);
            }
            sign = s[i];
            d = 0;
        } 
    }

    while (!nums.empty()) {
        res += nums.top();
        nums.pop();
    }
    return res;
}


228. Summary Ranges 总结区间  

Given a sorted integer array without duplicates, return the summary of its ranges.
For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].

这道题给定我们一个有序数组，让我们总结区间，具体来说就是让我们找出连续的序列，然后首尾两个数字之间用个“->"来连接，那么我只需遍历一遍数组即可，每次检查下一个数是不是递增的，如果是，则继续往下遍历，如果不是了，我们还要判断此时是一个数还是一个序列，一个数直接存入结果，序列的话要存入首尾数字和箭头“->"。我们需要两个变量i和j，其中i是连续序列起始数字的位置，j是连续数列的长度，当j为1时，说明只有一个数字，若大于1，则是一个连续序列

vector<string> summaryRanges(vector<int>& nums) {
    vector<string> res;
    int i = 0, n = nums.size();
    while (i < n) {
        int j = 1;
        while (i + j < n && nums[i + j] - nums[i] == j) 
            ++j;
        if(j <= 1)
            res.push_back(nums[i]); 
        else 
            res.push_back(to_string(nums[i]) + "->" + to_string(nums[i + j - 1]));
        i += j;
    }
    return res;
}


229. Majority Element II 求众数之二  

Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space. 

这道题让我们求出现次数大于n/3的众数，而且限定了时间和空间复杂度，那么就不能排序，也不能使用哈希表，这么苛刻的限制条件只有一种方法能解了，那就是摩尔投票法 Moore Voting，这种方法在之前那道题Majority Element 求众数中也使用了。题目中给了一条很重要的提示，让我们先考虑可能会有多少个众数，经过举了很多例子分析得出，任意一个数组出现次数大于n/3的众数最多有两个，具体的证明我就不会了，我也不是数学专业的。那么有了这个信息，我们使用投票法的核心是找出两个候选众数进行投票，需要两遍遍历，第一遍历找出两个候选众数，第二遍遍历重新投票验证这两个候选众数是否为众数即可，选候选众数方法和前面那篇Majority Element 求众数一样，由于之前那题题目中限定了一定会有众数存在，故而省略了验证候选众数的步骤，这道题却没有这种限定，即满足要求的众数可能不存在，所以要有验证

vector<int> majorityElement(vector<int>& nums) {
    vector<int> res;
    int m = 0, n = 0, cm = 0, cn = 0;
    for (auto &a : nums) {
        if (a == m) ++cm;
        else if (a ==n) ++cn;
        else if (cm == 0) m = a, cm = 1;
        else if (cn == 0) n = a, cn = 1;
        else --cm, --cn;
    }
    cm = cn = 0;
    for (auto &a : nums) {
        if (a == m) ++cm;
        else if (a == n) ++cn;
    }
    if (cm > nums.size() / 3) res.push_back(m);
    if (cn > nums.size() / 3) res.push_back(n);
    return res;
}


230. Kth Smallest Element in a BST 二叉搜索树中的第K小的元素  

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
Note: 
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Hint:
Try to utilize the property of a BST.
What if you could modify the BST node's structure?
The optimal runtime complexity is O(height of BST).

提示是让我们用BST的性质来解题，最重要的性质是就是左<根<右，那么如果用中序遍历所有的节点就会得到一个有序数组。所以解题的关键还是中序遍历  

//solution 1: 
int kthSmallest(TreeNode* root, int k) {
    int cnt = 0;
    stack<TreeNode*> s;
    TreeNode *p = root;
    while (p || !s.empty()) {
        while (p) {
            s.push(p);
            p = p->left;
        }
        p = s.top(); s.pop();
        ++cnt;
        if (cnt == k) return p->val;
        p = p->right;
    }
    return 0;
}

// solution 2: 
int kthSmallest(TreeNode* root, int k) {
    return kthSmallestDFS(root, k);
}

int kthSmallestDFS(TreeNode* root, int &k) {
    if (!root) return -1;
    int val = kthSmallestDFS(root->left, k);
    if (!k) return val;
    if (!--k) return root->val;
    return kthSmallestDFS(root->right, k);
}


231. Power of Two 判断2的次方数  

Given an integer, write a function to determine if it is a power of two. 
Hint:
Could you solve it in O(1) time and using O(1) space?

那么我们很容易看出来2的次方数都只有一个1，剩下的都是0，所以我们的解题思路就有了，我们只要每次判断最低位是否为1，然后向右移位，最后统计1的个数即可判断是否是2的次方数 

bool isPowerOfTwo(int n) {
    int cnt = 0;
    while (n > 0) {
        cnt += (n & 1);
        n >>= 1;
    }
    return cnt == 1;
} 


如果一个数是2的次方数的话，根据上面分析，那么它的二进数必然是最高位为1，其它都为0，那么如果此时我们减1的话，则最高位会降一位，其余为0的位现在都为变为1，那么我们把两数相与，就会得到0 

bool isPowerOfTwo(int n) {
    return (n > 0) && (!(n & (n - 1)));
}

232. Implement Queue using Stacks 用栈来实现队列 

Implement the following operations of a queue using stacks.
push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Notes:

You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).

那么我们要用栈的先进后出的特性来模拟出队列的先进先出。那么怎么做呢，其实很简单，只要我们在插入元素的时候每次都都从前面插入即可，比如如果一个队列是1,2,3,4，那么我们在栈中保存为4,3,2,1，那么返回栈顶元素1，也就是队列的首元素，则问题迎刃而解。所以此题的难度是push函数，我们需要一个辅助栈tmp，把s的元素也逆着顺序存入tmp中，此时加入新元素x，再把tmp中的元素存回来，这样就是我们要的顺序了，其他三个操作也就直接调用栈的操作即可

class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        stack<int> tmp;
        while (!s.empty()) {
            tmp.push(s.top());
            s.pop();
        }
        s.push(x);
        while (!tmp.empty()) {
            s.push(tmp.top());
            tmp.pop();
        }
    }

    // Removes the element from in front of queue.
    void pop(void) {
        s.pop();
    }

    // Get the front element.
    int peek(void) {
        return s.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s.empty();
    }

private:
    stack<int> s;
};


233. Number of Digit One 数字1的个数 

Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.

Hint:
Beware of overflow.

这题实际上相当于一道找规律的题. 通过上面的列举我们可以发现，100以内的数字，除了10-19之间有11个‘1’之外，其余都只有1个。如果我们不考虑[10, 19]区间上那多出来的10个‘1’的话，那么我们在对任意一个两位数，十位数上的数字(加1)就代表1出现的个数，这时候我们再把多出的10个加上即可。比如56就有(5+1)+10=16个。如何知道是否要加上多出的10个呢，我们就要看十位上的数字是否大于等于2，是的话就要加上多余的10个'1'。那么我们就可以用(x+8)/10来判断一个数是否大于等于2。对于三位数也是一样，除了[110, 119]之间多出的10个数之外，其余的每10个数的区间都只有11个‘1’，那么还是可以用相同的方法来判断并累加1的个数. 

int countDigitOne(int n) {
    int res = 0, a = 1, b = 1;
    while (n > 0) {
        res += (n + 8) / 10 * a + (n % 10 == 1) * b;
        b += n % 10 * a;
        a *= 10;
        n /= 10;
    }
    return res;
}

234. Palindrome Linked List 回文链表  

Given a singly linked list, determine if it is a palindrome. Follow up: Could you do it in O(n) time and O(1) space?

我们使用快慢指针找中点的原理是fast和slow两个指针，每次快指针走两步，慢指针走一步，等快指针走完时，慢指针的位置就是中点。我们还需要用栈，每次慢指针走一步，都把值存入栈中，等到达中点时，链表的前半段都存入栈中了，由于栈的后进先出的性质，就可以和后半段链表按照回文对应的顺序比较了

bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;
    ListNode *slow = head, *fast = head;
    stack<int> s;
    s.push(head->val);

    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
        s.push(slow->val);
    }

    if (!fast->next) s.pop();
    while (slow->next) {
        slow = slow->next;
        int tmp = s.top(); s.pop();
        if (tmp != slow->val) return false;
    }
    return true;
}

// solution 2:
这道题的Follow Up让我们用O(1)的空间，那就是说我们不能使用stack了，那么如果代替stack的作用呢，用stack的目的是为了利用其后进先出的特点，好倒着取出前半段的元素。那么现在我们不用stack了，如何倒着取元素呢。我们可以在找到中点后，将后半段的链表翻转一下，这样我们就可以按照回文的顺序比较了

bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *last = slow->next, *pre = head;
    while (last->next) {
        ListNode *tmp = last->next;
        last->next = tmp->next;
        tmp->next = slow->next;
        slow->next = tmp;
    }

    while (slow->next) {
        slow = slow->next;
        if (pre->val != slow->val) return false;
        pre = pre->next;
    }
    return true;
}


235. Lowest Common Ancestor of a Binary Search Tree 二叉搜索树的最小共同父节点 

由于二叉搜索树的特点是左<根<右，所以根节点的值一直都是中间值，大于左子树的所有节点值，小于右子树的所有节点值，那么我们可以做如下的判断，如果根节点的值大于p和q之间的较大值，说明p和q都在左子树中，那么此时我们就进入根节点的左子节点继续递归，如果根节点小于p和q之间的较小值，说明p和q都在右子树中，那么此时我们就进入根节点的右子节点继续递归，如果都不是，则说明当前根节点就是最小共同父节点，直接返回即可. 

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return NULL;

    if (root->val > max(p->val, q->val)) 
        return lowestCommonAncestor(root->left, p, q);
    else if (root->val < min(p->val, q->val)) 
        return lowestCommonAncestor(root->right, p, q);
    else return root;
}

此题也有非递归的写法，用个while循环来代替递归调用即可，然后不停的更新当前的根节点，也能实现同样的效果 

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (true) {
        if (root->val > max(p->val, q->val)) root = root->left;
        else if (root->val < min(p->val, q->val)) root = root->right;
        else break;
    }      
    return root;
}


236. Lowest Common Ancestor of a Binary Tree 二叉树的最小共同父节点  

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.  

这道求二叉树的最小共同父节点的题是之前那道Lowest Common Ancestor of a Binary Search Tree 二叉搜索树的最小共同父节点的Follow Up。跟之前那题不同的地方是，这道题是普通是二叉树，不是二叉搜索树，所以就不能利用其特有的性质，所以我们只能在二叉树中来搜索p和q，然后从路径中找到最后一个相同的节点即为父节点  

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
   if (!root || p == root || q == root) return root;
   TreeNode *left = lowestCommonAncestor(root->left, p, q);
   TreeNode *right = lowestCommonAncestor(root->right, p , q);
   if (left && right) return root;
   return left ? left : right;
}


237. Delete Node in a Linked List 删除链表的节点  

Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list should become 1 -> 2 -> 4 after calling your function.

void deleteNode(ListNode* node) {
    node->val = node->next->val;
    ListNode *tmp = node->next;
    node->next = tmp->next;
    delete tmp;
}


238. Product of Array Except Self 除本身之外的数组之积  

Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
Solve it without division and in O(n).
For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)

这道题给定我们一个数组，让我们返回一个新数组，对于每一个位置上的数是其他位置上数的乘积，并且限定了时间复杂度O(n)，并且不让我们用除法。如果让用除法的话，那这道题就应该属于Easy，因为可以先遍历一遍数组求出所有数字之积，然后除以对应位置的上的数字。但是这道题禁止我们使用除法，那么我们只能另辟蹊径。我们想，对于某一个数字，如果我们知道其前面所有数字的乘积，同时也知道后面所有的数乘积，那么二者相乘就是我们要的结果，所以我们只要分别创建出这两个数组即可，分别从数组的两个方向遍历就可以分别创建出乘积累积数组. 

vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> fwd(n, 1), bwd(n, 1), res(n);
    for (int i = 0; i < n - 1; ++i) {
        fwd[i + 1] = fwd[i] * nums[i];
    }

    for (int i = n - 1; i > 0; --i) {
        bwd[i - 1] = bwd[i] * nums[i];
    }

    for (int i = 0; i < n; ++i) {
        res[i] = fwd[i] * bwd[i];
    }
    return res;
}

239. Sliding Window Maximum 滑动窗口最大值  

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
You may assume k is always valid, 1 ≤ k ≤ input arrays size.

Follow up:
Could you solve it in linear time?

大概思路是用双向队列保存数字的下标，遍历整个数组，如果此时队列的首元素是i - k的话，表示此时窗口向右移了一步，则移除队首元素。然后比较队尾元素和将要进来的值，如果小的话就都移除，然后此时我们把队首元素加入结果中即可. 

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res;
    deque<int> q;
    for (int i = 0; i < nums.size(); ++i) {
        if (!q.empty() && q.front() == i - k) q.pop_front();
        while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
        q.push_back(i);
        if (i >= k - 1) res.push_back(nums[q.front()]);
    }
    return res;
}


240. Search a 2D Matrix II 搜索一个二维矩阵之二   

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,
Consider the following matrix:
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
Given target = 5, return true.

左下角和右上角的数。左下角的18，往上所有的数变小，往右所有数增加，那么我们就可以和目标数相比较，如果目标数大，就往右搜，如果目标数小，就往左搜。这样就可以判断目标数是否存在。当然我们也可以把起始数放在右上角，往左和下搜，停止条件设置正确就行. 

bool searchMatrix(vector<vector<int> > &matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    if (target < matrix[0][0] || target > matrix.back().back()) return false;
    int x = matrix.size() - 1, y = 0;

    while (true) {
        if (matrix[x][y] > target) 
            --x;
        else if (matrix[x][y] < target) 
            ++y;
        else 
            return true;

        if (x < 0 || y >= matrix[0].size()) break;
    }
    return false;
}


241. Different Ways to Add Parentheses 添加括号的不同方式

Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, -and *.
Example 1
Input: "2-1-1"
((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]

Example 2
Input: "2*3-4*5"
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
Output: [-34, -14, -10, -10, 10]

这道题让给我们一个可能含有加减乘的表达式，让我们在任意位置添加括号，求出所有可能表达式的不同值。这道题跟之前的那道Unique Binary Search Trees II 独一无二的二叉搜索树之二用的方法一样，用递归来解，划分左右子树，递归构造. 

vector<int> diffWaysToCompute(string input) {
    vector<int> res;

    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
            vector<int> left = diffWaysToCompute(input.substr(0, i));
            vector<int> right = diffWaysToCompute(input.substr(i + 1));
            for (int j = 0; j < left.size(); ++j) {
                for (int k = 0; k < right.size(); ++k) {
                    if (input[i] == '+') res.push_back(left[j] + right[k]);
                    else if (input[i] == '-') res.push_back(left[j] - right[k]);
                    else res.push_back(left[j] * right[k]);
                }
            }
        }
    }

    if (res.empty()) res.push_back(atoi(input.c_str()));
    return res;
}


242. Valid Anagram 验证变位词  

Given two strings s and t, write a function to determine if t is an anagram of s.
For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.
Note:
You may assume the string contains only lowercase alphabets.

这不算一道难题，核心点就在于使用哈希表映射，我们还是用一个数组来代替哈希表，使用类似方法的题目有Minimum Window Substring 最小窗口子串，Isomorphic Strings 同构字符串，Longest Substring Without Repeating Characters 最长无重复子串 和 1.1 Unique Characters of a String 字符串中不同的字符。我们先判断两个字符串长度是否相同，不相同直接返回false。然后把s中所有的字符出现个数统计起来，存入一个大小为26的数组中，因为题目中限定了输入字符串为小写字母组成。然后我们再来统计t字符串，如果发现不匹配则返回false. 

bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    int m[26] = {0};
    for (int i = 0; i < s.size(); ++i) 
        ++m[s[i] - 'a'];
    for (int i = 0; i < t.size(); ++i) {
        if (--m[t[i] - 'a'] < 0) return false;
    }
    return true;
}


243. Shortest Word Distance 最短单词距离  

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.
For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.
Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

这道题让我们给了我们一个单词数组，又给定了两个单词，让我们求这两个单词之间的最小距离，限定了两个单词不同，而且都在数组中。我最先想到的方法比较笨，我首先想的是要用哈希表来做，建立每个单词和其所有出现位置数组的映射，但是后来想想，反正建立映射也要遍历一遍数组，我们还不如直接遍历一遍数组，直接把两个给定单词所有出现的位置分别存到两个数组里，然后我们在对两个数组进行两两比较更新结果. 

int shortestDistance(vector<string>& words, string word1, string word2) {
    vector<int> idx1, idx2;
    int res = INT_MAX;

    for (int i = 0; i < words.size(); ++i) {
        if (words[i] == word1) idx1.push_back(i);
        else if (words[i] == word2) idx2.push_back(i);
    }

    for (int i = 0; i < idx1.size(); ++i) {
        for (int j = 0; j < idx2.size(); ++j) {
            res = min(res, abs(idx1[i] - idx2[j]));
        }
    }
    return res;
}


上面的那种方法并不高效，我们其实需要遍历一次数组就可以了，我们用两个变量p1,p2初始化为-1，然后我们遍历数组，遇到单词1，就将其位置存在p1里，若遇到单词2，就将其位置存在p2里，如果此时p1, p2都不为-1了，那么我们更新结果

int shortestDistance(vector<string>& words, string word1, string word2) {
    int p1 = -1, p2 = -1, res = INT_MAX;
    for (int i = 0; i < words.size(); ++i) {
        if (words[i] == word1) p1 = i;
        if (words[i] == word2) p2 = i;
        if (p1 != -1 && p2 != -1) res = min(res, abs(p1 - p2));
    }
    return res;
}


244. Shortest Word Distance II 最短单词距离之二  

This is a follow up of Shortest Word Distance. The only difference is now you are given the list of words and your method will be called repeatedly many times with different parameters. How would you optimize it?
Design a class which receives a list of words in the constructor, and implements a method that takes two words word1 and word2 and return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.

Note:
You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.

这道题是之前那道Shortest Word Distance的拓展，不同的是这次我们需要多次调用求最短单词距离的函数，那么用之前那道题的解法二和三就非常不高效，而当时我们摒弃的解法一的思路却可以用到这里，我们用哈希表来建立每个单词和其所有出现的位置的映射，然后在找最短单词距离时，我们只需要取出该单词在哈希表中映射的位置数组进行两两比较即可         

class WordDistance {
public:
    WordDistance(vector<string>& words) {
        for (int i = 0; i < words.size(); ++i) {
            m[words[i]].push_back(i);
        }
    }

    int shortest(string word1, string word2) {
        int res = INT_MAX;
        for (int i = 0; i < m[word1].size(); ++i) {
            for (int j = 0; j < m[word2].size(); ++j) {
                res = min(res, abs(m[word1][i] - m[word2][j]));
            }
        }
        return res;
    }
    
private:
    unordered_map<string, vector<int> > m;
};


245. Shortest Word Distance III 最短单词距离之三    

This is a follow up of Shortest Word Distance. The only difference is now word1 could be the same as word2.
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list. word1 and word2 may be the same and they represent two individual words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
Given word1 = “makes”, word2 = “coding”, return 1.
Given word1 = "makes", word2 = "makes", return 3.
Note:
You may assume word1 and word2 are both in the list.

这道题还是让我们求最短单词距离，有了之前两道题Shortest Word Distance II和Shortest Word Distance的基础，就大大降低了题目本身的难度。这道题增加了一个条件，就是说两个单词可能会相同，所以在第一题中的解法的基础上做一些修改，我最先想的解法是基于第一题中的解法二，由于会有相同的单词的情况，那么p1和p2就会相同，这样结果就会变成0，显然不对，所以我们要对word1和word2是否的相等的情况分开处理，如果相等了，由于p1和p2会相同，所以我们需要一个变量t来记录上一个位置，这样如果t不为-1，且和当前的p1不同，我们可以更新结果，如果word1和word2不等，那么还是按原来的方法做

我们并不需要变量t来记录上一个位置，我们将p1初始化为数组长度，p2初始化为数组长度的相反数，然后当word1和word2相等的情况，我们用p1来保存p2的结果，p2赋为当前的位置i，这样我们就可以更新结果了，如果word1和word2不相等，则还跟原来的做法一样 

int shortestWordDistance(vector<string>& words, string word1, string word2) {
    int p1 = words.size(), p2 = -words.size(), res = INT_MAX;
    for (int i = 0; i < words.size(); ++i) {
        if (words[i] == word1) p1 = word1 == word2 ? p2 : i;
        if (words[i] == word2) p2 = i;
        res = min(res, abs(p1 - p2));
    }
    return res;
}


246. Strobogrammatic Number 对称数

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
Write a function to determine if a number is strobogrammatic. The number is represented as a string.
For example, the numbers "69", "88", and "818" are all strobogrammatic.

这道题定义了一种对称数，就是说一个数字旋转180度和原来一样，也就是倒过来看一样，比如609，倒过来还是609等等，满足这种条件的数字其实没有几个，只有0,1,8,6,9。这道题其实可以看做求回文数的一种特殊情况，我们还是用双指针来检测，那么首尾两个数字如果相等的话，那么只有它们是0,1,8中间的一个才行，如果它们不相等的话，必须一个是6一个是9，或者一个是9一个是6，其他所有情况均返回false. 

bool isStrobogrammatic(string num) {
    int l = 0, r = num.size() - 1;
    while (l <= r) {
        if (num[l] == num[r]) {
            if (num[l] != '1' && num[l] != '0' && num[l] != '8'){
                return false;
            }
        } else {
            if ((num[l] != '6' || num[r] != '9') && (num[l] != '9' || num[r] != '6')) {
                return false;
            }
        }
        ++l; --r;
    }
    return true;
}


247. Strobogrammatic Number II 对称数之二        

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"].
Hint:
Try to use recursion and notice that it should recurse with n - 2 instead of n - 1.

这道题是之前那道Strobogrammatic Number的拓展，那道题让我们判断一个数是否是对称数，而这道题让我们找出长度为n的所有的对称数，我们肯定不能一个数一个数的来判断，那样太不高效了，而且OJ肯定也不会答应。题目中给了提示说可以用递归来做，而且提示了递归调用n-2，而不是n-1。我们先来列举一下n为0,1,2,3,4的情况：
n = 0:   none
n = 1:   0, 1, 8
n = 2:   11, 69, 88, 96
n = 3:   101, 609, 808, 906, 111, 619, 818, 916, 181, 689, 888, 986
n = 4:   1001, 6009, 8008, 9006, 1111, 6119, 8118, 9116, 1691, 6699, 8698, 9696, 1881, 6889, 8888, 9886, 1961, 6969, 8968, 9966
我们注意观察n=0和n=2，可以发现后者是在前者的基础上，每个数字的左右增加了[1 1], [6 9], [8 8], [9 6]，看n=1和n=3更加明显，在0的左右增加[1 1]，变成了101, 在0的左右增加[6 9]，变成了609, 在0的左右增加[8 8]，变成了808, 在0的左右增加[9 6]，变成了906, 然后在分别在1和8的左右两边加那四组数，我们实际上是从m=0层开始，一层一层往上加的，需要注意的是当加到了n层的时候，左右两边不能加[0 0]，因为0不能出现在两位数及多位数的开头，在中间递归的过程中，需要有在数字左右两边各加上0的那种情况

vector<string> findStrobogrammatic(int n) {
    return find(n, n);
}

vector<string> find(int m, int n) {
    if (m == 0) return {""};
    if (m == 1) return {"0", "1", "8"};
    vector<string> t = find(m - 2, n), res;

    for (auto a : t) {
        if (m != n) res.push_back("0" + a + "0");
        res.push_back("1" + a + "1");
        res.push_back("6" + a + "9");
        res.push_back("8" + a + "8");
        res.push_back("9" + a + "6");
    }
    return res;
}


248. Strobogrammatic Number III 对称数之三   

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.
For example,
Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.
Note:
Because the range might be a large number, the low and high numbers are represented as string.

这道题是之前那两道Strobogrammatic Number II和Strobogrammatic Number的拓展，又增加了难度，让我们找到给定范围内的对称数的个数，我们当然不能一个一个的判断是不是对称数，我们也不能直接每个长度调用第二道中的方法，保存所有的对称数，然后再统计个数，这样OJ会提示内存超过允许的范围，所以我们的解法是基于第二道的基础上，不保存所有的结果，而是在递归中直接计数，根据之前的分析，需要初始化n=0和n=1的情况，然后在其基础上进行递归，递归的长度len从low到high之间遍历，然后我们看当前单词长度有没有达到len，如果达到了，我们首先要去掉开头是0的多位数，然后去掉长度和low相同但小于low的数，和长度和high相同但大于high的数，然后结果自增1，然后分别给当前单词左右加上那五对对称数，继续递归调用

int strobogrammaticInRange(string low, string high) {
    int res = 0;
    find(low, high, "", res);
    find(low, high, "0", res);
    find(low, high, "1", res);
    find(low, high, "8", res);
    return res;
}

void find(string low, string high, string w, int &res) {
    if (w.size() >= low.size() && w.size() <= high.size()) {
        if ((w.size() == low.size() && w.compare(low) < 0) || (w.size() == high.size() && w.compare(high) > 0)) {
            return;
        }
        if (!(w.size() > 1 && w[0] == '0')) ++res;
    }
    if (w.size() + 2 > high.size()) return;

    find(low, high, "0" + w + "0", res);
    find(low, high, "1" + w + "1", res);
    find(low, high, "6" + w + "9", res);
    find(low, high, "8" + w + "8", res);
    find(low, high, "9" + w + "6", res);
}


249. Group Shifted Strings 群组偏移字符串   

Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:
"abc" -> "bcd" -> ... -> "xyz"
Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"], 
Return:
[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]
Note: For the return value, each inner lists elements must follow the lexicographic order.

更加巧妙的利用偏移字符串的特点，那就是字符串的每个字母和首字符的相对距离都是相等的，比如abc和efg互为偏移，对于abc来说，b和a的距离是1，c和a的距离是2，对于efg来说，f和e的距离是1，g和e的距离是2。再来看一个例子，az和yx，z和a的距离是25，x和y的距离也是25(直接相减是-1，这就是要加26然后取余的原因)，那么这样的话，所有互为偏移的字符串都有个unique的距离差，我们根据这个来建立映射就可以很好的进行单词分组了. 

vector<vector<string>> groupStrings(vector<string>& strings) {
    vector<vector<string> > res;
    unordered_map<string, multiset<string>> m;

    for (auto a : strings) {
        string t = "";
        for (char c : a) {
            t += to_string((c + 26 - a[0]) % 26) + ",";
        }
        m[t].insert(a);
    }

    for (auto it = m.begin(); it != m.end(); ++it) {
        res.push_back(vector<string>(it->second.begin(), it->second.end()));
    }
    return res;
}


250. Count Univalue Subtrees 计数相同值子树的个数  

Given a binary tree, count the number of uni-value subtrees.
A Uni-value subtree means all nodes of the subtree have the same value.
For example:
Given binary tree,
              5
             / \
            1   5
           / \   \
          5   5   5
return 4.

符合条件的相同值的字数肯定是有叶节点的，而且叶节点也都相同(注意单独的一个叶节点也被看做是一个相同值子树)，那么我们可以从下往上check，采用后序遍历的顺序，左右根，我们还是递归调用函数，对于当前遍历到的节点，如果对其左右子节点分别递归调用函数，返回均为true的话，那么说明当前节点的值和左右子树的值都相同，那么又多了一棵树，所以结果自增1，然后返回当前节点值和给定值(其父节点值)是否相同，从而回归上一层递归调用    

int countUnivalSubtrees(TreeNode* root) {
    int res = 0;
    isUnival(root, -1, res);
    return res;
}

bool isUnival(TreeNode *root, int val, int &res) {
    if (!root) return true;
    if (!isUnival(root->left, root->val, res) | !isUnival(root->right, root->val, res)) {
        return false;
    }
    ++res;
    return root->val == val;
}


251. Flatten 2D Vector 压平二维向量  

Implement an iterator to flatten a 2d vector.
For example,
Given 2d vector =
[
  [1,2],
  [3],
  [4,5,6]
]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].

这道题让我们压平一个二维向量数组，并且实现一个iterator的功能，包括next和hasNext函数，那么最简单的方法就是将二维数组按顺序先存入到一个一维数组里，然后此时只要维护一个变量i来记录当前遍历到的位置，hasNext函数看当前坐标是否小于元素总数，next函数即为取出当前位置元素，坐标后移一位
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        for (auto a : vec2d) {
            v.insert(v.end(), a.begin(), a.end());
        }    
    }
    int next() {
        return v[i++];
    }
    bool hasNext() {
        return i < v.size();
    }
private:
    vector<int> v;
    int i = 0;
};

题目中的Follow up让我们用interator来做，C++中iterator不像Java中的那么强大，自己本身并没有包含next和hasNext函数，所以我们得自己来实现，我们将x定义为行的iterator，再用个end指向二维数组的末尾，定义一个整型变量y来指向列位置
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        x = vec2d.begin();
        end = vec2d.end();
    }
    int next() {
        return (*x)[y++];
    }
    bool hasNext() {
        while (x != end && y == (*x).size()) {
            ++x; 
            y = 0;
        }
        return x != end;
    }
private:
    vector<vector<int>>::iterator x, end;
    int y = 0;
};


252. Meeting Rooms 会议室  

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.
For example,
Given [[0, 30],[5, 10],[15, 20]],
return false.

这道题给了我们一堆会议的时间，问我们能不能同时参见所有的会议，这实际上就是求区间是否有交集的问题，我们可以先给所有区间排个序，用起始时间的先后来排，然后我们从第二个区间开始，如果开始时间早于前一个区间的结束时间，则说明会议时间有冲突，返回false，遍历完成后没有冲突，则返回true 

bool canAttendMeetings(vector<Interval>& intervals) {
    sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b){return a.start < b.start;});
    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i].start < intervals[i - 1].end) {
            return false;
        }
    }
    return true;
}


253. Meeting Rooms II 会议室之二  

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.
For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

这道题是之前那道Meeting Rooms的拓展，那道题只让我们是否能参加所有的会，也就是看会议之间有没有时间冲突，而这道题让我们求最少需要安排几个会议室，有时间冲突的肯定需要安排在不同的会议室。这道题有好几种解法，我们先来看使用map来做的，我们遍历时间区间，对于起始时间，映射值自增1，对于结束时间，映射值自减1，然后我们定义结果变量res，和房间数rooms，我们遍历map，时间从小到大，房间数每次加上映射值，然后更新结果res，遇到起始时间，映射是正数，则房间数会增加，如果一个时间是一个会议的结束时间，也是另一个会议的开始时间，则映射值先减后加仍为0，并不用分配新的房间，而结束时间的映射值为负数更不会增加房间数. 

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

第二种方法是用两个一维数组来做，分别保存起始时间和结束时间，然后各自排个序，我们定义结果变量res和结束时间指针endpos，然后我们开始遍历，如果当前起始时间小于结束时间指针的时间，则结果自增1，反之结束时间指针自增1，这样我们可以找出重叠的时间段，从而安排新的会议室        

int minMeetingRooms(vector<Interval>& intervals) {
    vector<int> starts, ends;
    int res = 0, endpos = 0;
    for (auto a : intervals) {
        starts.push_back(a.start);
        ends.push_back(a.end);
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    for (int i = 0; i < intervals.size(); ++i) {
        if (starts[i] < ends[endpos]) ++res;
        else ++endpos;
    }
    return res;
}


再来一看一种使用最小堆来解题的方法，这种方法先把所有的时间区间按照起始时间排序，然后新建一个最小堆，开始遍历时间区间，如果堆不为空，且首元素小于等于当前区间的起始时间，我们去掉堆中的首元素，把当前区间的结束时间压入堆，由于最小堆是小的在前面，那么假如首元素小于等于起始时间，说明上一个会议已经结束，可以用该会议室开始下一个会议了，所以不用分配新的会议室，遍历完成后堆中元素的个数即为需要的会议室的个数

int minMeetingRooms(vector<Interval>& intervals) {
    sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b){return a.start < b.start;});
    
    priority_queue<int, vector<int>, greater<int>> q;
    for (auto a : intervals) {
        if (!q.empty() && q.top() <= a.start) q.pop();
        q.push(a.end);
    }
    return q.size();
}


254. Factor Combinations 因子组合  

Numbers can be regarded as product of its factors. For example,
8 = 2 x 2 x 2;
  = 2 x 4.
Write a function that takes an integer n and return all possible combinations of its factors.
Note: 
Each combinations factors must be sorted ascending, for example: The factors of 2 and 6 is [2, 6], not [6, 2].
You may assume that n is always positive.
Factors should be greater than 1 and less than n.

Examples: 
input: 1
output: 
[]

input: 37
output: 
[]

input: 12
output:
[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]

这道题给了我们一个正整数n，让我们写出所有的因子相乘的形式，而且规定了因子从小到大的顺序排列，那么对于这种需要列出所有的情况的题目，通常都是用回溯法来求解的，由于题目中说明了1和n本身不能算其因子，那么我们可以从2开始遍历到n，如果当前的数i可以被n整除，说明i是n的一个因子，我们将其存入一位数组out中，然后递归调用n/i，此时不从2开始遍历，而是从i遍历到n/i，停止的条件是当n等于1时，如果此时out中有因子，我们将这个组合存入结果res中. 

vector<vector<int>> getFactors(int n) {
    vector<vector<int>> res;
    helper(n, 2, {}, res);
    return res;
}

void helper(int n, int start, vector<int> out, vector<vector<int>> &res) {
    if (n == 1) {
        if (out.size() > 1) res.push_back(out);
    } else {
        for (int i = start; i <= n; ++i) {
            if (n % i == 0) {
                out.push_back(i);
                helper(n / i, i, out, res);
                out.pop_back();
            }
        }
    }
}


255. Verify Preorder Sequence in Binary Search Tree 验证二叉搜索树的先序序列  

Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.
You may assume each number in the sequence is unique.
Follow up:
Could you do it using only constant space complexity?

中序遍历得到的结果就是有序数组，而先序遍历的结果就不是有序数组了，但是难道一点规律都没有了吗，其实规律还是有的，根据二叉搜索树的性质，当前节点的值一定大于其左子树中任何一个节点值，而且其右子树中的任何一个节点值都不能小于当前节点值，那么我们可以用这个性质来验证，举个例子，比如下面这棵二叉搜索树. 
     5
    / \
   2   6
  / \
 1   3

其先序遍历的结果是{5, 2, 1, 3, 6}, 我们先设一个最小值low，然后遍历数组，如果当前值小于这个最小值low，返回false，对于根节点，我们将其压入栈中，然后往后遍历，如果遇到的数字比栈顶元素小，说明是其左子树的点，继续压入栈中，直到遇到的数字比栈顶元素大，那么就是右边的值了，我们需要找到是哪个节点的右子树，所以我们更新low值并删掉栈顶元素，然后继续和下一个栈顶元素比较，如果还是大于，则继续更新low值和删掉栈顶，直到栈为空或者当前栈顶元素大于当前值停止，压入当前值，这样如果遍历完整个数组之前都没有返回false的话，最后返回true即可

bool verifyPreorder(vector<int>& preorder) {
    int low = INT_MIN;
    stack<int> s;
    for (auto a : preorder) {
        if (a < low) return false;
        while (!s.empty() && a > s.top()) {
            low = s.top(); s.pop();
        }
        s.push(a);
    }
    return true;
}

下面这种方法和上面的思路相同，为了使空间复杂度为常量，我们不能使用stack，所以我们直接修改preorder，将low值存在preorder的特定位置即可，前提是不能影响当前的遍历. 

bool verifyPreorder(vector<int>& preorder) {
    int low = INT_MIN, i = -1;
    for (auto a : preorder) {
        if (a < low) return false;
        while (i >= 0 && a > preorder[i]) {
            low = preorder[i--];
        }
        preorder[++i] = a;
    }
    return true;
}

256. Paint House 粉刷房子  

There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.
Note:
All costs are positive integers.

这道题说有n个房子，每个房子可以用红绿蓝三种颜色刷，每个房子的用每种颜色刷的花费都不同，限制条件是相邻的房子不能用相同的颜色来刷，现在让我们求刷完所有的房子的最低花费是多少。这题跟House Robber II和House Robber很类似，不过那题不是每个房子都抢，相邻的房子不抢，而这道题是每个房子都刷，相邻的房子不能刷同一种颜色。而Paint Fence那道题主要考察我们有多少种刷法，这几道题很类似，但都不一样，需要我们分别区分。但是它们的解题思想都一样，需要用动态规划Dynamic Programming来做，这道题我们需要维护一个二维的动态数组dp，其中dp[i][j]表示刷到第i+1房子用颜色j的最小花费，递推式为:

dp[i][j] = dp[i][j] + min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3])；

这个也比较好理解，如果当前的房子要用红色刷，那么上一个房子只能用绿色或蓝色来刷，那么我们要求刷到当前房子，且当前房子用红色刷的最小花费就等于当前房子用红色刷的钱加上刷到上一个房子用绿色和刷到上一个房子用蓝色的较小值，这样当我们算到最后一个房子时，我们只要取出三个累计花费的最小值即可.  

int minCost(vector<vector<int>>& costs) {
    if (costs.empty() || costs[0].empty()) return 0;
    vector<vector<int>> dp = costs;
    for (int i = 1; i < dp.size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            dp[i][j] += min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
        }
    }
    return min(min(dp.back()[0], dp.back()[1]), dp.back()[2]);
}

由于只有红绿蓝三张颜色，所以我们就可以分别写出各种情况，这样写可能比上面的写法更加一目了然一些  

int minCost(vector<vector<int>>& costs) {
    if (costs.empty() || costs[0].empty()) 
        return 0;
    vector<vector<int>> dp = costs;

    for (int i = 1; i < dp.size(); ++i) {
        dp[i][0] += min(dp[i - 1][1], dp[i - 1][2]);
        dp[i][1] += min(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] += min(dp[i - 1][0], dp[i - 1][1]);
    }
    return min(min(dp.back()[0], dp.back()[1]), dp.back()[2]);
}


257. Binary Tree Paths 二叉树路径  

Given a binary tree, return all root-to-leaf paths.
For example, given the following binary tree:
   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:  ["1->2->5", "1->3"]

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res;
    if (root) dfs(root, "", res);
    return res;
}
void dfs(TreeNode *root, string out, vector<string> &res) {
    out += to_string(root->val);
    if (!root->left && !root->right) res.push_back(out);
    else {
        if (root->left) dfs(root->left, out + "->", res);
        if (root->right) dfs(root->right, out + "->", res);
    }
}

258. Add Digits 加数字  

Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.
For example:
Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime?

int addDigits(int num) {
    while (num / 10 > 0) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        num = sum;
    }
    return num;
}

// follow up . 每9个一循环，所有大于9的数的树根都是对9取余，那么对于等于9的数对9取余就是0了，为了得到其本身，而且同样也要对大于9的数适用
int addDigits(int num) {
    return (num - 1) % 9 + 1;
}


259. 3Sum Smaller 三数之和较小值   

Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.
For example, given nums = [-2, 0, 1, 3], and target = 2.
Return 2. Because there are two triplets which sums are less than 2:
[-2, 0, 1]
[-2, 0, 3]
Follow up:
Could you solve it in O(n2) runtime?

最简单的方法就是穷举法，将所有的可能的三个数字的组合都遍历一遍，比较三数之和跟目标值之间的大小，小于的话则结果自增1
int threeSumSmaller(vector<int>& nums, int target) {
    int res = 0;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < int(nums.size() - 2); ++i) {
        int left = i + 1, right = nums.size() - 1, sum = target - nums[i];
        for (int j = left; j <= right; ++j) {
            for (int k = j + 1; k <= right; ++k) {
                if (nums[j] + nums[k] < sum) ++res;
            }
        }
    }
    return res;
}

题目中的Follow up让我们在O(n^2)的时间复杂度内实现，那么我们借鉴之前那两道题3Sum Closest和3Sum中的方法，采用双指针来做，这里面有个trick就是当判断三个数之和小于目标值时，此时结果应该加上right-left，以为数组排序了以后，如果加上num[right]小于目标值的话，那么加上一个更小的数必定也会小于目标值，然后我们将左指针右移一位，否则我们将右指针左移一位.  

int threeSumSmaller(vector<int>& nums, int target) {
    if (nums.size() < 3) return 0;
    int res = 0;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; ++i) {
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            if (nums[i] + nums[left] + nums[right] < target) {
                res += right - left;
                ++left;
            } else {
                --right;
            }
        }
    }
    return res;
}

260. Single Number III 单独的数字之三  

Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.
For example:
Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].
Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

这道题是之前那两道Single Number 单独的数字和 Single Number II 单独的数字之二的再次延伸，说实话，这类位操作Bit Manipulation的题，如果之前没有遇到过类似的题目，楞想是很难相出来的，于是我只能上网搜大神们的解法，发现还真是巧妙啊。这道题其实是很巧妙的利用了Single Number 单独的数字的解法，因为那道解法是可以准确的找出只出现了一次的数字，但前提是其他数字必须出现两次才行。而这题有两个数字都只出现了一次，那么我们如果能想办法把原数组分为两个小数组，不相同的两个数字分别在两个小数组中，这样分别调用Single Number 单独的数字的解法就可以得到答案。那么如何实现呢，首先我们先把原数组全部异或起来，那么我们会得到一个数字，这个数字是两个不相同的数字异或的结果，我们取出其中任意一位为‘1’的位，为了方便起见，我们用 a &= -a 来取出最右端为‘1’的位，然后和原数组中的数字挨个相与，那么我们要求的两个不同的数字就被分到了两个小组中，分别将两个小组中的数字都异或起来.  

vector<int> singleNumber(vector<int>& nums) {
        int x = 0;
        size_t len = A.size();
        int pos = 0;

        for (int i = 0; i < len; ++i)
            x ^= nums[i];
        // get the first bit position of these two elements that number is different
        for (int i = 0; i < 32; ++i) {
            if (x & (1 << i)) {   // 1<<0 == 1; 1 << 1 == 2; 
                pos = i;
                break;
            }
        }
        // 把所有数分成两拨， 和那first bit position相&为0的和不为0的；
        vector<int> results(2);
        for (int i = 0; i < len; ++i) {
            if (nums[i] & (1 << pos))   // 不为0的
                results[0] ^= nums[i];
            else                      // 为0的
                results[1] ^= nums[i];
        }
        return results;
}


261. Graph Valid Tree 图验证树  

Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.
For example:
Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.
Hint:
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return? Is this case a valid tree?
According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

这道题给了我们一个无向图，让我们来判断其是否为一棵树，我们知道如果是树的话，所有的节点必须是连接的，也就是说必须是连通图，而且不能有环，所以我们的焦点就变成了验证是否是连通图和是否含有环。我们首先用DFS来做，根据pair来建立一个图的结构，用邻接链表来表示，还需要一个一位数组v来记录某个节点是否被访问过，然后我们用DFS来搜索节点0，遍历的思想是，当DFS到某个节点，先看当前节点是否被访问过，如果已经被访问过，说明环存在，直接返回false，如果未被访问过，我们现在将其状态标记为已访问过，然后我们到邻接链表里去找跟其相邻的节点继续递归遍历，注意我们还需要一个变量pre来记录上一个节点，以免回到上一个节点，这样遍历结束后，我们就把和节点0相邻的节点都标记为true，然后我们在看v里面是否还有没被访问过的节点，如果有，则说明图不是完全连通的，返回false，反之返回true

bool validTree(int n, vector<pair<int, int>>& edges) {
    vector<vector<int>> g(n, vector<int>());
    vector<bool> v(n, false);
    for (auto a : edges) {
        g[a.first].push_back(a.second);
        g[a.second].push_back(a.first);
    }
    if (!dfs(g, v, 0, -1)) return false;
    for (auto a : v) {
        if (!a) return false;
    }
    return true;
}

bool dfs(vector<vector<int>> &g, vector<bool> &v, int cur, int pre) {
    if (v[cur]) return false;
    v[cur] = true;
    for (auto a : g[cur]) {
        if (a != pre) {
            if (!dfs(g, v, a, cur)) return false;
        }
    }
    return true;
}

下面我们来看BFS的解法，思路很相近，需要用queue来辅助遍历，这里我们没有用一维向量来标记节点是否访问过，而是用了一个set，如果遍历到一个节点，在set中没有，则加入set，如果已经存在，则返回false，还有就是在遍历邻接链表的时候，遍历完成后需要将节点删掉

bool validTree(int n, vector<pair<int, int>>& edges) {
    vector<unordered_set<int>> g(n, unordered_set<int>());
    unordered_set<int> v;
    queue<int> q;
    q.push(0);
    v.insert(0);

    for (auto a : edges) {
        g[a.first].insert(a.second);
        g[a.second].insert(a.first);
    }

    while (!q.empty()) {
        int t = q.front(); q.pop();
        for (auto a : g[t]) {
            if (v.find(a) != v.end()) return false;
            v.insert(a);
            q.push(a);
            g[a].erase(t);
        }
    }
    return v.size() == n;
}

我们再来看Union Find的方法，这种方法对于解决连通图的问题很有效，思想是我们遍历节点，如果两个节点相连，我们将其roots值连上，这样可以帮助我们找到环，我们初始化roots数组为-1，然后对于一个pair的两个节点分别调用find函数，得到的值如果相同的话，则说明环存在，返回false，不同的话，我们将其roots值union上

bool validTree(int n, vector<pair<int, int>>& edges) {
    vector<int> roots(n, -1);
    for (auto a : edges) {
        int x = find(roots, a.first), y = find(roots, a.second);
        if (x == y) return false;
        roots[x] = y;
    }
    return edges.size() == n - 1;
}

int find(vector<int> &roots, int i) {
    while (roots[i] != -1) i = roots[i];
    return i;
}


263. Ugly Number 丑陋数  

Write a program to check whether a given number is an ugly number.
Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.
Note that 1 is typically treated as an ugly number.

这道题让我们检测一个数是否为丑陋数，所谓丑陋数就是其质数因子只能是2,3,5。那么最直接的办法就是不停的除以这些质数，如果剩余的数字是1的话就是丑陋数了 

bool isUgly(int num) {
    while (num >= 2) {
        if (num % 2 == 0) num /= 2;
        else if (num % 3 == 0) num /= 3;
        else if (num % 5 == 0) num /= 5;
        else return false;
    }
    return num == 1;
}

264. Ugly Number II 丑陋数之二

Write a program to find the n-th ugly number.
Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note that 1 is typically treated as an ugly number.
Hint:
-The naive approach is to call isUgly for every number until you reach the nth one. Most numbers are not ugly. Try to focus your effort on generating only the ugly ones.
-An ugly number must be multiplied by either 2, 3, or 5 from a smaller ugly number.
-The key is how to maintain the order of the ugly numbers. Try a similar approach of merging from three sorted lists: L1, L2, and L3.
-Assume you have Uk, the kth ugly number. Then Uk+1 must be Min(L1 * 2, L2 * 3, L3 * 5).           
这道题是之前那道Ugly Number 丑陋数的延伸，这里让我们找到第n个丑陋数，还好题目中给了很多提示，基本上相当于告诉我们解法了，根据提示中的信息，我们知道丑陋数序列可以拆分为下面3个子列表：
(1) 1×2, 2×2, 3×2, 4×2, 5×2, …
(2) 1×3, 2×3, 3×3, 4×3, 5×3, …
(3) 1×5, 2×5, 3×5, 4×5, 5×5, …
仔细观察上述三个列表，我们可以发现每个子列表都是一个丑陋数分别乘以2,3,5，而要求的丑陋数就是从已经生成的序列中取出来的，我们每次都从三个列表中取出当前最小的那个加入序列

int nthUglyNumber(int n) {
    vector<int> res(1, 1);
    int i2 = 0, i3 = 0, i5 = 0;

    while (res.size() < n) {
        int m2 = res[i2] * 2, m3 = res[i3] * 3, m5 = res[i5] * 5;
        int mn = min(m2, min(m3, m5));
        if (mn == m2) ++i2;
        if (mn == m3) ++i3;
        if (mn == m5) ++i5;
        res.push_back(mn);
    }
    return res.back();
}

265. Paint House II 粉刷房子之二  

There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2]is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.
Note:
All costs are positive integers.

这道题是之前那道Paint House的拓展，那道题只让用红绿蓝三种颜色来粉刷房子，而这道题让我们用k种颜色，这道题不能用之前那题的解法，会TLE。这题的解法的思路还是用DP，但是在找不同颜色的最小值不是遍历所有不同颜色，而是用min1和min2来记录之前房子的最小和第二小的花费的颜色，如果当前房子颜色和min1相同，那么我们用min2对应的值计算，反之我们用min1对应的值，这种解法实际上也包含了求次小值的方法，感觉也是一种很棒的解题思路. 
下面这种解法不需要建立二维dp数组，直接用三个变量就可以保存需要的信息即可  

int minCostII(vector<vector<int>>& costs) {
    if (costs.empty() || costs[0].empty()) return 0;
    int min1 = 0, min2 = 0, idx1 = -1;
    for (int i = 0; i < costs.size(); ++i) {
        int m1 = INT_MAX, m2 = m1, id1 = -1;
        for (int j = 0; j < costs[i].size(); ++j) {
            int cost = costs[i][j] + (j == idx1 ? min2 : min1);
            if (cost < m1) {
                m2 = m1; m1 = cost; id1 = j;
            } else if (cost < m2) {
                m2 = cost;
            }
        }
        min1 = m1; min2 = m2; idx1 = id1;
    }
    return min1;
}


266. Palindrome Permutation 回文全排列  

Given a string, determine if a permutation of the string could form a palindrome.
For example,
"code" -> False, "aab" -> True, "carerac" -> True.
Hint:
Consider the palindromes of odd vs even length. What difference do you notice?
Count the frequency of each character.
If each character occurs even number of times, then it must be a palindrome. How about character which occurs odd number of times?

这道题让我们判断一个字符串的全排列有没有是回文字符串的，那么根据题目中的提示，我们分字符串的个数是奇偶的情况来讨论，如果是偶数的话，由于回文字符串的特性，每个字母出现的次数一定是偶数次，当字符串是奇数长度时，只有一个字母出现的次数是奇数，其余均为偶数，那么利用这个特性我们就可以解题，我们建立每个字母和其出现次数的映射，然后我们遍历哈希表，统计出现次数为奇数的字母的个数，那么只有两种情况是回文数，第一种是没有出现次数为奇数的字母，再一个就是字符串长度为奇数，且只有一个出现次数为奇数的字母. 

bool canPermutePalindrome(string s) {
    unordered_map<char, int> m;
    int cnt = 0;
    for (auto a : s) ++m[a];
    for (auto it = m.begin(); it != m.end(); ++it) {
        if (it->second % 2) ++cnt;
    }
    return cnt == 0 || (s.size() % 2 == 1 && cnt == 1);
}

那么我们再来看一种解法，这种方法用到了一个set，我们遍历字符串，如果某个字母不在set中，我们加入这个字母，如果字母已经存在，我们删除该字母，那么最终如果set中没有字母或是只有一个字母时，说明是回文串. 

bool canPermutePalindrome(string s) {
    set<char> t;
    for (auto a : s) {
        if (t.find(a) == t.end()) t.insert(a);
        else t.erase(a);
    }
    return t.empty() || t.size() == 1;
}


267. Palindrome Permutation II 回文全排列之二     

Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.
For example:
Given s = "aabb", return ["abba", "baab"].
Given s = "abc", return [].
Hint:
If a palindromic permutation exists, we just need to generate the first half of the string.
To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.

这道题是之前那道Palindrome Permutation的拓展，那道题只是让判断存不存在回文全排列，而这题让我们返回所有的回文全排列，此题给了我们充分的提示：如果回文全排列存在，我们只需要生成前半段字符串即可，后面的直接根据前半段得到。那么我们再进一步思考，由于回文字符串有奇偶两种情况，偶数回文串例如abba，可以平均分成前后半段，而奇数回文串例如abcba，需要分成前中后三段，需要注意的是中间部分只能是一个字符，那么我们可以分析得出，如果一个字符串的回文字符串要存在，那么奇数个的字符只能有0个或1个，其余的必须是偶数个，所以我们可以用哈希表来记录所有字符的出现个数，然后我们找出出现奇数次数的字符加入mid中，如果有两个或两个以上的奇数个数的字符，那么返回空集，我们对于每个字符，不管其奇偶，都将其个数除以2的个数的字符加入t中，这样做的原因是如果是偶数个，那么将其一般加入t中，如果是奇数，如果有1个，那么除以2是0，不会有字符加入t，如果是3个，那么除以2是1，取一个加入t。等我们获得了t之后，t是就是前半段字符，我们对其做全排列，每得到一个全排列，我们加上mid和该全排列的逆序列就是一种所求的回文字符串，这样我们就可以得到所有的回文全排列了. 

vector<string> generatePalindromes(string s) {
    vector<string> res;
    unordered_map<char, int> m;
    string t = "", mid = "";
    for (auto a : s) ++m[a];
    for (auto it : m) {
        if (it.second % 2 == 1) mid += it.first;
        t += string(it.second / 2, it.first);
        if (mid.size() > 1) return {};
    }
    permute(t, 0, mid, res);
    return res;
}

void permute(string &t, int start, string mid, vector<string> &res) {
    if (start >= t.size()) {
        res.push_back(t + mid + string(t.rbegin(), t.rend()));
    } 
    for (int i = start; i < t.size(); ++i) {
        if (i != start && t[i] == t[start]) continue;
        swap(t[i], t[start]);
        permute(t, start + 1, mid, res);
        swap(t[i], t[start]);
    }
}

268. Missing Number 丢失的数字  

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
For example,
Given nums = [0, 1, 3] return 2.
Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?

这道题给我们n个数字，是0到n之间的数但是有一个数字去掉了，让我们寻找这个数字，要求线性的时间复杂度和常数级的空间复杂度。那么最直观的一个方法是用等差数列的求和公式求出0到n之间所有的数字之和，然后再遍历数组算出给定数字的累积和，然后做减法，差值就是丢失的那个数字. 

int missingNumber(vector<int>& nums) {
    int sum = 0, n = nums.size();
    for (auto &a : nums) {
        sum += a;
    }
    return 0.5 * n * (n + 1) - sum;
}

这道题还可以用二分查找法来做，我们首先要对数组排序，然后我们用二分查找法算出中间元素的下标 

int missingNumber(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int left = 0, right = nums.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > mid) right = mid;
        else left = mid + 1;
    }
    return right;
}

269. Alien Dictionary 另类字典  

There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.
For example,
Given the following words in dictionary,
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
The correct order is: "wertf".
Note:
You may assume all letters are in lowercase.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.

这道题让给了我们一些按“字母顺序”排列的单词，但是这个字母顺序不是我们熟知的顺序，而是另类的顺序，让我们根据这些“有序”的单词来找出新的字母顺序，这实际上是一道有向图的问题，跟之前的那两道Course Schedule II和Course Schedule的解法很类似，我们先来看BFS的解法，我们需要一个set来保存我们可以推测出来的顺序关系. 

那么set就用来保存这些pair，我们还需要另一个set来保存所有出现过的字母，需要一个一维数组in来保存每个字母的入度，另外还要一个queue来辅助拓扑遍历，我们先遍历单词集，把所有字母先存入ch，然后我们每两个相邻的单词比较，找出顺序pair，然后我们根据这些pair来赋度，我们把ch中入度为0的字母都排入queue中，然后开始遍历，如果字母在set中存在，则将其pair中对应的字母的入度减1，若此时入度减为0了，则将对应的字母排入queue中并且加入结果res中，直到遍历完成，我们看结果res和ch中的元素个数是否相同，若不相同则说明可能有环存在，返回空字符串

string alienOrder(vector<string>& words) {
    set<pair<char, char> > s;
    unordered_set<char> ch;
    vector<int> in(256, 0);
    queue<char> q;
    string res = "";

    for (auto a : words) 
        ch.insert(a.begin(), a.end());
    for (int i = 0; i < words.size() - 1; ++i) {
        int mn = min(words[i].size(), words[i + 1].size()), j = 0;
        for (; j < min(words[i].size(), words[i + 1].size()); ++j) {
            if (words[i][j] != words[i + 1][j]) {
                s.insert(make_pair(words[i][j], words[i + 1][j]));
                break;
            }
        }
        if (j == mn && words[i].size() > words[i + 1].size()) return "";
    }

    for (auto a : s) ++in[a.second];
    for (auto a : ch) {
        if (in[a] == 0) {
            q.push(a);
            res += a;
        } 
    }

    while (!q.empty()) {
        char c = q.front(); q.pop();
        for (auto a : s) {
            if (a.first == c) {
                --in[a.second];
                if (in[a.second] == 0) {
                    q.push(a.second);
                    res += a.second;
                }
            }
        }
    }

    return res.size() == ch.size() ? res : "";
}


270. Closest Binary Search Tree Value 最近的二分搜索树的值 

Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.
Note:
Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.

实际我们可以利用二分搜索树的特点(左<根<右)来快速定位，由于根节点是中间值，我们在往下遍历时，我们根据目标值和根节点的值大小关系来比较，如果目标值小于节点值，则我们应该找更小的值，于是我们到左子树去找，反之我们去右子树找

int closestValue(TreeNode* root, double target) {
    int res = root->val;
    while (root) {
        if (abs(res - target) >= abs(root->val - target)) {
            res = root->val;
        }
        root = target < root->val ? root->left : root->right;
    }
    return res;
}

下面这种递归的写法和上面迭代的方法思路相同，都是根据二分搜索树的性质来优化查找，但是递归的写法用的是回溯法，先遍历到叶节点，然后一层一层的往回走，把最小值一层一层的运回来. 

int closestValue(TreeNode* root, double target) {
    int a = root->val;
    TreeNode *t = target < a ? root->left : root->right;
    if (!t) return a;
    int b = closestValue(t, target);
    return abs(a - target) < abs(b - target) ? a : b;
}

271. Encode and Decode Strings 加码解码字符串 

Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.  

这道题让我们给字符加码再解码，先有码再无码，然后题目中并没有限制我们加码的方法，那么我们的方法只要能成功的把有码变成无码就行了，具体变换方法我们自己设计。由于我们需要把一个字符串集变成一个字符串，然后把这个字符串再还原成原来的字符串集，最开始我想能不能在每一个字符串中间加个空格把它们连起来，然后再按空格来隔开，但是这种方法的问题是原来的一个字符串中如果含有空格，那么还原的时候就会被分隔成两个字符串，所以我们必须还要加上长度的信息，我们的加码方法是长度+"/"+字符串，比如对于"a","ab","abc"，我们就变成"1/a2/ab3/abc"，那么我们解码的时候就有规律可寻，先寻找"/"，然后之前的就是要取出的字符个数，从"/"后取出相应个数即可，以此类推直至没有"/"了，这样我们就得到高清无码的字符串集了

// Encodes a list of strings to a single string.
string encode(vector<string>& strs) {
    string res = "";
    for (auto a : strs) {
        res.append(to_string(a.size())).append("/").append(a);
    }
    return res;
}

// Decodes a single string to a list of strings.
vector<string> decode(string s) {
    vector<string> res;
    int i = 0;
    while (i < s.size()) {
        auto found = s.find("/", i);
        int len = atoi(s.substr(i, found).c_str());
        res.push_back(s.substr(found + 1, len));
        i = found + len + 1;
    }
    return res;
}

272. Closest Binary Search Tree Value II 最近的二分搜索树的值之二  

Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.
Note:
Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

直接在中序遍历的过程中完成比较，当遍历到一个节点时，如果此时结果数组不到k个，我们直接将此节点值加入res中，如果该节点值和目标值的差值的绝对值小于res的首元素和目标值差值的绝对值，说明当前值更靠近目标值，则将首元素删除，末尾加上当前节点值，反之的话说明当前值比res中所有的值都更偏离目标值，由于中序遍历的特性，之后的值会更加的遍历，所以此时直接返回最终结果即可. 

vector<int> closestKValues(TreeNode* root, double target, int k) {
    vector<int> res;
    inorder(root, target, k, res);
    return res;
}

void inorder(TreeNode *root, double target, int k, vector<int> &res) {
    if (!root) return;
    inorder(root->left, target, k, res);
    if (res.size() < k) res.push_back(root->val);
    else if (abs(root->val - target) < abs(res[0] - target)) {
        res.erase(res.begin());
        res.push_back(root->val);
    } else return;
    inorder(root->right, target, k, res);
}

// iterative method 
vector<int> closestKValues(TreeNode* root, double target, int k) {
    vector<int> res;
    stack<TreeNode*> s;
    TreeNode *p = root;
    while (p || !s.empty()) {
        while (p) {
            s.push(p);
            p = p->left;
        }
        p = s.top(); s.pop();
        if (res.size() < k) res.push_back(p->val);
        else if (abs(p->val - target) < abs(res[0] - target)) {
            res.erase(res.begin());
            res.push_back(p->val);
        } else break;
        p = p->right;
    }
    return res;
}

在来看一种利用最大堆来解题的方法，堆里保存的一个差值diff和节点值的pair，我们中序遍历二叉树(也可以用其他遍历方法)，然后对于每个节点值都计算一下和目标值之差的绝对值，由于最大堆的性质，diff大的自动拍到最前面，我们维护k个pair，如果超过了k个，就把堆前面大的pair删掉，最后留下的k个pair，我们将pair中的节点值取出存入res中返回即可. 

vector<int> closestKValues(TreeNode* root, double target, int k) {
    vector<int> res;
    priority_queue<pair<double, int>> q;
    inorder(root, target, k, q);
    while (!q.empty()) {
        res.push_back(q.top().second);
        q.pop();
    }
    return res;
}

void inorder(TreeNode *root, double target, int k, priority_queue<pair<double, int>> &q) {
    if (!root) return;
    inorder(root->left, target, k, q);
    q.push({abs(root->val - target), root->val});
    if (q.size() > k) q.pop();
    inorder(root->right, target, k, q);
} 


273. Integer to English Words 整数转为英文单词 

Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.
For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Hint:
Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.
Group the number by thousands (3 digits). You can write a helper function that takes a number less than 1000 and convert just that chunk to words.
There are many edge cases. What are some good test cases? Does your code work with input such as 0? Or 1000010? (middle chunk is zero and should not be printed out)

题目中给足了提示，首先告诉我们要3个一组的进行处理，而且题目中限定了输入数字范围为0到231 - 1之间，最高只能到billion位，3个一组也只需处理四组即可，那么我们需要些一个处理三个一组数字的函数，我们需要把1到19的英文单词都列出来，放到一个数组里，还要把20,30，... 到90的英文单词列出来放到另一个数组里，然后我们需要用写技巧，比如一个三位数n，百位数表示为n/100，后两位数一起表示为n%100，十位数表示为n%100/10，个位数表示为n%10，然后我们看后两位数是否小于20，小于的话直接从数组中取出单词，如果大于等于20的话，则分别将十位和个位数字的单词从两个数组中取出来。然后再来处理百位上的数字，还要记得加上Hundred。主函数中调用四次这个帮助函数，然后中间要插入"Thousand", "Million", "Billion"到对应的位置，最后check一下末尾是否有空格，把空格都删掉，返回的时候检查下输入是否为0，是的话要返回'Zero'. 

string numberToWords(int num) {
    string res = convertHundred(num % 1000);
    vector<string> v = {"Thousand", "Million", "Billion"};
    for (int i = 0; i < 3; ++i) {
        num /= 1000;
        res = num % 1000 ? convertHundred(num % 1000) + " " + v[i] + " " + res : res;
    }
    while (res.back() == ' ') res.pop_back();
    return res.empty() ? "Zero" : res;
}

string convertHundred(int num) {
    vector<string> v1 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> v2 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    string res;
    int a = num / 100, b = num % 100, c = num % 10;
    res = b < 20 ? v1[b] : v2[b / 10] + (c ? " " + v1[c] : "");
    if (a > 0) res = v1[a] + " Hundred" + (b ? " " + res : "");
    return res;
}


274. H-Index 求H指数  

Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researchers h-index.
According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."
For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.
Note: If there are several possible values for h, the maximum one is taken as the h-index.

这道题让我们求H指数，这个质数是用来衡量研究人员的学术水平的质数，定义为一个人的学术文章有n篇分别被引用了n次，那么H指数就是n。而且wiki上直接给出了算法，可以按照如下方法确定某人的H指数：1、将其发表的所有SCI论文按被引次数从高到低排序；2、从前往后查找排序后的列表，直到某篇论文的序号大于该论文被引次数。所得序号减一即为H指数. 

int hIndex(vector<int>& citations) {
    sort(citations.begin(), citations.end(), greater<int>());
    for (int i = 0; i < citations.size(); ++i) {
        if (i >= citations[i]) return i;
    }
    return citations.size();
}


275. H-Index II 求H指数之二

Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?
Hint:
Expected runtime complexity is in O(log n) and the input is sorted.

这题是之前那道H-Index 求H指数的拓展，输入数组是有序的，让我们在O(log n)的时间内完成计算，看到这个时间复杂度，应该有很敏锐的意识应该用二分查找法，我们最先初始化left和right为0和数组长度len-1，然后取中间值mid，比较citations[mid]和len-mid做比较，如果前者大，则right移到mid之前，反之right移到mid之后，终止条件是left>right，最后返回len-left即可      

int hIndex(vector<int>& citations) {
    int len = citations.size(), left = 0, right = len - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (citations[mid] == len - mid) return len - mid;
        else if (citations[mid] > len - mid) right = mid - 1;
        else left = mid + 1;
    }
    return len - left;
}

276. Paint Fence 粉刷篱笆

There is a fence with n posts, each post can be painted with one of the k colors.
You have to paint all the posts such that no more than two adjacent fence posts have the same color.
Return the total number of ways you can paint the fence.
Note:
n and k are non-negative integers.

这道题让我们粉刷篱笆，有n个部分需要刷，有k种颜色的油漆，规定了不能有超过两个的相同颜色涂的部分，问我们总共有多少种刷法。那么我们首先来分析一下，如果n=0的话，说明没有需要刷的部分，直接返回0即可，如果n为1的话，那么有几种颜色，就有几种刷法，所以应该返回k，当n=2时，k=2时，我们可以分两种情况来统计，一种是相邻部分没有相同的，一种相同部分有相同的颜色，那么对于没有相同的，对于第一个格子，我们有k种填法，对于下一个相邻的格子，由于不能相同，所以我们只有k-1种填法。而有相同部分颜色的刷法和上一个格子的不同颜色刷法相同，因为我们下一格的颜色和之前那个格子颜色刷成一样的即可，最后总共的刷法就是把不同和相同两个刷法加起来. 

int numWays(int n, int k) {
    if (n == 0) return 0;
    int same = 0, diff = k;

    for (int i = 2; i <= n; ++i) {
        int t = diff;
        diff = (same + diff) * (k - 1);
        same = t;
    }
    return same + diff;
}

277. Find the Celebrity 寻找名人  

Suppose you are at a party with n people (labeled from 0 to n - 1) and among them, there may exist one celebrity. The definition of a celebrity is that all the other n - 1people know him/her but he/she does not know any of them.
Now you want to find out who the celebrity is or verify that there is not one. The only thing you are allowed to do is to ask questions like: "Hi, A. Do you know B?" to get information of whether A knows B. You need to find out the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).
You are given a helper function bool knows(a, b) which tells you whether A knows B. Implement a function int findCelebrity(n), your function should minimize the number of calls to knows.
Note: There will be exactly one celebrity if he/she is in the party. Return the celebritys label if there is a celebrity in the party. If there is no celebrity, return -1.

这道题让我们在一群人中寻找名人，所谓名人就是每个人都认识他，他却不认识任何人，限定了只有1个或0个名人，给定了一个API函数，输入a和b，用来判断a是否认识b，让我们尽可能少的调用这个函数，来找出人群中的名人。我最先想的方法是建立个一维数组用来标记每个人的名人候选状态，开始均初始化为true，表示每个人都是名人候选人，然后我们一个人一个人的验证其是否为名人，对于候选者i，我们遍历所有其他人j，如果i认识j，或者j不认识i，说明i不可能是名人，那么我们标记其为false，然后验证下一个候选者，反之如果i不认识j，或者j认识i，说明j不可能是名人，标记之。对于每个候选者i，如果遍历了一圈而其候选者状态仍为true，说明i就是名人，返回即可，如果遍历完所有人没有找到名人，返回-1. 

int findCelebrity(int n) {
    vector<bool> candidate(n, true);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (candidate[i] && i != j) {
                if (knows(i, j) || !knows(j, i)) {
                    candidate[i] = false;
                    break;
                } else {
                    candidate[j] = false;
                }
            }
        }
        if (candidate[i]) return i;
    }
    return -1;
}

设定候选人res为0，原理是先遍历一遍，对于遍历到的人i，若候选人res认识i，则将候选人res设为i，完成一遍遍历后，我们来检测候选人res是否真正是名人，我们如果判断不是名人，则返回-1，如果并没有冲突，返回res

int findCelebrity(int n) {

    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (knows(res, i)) res = i;
    }

    for (int i = 0; i < n; ++i) {
        if (res != i && (knows(res, i) || !knows(i, res))) return -1;
    }
    return res;
}

278. First Bad Version 第一个坏版本  

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

其中有一个版本是坏的，而且后面跟着的全是坏的，给了一个API函数可以用来判定当前版本是否是坏的，让我们尽可能少的调用这个API，找出第一个坏版本。那么这种搜索题最先开始考虑用二分查找法把，效率高嘛。由于这题很有规律，好版本和坏版本一定有个边界，那么我们用二分法来找这个边界，对mid值调用API函数，如果是坏版本，说明边界在左边，则把mid赋值给right，如果是好版本，则说明边界在右边，则把mid+1赋给left，最后返回left即可。需要注意的是，OJ里有个坑，那就是如果left和right都特别大的话，那么left+right可能会溢出，我们的处理方法就是变成left + (right - left) / 2，很好的避免的溢出问题. 

int firstBadVersion(int n) {
    int left = 1, right = n;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (isBadVersion(mid)) right = mid;
        else left = mid + 1;
    }
    return left;
}

如果习惯了二分搜索法从0开始找，可以用下面的方法：  

int firstBadVersion(int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (isBadVersion(mid + 1)) right = mid;
        else left = mid + 1;
    }
    return right + 1;
}


279. Perfect Squares 完全平方数  

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.

这个种方法只初始化了第一个值为0，那么在循环里计算，每次增加一个dp数组的长度，里面那个for循环一次循环结束就算好下一个数由几个完全平方数组成，直到增加到第n+1个，返回即可，想更直观的看这两种DP方法的区别，建议每次循环后都打印出dp数字的值来观察其更新的顺序  

int numSquares(int n) {
    vector<int> dp(1, 0);
    while (dp.size() <= n) {
        int m = dp.size(), val = INT_MAX;
        for (int i = 1; i * i <= m; ++i) {
            val = min(val, dp[m - i * i] + 1);
        }
        dp.push_back(val);
    }
    return dp.back();
}

recursive遍历所有比n小的完全平方数，然后对n与完全平方数的差值递归调用函数，目的是不断更新最终结果，知道找到最小的那个

int numSquares(int n) {
    int res = n, num = 2;
    while (num * num <= n) {
        int a = n / (num * num), b = n % (num * num);
        res = min(res, a + numSquares(b));
        ++num;
    }
    return res;
}

280. Wiggle Sort 摆动排序  

Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].      

这道题让我们求摆动排序，跟Wiggle Sort II相比起来，这道题的条件宽松很多，只因为多了一个等号。由于等号的存在，当数组中有重复数字存在的情况时，也很容易满足题目的要求。这道题我们先来看一种时间复杂度为O(nlgn)的方法，思路是先给数组排个序，然后我们只要每次把第三个数和第二个数调换个位置，第五个数和第四个数调换个位置，以此类推直至数组末尾，这样我们就能完成摆动排序了 

void wiggleSort(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    if (nums.size() <= 2) return;
    for (int i = 2; i < nums.size(); i += 2) {
        swap(nums[i], nums[i - 1]);
    }
}

281. Zigzag Iterator 之字形迭代器  

Given two 1d vectors, implement an iterator to return their elements alternately.
For example, given two 1d vectors:
v1 = [1, 2]
v2 = [3, 4, 5, 6]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].
Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

由于题目中的Follow up让我们考虑将输入换成k个数组的情况，那么上面两种解法显然就不适用了，所以我们需要一种通解。我们可以采用queue加iterator的方法，用一个queue里面保存iterator的pair，在初始化的时候，有几个数组就生成几个pair放到queue中，每个pair保存该数组的首位置和尾位置的iterator，在next()函数中，我们取出queue队首的一个pair，如果当前的iterator不等于end()，我们将其下一个位置的iterator和end存入队尾，然后返回当前位置的值。在hasNext()函数中，我们只需要看queue是否为空即可

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if (!v1.empty()) q.push(make_pair(v1.begin(), v1.end()));
        if (!v2.empty()) q.push(make_pair(v2.begin(), v2.end()));
    }

    int next() {
        auto it = q.front().first, end = q.front().second;
        q.pop();
        if (it + 1 != end) q.push(make_pair(it + 1, end));
        return *it;
    }

    bool hasNext() {
        return !q.empty();
    }

private:
    queue<pair<vector<int>::iterator, vector<int>::iterator>> q;
};


282. Expression Add Operators 表达式增加操作符   

Given a string that contains only digits 0-9 and a target value, return all possibilities to add operators +, -, or * between the digits so they evaluate to the target value.
Examples: 
"123", 6 -> ["1+2+3", "1*2*3"] 
"232", 8 -> ["2*3+2", "2+3*2"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []

这道题给了我们一个只由数字组成的字符串，让我们再其中添加+,-或*号来形成一个表达式，该表达式的计算和为给定了target值，让我们找出所有符合要求的表达式来。题目中给的几个例子其实并不好，很容易让人误以为是必须拆成个位数字，其实不是的，比如"123", 15能返回"12+3"，说明连着的数字也可以。如果非要在过往的题中找一道相似的题，我觉得跟Combination Sum II 组合之和之二很类似。不过这道题要更复杂麻烦一些。还是用递归来解题，我们需要两个变量diff和curNum，一个用来记录将要变化的值，另一个是当前运算后的值，而且它们都需要用long long型的，因为字符串转为int型很容易溢出，所以我们用长整型。对于加和减，diff就是即将要加上的数和即将要减去的数的负值，而对于乘来说稍有些复杂，此时的diff应该是上一次的变化的diff乘以即将要乘上的数，有点不好理解，那我们来举个例子，比如2+3*2，即将要运算到乘以2的时候，上次循环的curNum = 5, diff = 3, 而如果我们要算这个乘2的时候，新的变化值diff应为3*2=6，而我们要把之前+3操作的结果去掉，再加上新的diff，即(5-3)+6=8，即为新表达式2+3*2的值，有点难理解，大家自己一步一步推算吧。
还有一点需要注意的是，如果输入为"000",0的话，容易出现以下的错误：
Wrong:["0+0+0","0+0-0","0+0*0","0-0+0","0-0-0","0-0*0","0*0+0","0*0-0","0*0*0","0+00","0-00","0*00","00+0","00-0","00*0","000"]
Correct：["0*0*0","0*0+0","0*0-0","0+0*0","0+0+0","0+0-0","0-0*0","0-0+0","0-0-0"]

我们可以看到错误的结果中有0开头的字符串出现，明显这不是数字，所以我们要去掉这些情况，过滤方法也很简单，我们只要判断长度大于1且首字符是‘0’的字符串，将其滤去即可


vector<string> addOperators(string num, int target) {
    vector<string> res;
    addOperatorsDFS(num, target, 0, 0, "", res);
    return res;
}

void addOperatorsDFS(string num, int target, long long diff, long long curNum, string out, vector<string> &res) {
    if (num.size() == 0 && curNum == target) {
        res.push_back(out);
    }
    for (int i = 1; i <= num.size(); ++i) {
        string cur = num.substr(0, i);
        if (cur.size() > 1 && cur[0] == '0') return;
        string next = num.substr(i);
        if (out.size() > 0) {
            addOperatorsDFS(next, target, stoll(cur), curNum + stoll(cur), out + "+" + cur, res);
            addOperatorsDFS(next, target, -stoll(cur), curNum - stoll(cur), out + "-" + cur, res);
            addOperatorsDFS(next, target, diff * stoll(cur), (curNum - diff) + diff * stoll(cur), out + "*" + cur, res);
        } else {
            addOperatorsDFS(next, target, stoll(cur), stoll(cur), cur, res);
        }
    }
}


283. Move Zeroes 移动零

Given an array nums, write a function to move all 0 to the end of it while maintaining the relative order of the non-zero elements.
For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].
Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.

这道题让我们将一个给定数组中所有的0都移到后面，把非零数前移，要求不能改变非零数的相对应的位置关系，而且不能拷贝额外的数组，那么只能用替换法in-place来做，需要用两个指针，一个不停的向后扫，找到非零位置，然后和前面那个指针交换位置即可

void moveZeroes(vector<int>& nums) {
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        if (nums[i]) {
            swap(nums[i], nums[j++]);
        }
    }
}


284. Peeking Iterator 顶端迭代器

Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() operation -- it essentially peek() at the element that will be returned by the next call to next().
Here is an example. Assume that the iterator is initialized to the beginning of the list: [1, 2, 3].
Call next() gets you 1, the first element in the list.
Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.
You call next() the final time and it returns 3, the last element. Calling hasNext() after that should return false.
Hint:
-Think of "looking ahead". You want to cache the next element.
-Is one variable sufficient? Why or why not?
-Test your design with call order of peek() before next() vs next() before peek().
-For a clean implementation, check out Google guava library source code.
Follow up: How would you extend your design to be generic and work with all types, not just integer?

这道题让我们实现一个顶端迭代器，在普通的迭代器类Iterator的基础上增加了peek的功能，就是返回查看下一个值的功能，但是不移动指针，next()函数才会移动指针，那我们可以定义一个变量专门来保存下一个值，再用一个bool型变量标记是否保存了下一个值，再调用原来的一些成员函数，就可以实现这个顶端迭代器了

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        _flag = false;
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        if (!_flag) {
            _value = Iterator::next();
            _flag = true;
        }
        return _value;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        if (!_flag) return Iterator::next();
        _flag = false;
        return _value;
    }

    bool hasNext() const {
        if (_flag) return true;
        if (Iterator::hasNext()) return true;
        return false;
    }
private:
    int _value;
    bool _flag;
};


285. Inorder Successor in BST 二叉搜索树中的中序后继节点

Given a binary search tree and a node in it, find the in-order successor of that node in the BST.
Note: If the given node has no in-order successor in the tree, return null.

这种方法充分地利用到了BST的性质，我们首先看根节点值和p节点值的大小，如果根节点值大，说明p节点肯定在左子树中，那么此时我们先将res赋为root，然后root移到其左子节点，循环的条件是root存在，我们再比较此时root值和p节点值的大小，如果还是root值大，我们重复上面的操作，如果p节点值，那么我们将root移到其右子节点，这样当root为空时，res指向的就是p的后继节点. 

TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode *res = NULL;
    while (root) {
        if (root->val > p->val) {
            res = root;
            root = root->left;
        } else root = root->right;
    }
    return res;
}


286. Walls and Gates 墙和门

You are given a m x n 2D grid initialized with these three possible values.
-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

For example, given the 2D grid:
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4

这道题类似一种迷宫问题，规定了-1表示墙，0表示门，让求每个点到门的最近的曼哈顿距离，这其实类似于求距离场Distance Map的问题，那么我们先考虑用DFS来解，思路是，我们搜索0的位置，每找到一个0，以其周围四个相邻点为起点，开始DFS遍历，并带入深度值1，如果遇到的值大于当前深度值，我们将位置值赋为当前深度值，并对当前点的四个相邻点开始DFS遍历，注意此时深度值需要加1，这样遍历完成后，所有的位置就被正确地更新了. 我们将rooms[i][j]和val的大小判断放入起始判断条件中，这样我们就可以以门的位置开始调用DFS函数了 

void wallsAndGates(vector<vector<int>>& rooms) {
    for (int i = 0; i < rooms.size(); ++i) {
        for (int j = 0; j < rooms[i].size(); ++j) {
            if (rooms[i][j] == 0) {
                dfs(rooms, i, j, 0);
            }
        }
    }
}

void dfs(vector<vector<int>> &rooms, int i, int j, int val) {
    if (i < 0 || i >= rooms.size() || j < 0 || j >= rooms[i].size() || rooms[i][j] < val) return;
    rooms[i][j] = val;
    dfs(rooms, i + 1, j, val + 1);
    dfs(rooms, i - 1, j, val + 1);
    dfs(rooms, i, j + 1, val + 1);
    dfs(rooms, i, j - 1, val + 1);
}

那么下面我们再来看BFS的解法，却要借助queue，我们首先把门的位置都排入queue中，然后开始循环，对于门位置的四个相邻点，我们判断其是否在矩阵范围内，并且位置值是否大于上一位置的值加1，如果满足这些条件，我们将当前位置赋为上一位置加1，并将次位置排入queue中，这样等queue中的元素遍历完了，所有位置的值就被正确地更新了. 

void wallsAndGates(vector<vector<int>>& rooms) {
    queue<pair<int, int>> q;
    vector<vector<int>> dirs{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    for (int i = 0; i < rooms.size(); ++i) {
        for (int j = 0; j < rooms[i].size(); ++j) {
            if (rooms[i][j] == 0) q.push({i, j});   
        }
    }

    while (!q.empty()) {
        int i = q.front().first, j = q.front().second; q.pop();
        for (int k = 0; k < dirs.size(); ++k) {
            int x = i + dirs[k][0], y = j + dirs[k][1];
            if (x < 0 || x >= rooms.size() || y < 0 || y >= rooms[0].size() || rooms[x][y] < rooms[i][j] + 1) continue;
            rooms[x][y] = rooms[i][j] + 1;
            q.push({x, y});
        }
    }
}


287. Find the Duplicate Number 寻找重复数  

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate element must exist. Assume that there is only one duplicate number, find the duplicate one.
Note:
You must not modify the array (assume the array is read only).
You must use only constant extra space.
Your runtime complexity should be less than O(n2).

题目要求我们不能改变原数组，即不能给原数组排序，又不能用多余空间，那么哈希表神马的也就不用考虑了，又说时间小于O(n2)，也就不能用brute force的方法，那我们也就只能考虑用二分搜索法了，我们在区别[1, n]中搜索，首先求出中点mid，然后遍历整个数组，统计所有小于等于mid的数的个数，如果个数大于mid，则说明重复值在[mid+1, n]之间，反之，重复值应在[1, mid-1]之间，然后依次类推，直到搜索完成，此时的low就是我们要求的重复值

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


O(n)解法，其核心思想快慢指针在之前的题目Linked List Cycle II中就有应用，这里应用的更加巧妙一些，由于题目限定了区间[1,n]，所以可以巧妙的利用坐标和数值之间相互转换，而由于重复数字的存在，那么一定会形成环，我们用快慢指针可以找到环并确定环的起始位置

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


288. Unique Word Abbreviation 独特的单词缩写 

An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:
a) it                      --> it    (no abbreviation)
b) d|o|g                   --> d1g
c) i|nternationalizatio|n  --> i18n
d) l|ocalizatio|n          --> l10n
Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A words abbreviation is unique if no other word from the dictionary has the same abbreviation.
Example: 
Given dictionary = [ "deer", "door", "cake", "card" ]
isUnique("dear") -> false
isUnique("cart") -> true
isUnique("cane") -> false
isUnique("make") -> true

从上面三个例子我们可以看出，当缩写一致的时候，字典中的单词均和给定单词相同时，那么返回true。我们需要用哈希表来建立缩写形式和其对应的单词的映射，把所有缩写形式的相同单词放到一个set中，然后我们在判断是否unique的时候只需要看给定单词的缩写形式的set里面该单词的个数是否和set中的元素总数相同，相同的话就是上面的第二种情况，返回true。需要注意的是由于set中不能有重复值，所有上面第二种情况只会有一个door存在set里，但是并不影响判断结果. 

unordered_map<string, set<string>> m;

ValidWordAbbr(vector<string> &dictionary) {
    for (auto a : dictionary) {
        string k = a[0] + to_string(a.size() - 2) + a.back();
        m[k].insert(a);
    }
}

bool isUnique(string word) {
    string k = word[0] + to_string(word.size() - 2) + word.back();
    return m[k].count(word) == m[k].size();
}


289. Game of Life 生命游戏   

According to the Wikipedias article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):
Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state.
Follow up: 
Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?

这道题是有名的康威生命游戏, 而我又是第一次听说这个东东，这是一种细胞自动机，每一个位置有两种状态，1为活细胞，0为死细胞，对于每个位置都满足如下的条件：
1. 如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡
2. 如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活
3. 如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡
4. 如果死细胞周围正好有三个活细胞，则该位置死细胞复活
由于题目中要求我们用置换方法in-place来解题，所以我们就不能新建一个相同大小的数组，那么我们只能更新原有数组，但是题目中要求所有的位置必须被同时更新，但是在循环程序中我们还是一个位置一个位置更新的，那么当一个位置更新了，这个位置成为其他位置的neighbor时，我们怎么知道其未更新的状态呢，我们可以使用状态机转换：
状态0： 死细胞转为死细胞
状态1： 活细胞转为活细胞
状态2： 活细胞转为死细胞
状态3： 死细胞转为活细胞
最后我们对所有状态对2取余，那么状态0和2就变成死细胞，状态1和3就是活细胞，达成目的。我们先对原数组进行逐个扫描，对于每一个位置，扫描其周围八个位置，如果遇到状态1或2，就计数器累加1，扫完8个邻居，如果少于两个活细胞或者大于三个活细胞，而且当前位置是活细胞的话，标记状态2，如果正好有三个活细胞且当前是死细胞的话，标记状态3。完成一遍扫描后再对数据扫描一遍，对2取余变成我们想要的结果


void gameOfLife(vector<vector<int> >& board) {
    int m = board.size(), n = m ? board[0].size() : 0;
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int cnt = 0;
            for (int k = 0; k < 8; ++k) {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && (board[x][y] == 1 || board[x][y] == 2)) {
                    ++cnt;
                }
            }
            if (board[i][j] && (cnt < 2 || cnt > 3)) board[i][j] = 2;
            else if (!board[i][j] && cnt == 3) board[i][j] = 3;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] %= 2;
        }
    }
}


290. Word Pattern 词语模式  

Given a pattern and a string str, find if str follows the same pattern.
Examples:
-pattern = "abba", str = "dog cat cat dog" should return true.
-pattern = "abba", str = "dog cat cat fish" should return false.
-pattern = "aaaa", str = "dog cat cat dog" should return false.
-pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
-Both pattern and str contains only lowercase alphabetical letters.
-Both pattern and str do not have leading or trailing spaces.
-Each word in str is separated by a single space.
-Each letter in pattern must map to a word with length that is at least 1.

当然这道题也可以用两个哈希表来完成，分别将字符和单词都映射到当前的位置，那么我们在遇到新字符和单词时，首先看两个哈希表是否至少有一个映射存在，如果有一个存在，则比较两个哈希表映射值是否相同，不同则返回false。如果两个表都不存在映射，则同时添加两个映射

bool wordPattern(string pattern, string str) {
    unordered_map<char, int> m1;
    unordered_map<string, int> m2;
    istringstream in(str);
    int i = 0;

    for (string word; in >> word; ++i) {
        if (m1.find(pattern[i]) != m1.end() || m2.find(word) != m2.end()) {
            if (m1[pattern[i]] != m2[word]) return false;
        } else {
            m1[pattern[i]] = m2[word] = i + 1;
        }
    }
    return i == pattern.size();
}


291. Word Pattern II 词语模式之二     

Given a pattern and a string str, find if str follows the same pattern.
Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.
Examples:
pattern = "abab", str = "redblueredblue" should return true.
pattern = "aaaa", str = "asdasdasdasd" should return true.
pattern = "aabb", str = "xyzabcxzyabc" should return false.

这道题是之前那道Word Pattern的拓展，之前那道题词语之间都有空格隔开，这样我们可以一个单词一个单词的读入，然后来判断是否符合给定的特征，而这道题没有空格了，那么难度就大大的增加了，因为我们不知道对应的单词是什么，所以得自行分开，那么我们可以用回溯法来生成每一种情况来判断，我们还是需要用哈希表来建立模式字符和单词之间的映射，我们还需要用变量p和r来记录当前递归到的模式字符和单词串的位置，在递归函数中，如果p和r分别等于模式字符串和单词字符串的长度，说明此时匹配成功结束了，返回ture，反之如果一个达到了而另一个没有，说明匹配失败了，返回false。如果都不满足上述条件的话，我们取出当前位置的模式字符，然后从单词串的r位置开始往后遍历，每次取出一个单词，如果模式字符已经存在哈希表中，而且对应的单词和取出的单词也相等，那么我们再次调用递归函数在下一个位置，如果返回true，那么我们就返回true。反之如果该模式字符不在哈希表中，我们要看有没有别的模式字符已经映射了当前取出的单词，如果没有的话，我们建立新的映射，并且调用递归函数，注意如果递归函数返回false了，我们要在哈希表中删去这个映射

使用了set，而使用其的原因也是为了记录所有和模式字符建立过映射的单词，这样我们就不用每次遍历哈希表了，只要在set中查找取出的单词是否存在，如果存在了则跳过后面的处理，反之则进行和上面相同的处理，注意还要在set中插入新的单词，最后也要同时删除掉

unordered_map<char, string> m;
unordered_set<string> s;

bool wordPatternMatch(string pattern, string str) {
    if (pattern.empty()) return str.empty();
    if (m.count(pattern[0])) {
        string t = m[pattern[0]];
        if (t.size() > str.size() || str.substr(0, t.size()) != t) return false;
        if (wordPatternMatch(pattern.substr(1), str.substr(t.size()))) return true;
    } else {
        for (int i = 1; i <= str.size(); ++i) {
            if (s.count(str.substr(0, i))) 
                continue;

            m[pattern[0]] = str.substr(0, i);
            s.insert(str.substr(0, i));

            if (wordPatternMatch(pattern.substr(1), str.substr(i))) 
                return true;
            m.erase(pattern[0]);
            s.erase(str.substr(0, i));
        }
    }
    return false;
}


292. Nim Game 尼姆游戏   

You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones.
Both of you are very clever and have optimal strategies for the game. Write a function to determine whether you can win the game given the number of stones in the heap.
For example, if there are 4 stones in the heap, then you will never win the game: no matter 1, 2, or 3 stones you remove, the last stone will always be removed by your friend.

有史以来最少代码量的解法，虽然解法很简单，但是题目还是蛮有意思的，题目说给我们一堆石子，每次可以拿一个两个或三个，两个人轮流拿，拿到最后一个石子的人获胜，现在给我们一堆石子的个数，问我们能不能赢。那么我们就从最开始分析，由于是我们先拿，那么3个以内(包括3个)的石子，我们直接赢，如果共4个，那么我们一定输，因为不管我们取几个，下一个人一次都能取完。由此我们可以发现规律，只要是4的倍数个，我们一定会输，所以对4取余即可

bool canWinNim(int n) {
    return n % 4;
}


293. Flip Game 翻转游戏

You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip twoconsecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.
Write a function to compute all possible states of the string after one valid move.
For example, given s = "++++", after one move, it may become one of the following states:
[
  "--++",
  "+--+",
  "++--"
]
If there is no valid move, return an empty list [].

这道题让我们把相邻的两个++变成--，真不是一道难题，我们就从第二个字母开始遍历，每次判断当前字母是否为+，和之前那个字母是否为+，如果都为加，则将翻转后的字符串存入结果中即可 

vector<string> generatePossibleNextMoves(string s) {
    vector<string> res;
    for (int i = 1; i < s.size(); ++i) {
        if (s[i] == '+' && s[i - 1] == '+') {
            res.push_back(s.substr(0, i - 1) + "--" + s.substr(i + 1));
        }
    }
    return res;
}

294. Flip Game 翻转游戏之二  

You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip twoconsecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.
Write a function to determine if the starting player can guarantee a win.
For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

这道题是之前那道Flip Game的拓展，让我们判断先手的玩家是否能赢，那么我们可以穷举所有的情况，用回溯法来解题，我们的思路跟上面那题类似，也是从第二个字母开始遍历整个字符串，如果当前字母和之前那个字母都是+，那么我们递归调用将这两个位置变为--的字符串，如果返回false，说明当前玩家可以赢，结束循环返回false   

bool canWin(string s) {
    for (int i = 1; i < s.size(); ++i) {
        if (s[i] == '+' && s[i - 1] == '+' && !canWin(s.substr(0, i - 1) + "--" + s.substr(i + 1))) {
            return true;
        }
    }
    return false;
}


295. Find Median from Data Stream 找出数据流的中位数

Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
Examples:
[2,3,4] , the median is 3
[2,3], the median is (2 + 3) / 2 = 2.5
Design a data structure that supports the following two operations:
void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
For example:
add(1)
add(2)
findMedian() -> 1.5
add(3) 
findMedian() -> 2

这道题给我们一个数据流，让我们找出中位数，由于数据流中的数据并不是有序的，所以我们首先应该想个方法让其有序。如果我们用vector来保存数据流的话，每进来一个新数据都要给数组排序，很不高效。所以之后想到用multiset这个数据结构，是有序保存数据的，但是它不能用下标直接访问元素，找中位数也不高效。这里用到的解法十分巧妙，我们使用大小堆来解决问题，其中大堆保存右半段较大的数字，小堆保存左半段较小的数组。这样整个数组就被中间分为两段了，由于堆的保存方式是由大到小，我们希望大堆里面的数据是从小到大，这样取第一个来计算中位数方便。我们用到一个小技巧，就是存到大堆里的数先取反再存，这样由大到小存下来的顺序就是实际上我们想要的从小到大的顺序。当大堆和小堆中的数字一样多时，我们取出大堆小堆的首元素求平均值，当小堆元素多时，取小堆首元素为中位数. 

class MedianFinder {
public:
    // Adds a number into the data structure.
    void addNum(int num) {
        small.push(num);
        large.push(-small.top());
        small.pop();
        if (small.size() < large.size()) {
            small.push(-large.top());
            large.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        return small.size() > large.size() ? small.top() : 0.5 *(small.top() - large.top());
    }

private:
    priority_queue<long> small, large;
};


296. Best Meeting Point 最佳开会地点  

A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.
For example, given three people living at (0,0), (0,4), and (2,2):
1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (0,2) is an ideal meeting point, as the total travel distance of 2+2+2=6 is minimal. So return 6.
Hint:
Try to solve it in one dimension first. How can this solution apply to the two dimension case?
 这道题让我们求最佳的开会地点，该地点需要到每个为1的点的曼哈顿距离之和最小，题目中给了我们提示，让我们先从一维的情况来分析，那么我们先看一维时有两个点A和B的情况,
______A_____P_______B_______

那么我们可以发现，只要开会为位置P在[A, B]区间内，不管在哪，距离之和都是A和B之间的距离，如果P不在[A, B]之间，那么距离之和就会大于A和B之间的距离，那么我们现在再加两个点C和D：
______C_____A_____P_______B______D______

我们通过分析可以得出，P点的最佳位置就是在[A, B]区间内，这样和四个点的距离之和为AB距离加上CD距离，在其他任意一点的距离都会大于这个距离，那么分析出来了上述规律，这题就变得很容易了，我们只要给位置排好序，然后用最后一个坐标减去第一个坐标，即CD距离，倒数第二个坐标减去第二个坐标，即AB距离，以此类推，直到最中间停止，那么一维的情况分析出来了，二维的情况就是两个一维相加即可.我们也可以不用多写一个函数，直接对rows和cols同时处理 

int minTotalDistance(vector<vector<int>>& grid) {
    vector<int> rows, cols;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == 1) {
                rows.push_back(i);
                cols.push_back(j);
            }
        }
    }
    sort(cols.begin(), cols.end());
    int res = 0, i = 0, j = rows.size() - 1;
    while (i < j) res += rows[j] - rows[i] + cols[j--] - cols[i++];
    return res;
}


297. Serialize and Deserialize Binary Tree 二叉树的序列化和去序列化  

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.
For example, you may serialize the following tree
    1
   / \
  2   3
     / \
    4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

// Recursion
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }

private:
    void serialize(TreeNode *root, ostringstream &out) {
        if (root) {
            out << root->val << ' ';
            serialize(root->left, out);
            serialize(root->right, out);
        } else {
            out << "# ";
        }
    }

    TreeNode* deserialize(istringstream &in) {
        string val;
        in >> val;
        if (val == "#") return nullptr;
        TreeNode *root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};


298. Binary Tree Longest Consecutive Sequence 二叉树最长连续序列  



