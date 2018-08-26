644. Maximum Average Subarray II    

Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value. And you need to output the maximum average value.
Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation:
when length is 5, maximum average value is 10.8,
when length is 6, maximum average value is 9.16667.
Thus return 12.75.

题解：
(nums[i]+nums[i+1]+…+nums[j])/(j-i+1)>x
=>nums[i]+nums[i+1]+…+nums[j]>x*(j-i+1)
=>(nums[i]-x)+(nums[i+1]-x)+…+(nums[j]-x)>0

于是我们从结果x里面去找，x用binary search.
然后再用sliding window表示范围内的sum

double findMaxAverage(vector<int>& nums, int k) {
    double l = -10000, r = 10000;
    while (r - l > 10e-7) {
        double mid = (l+r)/2; 
        if (getMaxSubbaraySumOfSizeK(nums, k, mid) >= 0) l = mid;
        else r = mid;
    }
    return (l+r)/2;
}

double getMaxSubbaraySumOfSizeK(vector<int>& nums, int k, double mid) {
    double sum = 0.0;
    for (int i=0;i<=k-1;i++) 
        sum += nums[i] - mid;
    
    double maxSum = sum, prev = nums[0] - mid;
    
    for (int i=k;i < nums.size();i++) {
         sum = sum - nums[i-k] + nums[i];
         maxSum = max(maxSum, max(sum, sum + prev));
         prev = max(nums[i-k+1] + 0.0, nums[i-k+1] + prev) - mid;
    }
    
    return maxSum;
}

