879. Profitable Schemes


There are G people in a gang, and a list of various crimes they could commit.
The i-th crime generates a profit[i] and requires group[i] gang members to participate.
If a gang member participates in one crime, that member can't participate in another crime.
Let's call a profitable scheme any subset of these crimes that generates at least P profit, and the total number of gang members participating in that subset of crimes is at most G.
How many schemes can be chosen?  Since the answer may be very large, return it modulo 10^9 + 7.

Example 1:

Input: G = 5, P = 3, group = [2,2], profit = [2,3]
Output: 2
Explanation: 
To make a profit of at least 3, the gang could either commit crimes 0 and 1, or just crime 1.
In total, there are 2 schemes.
Example 2:

Input: G = 10, P = 5, group = [2,3,5], profit = [6,7,8]
Output: 7
Explanation: 
To make a profit of at least 5, the gang could commit any crimes, as long as they commit one.
There are 7 possible schemes: (0), (1), (2), (0,1), (0,2), (1,2), and (0,1,2).



// Time complexity: O(KPG)
// Space complexity: O(KPG)
// Running time: 64 ms
  int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {    
    const int kMod = 1000000007;
    const int K = group.size();
    // dp[k][i][j]:= # of schemes of making profit i with j people by commiting first k crimes.
    vector<vector<vector<int>>> dp(K + 1, vector<vector<int>>(P + 1, vector<int>(G + 1, 0)));
    dp[0][0][0] = 1;
    
    for (int k = 1; k <= K; ++k) {      
      const int p = profit[k - 1];
      const int g = group[k - 1];
      for (int i = 0; i <= P; ++i)    
        for (int j = 0; j <= G; ++j)
          dp[k][i][j] = (dp[k - 1][i][j] + (j < g ? 0 : dp[k - 1][max(0, i - p)][j - g])) % kMod;
    }
    return accumulate(begin(dp[K][P]), end(dp[K][P]), 0LL) % kMod;
  }


Space complexity: O(PG)
v1: Dimension reduction by copying.

int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {    
	const int kMod = 1000000007;
	const int K = group.size();
	// dp[i][j]:= # of schemes of making profit i with j people.
	vector<vector<int>> dp(P + 1, vector<int>(G + 1, 0));
	dp[0][0] = 1;

	for (int k = 1; k <= K; ++k) {
	  auto tmp = dp;  // copy from dp to tmp 
	  const int p = profit[k - 1];
	  const int g = group[k - 1];
	  for (int i = 0; i <= P; ++i)    
	    for (int j = 0; j <= G; ++j)
	      tmp[i][j] = (tmp[i][j] + (j < g ? 0 : dp[max(0, i - p)][j - g])) % kMod;
	  dp.swap(tmp);  // copy from tmp to dp
	}
	return accumulate(begin(dp[P]), end(dp[P]), 0LL) % kMod;
}











