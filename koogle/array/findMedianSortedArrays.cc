4. Median of Two Sorted Arrays  

There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
Example 1:
nums1 = [1, 3]
nums2 = [2]
The median is 2.0

Example 2:
nums1 = [1, 2]
nums2 = [3, 4]
The median is (2 + 3)/2 = 2.5

合并两个数组，并找到中位数。合并不需要全部完成，到中位数位置就可以停止。（中位数为第 (m+n+1)/2）
如果数组有偶数个数，则再向后看一个元素，并求平均值。

double next(int &p1, int &p2, const vector<int>& nums1, const vector<int>& nums2) {
    if (p1 >= nums1.size()) return nums2[p2++];
    if (p2 >= nums2.size()) return nums1[p1++];
    
    if (nums1[p1] < nums2[p2]) return nums1[p1++];
    else return nums2[p2++];
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size(), mid = (m+n+1)/2;	

    int p1=0, p2=0, val=0;
    for (int k = 0; k < mid; ++k)  
    	val = next(p1, p2, nums1, nums2);

    if ((m+n) % 2 == 1)  //total number is odd
    	return val; 
    else   //total number is even 
    	return (val + next(p1, p2, nums1, nums2)) / 2.0;
}






