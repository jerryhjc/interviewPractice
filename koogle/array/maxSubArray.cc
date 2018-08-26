53. Maximum Subarray
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

Sol1：naive enumeration
穷举数组的左右终点。

Sol2：cumsum + DP
从m到n的子数组之和为cumsum(n)-cumsum(m-1)。固定n，则达到最大子数组之和需要最小化 cumsum(m-1)，因此我们维护minmcumsum(m-1)的值和当前数组之和。这个算法的复杂度是O(n).


int maxSubArray(vector<int>& nums) {
	if (nums.size() == 0) return 0; 
	int res = INT_MIN;  
	int sum = 0;
	int min_sum = INT_MAX;  

	for (int i = 0; i < nums.size(); ++i) {
		min_sum = min(min_sum, sum); //注意顺序,若这句在下面则有bug: input为1个数时   
		sum += nums[i]; 
		// min_sum = min(min_sum, sum); 
		res = max(res, sum - min_sum); 
	}

	return res; 
}
