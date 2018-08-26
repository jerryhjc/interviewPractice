Max Chunks To Make Sorted II 可排序的最大块数之二

Given an array arr of integers (not necessarily distinct), we split the array into some number of "chunks" (partitions), and individually sort each chunk.  After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

Example 1:
Input: arr = [5,4,3,2,1]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.

Example 2:
Input: arr = [2,1,3,4,4]
Output: 4
Explanation:
We can split into two chunks, such as [2, 1], [3, 4, 4].
However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.

这道题是之前那道Max Chunks To Make Sorted的拓展，那道题说了数组是[0, n-1]中所有数字的一种全排列，n为数组的长度。而这道题的数字就没有这种限制，可以是大于n的数字，也可以有重复的数字。由于数字和坐标不再有太多的关联，所以之前那题中比较数字和坐标的大小的解法肯定行不通了。我们来看一种十分巧妙的解法，首先我们需要明确的一点是，拆分后的块儿排序后拼在一起会跟原数组相同，我们用一个例子来说明：

2  1  4  3  4
1  2  3  4  4
1  2  3  4  4

我们看到第一行是原数组，第二行是排序后并拼接在了一起的块儿，不同的颜色代表不同的块儿，而第三行是直接对原数组排序后的结果。仔细观察可以发现，能形成块儿的数字之和跟排序后的数组的相同长度的子数组的数字之和是相同的。比如第一个块儿是数字2和1，和为3，而排序后的前两个数字为1和2，和也是3，那么我们就知道原数组的前两个数字可以拆成一个块儿。同理，原数组中的第三个和第四个数字分别为4和3，和为7，而排序后的数组对应位置的数字之和也是7，说明可以拆分出块儿。就是这么简单而暴力的思路，时间复杂度为O(nlgn)，主要花在给数组排序上了。由于本题是Max Chunks To Make Sorted的generalized的情况，所以这种解法自然也可以解决之前那道题了，不过就是时间复杂度稍高了一些
// nlogn 
int maxChunksToSorted(vector<int>& arr) {
        int res = 0, sum1 = 0, sum2 = 0;
        vector<int> expect = arr;
        sort(expect.begin(), expect.end());
        for (int i = 0; i < arr.size(); ++i) {
            sum1 += arr[i];
            sum2 += expect[i];
            if (sum1 == sum2) ++res;
        }
        return res;
}

// n 
这道题的时间复杂度可以优化到线性，不过就是需要花点空间。下面这种解法也相当的巧妙，我们需要两个数组forward和backward，其中 foward[i] 表示 [0, i] 范围内最大的数字，而 backward[i] 表示 [i, n-1] 范围内最小的数字，实际上就是要知道已经遍历过的最大值，和还未遍历的到的最小值。为啥我们对这两个值感兴趣呢？这是本解法的精髓所在，我们知道可以拆分为块儿的前提是之后的数字不能比当前块儿中的任何数字小，不然那个较小的数字就无法排到前面。就像例子1，为啥不能拆出新块儿，就因为最小的数字在末尾。那么这里我们能拆出新块儿的条件就是，当前位置出现过的最大值小于等于之后还未遍历到的最小值时，就能拆出新块儿。比如例子2中，当 i=1 时，此时出现过的最大数字为2，未遍历到的数字中最小值为3，所以可以拆出新块儿

int maxChunksToSorted(vector<int>& arr) {
        int res = 1, n = arr.size();
        vector<int> f = arr, b = arr;   
        for (int i = 1; i < n; ++i) 
        	f[i] = max(arr[i], f[i - 1]);   
        
        for (int i = n - 2; i >= 0; --i) 
        	b[i] = min(arr[i], b[i + 1]);
        
        for (int i = 0; i < n - 1; ++i) {
            if (f[i] <= b[i + 1]) ++res;
        }
        return res;
}




