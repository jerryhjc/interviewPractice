683. K Empty Slots  

There is a garden with N slots. In each slot, there is a flower. The N flowers will bloom one by one in N days. In each day, there will be exactly one flower blooming and it will be in the status of blooming since then.

Given an array flowers consists of number from 1 to N. Each number in the array represents the place where the flower will open in that day.

For example, flowers[i] = x means that the unique flower that blooms at day i will be at position x, where i and x will be in the range from 1 to N.

Also given an integer k, you need to output in which day there exists two flowers in the status of blooming, and also the number of flowers between them is k and these flowers are not blooming.

If there is not such day, output -1.

Example 1:
Input: 
flowers: [1,3,2]
k: 1
Output: 2
Explanation: In the second day, the first and the third flower have become blooming.

Example 2:
Input: 
flowers: [1,2,3]
k: 1
Output: -1



下面这种方法用到了TreeSet来做，利用其自动排序的特点，然后用lower_bound和upper_bound进行快速的二分查找。 题目中的flowers[i] = x表示第i+1天放的花会在位置x。所以我们遍历flowers数组，其实就是按照时间顺序进行的，我们取出当前需要放置的位置cur，然后在集合set中查找第一个大于cur的数字，如果存在的话，说明两者中间点位置都没有放花，而如果中间正好有k个空位的话，那么当前天数就即为所求。这是当cur为左边界的情况，同样，我们可以把cur当右边界来检测，在集合set中查找第一个小于cur的数字，如果二者中间有k个空位，也返回当前天数


int kEmptySlots(vector<int>& flowers, int k) {
    int n = flowers.size();
    if (n == 0 || k >= n) return -1;     
    // set 是通过BST实现的                     
    set<int> xs; // 所有已经开花的坐标            

    for (int i = 0; i < n; ++i) {			
        int x = flowers[i];				
        auto r = xs.insert(x).first;  // 存iterator,  insert是logn操作 			
        auto l = r;  // 拷贝						
    
        if (++r != xs.end() && *r == x + k + 1) return i + 1; //  ++r 比r大的那个元素, *r(比r大的那个元素)是否等于x+k+1, 若等于则说明他们之间有k个元素是空的  // ++, --也是logn操作 
        if (l != xs.begin() && *(--l) == x - k - 1) return i + 1;
    }				
    					
    return -1;				
}						
					
				
// better time 148ms					
int kEmptySlots(vector<int>& flowers, int k) {
        if (flowers.empty()) return -1;
        multiset<int> garden;
        for (int i = 0; i < flowers.size(); i ++){
            auto it = garden.insert(flowers[i]);
            if (it != garden.begin()){
                auto it_left = it; it_left --;
                if (*it - *it_left == k + 1) {
                    //cout << *it_left << " " << *it << endl;
                    return i + 1;
                }
            }
            auto it_right = it; it_right ++; 
            if (it_right != garden.end()){
                if (*it_right - *it == k + 1) {
                    //cout << *it_right << " " << *it << endl;
                    return i + 1;
                }
            }
        }
        return -1;
}						
					





