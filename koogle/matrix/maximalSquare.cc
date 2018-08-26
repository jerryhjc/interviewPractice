Maximal Square

Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1 and return its area.
For example, given the following matrix:
1 0 1 0 0    
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0


这是个DP问题，定义
DP[i, j] 是the length of max square,这个square的最右下角是 (i,j)，那么
如果matrix[i][j] == 0, DP[i, j]也是0，因为square 不存在
如果matrix[i][j] == 1, 那么DP[i, j]就有如下三种可能

1）从DP[i-1, j]表述的square上加一行
2）从DP[i, j-1]表述的square上加一列
3）从DP[i-1, j-1]表述的square上加一行和一列
从三种可能中选出最小的那一个就是maximal square   

int maximalSquare(vector<vector<char>>& matrix) {  
    if (matrix.empty() || matrix[0].empty()) return 0; 
        
    int row = matrix.size();  
    int col = matrix[0].size();  
    vector<vector<int>> dp(row+1, vector<int>(col+1, 0));  
        
    int maxLen = 0;  
    for(int i = 1; i <= row; i++) {  
       	for(int j = 1; j <= col; j++) {  
        	if(matrix[i-1][j-1] == '1') {  
            	dp[i][j] = min(min(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1]) + 1 ;  
            	maxLen = max(maxLen, dp[i][j]);  
          }  
        }  
    }

    return maxLen * maxLen;  
}

