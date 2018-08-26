LeetCode 837 - New 21 Game

Alice plays the following game, loosely based on the card game "21".
Alice starts with 0 points, and draws numbers while she has less than K points.  During each draw, she gains an integer number of points randomly from the range [1, W], where W is an integer.  Each draw is independent and the outcomes have equal probabilities.
Alice stops drawing numbers when she gets K or more points.  What is the probability that she has N or less points?

Example 1:
Input: N = 10, K = 1, W = 10
Output: 1.00000
Explanation:  Alice gets a single card, then stops.



这个题目有点像爬楼梯问题，只不过楼梯问题要求的计算多少种爬的方式，但是本题是计算概率。因为点数超过或者等于K后就不允许再增加新的点数了，因此我们可以确定最终Alice拥有的点数的区间是[K,K-1+W]，下限等于K很好理解，Alice最后一次抽取点数前可能拥有的点数最大值是K-1，最后一次抽取的点数最大值是W,因此上限就是K-1+W。和爬楼梯类似，恰好获得点数n的概率dp[n] = sum(dp[n-w]/w + dp[n-w+1]/w + .... dp[n-1]/w)。因为获取任意一个点数的概率都是1/W，所以上面的公式中每个dp都要除以W。但是题目约定了一个K值，在n > k + 1的情况下，dp[n]是无法通过dp[n-1]得到，需要修正公式： dp[n] = sum(dp[n-w]/w + dp[n-w+1]/w + .... dp[K-1]/w)。最后，点数小于或者等于N的概率就是 sum(dp[K:N + 1])。


Then I realize that the transition equation dp[i] = (dp[i - W] + dp[i - W + 1] + ... + dp[i - 1]) / W could be simplified to dp[i] = (sum[i - 1] - sum[i - W - 1]) / W.
Furthermore, if we use dp[i] to directly represent the sum[i], we can get dp[i] = dp[i - 1] + (dp[i - 1] - dp[i - W - 1]) / W. This equation takes us to the final O(K + W) solution. Just take care with the beginning and the end of the array.



double new21Game(int N, int K, int W) {
        if (K == 0) {
            return 1;
        }
        int maxSum = K+W; // right before reach K, e,g. K-1, one still can draw one more time to get 1~W more points, so the max is K+W
        vector<double> dp(maxSum+1, 0.0 ); // use dp[i] to directly represent the sum[i] of f[i-w]+...+f[i-1], f is the probability

        dp[0]=1.0;    

        for (int i = 1; i <= maxSum; i++)
        {
            dp[i] = dp[i - 1];
            if (i <= W)
                dp[i] += dp[i - 1] / W;
            else 
                dp[i] += (dp[i - 1] - dp[i - W - 1]) / W; // for i point, the incremental part is sum of p[i-1], p[i-2]~ p[i-W]

            if (i > K) 
                dp[i] -= (dp[i - 1] - dp[K - 1]) / W;


        }
        return (dp[N] - dp[K - 1]) / (dp[maxSum] - dp[K - 1]);
}


