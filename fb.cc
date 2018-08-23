string: substr(pos, len), substr(pos), size(), auto, empty(), clear(), erase(), swap(), begin(), end(),            




自己写test case, 分析复杂度 n cubed, n square, n, n!: factorial n, 
c++ STL API time complexity 

判断个序是否是递增递减序  
convert binary tree to doubly linked list  
random return number according to weight  
找出string中出现次数最多的字母, followup 优化
K-Nearest Point C++ 
Previous Permutation  
https://www.kancloud.cn/kancloud/data-structure-and-algorithm-notes/72930 
lintcode: http://www.lintcode.com/en/problem/# 

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



56. Merge Intervals 合并区间 

Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

这次题目要求我们合并区间，之前那题明确了输入区间集是有序的，而这题没有，所有我们首先要做的就是给区间集排序，由于我们要排序的是个结构体，所以我们要定义自己的comparator，才能用sort来排序，我们以start的值从小到大来排序，排完序我们就可以开始合并了，首先把第一个区间存入结果中，然后从第二个开始遍历区间集，如果结果中最后一个区间和遍历的当前区间无重叠，直接将当前区间存入结果中，如果有重叠，将结果中最后一个区间的end值更新为结果中最后一个区间的end和当前end值之中的较大值，然后继续遍历区间集，以此类推可以得到最终结果


static bool comp(const Interval &a, const Interval &b) {
    return (a.start < b.start);  // sort Interval according to start
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


88. Merge Sorted Array 混合插入有序数组  

由于合并后A数组的大小必定是m+n，所以从最后面开始往前赋值，先比较A和B中最后一个元素的大小，把较大的那个插入到m+n-1的位置上，再依次向前推。如果A中所有的元素都比B小，那么前m个还是A原来的内容，没有改变。如果A中的数组比B大的，当A循环完了，B中还有元素没加入A，直接用个循环把B中所有的元素覆盖到A剩下的位置

void merge(int A[], int m, int B[], int n) {

    int count = m + n - 1;
    --m; --n;
    while (m >= 0 && n >= 0) A[count--] = A[m] > B[n] ? A[m--] : B[n--];
    while (n >= 0) A[count--] = B[n--];
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
            while (S[i] == S[i + 1]) ++i; // skip duplicates
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
    	if(!root)   
    		return;
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

    vector<int> all() {
        // all() return所以剩下的node value
    }

private:
    stack<TreeNode*> s;
};



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

// binary search 
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


301. Remove Invalid Parentheses 移除非法括号  

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).
Examples:
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")( -> [""]


vector<string> removeInvalidParentheses(string s) {
    vector<string> res;
    unordered_map<string, int> visited;  // 用于remove duplicate
    queue<string> q; // 通过queue FIFO 来实现minimum. 因为queue里的string长度最多相差1，所以若某一string是valid, 则比这string长度小1的string肯定不是valid. 要(,)为偶数个，奇数个(,)肯定不valid                   
    q.push(s);              
    ++visited[s];              
    bool found = false;          

    while (!q.empty()) {                       
        s = q.front(); q.pop();                       
        if (isValid(s)) {                    
            res.push_back(s);               
            found = true;                 
        }                    
        if (found) continue;                      

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != '(' && s[i] != ')') continue;  // ignore the letters aren't (,)  
            string t = s.substr(0, i) + s.substr(i + 1);  // remove the ith letter 
            if (visited.find(t) == visited.end()) {   // remove duplicate string 
                q.push(t);      
                ++visited[t];          
            }
        }
    }
    return res;
}

bool isValid(string t) { // ignore the letters aren't (,)  
    int cnt = 0;
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] == '(') ++cnt;
        if (t[i] == ')' && cnt-- == 0) return false;
    }
    return cnt == 0;
}


311. Sparse Matrix Multiplication 稀疏矩阵相乘  

Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.
Example:

A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]

     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |

这道题让我们实现稀疏矩阵相乘，稀疏矩阵的特点是矩阵中绝大多数的元素为0，而相乘的结果是还应该是稀疏矩阵，即还是大多数元素为0，那么我们使用传统的矩阵相乘的算法肯定会处理大量的0乘0的无用功，所以我们需要适当的优化算法，使其可以顺利通过OJ，我们知道一个 i x k 的矩阵A乘以一个 k x j 的矩阵B会得到一个 i x j 大小的矩阵C，那么我们来看结果矩阵中的某个元素C[i][j]是怎么来的，起始是A[i][0]*B[0][j] + A[i][1]*B[1][j] + ... + A[i][k]*B[k][j]，那么为了不重复计算0乘0，我们首先遍历A数组，要确保A[i][k]不为0，才继续计算，然后我们遍历B矩阵的第k行，如果B[K][J]不为0，我们累加结果矩阵res[i][j] += A[i][k] * B[k][j]; 这样我们就能高效的算出稀疏矩阵的乘法

vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
    vector<vector<int>> res(A.size(), vector<int>(B[0].size()));
    for (int i = 0; i < A.size(); ++i) {
        for (int k = 0; k < A[0].size(); ++k) {
            if (A[i][k] != 0) {
                for (int j = 0; j < B[0].size(); ++j) {
                    if (B[k][j] != 0) res[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }
    return res;
}


314. Binary Tree Vertical Order Traversal 二叉树的竖直遍历

Given a binary tree, return the vertical order traversal of its nodes values. (ie, from top to bottom, column by column).
If two nodes are in the same row and column, the order should be from left to right.

Given binary tree [3,9,20,4,5,2,7],
    _3_
   /   \
  9    20
 / \   / \
4   5 2   7

return its vertical order traversal as:
[
  [4],
  [9],
  [3,5,2],
  [20],
  [7]
]

这道题让我们竖直遍历二叉树，并把每一列存入一个二维数组，我们看题目中给的第一个例子，3和15属于同一列，3在前，第二个例子中，3,5,2在同一列，3在前，5和2紧随其后，那么我们隐约的可以感觉到好像是一种层序遍历的前后顺序，那么我们如何来确定列的顺序呢，我们可以把根节点给个序号0，然后开始层序遍历，凡是左子节点则序号减1，右子节点序号加1，这样我们可以通过序号来把相同列的节点值放到一起，我们用一个map来建立序号和其对应的节点值的映射，用map的另一个好处是其自动排序功能可以让我们的列从左到右，由于层序遍历需要用到queue，我们此时queue里不能只存节点，而是要存序号和节点组成的pair，这样我们每次取出就可以操作序号，而且排入队中的节点也赋上其正确的序号. 


// assign a label value for every node. 
vector<vector<int>> verticalOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;
    map<int, vector<int>> m;
    queue<pair<int, TreeNode*>> q;
    q.push({0, root});
    while (!q.empty()) {
        auto a = q.front(); q.pop();
        m[a.first].push_back(a.second->val);
        if (a.second->left) q.push({a.first - 1, a.second->left});
        if (a.second->right) q.push({a.first + 1, a.second->right});
    }
    for (auto a : m) {
        res.push_back(a.second);
    }
    return res;
}


325. Maximum Size Subarray Sum Equals k 最大子数组之和为k

Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there is not one, return 0 instead.
Example 1:
Given nums = [1, -1, 5, -2, 3], k = 3,
return 4. (because the subarray [1, -1, 5, -2] sums to 3 and is the longest)

Follow Up:
Can you do it in O(n) time?

直接用一个变量sum边累加边处理，而且我们哈希表也完全不用建立和一维数组的映射，只要保存第一个出现该累积和的位置，后面再出现直接跳过，这样算下来就是最长的子数组. 

int maxSubArrayLen(vector<int>& nums, int k) {
    int sum = 0, res = 0;
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); ++i) {
        sum += nums[i];

        if (!m.count(sum)) 
        	m[sum] = i;

        if (sum == k) 
        	res = i + 1;

        if (m.count(sum - k)) 
        	res = max(res, i - m[sum - k]);
    }
    return res;
}


334. Increasing Triplet Subsequence 递增的三元子序列  

Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.
Formally the function should:
Return true if there exists i, j, k 
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.  // i,j,k不需要是连续的
 
Your algorithm should run in O(n) time complexity and O(1) space complexity.

但是题目中要求我们O(n)的时间复杂度和O(1)的空间复杂度，上面的那种方法一条都没满足，所以白写了。我们下面来看满足题意的方法，这个思路是使用两个指针m1和m2，初始化为整型最大值，我们遍历数组，如果m1大于等于当前数字，则将当前数字赋给m1；如果m1小于当前数字且m2大于等于当前数字，那么将当前数字赋给m2，一旦m2被更新了，说明一定会有一个数小于m2，那么我们就成功的组成了一个长度为2的递增子序列，所以我们一旦遍历到比m2还大的数，我们直接返回ture。如果我们遇到比m1小的数，还是要更新m1，有可能的话也要更新m2为更小的值，毕竟m2的值越小，能组成长度为3的递增序列的可能性越大

bool increasingTriplet(vector<int>& nums) {
    int m1 = INT_MAX, m2 = INT_MAX;
    for (auto a : nums) {
        if (m1 >= a) m1 = a;
        else if (m2 >= a) m2 = a;
        else return true;
    }
    return false;
}

solution 2: 

如果觉得上面的解法不容易想出来，那么如果能想出下面这种解法，估计面试官也会为你点赞。这种方法的虽然不满足常数空间的要求，但是作为对暴力搜索的优化，也是一种非常好的解题思路。这个解法的思路是建立两个数组，forward数组和backward数组，其中forward[i]表示[0, i]之间最小的数，backward[i]表示[i, n-1]之间最大的数，那么对于任意一个位置i，如果满足 forward[i] < nums[i] < backward[i]，则表示这个递增三元子序列存在，举个例子来看吧，比如：
nums:      8  3  5  1  6
foward:    8  3  3  1  1
backward:  8  6  6  6  6
我们发现数字5满足forward[i] < nums[i] < backward[i]，所以三元子序列存在。


bool increasingTriplet(vector<int>& nums) {
    if (nums.size() < 3) return false;
    int n = nums.size();

    vector<int> f(n, nums[0]), b(n, nums.back());

    for (int i = 1; i < n; ++i) {
        f[i] = min(f[i - 1], nums[i]);
    }

    for (int i = n - 2; i >= 0; --i) {
        b[i] = max(b[i + 1], nums[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (nums[i] > f[i] && nums[i] < b[i]) return true;
    }
    return false;
}


341. Flatten Nested List Iterator 压平嵌套链表迭代器  

Given a nested list of integers, implement an iterator to flatten it.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].


这道题让我们建立压平嵌套链表的迭代器，关于嵌套链表的数据结构最早出现在Nested List Weight Sum中，而那道题是用的递归的方法来解的，而迭代器一般都是用迭代的方法来解的，而递归一般都需用栈来辅助遍历，由于栈的后进先出的特性，我们在对向量遍历的时候，从后往前把对象压入栈中，那么第一个对象最后压入栈就会第一个取出来处理，我们的hasNext()函数需要遍历栈，并进行处理，如果栈顶元素是整数，直接返回true，如果不是，那么移除栈顶元素，并开始遍历这个取出的list，还是从后往前压入栈，循环停止条件是栈为空，返回false. 


class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for (int i = nestedList.size() - 1; i >= 0; --i) {
            s.push(nestedList[i]);
        }
    }

    int next() {
        NestedInteger t = s.top(); s.pop();
        return t.getInteger();
    }

    bool hasNext() {
        while (!s.empty()) {
            NestedInteger t = s.top(); 
            s.pop();
            if (t.isInteger()) 
            	return true;

            for (int i = t.getList().size() - 1; i >= 0; --i) {
                s.push(t.getList()[i]);
            }
        }
        return false;
    }

private:
    stack<NestedInteger> s;
};


377. Combination Sum IV 组合之和之四

Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:
nums = [1, 2, 3]
target = 4
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.
Therefore the output is 7.
Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?

而这道题的真正解法应该是用DP来做，解题思想有点像之前爬梯子的那道题Climbing Stairs，我们需要一个一维数组dp，其中dp[i]表示目标数为i的解的个数，然后我们从1遍历到target，对于每一个数i，遍历nums数组，如果i>=x, dp[i] += dp[i - x]。这个也很好理解，比如说对于[1,2,3] 4，这个例子，当我们在计算dp[3]的时候，3可以拆分为1+x，而x即为dp[2]，3也可以拆分为2+x，此时x为dp[1]，3同样可以拆为3+x，此时x为dp[0]，我们把所有的情况加起来就是组成3的所有情况了. 


int combinationSum4(vector<int>& nums, int target) {
    vector<int> dp(target + 1);
    dp[0] = 1;
    for (int i = 1; i <= target; ++i) {
        for (auto a : nums) {
            if (i >= a) dp[i] += dp[i - a];
        }
    }
    return dp.back();
}


如果target远大于nums数组的个数的话，上面的算法可以做适当的优化，先给nums数组排个序，然后从1遍历到target，对于i小于数组中的数字x时，我们直接break掉，因为后面的数更大，其余地方不变. 

int combinationSum4(vector<int>& nums, int target) {

    vector<int> dp(target + 1);
    dp[0] = 1;
    sort(nums.begin(), nums.end());

    for (int i = 1; i <= target; ++i) {
        for (auto a : nums) {
            if (i < a) break;
            dp[i] += dp[i - a];
        }
    }
    return dp.back();
}


380.  Insert Delete GetRandom O(1) 常数时间内插入删除和获得随机数

Design a data structure that supports all following operations in average O(1) time.

1. insert(val): Inserts an item val to the set if not already present.
2. remove(val): Removes an item val from the set if present.
3. getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.

// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();
// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);
// Returns false as 2 does not exist in the set.
randomSet.remove(2);
// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);
// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();

这道题让我们在常数时间范围内实现插入删除和获得随机数操作，如果这道题没有常数时间的限制，那么将会是一道非常简单的题，我们直接用一个set就可以搞定所有的操作。但是由于时间的限制，我们无法在常数时间内实现获取随机数，所以只能另辟蹊径。此题的正确解法是利用到了一个一维数组和一个哈希表，其中数组用来保存数字，哈希表用来建立每个数字和其在数组中的位置之间的映射，对于插入操作，我们先看这个数字是否已经在哈希表中存在，如果存在的话直接返回false，不存在的话，我们将其插入到数组的末尾，然后建立数字和其位置的映射。删除操作是比较tricky的，我们还是要先判断其是否在哈希表里，如果没有，直接返回false。由于哈希表的删除是常数时间的，而数组并不是，为了使数组删除也能常数级，我们实际上将要删除的数字和数组的最后一个数字调换个位置，然后修改对应的哈希表中的值，这样我们只需要删除数组的最后一个元素即可，保证了常数时间内的删除。而返回随机数对于数组来说就很简单了，我们只要随机生成一个位置，返回该位置上的数字即可


class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {}
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (m.count(val)) return false;
        nums.push_back(val);
        m[val] = nums.size() - 1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (!m.count(val)) return false;
        int last = nums.back();
        m[last] = m[val];
        nums[m[val]] = last;
        nums.pop_back();
        m.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }

private:
    vector<int> nums;
    unordered_map<int, int> m;
};


398. Random Pick Index 随机拾取序列  

Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.  
Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

这道题指明了我们不能用太多的空间，那么省空间的随机方法只有水塘抽样了，LeetCode之前有过两道需要用这种方法的题目Shuffle an Array和Linked List Random Node。那么如果了解了水塘抽样，这道题就不算一道难题了，我们定义两个变量，计数器cnt和返回结果res，我们遍历整个数组，如果数组的值不等于target，直接跳过；如果等于target，计数器加1，然后我们在[0,cnt)范围内随机生成一个数字，如果这个数字是0，我们将res赋值为i即可. 

class Solution {
public:
    Solution(vector<int> nums): v(nums) {}
    
    int pick(int target) {
        int cnt = 0, res = -1;
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] != target) continue;
            ++cnt;
            if (rand() % cnt == 0) res = i;
        }
        return res;
    }
private:
    vector<int> v;
};


404. Sum of Left Leaves 左子叶之和 

Find the sum of all left leaves in a given binary tree.
Example:
    3
   / \
  9  20
    /  \
   15   7
There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.

直接在原函数中检查当前节点的左子节点是否是左子叶，如果是的话，则返回左子叶的值加上对当前结点的右子节点调用递归的结果；如果不是的话，我们对左右子节点分别调用递归函数，返回二者之和.

    int sumOfLeftLeaves(TreeNode* root) {
        if (!root) return 0;
        if (root->left && !root->left->left && !root->left->right) {
            return root->left->val + sumOfLeftLeaves(root->right);
        }
        return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    }

我们也可以使用迭代来解，因为这道题的本质是遍历二叉树，所以我们可以用层序遍历的迭代写法，利用queue来辅助，注意对左子叶的判断和处理. 

    int sumOfLeftLeaves(TreeNode* root) {
        if (!root || (!root->left && !root->right)) return 0;
        int res = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *t = q.front(); q.pop();
            if (t->left && !t->left->left && !t->left->right) res += t->left->val;
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
        return res;
    }


410. Split Array Largest Sum 分割数组的最大值   

Given an array which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.
Note:
Given m satisfies the following constraint: 1 ≤ m ≤ length(nums) ≤ 14,000.

Examples:
Input:
nums = [7,2,5,10,8]
m = 2

Output:
18
Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.

发现大家普遍使用了二分搜索法来做，感觉特别巧妙，原来二分搜索法还能这么用，厉害了我的哥。我们首先来分析，如果m和数组nums的个数相等，那么每个数组都是一个子数组，所以返回nums中最大的数字即可，如果m为1，那么整个nums数组就是一个子数组，返回nums所有数字之和，所以对于其他有效的m值，返回的值必定在上面两个值之间，所以我们可以用二分搜索法来做。我们用一个例子来分析，nums = [1, 2, 3, 4, 5], m = 3，我们将left设为数组中的最大值5，right设为数字之和15，然后我们算出中间数为10，我们接下来要做的是找出和最大且小于等于10的子数组的个数，[1, 2, 3, 4], [5]，可以看到我们无法分为3组，说明mid偏大，所以我们让right=mid，然后我们再次进行二分查找哦啊，算出mid=7，再次找出和最大且小于等于7的子数组的个数，[1,2,3], [4], [5]，我们成功的找出了三组，说明mid还可以进一步降低，我们让right=mid，然后我们再次进行二分查找哦啊，算出mid=6，再次找出和最大且小于等于6的子数组的个数，[1,2,3], [4], [5]，我们成功的找出了三组，我们尝试着继续降低mid，我们让right=mid，然后我们再次进行二分查找哦啊，算出mid=5，再次找出和最大且小于等于5的子数组的个数，[1,2], [3], [4], [5]，发现有4组，此时我们的mid太小了，应该增大mid，我们让left=mid+1，此时left=6，right=5，循环退出了，我们返回left即可

    int splitArray(vector<int>& nums, int m) {
        long long left = 0, right = 0;
        for (int i = 0; i < nums.size(); ++i) {
            left = max((int)left, nums[i]);
            right += nums[i];
        }

        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (can_split(nums, m, mid)) right = mid;
            else left = mid + 1;
        }
        return left;
    }

    bool can_split(vector<int>& nums, int m, int sum) {
        int cnt = 1, curSum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            curSum += nums[i];
            if (curSum > sum) {
                curSum = nums[i];
                ++cnt;
                if (cnt > m) return false;
            }
        }
        return true;
    }


461. Hamming Distance 汉明距离  

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
Given two integers x and y, calculate the Hamming distance.
Note:
0 ≤ x, y < 231.
Example:
Input: x = 1, y = 4
Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different.

这道题让我求两个数字之间的汉明距离，题目中解释的很清楚了，两个数字之间的汉明距离就是其二进制数对应位不同的个数，那么最直接了当的做法就是按位分别取出两个数对应位上的数并异或，我们知道异或的性质上相同的为0，不同的为1，我们只要把为1的情况累加起来就是汉明距离了

int hammingDistance(int x, int y) {
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        if ((x & (1 << i)) ^ (y & (1 << i))) {
            ++res;
        }
    }
    return res;
}

solution 2: 
我们可以一开始直接将两个数字异或起来，然后我们遍历异或结果的每一位，统计为1的个数
int hammingDistance(int x, int y) {
    int res = 0, exc = x ^ y;
    for (int i = 0; i < 32; ++i) {
        res += (exc >> i) & 1;
    }
    return res;
}

solution 3: 
上面的遍历每一位的方法并不高效，还可以进一步优化，假如数为num, num & (num - 1)可以快速地移除最右边的bit 1， 一直循环到num为0, 总的循环数就是num中bit 1的个数
int hammingDistance(int x, int y) {
    int res = 0, exc = x ^ y;
    while (exc) {
        ++res;
        exc &= (exc - 1);
    }
    return res;
}


477. Total Hamming Distance 全部汉明距离  

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
Now your job is to find the total Hamming distance between all pairs of the given numbers.
Example:
Input: 4, 14, 2
Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.

我们仔细观察累计汉明距离和0跟1的个数，我们可以发现其实就是0的个数乘以1的个数，发现了这个重要的规律，那么整道题就迎刃而解了，只要统计出每一位的1的个数即可. 

int totalHammingDistance(vector<int>& nums) {
    int res = 0, n = nums.size(); 
    for(int i = 0; i < 32; ++i) {
        int cnt = 0; 
        for(int num : nums) {
            if(num & (1 << i))
                ++cnt;
        }
        res += cnt * (n - cnt);
    }
    return res; 
}


494. Target Sum 目标和
You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.
Find out how many ways to assign symbols to make sum of integers equal to target S.
Example 1:
Input: nums is [1, 1, 1, 1, 1], S is 3. 
Output: 5
Explanation: 
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

这道题给了我们一个数组，和一个目标值，让我们给数组中每个数字加上正号或负号，然后求和要和目标值相等，求有多少中不同的情况。那么对于这种求多种情况的问题，我最想到的方法使用递归来做。我们从第一个数字，调用递归函数，在递归函数中，分别对目标值进行加上当前数字调用递归，和减去当前数字调用递归，这样会涵盖所有情况，并且当所有数字遍历完成后，我们看若目标值为0了，则结果res自增1. 

int findTargetSumWays(vector<int>& nums, int S) {
    int res = 0;
    helper(nums, S, 0, res);
    return res;
}

void helper(vector<int>& nums, int S, int start, int& res) {
    if (start == nums.size()) {
        if (S == 0) ++res;
        return;
    }
    helper(nums, S - nums[start], start + 1, res);
    helper(nums, S + nums[start], start + 1, res);
}


我们对上面的递归方法进行优化，使用dp数组来记录中间值，这样可以避免重复运算
solution 2: 
int findTargetSumWays(vector<int>& nums, int S) {
    vector<unordered_map<int, int>> dp(nums.size());
    return helper(nums, S, 0, dp);
}

int helper(vector<int>& nums, int sum, int start, vector<unordered_map<int, int>>& dp) {
    if (start == nums.size()) return sum == 0;
    if (dp[start].count(sum)) return dp[start][sum];
    int cnt1 = helper(nums, sum - nums[start], start + 1, dp);
    int cnt2 = helper(nums, sum + nums[start], start + 1, dp);
    return dp[start][sum] = cnt1 + cnt2;
}


523. Continuous Subarray Sum 连续的子数组之和  

Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to the multiple of k, that is, sums up to n*k where n is also an integer.

Example 1:
Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
Example 2:
Input: [23, 2, 6, 4, 7],  k=6
Output: True

Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
Note:
The length of the array will not exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.

bool checkSubarraySum(vector<int>& nums, int k) {
    for (int i = 0; i < nums.size(); ++i) {
        int sum = nums[i];
        for (int j = i + 1; j < nums.size(); ++j) {
            sum += nums[j];
            if (sum == k) return true;
            if (k != 0 && sum % k == 0) return true;
        }
    }
    return false;
}


525. Contiguous Array 邻近数组     

Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.
Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.

这道题给了我们一个二进制的数组，让我们找邻近的子数组使其0和1的个数相等。对于求子数组的问题，我们需要时刻记着求累积和是一种很犀利的工具，但是这里怎么将子数组的和跟0和1的个数之间产生联系呢？我们需要用到一个trick，遇到1就加1，遇到0，就减1，这样如果某个子数组和为0，就说明0和1的个数相等，这个想法真是太叼了，不过博主木有想出来。知道了这一点，我们用一个哈希表建立子数组之和跟结尾位置的坐标之间的映射。如果某个子数组之和在哈希表里存在了，说明当前子数组减去哈希表中存的那个子数字，得到的结果是中间一段子数组之和，必然为0，说明0和1的个数相等，我们更新结果res，

int findMaxLength(vector<int>& nums) {
    int res = 0, n = nums.size(), sum = 0;
    unordered_map<int, int> m{{0, -1}}; // m{{0,-1}} handles the corner case input: [0, 1] 
    // 把sum = 0时的index预先设置为-1. to handle corner case 

    for (int i = 0; i < n; ++i) {
        sum += (nums[i] == 1) ? 1 : -1;
        if (m.count(sum)) {
            res = max(res, i - m[sum]);
        } else {
            m[sum] = i;
        }
    }
    return res;
}


535. Encode and Decode TinyURL 编码和解码精简URL地址

TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.

而题目中明确推荐了使用六位随机字符来编码，那么我们只要在所有大小写字母和数字中随机产生6个字符就可以了，我们用哈希表建立6位字符和url之间的映射，如果随机生成的字符之前已经存在了，我们就继续随机生成新的字符串，直到生成了之前没有的字符串为止。下面的代码中使用了两个哈希表，目的是为了建立六位随机字符串和url之间的相互映射，这样进来大量的相同url时，就不用生成新的随机字符串了

class Solution {
public:
    Solution() {
        dict = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        short2long.clear();
        long2short.clear();
        srand(time(NULL));
    }

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        if (long2short.count(longUrl)) {
            return "http://tinyurl.com/" + long2short[longUrl];
        }
        int idx = 0;
        string randStr;
        for (int i = 0; i < 6; ++i) randStr.push_back(dict[rand() % 62]);
        while (short2long.count(randStr)) {
            randStr[idx] = dict[rand() % 62];
            idx = (idx + 1) % 5;
        }
        short2long[randStr] = longUrl;
        long2short[longUrl] = randStr;
        return "http://tinyurl.com/" + randStr;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        string randStr = shortUrl.substr(shortUrl.find_last_of("/") + 1);
        return short2long.count(randStr) ? short2long[randStr] : shortUrl;
    }
    
private:
    unordered_map<string, string> short2long, long2short;
    string dict;
};


543. Diameter of Binary Tree 二叉树的直径

Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longestpath between any two nodes in a tree. This path may or may not pass through the root.
Example:
Given a binary tree 

          1
         / \
        2   3
       / \     
      4   5    
 
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
Note: The length of path between two nodes is represented by the number of edges between them.

我们再来仔细观察例子中的那两个最长路径[4,2,1,3] 和 [5,2,1,3]，我们转换一种角度来看，是不是其实就是根结点1的左右两个子树的深度之和再加1呢。那么我们只要对每一个结点求出其左右子树深度之和，再加上1就可以更新结果res了。为了减少重复计算，我们用哈希表建立每个结点和其深度之间的映射，这样某个结点的深度之前计算过了，就不用再次计算了

unordered_map<TreeNode*, int> m;

int diameterOfBinaryTree(TreeNode* root) {
    if (!root) return 0;
    int res = getHeight(root->left) + getHeight(root->right);
    return max(res, max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right)));
}

int getHeight(TreeNode* node) {
    if (!node) return 0;
    if (m.count(node)) return m[node];  // 时间优化
    int h = 1 + max(getHeight(node->left), getHeight(node->right));
    return m[node] = h;
}


554. Brick Wall 砖头墙壁  

There is a brick wall in front of you. The wall is rectangular and has several rows of bricks. The bricks have the same height but different width. You want to draw a vertical line from the top to the bottom and cross the leastbricks.
The brick wall is represented by a list of rows. Each row is a list of integers representing the width of each brick in this row from left to right.
If your line go through the edge of a brick, then the brick is not considered as crossed. You need to find out how to draw the line to cross the least bricks and return the number of crossed bricks.
You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.
Example:
Input: 
[[1,2,2,1],
 [3,1,2],
 [1,3,2],
 [2,4],
 [3,1,2],
 [1,3,1,1]]
Output: 2

这道题给了我们一个砖头墙壁，上面由不同的长度的砖头组成，让我们选个地方从上往下把墙劈开，使得被劈开的砖头个数最少，前提是不能从墙壁的两边劈，这样没有什么意义。我们使用一个哈希表来建立每一个断点的长度和其出现频率之间的映射，这样只要我们从断点频率出现最多的地方劈墙，损坏的板砖一定最少. 

int leastBricks(vector<vector<int>>& wall) {
    int mx = 0;
    unordered_map<int, int> m;
    for (auto a : wall) {
        int sum = 0;
        for (int i = 0; i < a.size() - 1; ++i) {
            sum += a[i];
            ++m[sum];
            mx = max(mx, m[sum]);
        }
    }
    return wall.size() - mx;
}


572. Subtree of Another Tree 另一个树的子树  

Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this nodes descendants. The tree scould also be considered as a subtree of itself.

Example 1:
Given tree s:
     3
    / \
   4   5
  / \
 1   2
Given tree t:

   4 
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.

这道题让我们求一个数是否是另一个树的子树，从题目中的第二个例子中可以看出，子树必须是从叶结点开始的，中间某个部分的不能算是子树，那么我们转换一下思路，是不是从s的某个结点开始，跟t的所有结构都一样，那么问题就转换成了判断两棵树是否相同，也就是Same Tree的问题了，这点想通了其实代码就很好写了，用递归来写十分的简洁，我们先从s的根结点开始，跟t比较，如果两棵树完全相同，那么返回true，否则就分别对s的左子结点和右子结点调用递归再次来判断是否相同，只要有一个返回true了，就表示可以找得到。

bool isSubtree(TreeNode* s, TreeNode* t) {
    if (!s) return false;
    if (isSame(s, t)) return true;
    return isSubtree(s->left, t) || isSubtree(s->right, t);
}

bool isSame(TreeNode* s, TreeNode* t) {
    if (!s && !t) return true;
    if (!s || !t) return false;
    if (s->val != t->val) return false;
    return isSame(s->left, t->left) && isSame(s->right, t->right);
}


621. Task Scheduler 任务行程表
 
Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.
However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.
You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1:
Input: tasks = ['A','A','A','B','B','B'], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.


这道题让我们安排CPU的任务，规定在两个相同任务之间至少隔n个时间点。说实话，刚开始博主并没有完全理解题目的意思，后来看了大神们的解法才悟出个道理来。下面这种解法参考了大神fatalme的帖子，由于题目中规定了两个相同任务之间至少隔n个时间点，那么我们首先应该处理的出现次数最多的那个任务，先确定好这些高频任务，然后再来安排那些低频任务。如果任务F的出现频率最高，为k次，那么我们用n个空位将每两个F分隔开，然后我们按顺序加入其他低频的任务，来看一个例子：

AAAABBBEEFFGG 3

我们发现任务A出现了4次，频率最高，于是我们在每个A中间加入三个空位，如下：
A---A---A---A
AB--AB--AB--A   (加入B)
ABE-ABE-AB--A   (加入E)
ABEFABE-ABF-A   (加入F，每次尽可能填满或者是均匀填充)
ABEFABEGABFGA   (加入G)

再来看一个例子：
ACCCEEE 2
我们发现任务C和E都出现了三次，那么我们就将CE看作一个整体，在中间加入一个位置即可：
CE-CE-CE
CEACE-CE   (加入A)
注意最后面那个idle不能省略，不然就不满足相同两个任务之间要隔2个时间点了

而只是问所需的时间总长，那么我们就想个方法来快速计算出所需时间总长即可。我们仔细观察上面两个例子可以发现，都分成了(mx - 1)块，再加上最后面的字母，其中mx为最大出现次数。比如例子1中，A出现了4次，所以有A---模块出现了3次，再加上最后的A，每个模块的长度为4。例子2中，CE-出现了2次，再加上最后的CE，每个模块长度为3。我们可以发现，模块的次数为任务最大次数减1，模块出现次数为n+1，最后加上的字母个数为出现次数最多的任务，可能有多个并列。这样三个部分都搞清楚了，写起来就不难了，我们统计每个大写字母出现的次数，然后排序，这样出现次数最多的字母就到了末尾，然后我们向前遍历，找出出现次数一样多的任务个数，就可以迅速求出总时间长了

int leastInterval(vector<char>& tasks, int n) {
    vector<int> cnt(26, 0);
    for (char task : tasks) {
        ++cnt[task - 'A'];
    }
    sort(cnt.begin(), cnt.end());
    int i = 25, mx = cnt[25], len = tasks.size();
    while (i >= 0 && cnt[i] == mx) --i;
    return max(len, (mx - 1) * (n + 1) + 25 - i);
}


636. Exclusive Time of Functions 函数的独家时间  

Given the running logs of n functions that are executed in a nonpreemptive single threaded CPU, find the exclusive time of these functions.
Each function has a unique id, start from 0 to n-1. A function may be called recursively or by another function.
A log is a string has this format : function_id:start_or_end:timestamp. For example, "0:start:0" means function 0 starts from the very beginning of time 0. "0:end:0" means function 0 ends to the very end of time 0.
Exclusive time of a function is defined as the time spent within this function, the time spent by calling other functions should not be considered as this functions exclusive time. You should return the exclusive time of each function sorted by their function id.

Input:
n = 2
logs = 
["0:start:0",
 "1:start:2",
 "1:end:5",
 "0:end:6"]
Output:[3, 4]
Explanation:
Function 0 starts at time 0, then it executes 2 units of time and reaches the end of time 1. 
Now function 0 calls function 1, function 1 starts at time 2, executes 4 units of time and end at time 5.
Function 0 is running again at time 6, and also end at the time 6, thus executes 1 unit of time. 
So function 0 totally execute 2 + 1 = 3 units of time, and function 1 totally execute 4 units of time.

Note:
Input logs will be sorted by timestamp, NOT log id.
Your output should be sorted by function id, which means the 0th element of your output corresponds to the exclusive time of function 0.
Two functions will not start or end at the same time.
Functions could be called recursively, and will always end. 1 <= n <= 100

vector<int> exclusiveTime(int n, vector<string>& logs) {
    vector<int> res(n, 0);
    stack<int> st;
    int preTime = 0;
    for (string log : logs) {
        int found1 = log.find(":");
        int found2 = log.find_last_of(":");
        int idx = stoi(log.substr(0, found1));
        string type = log.substr(found1 + 1, found2 - found1 - 1);
        int time = stoi(log.substr(found2 + 1));
        if (!st.empty()) {
            res[st.top()] += time - preTime;
        }
        preTime = time;
        if (type == "start") st.push(idx);
        else {
            auto t = st.top(); st.pop();
            ++res[t];
            ++preTime;
        }
    }
    return res;
}


637. Average of Levels in Binary Tree 二叉树的层平均值  

Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
 
Note:
The range of node value is in the range of 32-bit signed integer.

vector<double> averageOfLevels(TreeNode* root) {
    vector<double> res;
    if (!root) return res;
    queue<TreeNode*> q{{root}};

    while (!q.empty()) {
        int n = q.size();
        double sum = 0;
        for (int i = 0; i < n; ++i) {
            TreeNode *t = q.front(); q.pop();
            sum += t->val;
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
        res.push_back(sum / n);
    }
    return res;
}

639. Decode Ways II 解码方法之二

A message containing letters from A-Z is being encoded to numbers using the following mapping way:
'A' -> 1
'B' -> 2
...
'Z' -> 26
Beyond that, now the encoded string can also contain the character '*', which can be treated as one of the numbers from 1 to 9.
Given the encoded message containing digits and the character '*', return the total number of ways to decode it.
Also, since the answer may be very large, you should return the output mod 109 + 7.
Example 1:
Input: "*"
Output: 9
Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".
 
Example 2:
Input: "1*"
Output: 9 + 9 = 18

Note:
The length of the input string will fit in range [1, 105].
The input string will only contain the character '*' and digits '0' - '9'.

下面这种解法是论坛上排名最高的解法，常数级的空间复杂度，写法非常简洁，思路也巨牛逼，博主是无论如何也想不出来的，只能继续当搬运工了。这里定义了一系列的变量e0, e1, e2, f0, f1, f2。其中：
e0表示当前可以获得的解码的次数，当前数字可以为任意数 (也就是上面解法中的dp[i])
e1表示当前可以获得的解码的次数，当前数字为1
e2表示当前可以获得的解码的次数，当前数字为2
f0, f1, f2分别为处理完当前字符c的e0, e1, e2的值
那么下面我们来进行分类讨论，当c为星号的时候，f0的值就是9*e0 + 9*e1 + 6*e2，这个应该不难理解了，可以参考上面解法中的讲解，这里的e0就相当于dp[i-1]，e1和e2相当于两种不同情况的dp[i-2]，此时f1和f2都赋值为e0，因为要和后面的数字组成两位数的话，不会增加新的解码方法，所以解码总数跟之前的一样，为e0, 即dp[i-1]。
当c不为星号的时候，如果c不为0，则f0首先应该加上e0。然后不管c为何值，e1都需要加上，总能和前面的1组成两位数；如果c小于等于6，可以和前面的2组成两位数，可以加上e2。然后我们更新f1和f2，如果c为1，则f1为e0；如果c为2，则f2为e0。
最后别忘了将f0，f1，f2赋值给e0，e1，e2，其中f0需要对超大数取余


int numDecodings(string s) {
    long e0 = 1, e1 = 0, e2 = 0, f0, f1, f2, M = 1e9 + 7;
    for (char c : s) {
        if (c == '*') {
            f0 = 9 * e0 + 9 * e1 + 6 * e2;
            f1 = e0;
            f2 = e0;
        } else {
            f0 = (c > '0') * e0 + e1 + (c <= '6') * e2;
            f1 = (c == '1') * e0;
            f2 = (c == '2') * e0;
        }
        e0 = f0 % M;
        e1 = f1;
        e2 = f2;
    }
    return e0;
}


647. Palindromic Substrings 回文子字符串  

Given a string, your task is to count how many palindromic substrings in this string.
The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.
Example 1:
Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

就是以字符串中的每一个字符都当作回文串中间的位置，然后向两边扩散，每当成功匹配两个左右两个字符，结果res自增1，然后再比较下一对。注意回文字符串有奇数和偶数两种形式，如果是奇数长度，那么i位置就是中间那个字符的位置，所以我们左右两遍都从i开始遍历；如果是偶数长度的，那么i是最中间两个字符的左边那个，右边那个就是i+1，这样就能cover所有的情况啦，而且都是不同的回文子字符串

int countSubstrings(string s) {
    if (s.empty()) return 0;
    int n = s.size(), res = 0;
    for (int i = 0; i < n; ++i) {
        helper(s, i, i, res);
        helper(s, i, i + 1, res);
    }
    return res;
}

void helper(string s, int i, int j, int& res) {
    while (i >= 0 && j < s.size() && s[i] == s[j]) {
        --i; ++j; ++res;
    }
}


653. Two Sum IV - Input is a BST 两数之和之四 - 输入是二叉搜索树  

Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.
Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9
Output: True

博主一直强调，平生不识TwoSum，刷尽LeetCode也枉然！只要是两数之和的题，一定要记得用哈希表来做，这道题只不过是把数组变成了一棵二叉树而已，换汤不换药，我们遍历二叉树就行，然后用一个哈希set，在递归函数函数中，如果node为空，返回false。如果k减去当前结点值在哈希set中存在，直接返回true；否则就将当前结点值加入哈希set，然后对左右子结点分别调用递归函数并且或起来返回即可. 

bool findTarget(TreeNode* root, int k) {
    if (!root) return false;
    unordered_set<int> s;
    return helper(root, k, s);
}

bool helper(TreeNode* node, int k, unordered_set<int>& s) {
    if (!node) return false;
    if (s.count(k - node->val)) return true;
    s.insert(node->val);
    return helper(node->left, k, s) || helper(node->right, k, s);
}

我们也可以用层序遍历来做，这样就是迭代的写法了，但是利用哈希表的精髓还是没变的

bool findTarget(TreeNode* root, int k) {
    if (!root) return false;
    unordered_set<int> s;
    queue<TreeNode*> q{{root}};
    while (!q.empty()) {
      auto t = q.front(); q.pop();
      if (s.count(k - t->val)) return true;
      s.insert(t->val);
      if (t->left) q.push(t->left);
      if (t->right) q.push(t->right);
    }
    return false;
}




670. Maximum Swap
Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.
Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7

int maximumSwap(int num) {
    string str = to_string(num); // 转成string好处理些
    int res = num, n = str.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            swap(str[i], str[j]);
            res = max(res, stoi(str));
            swap(str[i], str[j]);
        }
    }
    return res;
}


// better solution: greedy 
int maximumSwap(int num) {
    string numstr = std::to_string(num);

    int maxidx = -1; int maxdigit = -1;
    int leftidx = -1; int rightidx = -1;        

    for (int i = numstr.size() - 1; i >= 0; --i) {
        // current digit is the largest by far
        if (numstr[i] > maxdigit) {
            maxdigit = numstr[i];
            maxidx = i;
            continue;
        }
        // best candidate for max swap if there is no more 
        // such situation on the left side
        if (numstr[i] < maxdigit) {
            leftidx = i;
            rightidx = maxidx;
        }
    }
    // num is already in order
    if (leftidx == -1) return num;  // every digit num in decreasing order. 
    std::swap(numstr[leftidx], numstr[rightidx]);
    return std::stoi(numstr);
}


673. Number of Longest Increasing Subsequence

Given an unsorted array of integers, find the number of longest increasing subsequence.
Input: [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].

The idea is to use two arrays len[n] and cnt[n] to record the maximum length of Increasing Subsequence and the coresponding number of these sequence which ends with nums[i], respectively. That is:
len[i]: the length of the Longest Increasing Subsequence which ends with nums[i].
cnt[i]: the number of the Longest Increasing Subsequence which ends with nums[i].

Then, the result is the sum of each cnt[i] while its corresponding len[i] is the maximum length.
C++: use vector<pair<int, int>> dp to combine len[] and cnt[] 

int findNumberOfLIS(vector<int>& nums) {
    // Third Time
    // solution 1, didn't think out of this solution
    // https://discuss.leetcode.com/topic/103020/java-c-simple-dp-solution-with-explanation/2
    int n = nums.size();
    vector<int> len(n, 1);  // the length of the LIS which ends with nums[i]
    vector<int> cnt(n, 1);  // the number of the LIS which ends with nums[i]
    int res = 0, mxlen = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < i; ++j){
            if(nums[i] <= nums[j]) 
            	continue;
            if(len[i] == len[j]+1){
                cnt[i] += cnt[j];
            } else if(len[i] < len[j] + 1){
                len[i] = len[j] + 1;
                cnt[i] = cnt[j];
            }
        }
        
        if(len[i] == mxlen) 
        	res += cnt[i];
        else if(len[i] > mxlen) {
            mxlen = len[i];
            res = cnt[i];
        }
    }
    return res;
}


674. Longest Continuous Increasing Subsequence  

Given an unsorted array of integers, find the length of longest continuous increasing subsequence.
Example 1:
Input: [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3. 
Even though [1,3,5,7] is also an increasing subsequence, it is not a continuous one where 5 and 7 are separated by 4. 

int findLengthOfLCIS(vector<int>& a) {
    int mx = 0, len = 0;
    for (int i = 0; i < a.size(); i++) {
        if (i == 0 || a[i] <= a[i - 1]) len = 0;
        mx = max(mx, ++len);
    }
    return mx;
}

680. Valid Palindrome II  

Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.
Example 1:
Input: "aba"
Output: True

Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.


bool validPalindrome(string s) {
    int l = 0; int r = s.size() - 1;
    while(l < r){
        if(s[l] != s[r]) 
        	return isPalindrome(s, l, r-1) || isPalindrome(s, l+1, r);
        l++, r--;
    }
    return true;
}

bool isPalindrome(string s, int l, int r){

    while(l < r){
        if(s[l] != s[r]) 
        	return false;
        l++, r--;
    }
    return true;
}


689. Maximum Sum of 3 Non-Overlapping Subarrays

 (1) question 1: 求给定size Sum最大的subarray(连续) 
int maxSubarray(vector<int>& nums, int k) {
    int res = INT_MIN; 
    for (int i = 0; i < num.size() - k + 1; ++i) {
        int sum = 0;
        for (int j = i; j < i + k; ++j) {
            sum += nums[j]; 
        }
        res = max(res, sum);
    }
}


In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.
Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.
Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

Example:
Input: [1,2,1,2,6,7,5,1], 2
Output: [0, 3, 5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    int n = nums.size(), maxsum = 0;
    vector<int> sum = {0}, posLeft(n, 0), posRight(n, n-k), ans(3, 0);
    for (int i:nums) sum.push_back(sum.back()+i);
   // DP for starting index of the left max sum interval
    for (int i = k, tot = sum[k]-sum[0]; i < n; i++) {
        if (sum[i+1]-sum[i+1-k] > tot) {
            posLeft[i] = i+1-k;
            tot = sum[i+1]-sum[i+1-k];
        }
        else 
            posLeft[i] = posLeft[i-1];
    }
    // DP for starting index of the right max sum interval
    // caution: the condition is ">= tot" for right interval, and "> tot" for left interval
    for (int i = n-k-1, tot = sum[n]-sum[n-k]; i >= 0; i--) {
        if (sum[i+k]-sum[i] >= tot) {
            posRight[i] = i;
            tot = sum[i+k]-sum[i];
        }
        else
            posRight[i] = posRight[i+1];
    }
    // test all possible middle interval
    for (int i = k; i <= n-2*k; i++) {
        int l = posLeft[i-1], r = posRight[i+k];
        int tot = (sum[i+k]-sum[i]) + (sum[l+k]-sum[l]) + (sum[r+k]-sum[r]);
        if (tot > maxsum) {
            maxsum = tot;
            ans = {l, i, r};
        }
    }
    return ans;
}


==============================================  



K-Nearest Point C++ 

给定N个坐标Point，每个Point实例有x-坐标和y-坐标。题目要求函数返回离原点最近的k个坐标。  

这道题和找第k大或第k小的题目的思路基本相同，就是在遍历所有Point的同时，维护一个size为k的max—heap，一旦发现size为k+1，我们就把max-heap头上最大的元素移出heap，因为这里的heap是max-heap，所以heap头部的元素比heap里其他的元素都要比heap里的其他元素离原点远。这样使得heap里的元素是到目前为止里原点最近的k的点。

时间复杂度：O(NlogK)
因为需要遍历所有元素，每次遍历一个元素的同时，还要在耗费logk的时间来维护heap。

空间复杂度： O(K) 
heap的size 是k

// Example program
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <math.h>  
#include <vector>
using namespace std;

struct Point { 
    double x;
    double y; 
    Point(double a, double b) {
        x = a;
        y = b;
    }
};

double getDistance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

typedef bool (*comp)(Point, Point);

Point global_origin = Point(0,0);

bool compare(Point a, Point b) {
   return (getDistance(a, global_origin)< getDistance(b, global_origin));
}

vector<Point> Solution(vector<Point> &array, Point origin, int k) {
    global_origin = Point(origin.x, origin.y);
    
    priority_queue<Point, std::vector<Point>, comp> pq(compare);

    vector<Point> ret;

    for (int i = 0; i < array.size(); i++) {
        Point p = array[i];
        pq.push(p);
        if (pq.size() > k)
            pq.pop();
    }

    while (!pq.empty()){
        Point p = pq.top();
        pq.pop();
        ret.push_back(p);
    }
    return ret;
}



int main()
{
   Point p1 = Point(4.5, 6.0);
   Point p2 = Point(4.0, 7.0);
   Point p3 = Point(4.0, 4.0);
   Point p4 = Point(2.0, 5.0);
   Point p5 = Point(1.0, 1.0);
   vector<Point> array = {p1, p2, p3, p4, p5};
   int k = 2;
   Point origin = Point(0.0, 0.0);
   vector<Point> ans = Solution(array, origin, k);
   for (int i = 0; i < ans.size(); i++) {
       cout << i << ": " << ans[i].x << "," << ans[i].y << endl;
   }
   //cout << getDistance(p1, p2) << endl;
}


===============================

//a function to randomly select k items from a stream of n items (reservoir sampling)  
void selectKItems(int stream[], int n, int k) {
    int i;  // index for elements in stream[]
 
    // reservoir[] is the output array. Initialize it with
    // first k elements from stream[]
    int reservoir[k];
    for (i = 0; i < k; i++)
        reservoir[i] = stream[i];
 
    // Use a different seed value so that we don't get
    // same result each time we run this program
    srand(time(NULL));
 
    // Iterate from the (k+1)th element to nth element
    // for (; i < n; i++)  // i start from k
    while(i < n) {
	    // Pick a random index from 0 to i.
	    int j = rand() % (i+1);

	    // If the randomly  picked index is smaller than k, then replace
	    // the element present at the index with new element from stream
	    if (j < k)
	      reservoir[j] = stream[i];

	    ++i;
    }
 
    printf("Following are k randomly selected items \n");
    printArray(reservoir, k);
}



void selectKItems(int stream[], int n, int k) { 


}



====================================

Random Pick Index 随机拾取序列 // reservoir sampling

Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
Note:
The array size can be very large. Solution that uses too much extra space will not pass the judge.

那么如果了解了水塘抽样，这道题就不算一道难题了，我们定义两个变量，计数器cnt和返回结果res，我们遍历整个数组，如果数组的值不等于target，直接跳过；如果等于target，计数器加1，然后我们在[0,cnt)范围内随机生成一个数字，如果这个数字是0，我们将res赋值为i即可. 

int pick(vector<int> v, int target) {

    int cnt = 0, res = -1;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] != target) continue;
        ++cnt;
        if (rand() % cnt == 0) res = i;
    }
    return res;
}

382. Linked List Random Node 链表随机节点  

Given a singly linked list, return a random nodes value from the linked list. Each node must have the same probability of being chosen.

Follow up:
What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?

这道题给了我们一个链表，让我们随机返回一个节点，那么最直接的方法就是先统计出链表的长度，然后根据长度随机生成一个位置，然后从开头遍历到这个位置即可 

solution 1: 

/** Returns a random node's value. */
int getRandom(ListNode* head) {
	int len = 0; 
	ListNode* cur = head; 
	while(cur) {
		++len; 
		cur = cur->next; 
	}

    int t = rand() % len;
    ListNode *cur = head;
    while (t) {
        --t;
        cur = cur->next;
    }
    return cur->val;
}

solution 2: // reservoir sampling 

Follow up中说链表可能很长，我们没法提前知道长度，这里用到了著名了水塘抽样的思路，由于限定了head一定存在，所以我们先让返回值res等于head的节点值，然后让cur指向head的下一个节点，定义一个变量i，初始化为2，若cur不为空我们开始循环，我们在[0, i - 1]中取一个随机数，如果取出来0，那么我们更新res为当前的cur的节点值，然后此时i自增一，cur指向其下一个位置，这里其实相当于我们维护了一个大小为1的水塘，然后我们随机数生成为0的话，我们交换水塘中的值和当前遍历到底值，这样可以保证每个数字的概率相等


int getRandom(head) {

    int res = head->val, i = 2;
    ListNode *cur = head->next;

    while (cur) {
        int j = rand() % i;
        if (j == 0) res = cur->val;
        ++i;
        cur = cur->next;
    }
    return res;
}

==============================================  
[LintCode] 378 Convert Binary Search Tree to Doubly Linked List 
/**
 * Definition of TreeNode:
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left, right;
 *     public TreeNode(int val) {
 *         this.val = val;
 *         this.left = this.right = null;
 *     }
 * }
 * Definition for Doubly-ListNode.
 * public class DoublyListNode {
 *     int val;
 *     DoublyListNode next, prev;
 *     DoublyListNode(int val) {
 *         this.val = val;
 *         this.next = this.prev = null;
 *     }
 * }
 */ 

public DoublyListNode bstToDoublyList(TreeNode root) {  
    // Write your code here
    if (root == null) return null;

    Stack<TreeNode> stack = new Stack<TreeNode>();
    TreeNode cur = root;
    DoublyListNode head = null;
    DoublyListNode prev = null;
    
    while (cur != null || !stack.empty()) {
        while (cur != null) {
            stack.push(cur);
            cur = cur.left;
        }
        cur = stack.pop();
        DoublyListNode node = new DoublyListNode(cur.val);
        if (head == null) {
            head = node;
        }
        node.prev = prev;
        if (prev != null) {
            prev.next = node;
        }
        cur = cur.right;
        prev = node;
    }
    return head;
}

===========================================

找出string中出现次数最多的字母, followup 优化

Time Complexity: O(n)
Space Complexity: O(1) — Because we are using fixed space (Hash array) irrespective of input string size.

char getMaxOccuringChar(string str) {
    // Create array to keep the count of individual
    // characters and initialize the array as 0
    const it ASCII_SIZE = 256; 
    int count[ASCII_SIZE] = {0};
 
    // Construct character count array from the input
    // string.
    int len = str.size();
    for (int i=0; i<len; i++)
        count[str[i]]++;
 
    int max = -1;  // Initialize max count
    char result;   // Initialize result
 
    // Traversing through the string and maintaining
    // the count of each character
    for (int i = 0; i < len; i++) {
        if (max < count[str[i]]) {
            max = count[str[i]];
            result = str[i];
        }
    }
    return result;
}

===========================================  
题目是给定W*H的Grid，给出算法在其中随机均匀地放M颗地雷。 reservoir sampling 

int main() {

const int W = 6; 
const int H = 3; 
const int m = 4; 

vector<vector<int>> res;  // 注意
// vector<vector<int>> res(H, vector<int>(W));  // create additional H*W 个 0

int cnt = 0; 
vector<int> vec1; 
vector<int> vec(W*H); // 默认生成W*H 个 0
// vector<int> vec(W*H, 0);
int n = vec.size();

for (int i = 0; i < m;) {
    srand((unsigned)time(NULL)); // time seed
    int index = random() % n; 
    if (vec[index] == 0)
        vec[index] = 1; 
    else 
        continue;
    ++i;
}


for (int i = 0; i < vec.size(); ++i) {
    cnt++; 
    vec1.push_back(vec[i]);

    if (cnt == W) {
        res.push_back(vec1);
        cnt = 0; 
        vec1.clear(); 
    }

}

for (auto i : res) {
    for (auto j : i) {
        cout << j << " "; 
    }
    cout << endl;
}

return 0; 
}

======================================   
125. Valid Palindrome 验证回文字符串  
  // 大小写不同也算错。 如'A'和'a'是不一样的。没有followup。

bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1 ;
    while (left < right) {
        if (!isAlphaNum(s[left])) ++left;
        else if (!isAlphaNum(s[right])) --right;
        // else if ((s[left] + 32 - 'a') %32 != (s[right] + 32 - 'a') % 32) return false;
        else if (s[left] != s[right]) return false; 
        else {
            ++left; --right;
        }
    }
    return true;
}


253. Meeting Rooms II 会议室之二  变异： 
// 输出最 overlap的数 。跟原题不同的是，[3,5]和[5,5]这两个interval也算overlap，应该输出2，不是 1。所以只要把原题的intervals.start >= heap.peek()改成>就可以  

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
        // if (starts[i] < ends[endpos]) ++res; // !!!!!!  改了这行
        if (starts[i] <= ends[endpos]) ++res;
        else ++endpos;
    }
    return res;
}


再来一看一种使用最小堆来解题的方法，这种方法先把所有的时间区间按照起始时间排序，然后新建一个最小堆，开始遍历时间区间，如果堆不为空，且首元素小于等于当前区间的起始时间，我们去掉堆中的首元素，把当前区间的结束时间压入堆，由于最小堆是小的在前面，那么假如首元素小于等于起始时间，说明上一个会议已经结束，可以用该会议室开始下一个会议了，所以不用分配新的会议室，遍历完成后堆中元素的个数即为需要的会议室的个数

int minMeetingRooms(vector<Interval>& intervals) {
    sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b){return a.start < b.start;});
    
    priority_queue<int, vector<int>, greater<int>> q;
    for (auto a : intervals) {
        // if (!q.empty() && q.top() <= a.start) q.pop();  // !!!!!!  改了这行
        if (!q.empty() && q.top() < a.start) q.pop();
        q.push(a.end);
    }
    return q.size();
}

============================================= 

moveZero的变种，就是要moveZero到前 ，moveOne到后 ， 改变顺序

void moveZeroesToBack(vector<int>& nums) {
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        if (nums[i] == 1) {
            swap(nums[i], nums[j++]);
        }
    }
}

void moveZeroesToFront(vector<int>& nums) {
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        if (nums[i] == 0) {
            swap(nums[i], nums[j++]);
        }
    }
}


=========================================== 

1. 几何算法问题，给你一堆重复的矩形，求重合矩形最多的坐标位置，思路是一个二位的meeting room II 但不太会

2. 合并邮件列表
list1 a@a.com b@b.com
list2 b@b.com c@c.com. 
list3 e@e.com.
list4 a@a.com

=======================

85. Maximal Rectangle 最大矩形  

====================

sort color, valid parenthesis， subset II  
======================

Kth Smallest Element in Array LC215    第k小的数字

solution 1: using heap  O(n)*h
int findKthSmallest(vector<int>& nums, int k) {
    // priority_queue<int, vector<int>, greater<int>> q;  // 从大到小排列 
    priority_queue<int> q;  // default: 从小到大排列 
    for (int i = 0; i < nums.size(); ++i) {
        q.push(nums[i]); 
        if (q.size() > k) 
            q.pop(); 
    }
    if (q.size() < k) 
        return -1; 
    else
        return q.top();
}

solution 2: quickselect O(n)

int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[left], l = left + 1, r = right;
    while (l <= r) {
        if (nums[l] < pivot && nums[r] > pivot) {   // large value on the left, small value on the right
            swap(nums[l++], nums[r--]);
        }
        if (nums[l] >= pivot) ++l;
        if (nums[r] <= pivot) --r;
    }
    swap(nums[left], nums[r]);
    return r;
}

// array is sorted from large to small
int findKthSmallest(vector<int>& nums, int k) {
    int left = 0, right = nums.size() - 1;
    int n = nums.size(); 
    while (true) {
        int pos = partition(nums, left, right);
        // if (pos == k - 1) return nums[pos]; 
        if (pos == n - k) return nums[pos]; // Kth Smallest Element in Array
        // else if (pos > k - 1) right = pos - 1;
        else if (pos > n - k) right = pos - 1;  // Kth Smallest Element in Array
        else left = pos + 1;
    }
}
=====================================

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

=============================================  

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
====================================== 

3 Sum，返回值是boolean  

Validate BST 

57. Insert Interval 插入区间  

56. Merge Intervals 合并区间 

find the k-th largest number in an unsorted array of length n. follow up, what if n is much greater than k.  如n=1000000000， k=10

number of islands  

Merge K sorted List

word break, recursion + DP 

sparse vector dot product  

398. Random Pick Index 随机拾取序列  

138. Copy List with Random Pointer 拷贝带有随机指针的链表 

Friend Recommendation, Recommend K friends with most mutual friends. 

Combination sum I & II

2维矩形最大重合问题
一维： Maximum number of overlapping intervals 

random subset of size K 

vector<vector<int> > subsetsWithDup(vector<int> &S, int k) {
    vector<vector<int> > res;
    vector<int> out;
    sort(S.begin(), S.end());
    getSubsets(S, 0, out, res, k);
    return res;
}

void getSubsets(vector<int> &S, int pos, vector<int> &out, vector<vector<int> > &res, int k) {
    if (out.size() == k)  // additional line here
        res.push_back(out);
    for (int i = pos; i < S.size(); ++i) {
        out.push_back(S[i]);
        getSubsets(S, i + 1, out, res);
        out.pop_back();
        while (S[i] == S[i + 1]) ++i; // skip duplicates
    }
}

===================

257. Binary Tree Paths 二叉树路径  

Given a binary tree, return all root-to-leaf paths.
For example, given the following binary tree:
   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:  ["1->2->5", "1->3"]
// 直接打印, time complexity: O(nlogn) , logn 为path的长度

// vector<string> binaryTreePaths(TreeNode* root) {
void binaryTreePaths(TreeNode* root) {
    vector<string> res;
    if (root) dfs(root, "", res);
    // return res;
}
void dfs(TreeNode *root, string out, vector<string> &res) {
    out += to_string(root->val);
    if (!root->left && !root->right) 
        cout << out << end; 
        // res.push_back(out);
    else {
        if (root->left) dfs(root->left, out + "->", res);
        if (root->right) dfs(root->right, out + "->", res);
    }
}

=======================

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
======================== 

写个BST 的 in-order iterator. 要写的function有 next() 和 all()。follow up是改成preorder和 postorder。 我全用的stack

 合并邮件列表, Merge Email Lists
https://gist.github.com/gcrfelix/a6849f256372b7c40a2265ed88d4a8b8


=================================================

[LeetCode] Daily Temperatures 日常温度
 
Given a list of daily temperatures, produce a list that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.
For example, given the list temperatures = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].
Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].

这道题给了我们一个数组，让我们找下一个比当前数字大的数字的距离，我们研究一下题目中给的例子，发现数组是无序的，所以没法用二分法快速定位下一个大的数字，那么最先考虑的方法就是暴力搜索了，写起来没有什么难度，但是OJ并不答应。实际上这道题应该使用递减栈Descending Stack来做，栈里只有递减元素，思路是这样的，我们遍历数组，如果栈不空，且当前数字大于栈顶元素，那么如果直接入栈的话就不是递减栈了，所以我们取出栈顶元素，那么由于当前数字大于栈顶元素的数字，而且一定是第一个大于栈顶元素的数，那么我们直接求出下标差就是二者的距离了，然后继续看新的栈顶元素，直到当前数字小于等于栈顶元素停止，然后将数字入栈，这样就可以一直保持递减栈，且每个数字和第一个大于它的数的距离也可以算出来了           

time: O(n)  
 vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res; 
        for (int i = 0; i < temperatures.size(); ++i) {
            int j; 
            for (j = i + 1; j < temperatures.size(); ++j) {
                if (temperatures[j] > temperatures[i]) { res.push_back(j - i); break;}
            }
            if (j >= temperatures.size()) res.push_back(0);
        }
        
        return res;
        
    }


time: O(n), space: O(n)
vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size(), 0); 
        stack<int> st; 
        
        for (int i = 0; i < temperatures.size(); ++i) { 
            while(!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int t = st.top(); st.pop();
                res[t] = i - t; 
            }
            
            st.push(i);   
        }
        return res; 
}

========================================   


[LeetCode] Maximum XOR of Two Numbers in an Array 数组中异或值最大的两个数字
Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.
Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.
Could you do this in O(n) runtime?

Input: [3, 10, 5, 25, 2, 8]
Output: 28
Explanation: The maximum result is 5 ^ 25 = 28.

我们还需要用上一个异或的特性，假设a和b产生了最终的答案max，即a ^ b = x，那么根据异或的特性，a ^ x = b。同理，a和b的最高位（前n位）也有相同的性质。

先以最高位为例子，我们可以把所有的数字的最高位放到一个HashSet里面，然后使用1与set里面的所有数字进行异或，如果得出的结果仍然在set里面，那么最终结果的最高位必然为1，否则为0。也即，先假定结果为1，然后与set中所有数字异或，假定a与1异或得到结果b（a ^ 1 = b），而b仍然在set里面，那么说明set中有两个数字异或能得到1（a ^ b = 1）。否则，set中没有两个数字能够异或得到1，那么最终结果的最高位为1的假设失败，说明最终结果的最高位为0。以此类推可以得到第二位、第三位。。。的数字。

再做一下推广，我们将所有数字的前N位放到一个HashSet里面，然后使用之前N-1位得到的最大值前缀prefix与set里面的所有数字进行异或，如果得出的结果仍然在set中，那么第N位必然为1，否则为0。

举个例子，给定数组[14, 11, 7, 2]，二进制表示分别为[1110, 1011, 0111, 0010]。题目说了，数字最长不会超过32位，所以应从i = 31开始，但是所有数字中最多位4位数，简单起见，我直接从最高位i=3开始

1. i = 3, set = {1000, 0000} => max = 1000
2. i = 2, set = {1100, 1000, 0100, 0000} => max = 1100
3. i = 1, set = {1110, 1010, 0110, 0010} => max = 1100
4. i = 0, set = {1110, 1011, 0111, 0010} => max = 1100
最终答案是1100 => 12，1011 ^ 0111 = 1100(11 ^ 7 = 12)。


// time: O(n), space: O(n)
   int findMaximumXOR(vector<int>& nums) {
        int res = 0, mask = 0;
        // unordered_set<int> st;  wrong 

        for (int i = 31; i >= 0; --i) {
        // for (int i = 0; i <= 31; ++i) {  // wrong, 因为要取可行temp的最大值 

            // 为获取前n位的临时变量  
            mask = mask | (1 << i);
            unordered_set<int> s;  //每次循环s都会清空
            for (int num : nums) {
                  // 将所有数字的前n位放入set中  
                s.insert(num & mask);  // 注意是& 
            }
            // 假定第n位为1,前n-1位max为之前迭代求得 
            int tmp = res | (1 << i);  // 先假设 res 为 res| (1<<i)
            for (int prefix : s) {   
                // 查看`b`是否在
                if (s.count(tmp ^ prefix)) {
                 // b存在，第n位为1         
                    res = tmp;
                    break;
                }
            }
        }
        return res;
    }

=======================================  

[LeetCode] Flatten Nested List Iterator 压平嵌套链表迭代器
Given a nested list of integers, implement an iterator to flatten it.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].
Example 2:
Given the list [1,[4,[6]]],
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].

这道题让我们建立压平嵌套链表的迭代器，关于嵌套链表的数据结构最早出现在Nested List Weight Sum中，而那道题是用的递归的方法来解的，而迭代器一般都是用迭代的方法来解的，而递归一般都需用栈来辅助遍历，由于栈的后进先出的特性，我们在对向量遍历的时候，从后往前把对象压入栈中，那么第一个对象最后压入栈就会第一个取出来处理，我们的hasNext()函数需要遍历栈，并进行处理，如果栈顶元素是整数，直接返回true，如果不是，那么移除栈顶元素，并开始遍历这个取出的list，还是从后往前压入栈，循环停止条件是栈为空，返回false

solution 1: stack 从后往前iteration 去模拟recursion 

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for (int i = nestedList.size() - 1; i >= 0; --i) {
            st.push(nestedList[i]);
        }
    }

    int next() {
        auto a = st.top(); st.pop(); 
        return a.getInteger();
    }

    bool hasNext() {
        while(!st.empty()) {
            auto a = st.top(); // st.pop(); 有bug 
            if (a.isInteger()) return true; 
            st.pop(); 

            for(int i = a.getList().size() - 1; i >= 0; --i) {
                st.push(a.getList()[i]);
            }
        }
        return false; 
    }
private: 
    stack<NestedInteger> st; 
};

solution 2: queue recusion 去模拟stack  

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        make_queue(nestedList);
    }
    
    void make_queue(vector<NestedInteger>& nestedList) {
        for (int i = 0; i < nestedList.size(); ++i) {
            if (nestedList[i].isInteger()) q.push(nestedList[i].getInteger());
            else {
                make_queue(nestedList[i].getList());
            }
        }
    }

    int next() {
        int res = q.front(); q.pop();
        return res; 
    }

    bool hasNext() {
        return !q.empty(); 
    }
    
private: 
    queue<int> q; 
};
=======================================   
[LeetCode] Meeting Rooms II 会议室之二
 
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.
For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

这道题是之前那道Meeting Rooms的拓展，那道题只让我们是否能参加所有的会，也就是看会议之间有没有时间冲突，而这道题让我们求最少需要安排几个会议室，有时间冲突的肯定需要安排在不同的会议室。这道题有好几种解法，我们先来看使用TreeMap来做的，我们遍历时间区间，对于起始时间，映射值自增1，对于结束时间，映射值自减1，然后我们定义结果变量res，和房间数rooms，我们遍历TreeMap，时间从小到大，房间数每次加上映射值，然后更新结果res，遇到起始时间，映射是正数，则房间数会增加，如果一个时间是一个会议的结束时间，也是另一个会议的开始时间，则映射值先减后加仍为0，并不用分配新的房间，而结束时间的映射值为负数更不会增加房间数

  int minMeetingRooms(vector<Interval>& intervals) {
        // unordered_map<int, int> m; // wrong 有bug   
        map<int, int> m; 
        
        for (auto a : intervals) {          
            m[a.start]++;                       
            m[a.end]--;                        
        }
        
        int res = 0, cur = 0; 
        for (auto a : m) {
            // res = max(res, res += a.second);  //wrong, 
            res = max(res, cur += a.second);  
        }
        
        return res; 
    }

==============================================   
[LeetCode] Game of Life 生命游戏
 
According to the Wikipedia article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 

Write a function to compute the next state (after one update) of the board given its current state.

Follow up: 
Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?
---------------------------
由于题目中要求我们用置换方法in-place来解题，所以我们就不能新建一个相同大小的数组，那么我们只能更新原有数组，但是题目中要求所有的位置必须被同时更新，但是在循环程序中我们还是一个位置一个位置更新的，那么当一个位置更新了，这个位置成为其他位置的neighbor时，我们怎么知道其未更新的状态呢，我们可以使用状态机转换：
状态0： 死细胞转为死细胞
状态1： 活细胞转为活细胞
状态2： 活细胞转为死细胞
状态3： 死细胞转为活细胞
最后我们对所有状态对2取余，那么状态0和2就变成死细胞，状态1和3就是活细胞，达成目的。

live -> live : 2, 3 live neighbors          
live -> die : 0, 1, 4, 5, 6 ... live neighbors          
die -> live : 3 live neighbors                  
                                    
die -> die 0                
live -> live 1              
die -> live 3           
live -> die 2       

vector<pair<int, int>> dir = {{-1, -1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}, {1, 1}, {0, -1}, {0, 1}};
    
    void gameOfLife(vector<vector<int>>& board) {
        if(board.empty() || board[0].empty()) return; 
        
        for(int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                int count = 0; 
               for (auto a : dir) {
                   int x = i + a.first, y = j + a.second; 
                   if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size()) continue; 
                   // if (board[x][y] == 1) count++;  // 有bug    
                   if (board[x][y] == 1 || board[x][y] == 2) count++; 
                  
               } 
                // if (board[i][j] == 1 && (count != 2 || count != 3)) {board[i][j] = 2; continue;}         // 有bug      
                if (board[i][j] == 1 && (count != 2 && count != 3)) {board[i][j] = 2; continue;}       
                if (board[i][j] == 0 && count == 3) {board[i][j] = 3; continue;}   
                
            }    
        }
        
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                board[i][j] = board[i][j] % 2; 
            }
        }
    }


==============================================   
Longest Absolute File Path  

 下面这种方法用到了字符串流机制，通过getline函数可以一行一行的获取数据，实际上相当于根据回车符\n把每段分割开了，然后对于每一行，我们找最后一个空格符\t的位置，然后可以得到文件或文件夹的名字，然后我们判断其是文件还是文件夹，如果是文件就更新res，如果是文件夹就更新哈希表的映射

input: "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"        
output: 20  dir\nsubdir1\nfile.ext       

  int lengthLongestPath(string input) {         
        int res = 0;                     
        istringstream ss(input);        
        unordered_map<int, int> m{{0, 0}};      
        string str;            
        while (getline(ss, str, '\n')) {           
            
            int level = str.find_last_of('\t') + 1;   // static const size_t npos = -1;     
            int len = str.substr(level).size();         
            
            if (str.find('.') != string::npos) {            
                res = max(res, m[level] + len);   // 最后文件名没有\n, 所以没有\n                   
            } else {                                        
                m[level + 1] = m[level] + len + 1;  // len是dir的长度, 1是\n的长度                   
            }                                                    
        }                                   
        return res;                     
    }   


int lengthLongestPath(string input) {
    in res = 0;
    istringstream ss(input); 
    string str; 
    unordered_map<int, int> m = {{0, 0}}; 

    while(getline(ss, str, '\n')) {
        int level = str.find_last_of('\t') + 1;
        int len = str.substr(level).size(); 

        if (str.find('.') == string::npos) {
            m[leve + 1] = m[level] + len + 1; 
        }  else {
            res = max(res, m[level] + len); 
        }

    }

    return res; 
}


============================================
[LeetCode] Implement Trie (Prefix Tree) 实现字典树(前缀树)
 
Implement a trie with insert, search, and startsWith methods.
Note:
You may assume that all inputs are consist of lowercase letters a-z.

class TrieNode {
public: 
    TrieNode* child[26]; 
    bool isWord; 
    TrieNode() : isWord(false) {
        // for (auto a : child) a = NULL;  // there is bug without &, 因为要auto& 才能更改child的值 
        for (auto& a : child) a = NULL; 

    }
};


class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();     
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* p = root; 
        // TrieNode* p = new TrieNode(); 

        for (auto a : word) {
            int i = a - 'a'; 
            if (!p->child[i]) p->child[i] = new TrieNode(); 
            p = p->child[i]; 
        }
        p->isWord = true; 
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* p = root; 
     // TrieNode* p = new TrieNode();
        for (auto a : word) {
            int i = a - 'a'; 
            if (!p->child[i]) return false; 
            p = p->child[i]; 
        }
        return p->isWord; 
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* p = root; 
     // TrieNode* p = new TrieNode();
        for (auto a : prefix) {
            int i = a - 'a'; 
            if (!p->child[i]) return false; 
            p = p->child[i]; 
        }
        return true; 
    }
private: 
    TrieNode* root; 
};

===================================   
[LeetCode] Letter Combinations of a Phone Number 电话号码的字母组合
Given a digit string, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.


    vector<string> letterCombinations(string digits) {
        vector<string> res; 
        string str; 
        vector<string> board = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        if (digits.empty()) return res;                                 
        
        dfs(res, str, board, digits, 0); 
        return res;
    }
    
    void dfs(vector<string>& res, string& str, vector<string> board, string digits, int idx) {
        if (idx == digits.size()) {
            res.push_back(str);
        } else {
            
            string temp = board[digits[idx] - '2']; 
            for (int i = 0; i < temp.size(); ++i) {
                str.push_back(temp[i]);
                dfs(res, str, board, digits, idx + 1);
                str.pop_back(); 
            }   
            
        }
    }

========================================  
[LeetCode] Summary Ranges 总结区间
 
Given a sorted integer array without duplicates, return the summary of its ranges.
For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].
// k 记录开始数字, i - 1 记录结束数字 

vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res; 
        if (nums.empty()) return res; 
        string str; 
        // str += nums[0];
        int k = 0; 
        for (int i = k + 1; i <= nums.size(); ++i) {
            if (nums[i] - nums[i-1] == 1) continue;   // 可能有bug  
            else {
                if ((i - 1) - k > 0) {
                    str += to_string(nums[k]);        
                    str += "->";                    
                    str += to_string(nums[i-1]); 
                    res.push_back(str);
                    str.clear(); 
                    k = i; 
                } else {
                    str += to_string(nums[k]);
                    res.push_back(str); 
                    str.clear(); 
                    k = i; 
                }
            }
            
        }
        
        return res;
    }

better solution: 
vector<string> summaryRanges(vector<int>& nums) {
        vector<string> res;
        int i = 0, n = nums.size();
        while (i < n) {
            int j = 1;
            while (i + j < n && nums[i + j] - nums[i] == j) ++j;
            
            if (j <= 1) 
                res.push_back(to_string(nums[i])); 
            else 
                res.push_back(to_string(nums[i]) + "->" + to_string(nums[i + j - 1]));

            i += j;
        }
        return res;
}


     
=================================   
[LeetCode] License Key Formatting 注册码格式化
 
Now you are given a string S, which represents a software license key which we would like to format. The string S is composed of alphanumerical characters and dashes. The dashes split the alphanumerical characters within the string into groups. (i.e. if there are M dashes, the string is split into M+1 groups). The dashes in the given string are possibly misplaced.
We want each group of characters to be of length K (except for possibly the first group, which could be shorter, but still must contain at least one character). To satisfy this requirement, we will reinsert dashes. Additionally, all the lower case letters in the string must be converted to upper case.
So, you are given a non-empty string S, representing a license key to format, and an integer K. And you need to return the license key formatted according to the description above.
Example 1:
Input: S = "2-4A0r7-4k", K = 4
Output: "24A0-R74K"

string licenseKeyFormatting(string S, int K) {
    string res; 
    
    int count = 0; 
    for (int i = S.size() - 1; i >= 0; --i) {
        if (S[i] == '-') continue; 
        res.push_back(toupper(S[i])); 
        count++; 
        if (count % K == 0) res.push_back('-'); 
    }
    if (!res.empty() && res.back() == '-') res.pop_back(); 
    
    return string(res.rbegin(), res.rend()); 
    
}


=====================================================          

// 在vector vec里删掉另一个vector nums里的数据 
int count = 0;    
for (auto a : nums) {
    if (a <= upper && a >= lower) {
        vec.erase(vec.begin() + (a - lower - count)); 
        count++; 
    }
}

============================================  

[LeetCode] Missing Ranges 缺失区间
 
Given a sorted integer array where the range of elements are [0, 99] inclusive, return its missing ranges.
For example, given [0, 1, 3, 50, 75], return [“2”, “4->49”, “51->74”, “76->99”]

string get_range(int start, int end) {
    if (start == end) 
        return to_string(start); 
    else 
        return to_string(start) + "->" + to_string(end);
}
    
vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
    vector<string> result;
    long int pre = (long) lower - 1;
    long int cur; 
    
    if(nums.size() <= 0) {
        result.push_back(get_range(lower, upper));
        return result;
    }   
    
    for(int i = 0; i <= nums.size(); i++) {
        if (i == nums.size()) {
            cur = (long) upper + 1; 
        } else {
            cur = (long) nums[i]; 
        }
        
       // long int cur = (i==nums.size()? (long)upper+1:(long)nums[i]);
       if(cur - pre >= 2)
           result.push_back(get_range(pre + 1, cur - 1));
        
        pre = cur;
    }
    
    return result;
}

=====================================  
[LeetCode] Moving Average from Data Stream 从数据流中移动平均值
 
Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

For example,
MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3

这道题定义了一个MovingAverage类，里面可以存固定个数字，然后我们每次读入一个数字，如果加上这个数字后总个数大于限制的个数，那么我们移除最早进入的数字，然后返回更新后的平均数，这种先进先出的特性最适合使用队列queue来做，而且我们还需要一个double型的变量sum来记录当前所有数字之和，这样有新数字进入后，如果没有超出限制个数，则sum加上这个数字，如果超出了，那么sum先减去最早的数字，再加上这个数字，然后返回sum除以queue的个数即可


class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        // vec.resize(size);
        size_ = size; 
        sum = 0; 
    }
    
    double next(int val) {
        // int sum = 0; 
        if (vec.size() < size_)
            vec.push_back(val); 
        else {
            sum -= vec[0]; 
            vec.erase(vec.begin()); 
            vec.push_back(val);
        }
        // for (auto a : vec) sum += a; 
        // sum += vec[vec.size() - 1];
        sum += val; 
        return sum / vec.size(); 
        
    }
private: 
    vector<int> vec; 
    int size_;
    double sum; 
};


==========================================    
[LeetCode] Repeated String Match 重复字符串匹配
 
Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.
For example, with A = "abcd" and B = "cdabcdab".
Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

都是每次给t增加一个字符串A，我们其实可以直接算出最多需要增加的个数，即B的长度除以A的长度再加上2，当B小于A的时候，那么可能需要两个A，所以i就是小于等于2，这样我们每次在t中找B，如果找到了，就返回i，没找到，就增加一个A，循环推出后返回-1即可


int repeatedStringMatch(string A, string B) {
        string t = A;
        for (int i = 1; i <= B.size() / A.size() + 2; ++i) {
            if (t.find(B) != string::npos) return i;
            t += A; 
            // A += A;
        }
        return -1;    
}

=====================================
Binary Tree Longest Consecutive Sequence 二叉树最长连续序列

Given a binary tree, find the length of the longest consecutive sequence path.
The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

   1
    \
     3
    / \
   2   4
        \
         5
Longest consecutive sequence path is 3-4-5, so return 3.

   2  
    \
     3  
    / 
   2    
  / 
 1
Longest consecutive sequence path is 2-3,not3-2-1, so return 2.

这道题让我们求二叉树的最长连续序列，关于二叉树的题基本都需要遍历树，而递归遍历写起来特别简单，下面这种解法是用到了递归版的先序遍历，我们对于每个遍历到的节点，我们看节点值是否比参数值(父节点值)大1，如果是则长度加1，否则长度重置为1，然后更新结果res，再递归调用左右子节点即可，

Time complexity: O(n). The time complexity is the same as an in-order traversal of a binary tree with n nodes.
Space complexity: O(n). The extra space comes from implicit stack space due to recursion. For a skewed binary tree, the recursion could go up to n levels deep.

int longestConsecutive(TreeNode* root) {
    if (!root) return 0; 
    int count = 0;
    int res = 0; 
    dfs(root, root->val, count, res);
    
    return res; 
}

// void dfs(TreeNode* node, int val, int& count, int& res) {  // 若int& count则有bug, 因为count不做global存储   
void dfs(TreeNode* node, int val, int count, int& res) {
    if (!node) return; 
    if (node->val == val + 1) count++; 
    else count = 1; 
    res = max(res, count); 
    dfs(node->left, node->val, count, res);
    dfs(node->right, node->val, count, res);
}

===============================================    
[LeetCode] Zigzag Iterator 之字形迭代器
 

Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question - Update (2015-09-18):
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

[1,2,3]
[4,5,6,7]
[8,9]
It should return [1,4,8,2,5,9,3,6,7].

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        int n1 = v1.size(), n2 = v2.size(), n = max(n1, n2);
        for (int i = 0; i < n; ++i) {
            if (i < n1) v.push_back(v1[i]);
            if (i < n2) v.push_back(v2[i]);
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
    int i = 0;  // 这个i 和 for循环里的i是独立的; 这个i是给next和hasNext看的   
};

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

=====================================   
[LeetCode] Bomb Enemy 炸弹人
 
Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
Note that you can only put the bomb at an empty cell.

Example:
For the given grid
0 E 0 0
E 0 W E
0 E 0 0
return 3. (Placing a bomb at (1,1) kills 3 enemies)

=======================================  
Word Break 

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

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

===================
1. Given a doubly linked list, remove the first node with a value input.  
case 1 (value is head): 
Node* p = head; 
if (value == head->val) {
    head = head->next; 
    head->pre = NULL; 
    delete p; 
} 

case 2, 3 (value in the middle or tail) 
while(value != p->val) {
    p = p->next; 
}
if (p->next != NULL) {
    Node* Pre = p->prev; 
    Node* Next = p->next; 
    Next->pre = Pre; 
    Pre->next = Next; 
    delete p; 
} else {
    Node* Pre = p->pre; 
    Pre->next = NULL; 
    delete p; 
}

================================================  


template<typename T> 
class TreeNode {
    TreeNode* left, *right;  
    int val; 
    
};
vector<T> vec; 



int rand (void);
Generate random number
Returns a pseudo-random integral number in the range between 0 and RAND_MAX.     
v1 = rand() % 100;         // v1 in the range 0 to 99     
v2 = rand() % 100 + 1;     // v2 in the range 1 to 100      
v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 


#include <iostream>
#include <ctime>
using namespace std;

int main() {
    const int MAX_TIMES = 20000000;
    srand(static_cast<unsigned int>(time(0)));
    
    int in = 0;
    for (int i = 0; i < MAX_TIMES;i++) {
        double x = static_cast<double>(rand()) / RAND_MAX;
        double y = static_cast<double>(rand()) / RAND_MAX;
        if (x*x+y*y<=1.0) {
            in++;
        }
    }

    double pi = 4.0 * in / MAX_TIMES;
    cout << "PI = " << pi << endl;
    return 0;
}



bubble sort  
// A function to implement bubble sort
void bubbleSort(vecto<int>& arr) {
   // int i, j;
   for (int i = 0; i < arr.size() - 1; i++) {     
        // Last i elements are already in place   
        for (int j = 0; j < arr.size() - 1 - i; j++) {
           if (arr[j] > arr[j+1])
              swap(arr[j], arr[j+1]);  
        }
    }
}

merge sort, binary search, quick sort, 

================================
  思路是在原链表之前建立一个dummy node，因为首节点会变，然后从head开始，将之后的一个节点移到dummy node之后，重复此操作知道head成为末节点为止，

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


==================================



soulmachine.gitbooks.io/algorithm-essentials/cpp/dfs/unique-paths.html



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

DS: vector<string> vec(n); 
Alg: bool down; 

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
    // vector<string> arr(n); 

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

    if(n%2==1) ret[n/2][n/2] = val;
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

void dfs(int n, int step, int k, vector<bool> &flag, string path, string &result)
{
    if( step == n )
    {
        num++;
        if( num == k )
            result = path;
        return;
    }
    
    for(int i=1; i <= n; ++i)
    {
        if( !flag[i] )
        {
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


65. 



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


68. 

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

126. 

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



class Buggy {
public: 
    Buggy(int mParam); 
    virtual ~Buggy(); 
    Buggy(const Buggy& src); 
    Buggy& operator=(const Buggy& rhs); 
    Buggy(Buggy&& src) noexcept;  
    Buggy& operator=(Buggy&& rhs) noexcept; 

private: 
    void func(int mparam); 
    int mParam;
    double* mGraphicDimension;
};


Buggy::Buggy(int inParam) : mParam(inParam) {
    mGraphicDimension = new double; 
}

Buggy::Buggy(const Buggy& src) {
    mParam = src.mParam; 
    mGraphicDimension = new double; 
    *mGraphicDimension = *(src.mGraphicDimension);
}

Buggy& Buggy::operator=(const Buggy& rhs) {
    if(&rhs == this) return *this;  
    mParam = rhs.mParam; 
    delete mGraphicDimension; // 要先delete, 因为有可能存在
    mGraphicDimension = new double; 
    *mGraphicDimension = *(rhs.mGraphicDimension); 
    return *this; 
}

Buggy::Buggy(Buggy&& src) noexcept {
    mParam = src.mParam; 
    // mGraphicDimension = new double; 
    mGraphicDimension = src.mGraphicDimension; 
    src.mGraphicDimension = nullptr; 

}

Buggy& Buggy::operator=(Buggy&& rhs) noexcept {
    if (this == &rhs) return *this; 
    mParam = rhs.mParam; 
    mGraphicDimension = rhs.mGraphicDimension; 
    rhs.mGraphicDimension = nullptr; 
    return *this; 
}

Buggy::~Buggy() {
    delete mGraphicDimension; 
    mGraphicDimension = nullptr; 

}


