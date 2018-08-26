239. Sliding Window Maximum
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note: 
You may assume k is always valid, ie: 1 ≤ k ≤ input array size for non-empty array. 


// better solution:  
// 维护一个大小为k的multiset，每次删去过期的数，取最大数。
//  multiset 自动从小到大排序 

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    multiset<int> history;
    vector<int> result;
    for (int j = 0; j < nums.size(); ++j) {
        if (j >= k) history.erase(history.find(nums[j-k]));
        history.insert(nums[j]);
        if (j >= k-1) result.push_back(*history.rbegin());
    }
    return result;
}





