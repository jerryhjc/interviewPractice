
Range Sum Query 2D - Immutable 二维区域和检索 - 不可变
 

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

vector<vector<int>> dp;

NumMatrix(vector<vector<int> > &matrix) {
    if (matrix.empty() || matrix[0].empty()) return;
    dp.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));

    for (int i = 1; i <= matrix.size(); ++i) {
        for (int j = 1; j <= matrix[0].size(); ++j) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1] + matrix[i - 1][j - 1];
        }
    }
}

int sumRegion(int row1, int col1, int row2, int col2) {
    return dp[row2 + 1][col2 + 1] - dp[row1][col2 + 1] - dp[row2 + 1][col1] + dp[row1][col1];
}

// matrix里的 matrix[row][col] 对应dp里的 dp[row + 1][col + 1]   


(i-1)(j-1)		(i-1)j	
	
i(j-1)  		ij


r1c1  
	
	 r2c2  



Range Sum Query 2D - Mutable 二维区域和检索 - 可变

这种解法并没有用到树状数组，而是利用了列之和，所谓列之和，就是(i, j)就是(0, j) + (1, j) + ... + (i, j) 之和，相当于把很多个一维的区间之和拼到了一起，那么我们在构造函数中需要建立起这样一个列之和矩阵，然后再更新某一个位置时，我们只需要将该列中改变的位置下面的所有数字更新一下即可，而在求某个区间和时，只要将相差的各列中对应的起始和结束的行上的值的差值累加起来即可

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
Note:
The matrix is only modifiable by the update function.
You may assume the number of calls to update and sumRegion function is distributed evenly.
You may assume that row1 ≤ row2 and col1 ≤ col2.


// Column Sum
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        mat = matrix;
        colSum.resize(matrix.size() + 1, vector<int>(matrix[0].size(), 0));
        for (int i = 1; i < colSum.size(); ++i) {
            for (int j = 0; j < colSum[0].size(); ++j) {
                colSum[i][j] = colSum[i - 1][j] + matrix[i - 1][j];
            }
        }
    }

    void update(int row, int col, int val) {
        for (int i = row + 1; i < colSum.size(); ++i) {
            colSum[i][col] += val - mat[row][col];
        }
        mat[row][col] = val;
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int res = 0;
        for (int j = col1; j <= col2; ++j) {
            res += colSum[row2 + 1][j] - colSum[row1][j];
        } 
        return res;
    }

private:
    vector<vector<int>> mat;
    vector<vector<int>> colSum;
};

