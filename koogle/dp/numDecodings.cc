
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

比如说一位数时不能为0，两位数不能大于26，其十位上的数也不能为0，出去这些限制条件，根爬梯子基本没啥区别，也勉强算特殊的斐波那契数列，当然需要用动态规划Dynamci Programming来解。建立一位dp数组，长度比输入数组长多1，全部初始化为0，因为斐波那契数列的前两项也为1，然后从第三个数开始更新，对应数组的第一个数。对每个数组首先判断其是否为0，若是将改为dp赋0，若不是，赋上一个dp值，此时相当如加上了dp[i - 1], 然后看数组前一位是否存在，如果存在且满足前一位不是0，且和当前为一起组成的两位数不大于26，则当前dp值加上dp[i - 2], 至此可以看出来跟斐波那契数组的递推式一样

dp[i] 表示长度为i-1的string的decoding ways 

int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        for (int i = 1; i < dp.size(); ++i) {
        	if (s[i-1] == '0') 
        		dp[i] = 0;   // s[i-1] 对应的是dp[i] 
        	else 
        		dp[i] = dp[i-1]; 

            // 只有10 - 26 之间才有 dp[i] = dp[i-1] + dp[i-2] 
            // 否则 dp[i] = dp[i-1]  
            if (i > 1 && (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6'))) {
                dp[i] = dp[i] + dp[i - 2];  // 其实就是: dp[i] = dp[i-1] + dp[i-2]  // 斐波那契数列   或者 dp[i] = dp[i-2]    // 等号右边的dp[i]取决于上文   
            }
        }
        
        return dp.back();
    }




