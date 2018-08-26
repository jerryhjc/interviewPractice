Rotate Image 旋转图像
 
You are given an n x n 2D matrix representing an image.
Rotate the image by 90 degrees (clockwise).
Follow up:
Could you do this in-place?    

最后再来看一种方法，这种方法首先对原数组取其转置矩阵，然后把每行的数字翻转可得到结果，如下所示(其中蓝色数字表示翻转轴)：

1  2  3　　　 　　 1  4  7　　　　　    7  4  1

4  5  6　　-->　　 2  5  8　　 -->  　 8  5  2　　

7  8  9 　　　 　　3  6  9　　　　      9  6  3


// 1. 先以 1 5 9 为轴翻转
// 2. 每行reverse 

    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);   // 
            }
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }



