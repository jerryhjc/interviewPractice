vector<int> vec(vec1.size(), 0);  // vec 初始化为 vec1大小，值全为0 
 

==================================

www.cnblogs.com/grandyang/p/4606334.html
www.geeksforgeeks.org/program-for-nth-fibonacci-number/

想不通: Combination Sum II 组合之和之二; 



linked list 等号左边的->next 表示指向的意思;  等号右边的->next 表示下一个node的意思;

0跟任何数异或都还是那个数
=======================
Code snippet

// Replace substring with another substring 
size_t index = 0;
while (true) 
{
     /* Locate the substring to replace. */
     index = str.find("abc", index);
     if (index == std::string::npos) 
     	break;

     /* Make the replacement. */
     str.replace(index, 3, "def");

     /* Advance index forward so the next iteration doesn't pick it up as well. */
     index += 3;
}


  /* reverse the number: e.g. 123 -> 321 */
while (number != 0)
{
    reverse = reverse * 10 + number % 10;
    number /= 10;
}




====================================

Merge sort  


#include<stdlib.h>
#include<stdio.h>

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];  // 括号里的l重要
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

/* Driver program to test above functions */
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}


==========================================
quick sort
https://www.youtube.com/watch?v=COk73cpQbFQ  

#include<stdio.h>
#include<algorithm>


// 记住这个函数算法, 关键是index下标的移动 
//return value 是pivot新的index
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int pIndex = low;  // 添加index从第一个元素开始移动 

    for (int i = low; i <= high - 1; i++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[i] <= pivot)
        {
            swap(arr[i], arr[pIndex]);
            pIndex++;   // increment index of smaller element
        }
    }
    swap(arr[pIndex], arr[high]);  // finally, swap index number and pivot
    return pIndex;
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */  
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program to test above functions
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    quickSort(arr, 0, n-1);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}


===================================
remove all specific element of array, 
input: array, array size, element 
output: return array new length

int remove(int arr[], int n, int element)
{
    int j = 0; 

    for(int i = 0; i < n; )
    {
        if(arr[i] == element)
            ++i;
        else
        {   
            arr[j] = arr[i]; //  j是removed element的index,  
            ++j;   // ++j 是index 指向下一个元素 ; 所以array length 直接返回 j  
            ++i; 
        }
    }

    return j;   
}
// 关键使用了连个index: i, j. 有点违反直觉

=========================================
remove duplicate element of array, that every element only appear once  
output: new length

int remove(int arr[], int n)
{
    if(n == 0)
        return 0;

    int j = 0; 
    for(int i = 1; i < n; )
    {
        if(A[j] == A[i])
            ++i; 
        else 
        {
            ++j;
            A[j] = A[i];
        }     
    }

    return j+1 // j是最后个元素的index, 所以元素个数为j+1

}

=========================================
2SUM
input: array, target number
output: indexs of two number, where index1 must be less than index2

vector<int> twoSum(vector<int>& numbers, int target)
{
    vector<int> ret; 

    if(numbers.size() <= 1)
        return ret; 

    unordered_map<int, int> map; 
    for(int i = 0; i < numbers.size(); ++i)
    {
        map[numbers[i]] = i; 
    }

    for(int i = 0; i < numbers.size(); ++i)
    {
        int res_val = target - numbers[i];
        if(map.find(res_val) != map.end())
        {
            int index = map[res_val];
            if(index == i)
                continue;
            else if(index < i)
            {
                ret.push_back(index);
                ret.push_back(i);
                // ret.push_back(index+1);  // non-zero based index
                // ret.push_back(i+1);
                return ret; 
            }
            else if(index > i)
            {
                ret.push_back(i);
                ret.push_back(index);
                // ret.push_back(i+1);  // non-zero based index
                // ret.push_back(index+1);
                return ret; 
            }
        }
    }

}

solution 2: 

vector<int> twoSum(vector<int>& arr, int target)
{
    sort(arr.begin(), arr.end());  // need to sort the array first 

    vector<int> ret; 
    while(i < j)
    {
        int i = 0, j = arr.size() - 1; 
        if(arr[i] + arr[j] == target)
        {
            ret.push_back(i);
            ret.push_back(j);
            return ret; 
        }
        else if(arr[i] + arr[j] > target)
            --j;
        else if(arr[i] + arr[j] < target)
            ++i; 
    }

    return ret; 
}


========================================
3SUM
Find all unique triplets in the array that a+b+c=0 
a, b, c must be in non-descending order 

vector<vector<int>> threeSum(vector<int>& arr)
{
    vector<vector<int>> ret; 

    if(arr.size() <= 2)
        return ret; 

    sort(arr.begin(), arr.end());

    for(int i = 0; i < arr.size() - 2; ++i)
    {
        int j = i+1;
        int k = arr.size() - 1;
        vector<int> cur; 

        while(i > 0 && arr[i] == arr[i-1])   //avoid duplicate for i
            continue; 

        while(i < k)
        {
            if(arr[i] + arr[j] + arr[k] == 0)
            {
                cur.push_back(i);
                cur.push_back(j);
                cur.push_back(k);
                ret.push_back(cur);
                ++j;
                --k;

                while(j < k && arr[j-1] == arr[j])   // skip duplicate for j
                    ++j;
                while(j < k && arr[k] == arr[k+1])   // skip duplicate for k
                    --k;
            }
            else if(arr[i] + arr[j] + arr[k] < 0)
                ++j;
            else if(arr[i] + arr[j] + arr[k] > 0)
                --k;
        }
        // while(i < arr.size() - 2 && arr[i] == arr[i + 1])   // skip duplicate for i
            // ++i;
    }

    return ret; 

}


==========================================
closest 3SUM
find 3 integer that the sum is closest to a given number. 
output: sum of the three integers 

int threeSum(vector<int>& arr, int target)
{

    if(arr.size() <= 2)
        return -1; 
        // return ret; 

    sort(arr.begin(), arr.end());

    int ret; 
    int dist = INT_MAX; 
    for(int i = 0; i < arr.size() - 2; ++i)
    {
        // while(i > 0 && arr[i] == arr[i-1])   //avoid duplicate 
        //     continue;     // the problem has assume there is only one solution. 

        int j = i+1;
        int k = arr.size() - 1;

        // while(i < k)
        while(j < k)
        {

            int sum = arr[i] + arr[j] + arr[k];
            int temp_dist;
            
            if(arr[i] + arr[j] + arr[k] == target)
            {
                return target; 
                
            }
            else if(arr[i] + arr[j] + arr[k] < target)
            {

                temp_dist = target - (arr[i] + arr[j] + arr[k]);
                if(temp_dist < dist)
                {
                    dist = temp_dist;  
                    ret = sum; 
                }
                ++j; 
                
            }
            else if(arr[i] + arr[j] + arr[k] > target)
            {
                temp_dist = (arr[i] + arr[j] + arr[k]) - target;
                if(temp_dist < dist)
                {
                    dist = temp_dist;
                    ret = sum; 
                }
                --k; 
            }
        }
    }

    return ret; 

}


=======================================
4SUm 
output: all non-duplicate elements (4个一组)

vector<vector<int>> threeSum(vector<int>& arr, int target)
{
    vector<vector<int>> ret; 
    vector<int> cur; 

    if(arr.size() <= 3)
        return ret; 

    sort(arr.begin(), arr.end());

    for(int i = 0; i < arr.size() - 3; ++i)
    {
        while(i > 0 && arr[i] == arr[i-1])  // avoid duplicate 
            continue; 

        for(int j = i+1; j < arr.size - 2; ++j)
        {
            int k = j + 1; 
            int l = arr.size() - 1; 

            while(k < l)
            {
                if(arr[i] + arr[j] + arr[k] + arr[l] == target)
                {
                    cur.push_back(arr[i]);
                    cur.push_back(arr[j]);
                    cur.push_back(arr[k]);
                    cur.push_back(arr[l]);
                    ret.push_back(cur);

                    while(k < l && arr[k] == arr[k+1])  // avoid duplicate 
                        ++k;

                    while(k < l && arr[l] == arr[l-1])  // avoid duplicate
                        --l
                }
                else if(ar[i] + arr[j] + arr[k] + arr[l] > target)
                {
                    ++k;
                }
                else if(ar[i] + arr[j] + arr[k] + arr[l] < target)
                {
                    --l;
                }

            }

        }

    }

    return ret; 

}

===========================================
atoi 函数 
convert char* str (string) to integer  
  
// A utility function to check whether x is numeric
bool isNumericChar(char x)
{
    return (x >= '0' && x <= '9')? true: false;
}
  
// A simple atoi() function. If the given string contains
// any invalid character, then this function returns 0
int myAtoi(char *str)
{
    //****** check given string contain any invalid character 
    if (*str == NULL)
       return 0;
  
    int res = 0;  // Initialize result
    int sign = 1;  // Initialize sign as positive
    int i = 0;  // Initialize index of first digit
  
    //****** check is negative or not // If number is negative, then update sign
    if (str[0] == '-')
    {
        sign = -1;
        i++;  // Also update index of first digit
    }
  
    // Iterate through all digits of input string and update result
    for (; str[i] != '\0'; ++i)
    {
        //****** check is error or not 
        if (isNumericChar(str[i]) == false)
            return 0; // You may add some lines to write error message

        res = res*10 + str[i] - '0';
    }
  
    // Return result with sign
    return sign*res;
}



==========================================  
find minimum in rotated sorted array 
the sorted array is rotated at some unknown pivot.  
key idea: binary search 


int findMin(vector<int> arr)
{
    if(arr.size() == 0)
        return 0; 
    else if(arr.size() == 1)
        return arr[0];
    else if(arr.size() == 2)
        return min(arr[0], arr[1]);

    int lowerBound = 0; 
    int upperBound = arr.size() - 1; 

    while(lowerBound < upperBound - 1)  // 注意
    {
        if(arr[lowerBound] < arr[upperBound]) // 注意
            return arr[lowerBound]; 

        int mid = (upperBound - lowerBound)/2 + lowerBound; 
        if(arr[lowerBound] < arr[mid])
            lowerBound = mid; 
        else if(arr[lowerBound] > arr[mid])
            upperBound = mid; 
    }

    return min(arr[lowerBound], arr[upperBound]); // 注意 
}


my solution: 
  int findMin(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        else if(nums.size() == 1)
            return nums[0];
        else if(nums.size() == 2)
            return min(nums[0], nums[1]);
            
        if(nums[0] < nums[nums.size() - 1] )
            return nums[0];
            
    int lower = 0;
    int upper = int(nums.size() - 1);
    
    int mid;
    
    while(lower < upper)
    {
        
        mid = lower + (upper - lower)/2;
        
        if(nums[mid] < nums[mid - 1] && nums[mid] < nums[mid + 1])
            return nums[mid];
        
        if(nums[lower] < nums[mid])
            lower = mid;
        else if(nums[lower] > nums[mid])
            upper = mid;
            
            
        if(mid == 0)
            return nums[0];
        
        if(mid == (nums.size() - 2))
            return nums[nums.size() - 1];
    }
    
    return 0;
    }

==========================================
find minimum in rotated sorted array, the sorted array has duplicate number 

int findMin(vector<int> arr)
{
    if(arr.size() == 0)
        return 0; 
    else if(arr.size() == 1)
        return arr[0];
    else if(arr.size() == 2)
        return min(arr[0], arr[1]);

    int lowerBound = 0; 
    int upperBound = arr.size() - 1; 

    while(lowerBound < upperBound - 1)  // 注意
    {
        if(arr[lowerBound] < arr[upperBound]) // 注意
            return arr[lowerBound]; 

        int mid = (upperBound - lowerBound)/2 + lowerBound; 
        if(arr[lowerBound] < arr[mid])
            lowerBound = mid; 
        else if(arr[lowerBound] > arr[mid])
            upperBound = mid; 
        else if (arr[lowerBound] == arr[mid])
            lowerBound++;   // 注意, 跳过就查找 
    }

    return min(arr[lowerBound], arr[upperBound]); // 注意 
}

===========================================
largest rectangle in histogram 
input: high of each bar ( the width of bar is 1)
output: area of largest rectangle in the histogram 

solution 1
// 对于每一个height，遍历前面所有的height，求取面积最大值, O(n^2)

int largestRectangle(vector<int>& height)
{
    int maxValue = 0;
    for(int i = 0; i < height.size(); ++i)
    {
        // for(int j = i; j < height.size(); ++j)
        for(int j = i; j >= 0; --j)  // 注意是要往前遍历, 往后遍历是错的
        {
            int minValue = min(height[i], height[j]);
            maxValue = max(maxValue, minValue * (j-i+1));

        }
    }
    return maxValue; 
}


solution 2: 
continuously push index into stack, until next bar is shorter than previous bar. Then go to else 去处理之前所积累的bar de max area. 

int largestHistRectangle(vector<int>& height)
{
    stack<int> st; 
    int maxValue = 0; 

    height.push_back(0);  // in case of all bars are increasing 
    int sum = 0; 

    for(int i = 0; i < height.size(); ++i)
    {
        if(st.empty() || height[i] > height[st.top()])
            st.push(i);   // 注意压栈的是bar的index 
        else
        {
            int temp = st.top()
            st.pop();
            maxValue = max(maxValue, heigh[temp]* (st.empty()? i : (i - s.top() - 1))); 
            --i; // 重要, 保证接下来的循环i不变. 分别计算area[i to i-1], area[i to i-2], area[i to i-3]
        }
    }

}

==================================================
maxRectangle, find the largest rectangle containging all ones and return its area
input: 0-1 matrix 
基于上题, matrix的每一行都计算maxHistRectangle,  www.geeksforgeeks.org/maximum-size-rectangle-binary-sub-matrix-1s/


int maxRectangle(vector<vector<int>>& matrix)
{
    int R = matrix.size();
    int C = matrix[0].size();

    int maxValue = largestRectangle(matrix[0]);

    for(int i = 1; i < R; ++i)
    {
        for(int j = 0; j < C; j++)
        {

            if(matrix[i][j]) 
                matrix[i][j] = matrix[i][j] + matrix[i-1][j];
        }
        maxValue = max(maxValue, largestRectangle(matrix[i]));
    }

    return maxValue; 
}


=======================================
Check integer number is palindrome or not

bool isPalindrome(int num)
{
    if(num < 0)
        return false;
    if(num == 0)
        return true; 

    int origin_value = num; 
    int value = 0;

    while(num > 0)
    {
        value = value*10 + num%10;   // 这个公式要记住 
        num = num/10; 
    }

    if(value == origin_value)
        return true; 
    else 
        retur false; 
}

========================================
search 2D matrix, each row is sorted from small to large, the first element of each row is larger than the last element of previous row 

solution: 会超时 
bool searchMatrix(const vector<vector<int>>& matrix, const int target)
{

    if(matrix.size() == 0)
        return false; 
    if(matrix[0].size() == 0)
        return false; 

    int R = matrix.size();
    int C = matrix[0].size();

    for(int i = 0; i < R;)
    {
        for(int j = C-1; j >= 0;)
        {
            if(matrix[i][j] == target)
                return true;
            else if(matrix[i][j] > target)
                --j;
            else if(matrix[i][j] < target)
                ++i;
        }
    }

    return false; 
}

=========================================
search for a range 
find starting and ending position of target value in sorted array.
time logn. If target is not found, return [-1, -1]
// 用了, 两次二分搜索. 注意while(xxx) 判断

vector<int> searchRange(vector<int>& arr, int target)
{
    if(arr.size() == 0)
        return vector<int>({-1, -1}); 

    vector<int> ret; 
    int lowerBound = 0; 
    int upperBound = arr.size() - 1; 

    // while(lowerBound < upperBound)
    while(lowerBound <= upperBound) // 注意是 <= 
    {
        int mid = lowerBound + (upperBound - lowerBound)/2; 
        if(arr[mid] >= target )   //注
            upperBound = mid - 1;
        else
            lowerBound = mid + 1; 
    }

    if(arr[lowerBound] == target && lowerBound < n)
        ret.push_back(lowerBound);
    else 
        return vector<int>({-1, -1});

    lowerBound = lowerBound; 
    upperBound = arr.size() - 1; 

    while(lowerBound <= upperBound)
    {
        int mid = lowerBound + (upperBound - lowerBound)/2;
        if(arr[mid] <= target)   // 注
            lowerBound = mid + 1; 
        else
            upperBound = mid - 1; 

    }

    ret.push_back(upperBound);
    return ret; 
}

=====================================================
search insert position 
return the index if the target is found in sorted array. If not, return the index where target will be inserted in order 

int searchInsert(vector<int>& arr, int target)
{


    int lowerBound = 0;
    int upperBound = arr.size() - 1; 

    // while(lowerBound < upperBound)
    while(lowerBound <= upperBound)
    {
        int mid = lowerBound + (upperBound - lowerBound)/2; 
        if(arr[mid] == target)
            return mid; 
        else if(arr[mid] > target)
            upperBound = mid - 1; 
        else
            lowerBound = mid + 1; 

    }    

    return lowerBound; 

}

=====================================
Find peak element 
a peak element is greater than its neighbors, return its index 
arr[-1] = arr[n] = INT_MIN;

int peakElement(vector<int>& arr)
{
    if(arr.size() == 1)
        return 0; 

    int lowerBound = 0; 
    int upperBound = arr.size() - 1;
    int mid = 0; 

    while(lowerBound <= upperBound)
    {
        mid = lowerBound + (upperBound - lowerBound)/2;   //往下取整 

        if(mid == 0 || arr[mid] >= arr[mid-1]) && (mid == arr.size() -1 || arr[mid] >= arr[mid+1])
            return mid;
        else if(arr[mid - 1] > arr[mid])  // 注
            upperBound = mid - 1;  // 注, 因为arr[-1] = INT_MIN
            // upperBound = mid;
        else if(arr[mid + 1] > arr[mid])
            lowerBound = mid + 1;  // 因为arr[n] = INT_MIN
    }
    return mid; 

}


solution 2: 

    int findPeakElement(vector<int>& nums) 
    {

		int left = 0, right = nums.size() - 1;  // right != nums.size(); 因为有可能输入一个元素

        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] < nums[mid + 1]) 
            	left = mid + 1;
            else 
            	right = mid;
        }

        return right;
    }

===========================================
Missing number 
Array containing n distinct numbers from 0 ,1, 2..n. find the missing number 

solution 1: 
int missingNum(vector<int>& num)
{
    int x = 0; 
    for(int i = 0; i <= num.size(); ++i)
        x = x^i; 
    for(int i = 0; i < num.size(); ++i)
        x = x^num[i];

    return x;  
}


solution 2: 
n sorted number: 0..n, but 1 number is missing. Find out that number 
binary search 

int solution(vector<int>& arr)
{
	int lowerBound = 0; 
	int upperBound = arr.size(); 

    while(lowerBound < upperBound)
    {
        if(arr.size() == 0)
            return 999;

        if(arr[0] != 0)
            return 0;

        int mid = lowerBound + (upperBound - lowerBound)/2; 

        if(arr[mid] - arr[mid-1] > 1) 
            return arr[mid] - 1;
        else if(arr[mid+1] - arr[mid] > 1)
            return arr[mid] + 1; 
        else if(arr[mid] > mid)
            upperBound = mid;
        else if(arr[mid] == mid)
            lowerBound = mid; 
    }
} 


solution 3: 
int missingNumber(vector<int>& arr) {
        
        sort(arr.begin(), arr.end());
        
        int lowerBound = 0; 
	int upperBound = arr.size(); 

    while(lowerBound < upperBound)  // 注意
    {
        int mid = lowerBound + (upperBound - lowerBound)/2; 
        
        if(arr[mid] > mid)
            upperBound = mid;  // 注意
        // else if(arr[mid] == mid)  // arr[mid] 不可能小于mid
        else 
            lowerBound = mid + 1;  // 注意
            
    }
       return upperBound;  // 注意
        
    }

=========================================
power of two
determine if a number is power of two
.优先于*   []优先于*  函数()优先于*  运算符优(+-*/ +=) 先于位运算符 (>> & | ^ )

bool powerTwo(int num)
{
    if(num < 0)   // corner case: negative
        return false; 

    if(num == 0)  // corner case: 0
        return true; 

    int sum = 0;
    while(num > 0)
    {
        sum = sum + (num & 1);
        // sum = sum + num & 1;   // 是错的, 因为算数运算符优先于位运算符 ********
        num = num >> 1;
    }

    if(sum == 1)
        return true; 
    else 
        return false;

}

======================================
Number of one bit in a number 

int sumOne(int num)
{
    int sum = 0;
    while(num > 0)
    {
        sum = sum + (num & 1);
        num = num >> 1; 
    }

    return sum; 
}

=============================
min/max depth of binary tree 

int maxDepth(Node* node)
{
    if(node == NULL)
        return 0;
    // if(node->right == NULL && node->left == NULL)  //当只有一个root时,    
    //     return 1; 
    // if(root->left != NULL)   //当只有一个root时, 有bug 
    //     int leftDepth = minDepth(root->left) + 1; 
    // else if(root->right != NULL)   //当只有一个root时, 有bug 
    //     int rightDepth = minDepth(root->right) + 1; 
 
    int leftDepth = minDepth(root->left) + 1;
    int rightDepth = minDepth(root->right) + 1;


    if(leftDepth >= rightDepth)
        return leftDepth;
    else 
        return rightDepth;
}


int minDepth(Node* node)
{
    if(node == NULL)
        return 0;

    // if(node->right == NULL && node->left == NULL)
    //     return 1; 
    // if(root->left != NULL)   //当只有一个root时, 有bug 
    //     int leftDepth = minDepth(root->left) + 1; 
    // else if(root->right != NULL)   //当只有一个root时, 有bug 
    //     int rightDepth = minDepth(root->right) + 1; 
 
    int leftDepth = minDepth(root->left) + 1;
    int rightDepth = minDepth(root->right) + 1;

    if(leftDepth <= rightDepth)
        return leftDepth;
    else 
         return rightDepth;    
}

==================================
Find the Kth largest element in unsorted array using miniHeap -- O(n)
Mini-heap: is complete binary tree, root has minimum value starting at index 0, children value is smaller than parent value. The index of the last element of the tree is size()-1.  
1. 先heapify 2. extract k-1 element  
// A class for Min Heap
class MinHeap
{
private:
    int *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    MinHeap(int a[], int size); // Constructor
    void MinHeapify(int i);  //To minheapify subtree rooted with index i
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
 
    int extractMin();  // extracts root (minimum) element
    int getMin() { return harr[0]; } // Returns minimum
};
 
MinHeap::MinHeap(int a[], int size)
{
    heap_size = size;
    harr = a;  // store address of array
    int i = (heap_size - 1)/2;   //注意, 从最后那个元素的parent开始heapify, 至到元素with 0 index  
    while (i >= 0)
    {
        MinHeapify(i);
        i--;
    }
}
 
// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
    if (heap_size == 0)
        return INT_MAX;
 
    // Store the minimum vakue.
    int root = harr[0];
 
    // If there are more than 1 items, move the last item to root
    // and call heapify.
    if (heap_size > 1)
    {
        harr[0] = harr[heap_size-1]; 
        MinHeapify(0);
    }
    heap_size--;
 
    return root;
}
 
// A recursive method to heapify a subtree with root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)   // heapify用了recursion 
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(harr[i], harr[smallest]);
        MinHeapify(smallest); // 注意
    }
}
 

// Function to return k'th smallest element in a given array
int kthSmallest(int arr[], int n, int k)
{
    // Build a heap of n elements: O(n) time
    MinHeap mh(arr, n);
 
    // Do extract min (k-1) times
    for (int i=0; i<k-1; i++)
        mh.extractMin();
 
    // Return root
    return mh.getMin();
}
 
=================================================
path sum 

solution 1: 
bool hasPathSum(TreeNode* root, int sum) 
{
    if(root == NULL)
    {
        // if(sum == 0)
        //     return true;
        // else return false; 
        return false;
    }
    
    
    int remain = sum - root->val;
    if( remain == 0 && node->left == NULL && node->right == NULL )
      return 1;
    
    return hasPathSum(root->left, remain) || hasPathSum(root->right, remain);


    //solution 2:
    /////// be low solution is correct, I don't know why 
    // if(root->left)
    //     return hasPathSum(root->left, remain);
    
    // if(root->right)
    //     return hasPathSum(root->right, remain);

    // return false;

}

solution 3: 
  bool hasPathSum(TreeNode* node, int sum) {
  if(node == NULL)
  {
     return false;
  }
  else
  {
    bool ans = 0;  
  
    /* otherwise check both subtrees */
    int subSum = sum - node->val;
  
    /* If we reach a leaf node and sum becomes 0 then return true*/
    if( subSum == 0 && node->left == NULL && node->right == NULL )
      return 1;
  
    if(node->left)
      ans = ans || hasPathSum(node->left, subSum);
    if(node->right)
      ans = ans || hasPathSum(node->right, subSum);
  
    return ans;
  }
        
}

===============================================

Edit Distance  

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.) You have the following 3 operations permitted on a word: Insert a character, Delete a character, Replace a character 

solution 1: recusion, T = O(3^m), time out for leetcode 

int editDist(string str1 , string str2 , int m ,int n)
{
    // If first string is empty, the only option is to
    // insert all characters of second string into first
    if (m == 0) return n;
 
    // If second string is empty, the only option is to
    // remove all characters of first string
    if (n == 0) return m;
 
    // If last characters of two strings are same, nothing
    // much to do. Ignore last characters and get count for
    // remaining strings.
    if (str1[m-1] == str2[n-1])
        return editDist(str1, str2, m-1, n-1);
 
    // If last characters are not same, consider all three
    // operations on last character of first string, recursively
    // compute minimum cost for all three operations and take
    // minimum of three values.
    return 1 + min ( editDist(str1,  str2, m, n-1),    // Insert
                     editDist(str1,  str2, m-1, n),   // Remove
                     editDist(str1,  str2, m-1, n-1) // Replace
                   );
}


solution 2: dynamic programming ;  T=O(m*n), S=O(m*n)  

int editDistDP(string str1, string str2, int m, int n)
{

    // dp[i][j] means 当str1为i length和str2为j length时, 的minimum step to convert  
    // Create a table to store results of subproblems
    int dp[m+1][n+1];  // this is (m+1)*(n+1) matrix  !!!!!!!!  
 
    // Fill d[][] in bottom up manner
    for (int i=0; i<=m; i++)   // i: 0...m
    {
        for (int j=0; j<=n; j++)   // j: 0...n
        {
            // If first string is empty, only option is to
            // insert all characters of second string
            if (i==0)
                dp[i][j] = j;  // Min. operations = j
 
            // If second string is empty, only option is to
            // remove all characters of second string
            else if (j==0)
                dp[i][j] = i; // Min. operations = i
 
            // If last characters are same, ignore last char
            // and recur for remaining string
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];
 
            // If last character are different, consider all
            // possibilities and find minimum
            else
                dp[i][j] = 1 + min(dp[i][j-1],  // Insert
                                   dp[i-1][j],  // Remove
                                   dp[i-1][j-1]); // Replace
        }
    }
 
    return dp[m][n];
}

//////////////////////////////////////          
Decode Ways

A message containing letters from A-Z is being encoded to numbers using the following mapping:
'A' -> 1, 'B' -> 2, ..., 'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

假设解码函数为h。对于一位数X，只能解码成h[X]。而对于一个两位数XY：
1. 如果XY<=26，那么能解码成h[X], h[Y], h[XY]
2. 否则，只能解码成h[X], h[Y]
由于只要求计算最多的解码方法而并不要求每种解码的结果，所以用DP做更为合适高效。

定义dp[i+1]为能解码长度为i+1的string s[0:i]的方法数：
1. dp[0] = 1，dp[1] = 1
2. v = s[i-1]*10+s[i]：
v<=26： dp[i+1] = dp[i] + dp[i-1]
v>26：dp[i+1] = dp[i]

corner case：有0的情况
Y = 0：显然无法解码成h[Y]，此时只能看h[XY]是否valid：dp[i+1] = dp[i-1]
X = 0：显然无法解码成h[XY]，此时dp[i+1] = dp[i]


整理总结corner case： // 重要
XY可以解码的条件是：9<XY<=26
Y可以单独解码的条件是：Y != '0'


solution: it is like climbing stair problem, fibonacci number,  定义 dp[i] 为能解码长度为i的string s[0:i-1]的方法数：

int numDecodings(string s) 
{
    if(s.empty() || s[0]<'1' || s[0]>'9')   // corner case
        return 0;
    
    vector<int> dp(s.size()+1,0);  // initialize array size 
    dp[0] = dp[1] = 1;   // initialized value 
    
    for(int i=1; i<s.size(); i++) 
    {
        if(!isdigit(s[i]))   // 判断string的字符是否为数字 
            return 0;
        
        // s的i index 对应dp的i+1 index 
        int v = (s[i-1]-'0')*10 + (s[i]-'0');  // 初始化XY 
        if(9<v && v<=26)  // 如果XY两个数有效, 则 dp[i+1] = dp[i-1]
            dp[i+1] = dp[i-1]; // 更容易理解
            // dp[i+1] += dp[i-1];  // it's also OK, because dp[i+1] is always 0 at the beginning

        if(s[i]!='0')   // 如果单个数有效, (并且XY有效) dp[i+1] = dp[i] + dp[i-1], else dp[i+1] = dp[i]
            dp[i+1] += dp[i];
    
    }

    return dp[s.size()];
}

///////////////////////////////////
Distinct Subsequences 

Given a string S and a string T , count the number of distinct subsequences of T in S.
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not). 

(即从S中remove x characters后, T=S)


solution: We define the computation structure to be C[i][j] indicating the number of solutions for S[0...i-1] and T[0...j-1]. i/j in C represents #chars in the substring. It's easier if we include 0 in the structure to accommodate the case when there's no chars(empty string) considered. In order to expand this structure, when updating C[i][j] we have two options:

1. C[i][j] = C[i-1][j]. No matter what current char of S is we simply do not use it. We will only use chars [0,...i-2] from S no matter how many solutions there are to cover T[0...j-1]
2. But if current char of S is same to current of T (S[i-1]==T[j-1]) then we have another choice: we can use all the solutions of C[i-1][j-1] to increment the solution C[i][j]. Therefore C[i][j] += C[i-1][j-1]


int numDistinct(string s, string t) 
{
    int m = s.size(), n = t.size();
    vector<vector<int>> C(m+1, vector<int>(n+1));  // good to initialize 2D vector/array 
    // int C[m+1][n+1];  // this 2D array will fail in leetcode !!!!!!
    
    for(int i=0; i<=m; i++) 
        C[i][0] = 1;
    
    for(int i=1; i<=m; i++) 
    {
        for(int j=1; j<=n; j++) 
        {
            C[i][j] = C[i-1][j];
            if(s[i-1] == t[j-1]) 
                C[i][j] += C[i-1][j-1];  // 为什么有 +  
        }
    }

    return C[m][n];    
}

////////////////////////////////////////////////
Print a Binary Tree in Vertical Order
Given a binary tree, print it vertically. 
           1
        /    \
       2      3
      / \    / \
     4   5  6   7
             \   \
              8   9 
               
              
The output of print this tree vertically will be:
4
2
1 5 6
3 8
7
9

//用inorder search to store vertical order for every node !!!  
// Utility function to store vertical order in map 'm'
// 'hd' is horigontal distance of current node from root.
// 'hd' is initally passed as 0
void getVerticalOrder(Node* root, int hd, map<int, vector<int>> &m)
{
    // Base case
    if (root == NULL)
        return;
 
    // Store current node in map 'm'
    m[hd].push_back(root->key);
 
    // Store nodes in left subtree
    getVerticalOrder(root->left, hd-1, m);
 
    // Store nodes in right subtree
    getVerticalOrder(root->right, hd+1, m);
}
 
// The main function to print vertical oder of a binary tree
// with given root
void printVerticalOrder(Node* root)
{
    // Create a map and store vertical oder in map using
    // function getVerticalOrder()
    map < int,vector<int> > m;
    int hd = 0;
    getVerticalOrder(root, hd,m);
 
    // Traverse the map and print nodes at every horigontal
    // distance (hd)
    map< int,vector<int> > :: iterator it;
    for (it=m.begin(); it!=m.end(); it++)
    {
        for (int i=0; i<it->second.size(); ++i)
            cout << it->second[i] << " ";
        cout << endl;
    }
}

The O(n) for recursion is n, and all operations of map take O(Logn) time. Thus, total O(n) = nlogn
=====================================
Merge sort of linked list 

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct node** headRef)
{
  struct node* head = *headRef;
  struct node* a;
  struct node* b;
 
  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }
 
  /* Split head into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b); 
 
  /* Recursively sort the sublists */
  MergeSort(&a);
  MergeSort(&b);
 
  /* answer = merge the two sorted lists together */
  *headRef = SortedMerge(a, b);
}
 
/* See http://geeksforgeeks.org/?p=3622 for details of this 
   function */
struct node* SortedMerge(struct node* a, struct node* b)
{
  struct node* result = NULL;
 
  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);
 
  /* Pick either a or b, and recur */
  if (a->data <= b->data)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);
}
 
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra node should go in the front list.
     Uses the fast/slow pointer strategy.  */
void FrontBackSplit(struct node* source,
          struct node** frontRef, struct node** backRef)
{
  struct node* fast;
  struct node* slow;
  if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}

//////////////////////////////////////
Maximum of all subarrays of size k 

Given an array and an integer k, find the maximum for each and every contiguous subarray of size k. 
找每连续k个element的subarray的maximum, 所以output 有n-k+1个  (subarray: (1,2,3), (2,3,1), (3,1,4)...) 
Input :
arr[] = {1, 2, 3, 1, 4, 5, 2, 3, 6}
k = 3
Output :
3 3 4 5 5 5 6


simple solution 1. two for loop for array size and integer k .  T = O(n*k)

solution 2: 
void printKMax(int arr[], int n, int k)
{
    // Create a Double Ended Queue, Qi that will store indexes of array elements
    // The queue will store indexes of useful elements in every window and it will
    // maintain decreasing order of values from front to rear in Qi, i.e., 
    // arr[Qi.front[]] to arr[Qi.rear()] are sorted in decreasing order
    std::deque<int>  Qi(k);

    /* Process first k (or first window) elements of array */
    int i;
    for (i = 0; i < k; ++i)  // 让deque的back to front 从小到大排列
    {
        // For very element, the previous smaller elements are useless so
        // remove them from Qi
        while ( (!Qi.empty()) && arr[i] >= arr[Qi.back()])
            Qi.pop_back();  // Remove from rear

        // Add new element at rear of queue
        Qi.push_back(i);
    }

    // Process rest of the elements, i.e., from arr[k] to arr[n-1]
    for ( ; i < n; ++i)
    {
        // The element at the front of the queue is the largest element of
        // previous window, so print it
        cout << arr[Qi.front()] << " ";

        // Remove the elements which are out of this window
        while ( (!Qi.empty()) && Qi.front() <= i - k)  // 若front是之前k个数的第一个, 则在下一轮k个数front要被删掉.
            Qi.pop_front();  // Remove from front of queue

        // Remove all elements smaller than the currently
        // being added element (remove useless elements)
        while ( (!Qi.empty()) && arr[i] >= arr[Qi.back()])   // 同理, 让deque的back to front 从小到大排列
            Qi.pop_back();

         // Add current element at the rear of Qi
        Qi.push_back(i);
    }

    // Print the maximum element of last window
    cout << arr[Qi.front()];
}

======================================

Given a string s and a dictionary of dict, e.g. s = "leetcode", dict = ["leet", "code"], return true if "leetcode" can be segmented as "leet code" 
output: return true if string can be segmented. 

dp[i] = dp[j] && s[j, i] in dict,  where dp[i] means if the string with length i can be segmented 

bool wordBreak(string s, unordered_set<string>& dic)
{
    int len = s.size();
    vector<bool> dp(len+1, false);
    dp[0] = true; 

    for(int i = 1; i <= len; ++i)
    {
        for(int j = i-1; j >= 0; j--)
        {
            if(dp[j] && dict.find(s.substr(j, i-j)) != dict.end())
            {
                dp[i] = true; 
                break; 
            }
        }
    }
    return dp[len]; 

}


=======================================================
reverse linked list in easier way 

/* Function to reverse the linked list */
node* reverse(struct node* head)
{
    
///////////////  method 1 to create dummy node
//    node dummy;
//    dummy.data = 0;
//    dummy.next = (*head);
//    node* prev = &dummy;
    
//////////////   method 2 to create dummy node 
//    struct node* dummy = (node*) malloc(sizeof(node));  // 若设置dummy pointer, 要用malloc/new; 否则会有error
    node* dummy = new node;
    dummy->data = 0;
    dummy->next = head;
    
    struct node* prev = dummy;   // dummy node before starting node  
    struct node* cur = prev->next;   // starting node, or current node
    
    
    int num = 0;
    node* temp = head;
    while(temp != NULL)
    {
        ++num;  // count total node in linked list
        temp = temp->next;
    }
    
    
    for(int i = 1; i < num;++i)    // 需要 num-1 次iteration !!!!!!!!!
    {
        struct node* nex = cur->next;   // important!!! as the first line in the loop
        cur->next = nex->next;
        nex->next =prev->next;
        prev->next = nex;
        
    }
    
    return dummy->next;  // 注意!!!
}

//////////////////////////////////////////////
strlen of c style string 

int strlen(char* str)
{
    int len = 0; 
    while((*str) != '\0')
    {
        len++;
        str++;
    }

    return len; 
}

////////////////////////////////////////////// 
Spiral matrix  
Given a matrix of m × n elements (m rows, n columns), return all elements of the matrix in spiral order
input: number of columns and rows of matrix 

void spiralPrint(int m, int n, int a[][])
{
    int i, k = 0, l = 0;
 
    /*  k - starting row index
        m - ending row index 
        l - starting column index
        n - ending column index
        i - iterator
    */
 
    while (k < m && l < n)
    {
        /* Print the first row from the remaining rows */
        for (i = l; i < n; ++i)
        {
            printf("%d ", a[k][i]);
        }
        k++;
 
        /* Print the last column from the remaining columns */
        for (i = k; i < m; ++i)
        {
            printf("%d ", a[i][n-1]);
        }
        n--;
 
        /* Print the last row from the remaining rows */
        if ( k < m)   //  因为matrix 可能有奇数行
        {
            for (i = n-1; i >= l; --i)
            {
                printf("%d ", a[m-1][i]);
            }
            m--;
        }
 
        /* Print the first column from the remaining columns */
        if (l < n)    // //  因为matrix 可能有奇数列  
        {
            for (i = m-1; i >= k; --i)
            {
                printf("%d ", a[i][l]);
            }
            l++;    
        }        
    }
}


////////////////////////////////////////


Given an integer n, generate a square matrix filled with elements from 1 to n 2 in spiral order.
For example, Given n = 3,
You should return the following matrix:
[
[ 1, 2, 3 ],
[ 8, 9, 4 ],
[ 7, 6, 5 ]
]


vector<vector<int>> generateMatrix(int n)
{
    vector<vector<int>> matrix(n, vector<int>(n));  // initialize 2D matrix with size n*n
    int begin = 0, end = n - 1; // initialize index
    int num = 1; 

    while(begin < end)
    {
        for(int j = begin; j < end; ++j)
        {
            matrix[begin][j] = num;
            num++;
        }

        for(int i = begin; i < end; ++i)
        {
            matrix[i][end] = num;
            num++;
        }

        for(int j = end; j > begin; --j)
        {
            matrix[end][j] = num;
            num++;
        }

        for(int i = end; i > begin; --i)
        {
            matrix[i][begin] = num; 
            num++; 
        }

        ++begin; 
        --end; 
    }

    if(begin == end)   // in case of matrix with odd row/column  !!!!  matrix 中间那个数  
        matrix[begin][end] = num; 

    return matrix; 
}

///////////////////////////////////////////

Convert array into Zig-Zag fashion

Given an array of distinct elements, rearrange the elements of array in zig-zag fashion in O(n) time. The converted array should be in form a < b > c < d > e < f.

solution 1: first sort the array, keep arr[0] as it is, swap arr[1] and arr[2], swap arr[3] and arr[4], and so on.  O(n) = nlgn


solution 2:  using flag to represent < or >. < and > will show one by one . O(n) = n
void zigZag(int arr[], int n)
{
    // Flag true indicates relation "<" is expected,
    // else ">" is expected.  The first expected relation
    // is "<"
    bool flag = true;
 
    for (int i=0; i<=n-2; i++)
    {
        if (flag)  /* "<" relation expected */
        {
            /* If we have a situation like A > B > C,
               we get A > B < C by swapping B and C */
            if (arr[i] > arr[i+1])
                swap(arr[i], arr[i+1]);
        }
        else /* ">" relation expected */
        {
            /* If we have a situation like A < B < C,
               we get A < C > B by swapping B and C */
            if (arr[i] < arr[i+1])
                swap(arr[i], arr[i+1]);
        }
        flag = !flag; /* flip flag */
    }
}

/////////////////////////////////////////////////////
Multiply two integers without using multiplication, division and bitwise operators, and no loops  

/* function to multiply two numbers x and y*/
int multiply(int x, int y)
{
   /* 0  multiplied with anything gives 0 */
   if(y == 0)
     return 0;
 
   /* Add x one by one */
   if(y > 0 )
     return (x + multiply(x, y-1));
  
  /* the case where y is negative */
   if(y < 0 )
     return -multiply(x, -y);
}

//////////////////////////////////////////////////

// Calculates x / y  without using / * 
int solve(int x, int y) {
    
    int n = abs(x);
    int d = abs(y);
    int q = 0;
    
    while(n >= d)
    {
        q++;
        n -= d;
    }
    
    // if ((x < 0)^(y < 0)) return -q;
    if ((x < 0) || (y < 0)) return -q;

    return q;
}

//////////////////////////////////////
KMP algorithm 
intput: char* pat  // pattern 
    char* text   // text 

lps[] indicates longest proper prefix which is also suffix. 
e.g. The largest common part of prefix and suffix for every substring of AAAAA is [0, 1, 2, 3, 4]   
!! lps[0] is always 0, ABCD has prefix: A, AB, ABC;  ABCD has suffix: D, CD, BCD  



// compute the length of longest common prefix and suffix
void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;  // length of the previous longest common prefix and suffix
    int i = 1; 
 
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    while (i < M)
    {
       if (pat[i] == pat[len])
       {
         len++;
         lps[i] = len;
         i++;
       }
       else // (pat[i] != pat[len])
       {
         if (len != 0)
         {
           // This is tricky. Consider the example 
           // AAACAAAA and i = 7.
           len = lps[len-1];  //有点动态规划的味道 !!!!!!!!
 
           // Also, note that we do not increment i here
         }
         else // if (len == 0)
         {
           lps[i] = 0;
           i++;
         }
       }
    }
}


void KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
 
    // create lps[] that will hold the common longest prefix suffix values for pattern
    char* lps[M]; 
    int j  = 0;  // index for pat[]
    int i = 0;  // index for txt[]
 
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
 
    while (i < N)
    {
      if (pat[j] == txt[i])
      {
        j++;
        i++;
      }
 
      if (j == M)
      {
        printf("Found pattern at index %d \n", i-j);
        j = lps[j-1];   // search for the next pattern 
      }
 
      // mismatch after j matches
      else if (i < N && pat[j] != txt[i])
      {
        // Do not match lps[0..lps[j-1]] characters, // skip the common prefix and suffix 
        // they will match anyway
        if (j != 0)
         j = lps[j-1];  // pattern search from j index 
        else
         i = i+1;
      }
    }
}

////////////////////////////////////////
Max Points on a Line

以每个“点”为中心,然后遍历剩余点,找到所有的斜率,如果斜率相同,那么一定共线对每个点,用一个哈希表,key 为斜率,value 为该直线上的点数,计算出哈希表后,取最大值,并更新全局最大值,最后就是结果。时间复杂度 O(n^2 ),空间复杂度 O(n)。



int maxPoints(vector<Point> &points) 
{
    if (points.size() < 3) return points.size();
    int result = 0;
    unordered_map<double, int> slope_count;
    for (int i = 0; i < points.size()-1; i++) 
    {
        slope_count.clear();
        int samePointNum = 0; // 与 i 重合的点
        int point_max = 1;
        // 和 i 共线的最大点数
        for (int j = i + 1; j < points.size(); j++)   // iterate from i+1, ignore the points that has iterated 
        {
            double slope; // 斜率
            if (points[i].x == points[j].x)   // slope may be infinity,
            {
                slope = std::numeric_limits<double>::infinity();
                if (points[i].y == points[j].y)   // the same points
                {
                    ++samePointNum;
                    continue;
                }
            } 
            else 
            {
                slope = 1.0 * (points[i].y - points[j].y) /
                (points[i].x - points[j].x);
            }

            int count = 0;
            if (slope_count.find(slope) != slope_count.end())
                count = ++slope_count[slope];
            else 
            {
                count = 2;
                slope_count[slope] = 2;
            }

            if (point_max < count) 
                point_max = count;
        }

        result = max(result, point_max + samePointNum);
    }
    return result; 
}


/////////////////////////////////////////
minimum window substring 
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).  


   string minWindow(string S, string T)
{
    if(S == "" || T == "")
        return "";
    if(S.size()< T.size())
        return ""; 

    map<char, int> appeared_count; 
    map<char, int> expected_count; 

    for(int i = 0; i < T.size(); ++i)
        expected_count[T[i]]++; 

    int minWidth = INT_MAX, min_start = 0;   // global windows min width, starting index.  variables that need to return  
    int window_start = 0;   // change all over program, local windows starting index, 
    int total_appear = 0;  // count total number of character in T 

    for(int window_end = 0; window_end < S.size(); ++window_end)  // local windows ending index 
    {
        if(expected_count[S[window_end]] > 0)
        {
            appeared_count[S[window_end]]++; 
            // if(total_appear < T.size())   /// wrong  
            if(appeared_count[S[window_end]] <= expected_count[S[window_end]]);  // !!!  
                total_appear++;  // total_appear will stop at the size of T.size(), not increase/decrease 


            if(total_appear == T.size())  // if string window 完整包含了一个 T
            {
                while(appeared_count[S[window_start]] > expected_count[S[window_start]] 
                    || expected_count[S[window_start]] == 0)  // if the char at window_start index appears more than expected in T, or the char not belongs to expected T, then 收缩头指针
                {
                    window_start++;
                    appeared_count[S[window_start]]--;
                }

                if(minWidth > (window_end - window_start + 1))
                {
                    minWidth = window_end - window_start + 1; 
                    min_start = window_start; 
                }

            }


        }       

    }
    
    if(minWidth == INT_MAX)  // if S doesn't match T 
        return "";
    else 
        return S.substr(min_start, minWidth);

}

///////////////////////////////////////
Insert Interval 

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary)
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16]. 

struct Interval
{
  int start;
  int end;
  Interval(): start(0), end(0) {}
  Interval(int s, int e): start(s), end(e) {}
};


vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
{
  vector<Interval>::iterator it = intervals.begin();
  while(it != intervals.end())
  {
    if(newInterval.start > it->end)
    {
      it++;
    }
    else if(newInterval.end < it->start)  
    {
      intervals.insert(it, newInterval);   // insert element before iterator 
      return intervals; 
    }
    else
    {
      newInterval.start = min(newInterval.start, it->start);
      newInterval.end = max(newInterval.end, it->end);
      it = intervals.erase(it);  // erase return iterator that follows the removed element 

    }
  }
    intervals.insert(intervals.end(), newInterval);  // if newInterval.start is always > it->end !!!
    return intervals; 
}

////////////////////////////////////////
Merge Intervals 

Given a collection of intervals, merge all overlapping intervals.
For example, Given [1,3],[2,6],[8,10],[15,18], return [1,6],[8,10],[15,18]

// based on Insert Interval above 
vector<Interval> merge(vector<Interval>& intervals)
{
  vector<Interval> result;
  for(int i = 0; i < intervals.size(); ++i)
  {
    insert(result, intervals[i]);
  }
  return result; 
}

///////////////////////////////////////
ZigZag Conversion
input: "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this 
P   A   H   N
A P L S I I G
Y   I   R

output: "PAHNAPLSIIGYIR"  

time: O(len)  space: O(len) 
// use n array to store every row of elements, and use a flag to indicate movement direction 
string convert(string str, int n) 
{
  // Corner Case (Only one row)
  if (n <= 1 || str.size() <= 1)
  {
      return str;      
  }   

  // Find length of string
  int len = str.size();

  // Create an array of strings for all n rows
  string arr[n];

  // Initialize index for array of strings arr[]
  int row = 0;
  bool down; // True if we are moving down in rows, 
             // else false

  // Travers through given string
  for (int i = 0; i < len; ++i)
  {
      // append current character to current row
      arr[row].push_back(str[i]);

      // If last row is reached, change direction to 'up'
      if (row == n-1)
        down = false;

      // If 1st row is reached, change direction to 'down'
      else if (row == 0)
        down = true;

      // If direction is down, increment, else decrement
      (down)? (row++): (row--);
  }

  string ret;

  // Print concatenation of all rows
  for (int i = 0; i < n; ++i)
      ret = ret + arr[i];
      
  return ret;    
}

///////////////////////////////////////
Clone graph 
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbours.

input: node 
output: new_node  

UndirectedGraphNode *cloneGraph(const UndirectedGraphNode *node) 
{
  if(node == nullptr) return nullptr;
  // key is original node,value is copied node
  unordered_map<const UndirectedGraphNode *, UndirectedGraphNode *> copied;

  clone(node, copied);  // copy existing node to the value of copied 
  
  return copied[node];
}

// DFS
static UndirectedGraphNode* clone(const UndirectedGraphNode *node, unordered_map<const UndirectedGraphNode *, UndirectedGraphNode *> &copied) 
{
  // a copy already exists
  if (copied.find(node) != copied.end()) 
    return copied[node];
  
  UndirectedGraphNode *new_node = new UndirectedGraphNode(node->label);
  copied[node] = new_node;
  
  for (auto nbr : node->neighbors)
    new_node->neighbors.push_back(clone(nbr, copied));  // recursion here: clone()
  
  return new_node;
}

////////////////////////////////////
Triangle

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent
numbers on the row below.
For example, given the following triangle
[
[2],
[3,4],
[6,5,7],
[4,1,8,3]
]

自底向上了, 设状态为 f(i, j),表示从最底向上到位置(i, j)时,路径的最小和. 则状态转移方程为
f(i, j) = min {f(i, j + 1), f(i + 1, j + 1)} + f(i, j)

t = O(n^2), S = O(1) 

int minimumTotal (vector<vector<int>>& triangle) 
{
  for (int i = triangle.size() - 2; i >= 0; --i)   // i iterates from triangle.size()-2 to 0  
  {
    for (int j = 0; j <= i; ++j)   // j iterates from 0 to i  
      triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);  // 从倒数第二行iterate到第一行
  }

  return triangle[0][0];   // output triangle[0][0]
}

///////////////////////////////////

Maximum Subarray 
Find the contiguous subarray within an array (containing at least one number) which has the largest sum

设状态为 f[j],表示以 S[j] 结尾的最大连续子序列和,则状态转移方程如下
f[j] = max{f[j − 1] + S[j], S[j]} , 其中1 ≤ j ≤ n
target = max{f[j]} , 其中1 ≤ j ≤ n

T = O(n)

int maxSubArray(const vector<int> &A) 
{
  int result = INT_MIN, f = 0;
  for (int i = 0; i < A.size(); ++i) 
  {
    f = max(f + A[i], A[i]);  // f[j], f[j-1] are all represented by f 
    result = max(result, f);
  }

  return result;
}

T = O(n^2)
int maxSubArray(const vector<int> &A) 
{
  int result = INT_MIN;
  for(int i = 0; i < A.size(); ++i)
  {
     int sum = 0;   
    for(int j  = i; j < A.size(); ++j)
    {
      sum = sum + A[j];
      result = max(result, sum); 
    }
      
  }

  return result; 
}


////////////////////////////////
Maxmimum  Product Subarray 
Find  the contiguous  subarray  within  an  array (containing at  least one number) which has the largest product.

对于乘法,我们需要注意,负数乘以负数,会变成正数,所以解这题时候我们需要维护两个变量,当前的最大值,以及最小值,最小值可能为负数,但没准下一步乘以一个负数,当前的最大值就变成最小值,而最小值则变成最大值了。

maxDP[i + 1]  = max(maxDP[i]  * A[i + 1], A[i + 1], minDP[i]  * A[i + 1])
minDP[i + 1]  = min(minDP[i]  * A[i + 1], A[i + 1], maxDP[i]  * A[i + 1])

dp[i + 1]  = max(dp[i],  maxDP[i + 1])  


int maxProduct(int  A[],  int n)  
{
    if(n == 0)
    {
        return 0;
    } 
    else if(n == 1)  
    {
        return  A[0];
    }

   // another solution with iteration from i = 0 
    // int p = A[0]; 
    // int maxP  = 1
    // int minP  = 1
    // for(int i = 0 i < n; i++)  // iterate from i = 0
    // {
    //     int t = maxP;
    //     maxP  = max(max(maxP * A[i], A[i]), minP * A[i]);
    //     minP  = min(min(t * A[i], A[i]),  minP * A[i]);
    //     p = max(maxP, p);
    // }

    int p = A[0];
    int maxP  = A[0];
    int minP  = A[0];
    for(int i = 1; i < n; i++)  // iterate from i = 1 
    {
        int t = maxP;
        maxP  = max(max(maxP * A[i], A[i]), minP * A[i]);
        minP  = min(min(t * A[i], A[i]),  minP * A[i]);
        p = max(maxP, p);
    }
    return  p;
}

///////////////////////////////////////
Climbing  Stairs 

You are climbing a stair case. It takes n steps to reach to the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?


这道题目其实就是斐波那契数列问题, 初始条件dp[1] = 1,  dp[2] = 2 
dp[n] = dp[n - 1] + dp[n - 2]  

// input: number of stair step  
//output: ways to climb to the top

int climbStairs(int n)  
{
  int f1 = 1; 
  int f2 = 2; 

  if(n == 1)
  {
    return f1;
  }
  else if(n == 2)
  {
    return f2; 
  }

  int fn; 
  for(int i = 3; i < n; ++i)
  {
    fn = f1 + f2; 
    f1 = f2; 
    f2 = fn; 
  }
  return fn; 

}

///////////////////////////////
Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below). The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below). How many possible unique paths are there?

如果机器人要到(i,  j)这个点,他可以选择先到(i - 1, j)或者,(i, j - 1),也就是说,到(i, j)的唯一路径数等于(i - 1, j)加上(i, j - 1)的个数,所以我们很容易得出dp方程:

dp[i][j]  = dp[i - 1][j] + dp[i][j - 1]  

//动态规划需要逆向反推思维

int uniquePaths(int m,  int n)  
{
  int dp[m][n];
  //初始化dp,m x 1情况全为1
  for(int i = 0;  i < m;  i++)  
  {
      dp[i][0]  = 1;
  }
  //初始化dp,1 x n情况全为1
  for(int j = 0;  j < n;  j++)  
  {
      dp[0][j]  = 1;
  }
  
  for(int i = 1;  i < m;  i++)    // iterate from [1][1]  
  {
      for(int j = 1;  j < n;  j++)  
      {
          dp[i][j]  = dp[i - 1][j] + dp[i][j - 1];   // because robot can only move down or right 
      }
  }
  return  dp[m - 1][n - 1];
}

//////////////////////////////////
Now consider if some  obstacles are added to  the grids.  How many  unique  paths would there be?
An obstacle and empty space is marked as 1 and 0 respectively in the grid.



int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid)  {
    if(obstacleGrid.empty() ||  obstacleGrid[0].empty())  
    {
        return  0;
    }

    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    int dp[m][n];
    //下面初始dp的时候需要根据obstacleGrid的值来确定
    dp[0][0]  = (obstacleGrid[0][0] ==  0 ? 1 : 0);
    //我们需要注意m x 1以及1  x n的初始化
    for(int i = 1;  i < m;  i++)  
    {
        dp[i][0]  = ((dp[i  - 1][0] ==  1 &&  obstacleGrid[i][0]  ==  0)  ? 1 : 0);
    }

    for(int j = 1;  j < n;  j++)  
    {
        dp[0][j]  = ((dp[0][j - 1]  ==  1 &&  obstacleGrid[0][j]  ==  0)  ? 1 : 0);
    }
 
    for(int i = 1;  i < m;  i++)  
    {
        for(int j = 1;  j < n;  j++)  
        {
            if(obstacleGrid[i][j] ==  1)  
            {
                dp[i][j]  = 0;
            } 
            else  
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }

    return  dp[m - 1][n - 1];
}

////////////////////////////////////////

Minimum Path Sum  

Given a m x n grid  filled  with  non-negative  numbers,  find  a path  from  top left  to  bottom  right which minimizes the sum of  all numbers along its path.

dp[i][j] = min(dp[i][j-1], dp[i - 1][j]) + grid[i][j]  


int minPathSum(vector<vector<int> > &grid)  {
    if(grid.empty() || grid[0].empty())  
    {
        return  0;
    }

    int row = grid.size();
    int col = grid[0].size();
    int dp[row][col];
    dp[0][0]  = grid[0][0];
    
    for(int i = 1; i < row; i++)  // initialize first row  
    {
        dp[i][0]  = dp[i  - 1][0] + grid[i][0];
    }

    for(int j = 1; j < col; j++)   // initialize first column
    {
        dp[0][j]  = dp[0][j - 1]  + grid[0][j];
    }

    for(int i = 1;  i < row;  i++)   // dp equation, iterate from [1][1] to [row][col]
    {
        for(int j = 1;  j < col;  j++)  
        {
            dp[i][j]  = min(dp[i - 1][j],  dp[i][j - 1]) + grid[i][j];
        }
    }

    return  dp[row - 1][col - 1];
}

///////////////////////////////////
Unique Binary Search Trees 
Given n,  how many  structurally  unique  BST (binary search  trees)  that  store values  1...n? 

定义f(n)为unique BST的数量, 找规律n=0, n=1, n=2, n=3. 以n = 3为例：构造的BST的根节点可以取{1, 2, 3} 中的任一数字。 
如以1为节点，则left subtree只能有0个节点，而right subtree有2, 3两个节点。所以left/right subtree一共的combination数量为：f(0) * f(2) = 2. 
以2为节点， 则left subtree只能为1， right subtree只能为2： f(1) * f(1) = 1. 以3为节点，则left subtree有1, 2两个节点，right subtree有0个节点：f(2)*f(0) = 2


总结规律：
f(0) = 1
f(n) = f(0)*f(n-1) + f(1)*f(n-2) + ... + f(n-2)*f(1) + f(n-1)*f(0)  
=> f(i) = f(j)*f(i-1-j)

int numTrees(int n) 
{
    vector<int> numBST(n+1,0);
    numBST[0] = 1;
    
    for(int i=1; i<=n; i++)   // n nodes needs to iterate from 0 to n 
    {
        for(int j=0; j<i; j++)   // j iterates from 0 to i-1 based on equation   
        {
            numBST[i] += numBST[j]*numBST[i-1-j];
        }
    }

    return numBST[n];
}

///////////////////////////////////
Perfect Squares 

Given a positive integer n, find the least number of perfect square  numbers (for example, 1,  4,  9,  16, ...)  which sum to n. For example,  given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13 , return 2 because 13 = 4 + 9.


int numSquares(int  n)  {
    vector<int> dp(n + 1,  INT_MAX);
    dp[0] = 0;  // initialize dp[0]
 
    for (int i = 0; i <= n; i++)    // i iterates from 0 to n 
    {
        for (int j = 1; i + j * j <= n; j++)   // j iterates from 1 to n 
        {
            dp[i + j * j] = min(dp[i + j * j], dp[i] + 1);
        }
    }

    return  dp[n];
  }


///////////////////////////////////
Palindrome Partitioning

Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s. For example, given s = "aab", Return [ ["aa","b"], ["a","a","b"] ]

遇到要求所有组合、可能、排列等解集的题目，一般都是用DFS + backtracking来做。

 /*
 * @param s: A string
 * @return: A list of lists of string
 */
vector<vector<string>>v;
vector<string>v1;
vector<vector<string>> partition(string s) 
{
    // write your code here
    v.clear();
    if(s.size()==0)return v;
    v1.clear();
    dfs(0,s);
    return v;         
}

bool isPalindrome(string s) 
{
    int i=0,j=s.size()-1;
    while(i<j)
    {
        if(s[i]==s[j])
        {
            i++;j--;
        }
        else return false;
    }
    return true;
}

void dfs(int depth,string s) 
{
    if(depth==s.size())
    {
        v.push_back(v1);
    }

    if(depth<s.size())
    {
        for(int i=depth;i<s.size();i++)
        {
            if(isPalindrome(s.substr(depth,i-depth+1)))
            {
                v1.push_back(s.substr(depth,i-depth+1));
                dfs(i+1,s);
                v1.pop_back();                   
            }
        }
    }
}

///////////////////////////////////////
Palindrome Partitioning II

Given a string s, cut s into some substrings such that every substring is a palindrome. Return the minimum cuts needed for a palindrome partitioning of s.

solution: based on the solution of Palindrome Partitioning

// size() return type is: size_type,  which is an unsigned integral type 
// there is out of memory error in leetcode  
vector<vector<string>>v;
vector<string>v1;
int minCut(string s) 
{
    // write your code here
    v.clear();
    if(s.size()==0)
      return 0;
    v1.clear();
    dfs(0,s);

    int ret = INT_MAX; 
    for(auto str : v)     // find the minimum size in v 
      ret = min(ret, int(str.size()));

    return ret-1; 
    // return v;         
}

bool isPalindrome(string s) 
{
    int i=0,j=s.size()-1;
    while(i<j)
    {
        if(s[i]==s[j])
        {
            i++;j--;
        }
        else return false;
    }
    return true;
}

void dfs(int depth,string s) 
{
    if(depth==s.size())
    {
        v.push_back(v1);
    }

    if(depth<s.size())
    {
        for(int i=depth;i<s.size();i++)
        {
            if(isPalindrome(s.substr(depth,i-depth+1)))
            {
                v1.push_back(s.substr(depth,i-depth+1));
                dfs(i+1,s);
                v1.pop_back();                   
            }
        }
    }
}

///////////////////////////////


int minCut(string s) {
    int n = s.length();
    int f[n];
    bool isPalin[n][n];

    for (int i = 0; i < n; i++)   // initialization
    {
        isPalin[i][i] = true;  // 对角线
        if (i + 1 < n) {
            isPalin[i][i + 1] = (s[i] == s[i + 1]);  // 对角线上一斜行
        }
    }
    
    for (int i = n - 1; i >= 0; i--)   // initialization 
    {
        for (int j = i + 2; j < n; j++) 
        {
            isPalin[i][j] = isPalin[i + 1][j - 1] && (s[i] == s[j]); // isPalin判断 [i,j] i到j之间是否是回文
        }
    }

    //for f(i), 0 <= i <= n ; 
    //for isPalin[i][j], 0 <= i, j <= n-1 

    //  f(i)= 区间 [0, i-1] 之间最小的 cut 数, e.g. f(n) 存的是 s[0] ... s[n-1] 之间最小的 cut 数. 有一点tricky, 
    for (int i = 0; i <= n; i++)  // i iterates from 1 to n
    {
        f[i] = i - 1;   // initialize  max cut  first
        for (int j = 0; j < i; j++)  // j iterates from 0 to n-1
        {
            if (isPalin[j][i - 1]) // //  f(i)= 区间 [0, i-1] 之间最小的 cut 数, so [i - 1]
            {
                f[i] = min(f[i], f[j] + 1);  // j < i, two choice: 1. keep i, 2. or select j, then plus 1 
            }
        }
    }
        
    return f[n];
}

/////////////////////////////////////
Largest Rectangle in  Histogram

Given n non-negative integers representing the histogram bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

solution 1: 首先最简单的做法就是对于任意一个bar,向左向右遍历,直到高度小于该bar,这时候计算该区域的矩形区域面积。T=O(n)
 
solution 2: 从左到右遍历所有bar, 分别将bar的index push到stack中去。如果当前bar的高度大于stack栈顶的高度，则push当前bar的index到stack中。 如果当前bar的高度小于stack栈顶的高度，则pop栈顶的bar的index, 同时动态计算矩形面积。矩形面积的右边界即是前遍历到的bar的索引,而做边界则是当前的栈顶bar的索引. 

 注意： 要在所有bar后尾插入一个高度为0的bar， 以便求解所有bar高度递增的情况

int  largestRectangleArea(vector<int>  &height)  
{

    vector<int> s;  // mimic stack 
    //插入高度为0的bar
    height.push_back(0);
    int sum = 0;
    int i = 0;

    while(i < height.size())  
    {
        if(s.empty()  ||  height[i] > height[s.back()])  //stack为空时肯定要压栈
        {
            s.push_back(i);
            i++;
        }
        else
        {
            int t = s.back();
            s.pop_back();
            //这里还需要考虑stack为空的情况
            sum = max(sum, height[t] * (s.empty() ? i : i - s.back() - 1));  // empty
        }
    }

    return  sum;
}

////////////////////////////
Maximal Square 

Given a 2D binary matrix filled with 0 and 1's, find the largest square containing all 1's and return its area.

solution: Based on the Largest Rectangle in  Histogram above, 


int maximalSquare(vector<vector<char>>& matrix) 
{
    if(matrix.empty())
        return 0; 
    
    // if(matrix.size() == 1)
    //     return largestRectangleArea(matrix[0]); 
    
    int row = matrix.size();
    int col = matrix[0].size();
    
    // vector<vector<int>> int_matrix;   // error when define 2D vector like this !!!!! 
    vector<vector<int>> int_matrix(row, vector<int>(col));   // need to define space first 

    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            int_matrix[i][j] = matrix[i][j] - '0';  // convert vector<vector<char>> to vector<vector<int>>
        }            
    }

    int maxVal = largestRectangleArea(int_matrix[0]);

    for(int i = 1; i < int_matrix.size(); ++i)
    {
        for(int j = 0; j < (int_matrix[0]).size(); ++j)
        {
            if(int_matrix[i][j] == 1)
                int_matrix[i][j] += int_matrix[i-1][j];
            // else if(int_matrix[i][j] == 0)
            //     int_matrix[i][j] = 0;
            
        }
        maxVal = max(maxVal, largestRectangleArea(int_matrix[i]));

    }
    
    return maxVal;    
}


//////////////////////////////////////////////
Interleaving String

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

solution 1: recursion, but time out in leetcode  T = O(2^n)

bool isInterleave(string s1, string s2, string s3) 
{
// Base Case: If all strings are empty
    if(s1.empty() && s2.empty() && s3.empty())
        return true;

// If C is empty and any of the two strings is not empty
    if(s3.empty())
        return false; 

// If any of the above mentioned two possibilities is true,
// then return true, otherwise false        
    return (s1[0] == s3[0] && isInterleave(s1.substr(1), s2, s3.substr(1))) || (s2[0] == s3[0] && isInterleave(s1, s2.substr(1), s3.substr(1)));
    
}


solution 2: Dynamic programming, 注意下标. 2D table, row is size of s1, column is size of s2. 


bool isInterleave(string s1, string s2, string s3) {
    
   // c_str(): change string to c-style string, return type is const char*  
  const char* A = s1.c_str();  //
  const char* B = s2.c_str();
  const char* C = s3.c_str(); 
// Find lengths of the two strings
  int M = strlen(A), N = strlen(B);

  // Let us create a 2D table to store solutions of
  // subproblems.  IL[i][j] will be true if C[0..i+j-1]
  // is an interleaving of A[0..i-1] and B[0..j-1].
  bool IL[M+1][N+1];  // initialize (M+1)*(N+1) matrix 

// IL[i][j]的意思是i length的s1和j length的s2是否interleaving成i+j length的s3; true/false 
  memset(IL, 0, sizeof(IL)); // Initialize all values as false.

  // C can be an interleaving of A and B only of sum
  // of lengths of A & B is equal to length of C.
  if ((M+N) != strlen(C))
     return false;

  // Process all characters of A and B
  for (int i=0; i<=M; ++i)
  {
      for (int j=0; j<=N; ++j)
      {
          // two empty strings have an empty string
          // as interleaving
          if (i==0 && j==0)
              IL[i][j] = true;

          // A is empty
          else if (i==0 && B[j-1]==C[j-1])  // why index with [j-1]: j must >= 1, IL is (M+1)*(N+1) matrix. 注意i, j对于IL和A,B,C的意义不一样. 所以下标有点怪.   j-1对应B matrix. IL的index要比A,B,C对应的index大1; 即IL[i][j] 对应 A[i-1], B[j-1], C[(i-1)+j] or C[i+(j-1)] 
              IL[i][j] = IL[i][j-1];

          // B is empty
          else if (j==0 && A[i-1]==C[i-1])  // i-1对应A matrix, i must >= 1
              IL[i][j] = IL[i-1][j];

          // Current character of C matches with current character of A,
          // but doesn't match with current character of B
          else if(A[i-1]==C[(i-1)+j] && B[j-1]!=C[i+(j-1)])  // i, j must >= 1 ; 
              IL[i][j] = IL[i-1][j];

          // Current character of C matches with current character of B,
          // but doesn't match with current character of A
          else if (A[i-1]!=C[(i-1)+j] && B[j-1]==C[i+(j-1)])
              IL[i][j] = IL[i][j-1];

          // Current character of C matches with that of both A and B
          else if (A[i-1]==C[(i-1)+j] && B[j-1]==C[i+(j-1)])
              IL[i][j]=(IL[i-1][j] || IL[i][j-1]);
      }
  }

  return IL[M][N];

}

//////////////////////////////////////
LRU cache

简单的说，cache的存储是一个链表的话，那么只要保证从头到尾的顺序就是cache从新到旧的顺序就好了，
对于任何一个节点，如果被访问了，那么就将该节点移至头部。如果cache已满，那么就把尾部的删掉，从头部插入新节点。


class LRUCache{
 public:
     struct CacheEntry
     {
     public:
         int key;
         int value;
         CacheEntry(int k, int v) :key(k), value(v) {}
     };
 
     LRUCache(int capacity) {
         m_capacity = capacity;
     }
 
     int get(int key) {
         if (m_map.find(key) == m_map.end())
             return -1;
 
         MoveToHead(key);
         return m_map[key]->value;
     }
 
     void set(int key, int value) {
         if (m_map.find(key) == m_map.end())
         {
             CacheEntry newItem(key, value);
             if (m_LRU_cache.size() >= m_capacity)
             {
                 //remove from tail
                 m_map.erase(m_LRU_cache.back().key);
                 m_LRU_cache.pop_back();                
             }
 
             // insert in head.
             m_LRU_cache.push_front(newItem);
             m_map[key] = m_LRU_cache.begin();
             return;
         }
 
         m_map[key]->value = value;
         MoveToHead(key);
     }
 
 private:
     unordered_map<int, list<CacheEntry>::iterator> m_map;
     list<CacheEntry> m_LRU_cache;
     int m_capacity;
 
     void MoveToHead(int key) 
     {
         //Move key from current location to head
         auto updateEntry = *m_map[key];
         m_LRU_cache.erase(m_map[key]);
         m_LRU_cache.push_front(updateEntry);
         m_map[key] = m_LRU_cache.begin();
     }
 
 };



/////////////////////////////////////////////  
combinations 

Given two integers n and k, return all possible combination of k numbers out of 1, 2, ..., n. 
solution: 1. 暴力求解n!循环  2. DFS + backtracking.  注意level的初始值由题目决定
e.g. n = 3, k=2. output: (1,2), (1,3), (2,3)


class Solution
{
    public:
        vector<vector<int>> combine(int n, int k)
        {
            vector<vector<int>> ret; 

            // corner case 
            if(n <= 0)
                return ret; 

            vector<int> curr; 
            DFS(ret, curr, n, k, 1);
            return ret;

        }    

        void DFS(vector<vector<int>>& ret, vector<int> curr, int n, int k, int level)
        {
            if(curr.size() == k)
            {
                ret.push_back(curr);    // 需要满足条件才能push back
                return; 
            }
            if(curr.size() > k)
                return; 

            for(int i = level; i <=n; ++i)
            {
                curr.push_back(i);   // preorder-search
                DFS(ret, curr, n, k, i+1);  // recursion here 
                curr.pop_back();   // backtracking
            }

        }

};

time complexity O(n!)


solution 2: 
 vector<vector<int>> combine(int n, int k) 
    {
        vector<vector<int>> res; 
        vector<int> out; 
        combineDFS(n, k, 1, res, out);
        return res; 
    }
    
    void combineDFS(int n, int k, int level, vector<vector<int>>& res, vector<int>& out)
    {
        if(out.size() == k)
            res.push_back(out); 
        
        for(int i = level; i <= n; ++i)
        {
            out.push_back(i);
            combineDFS(n, k, i+1, res, out); 
            out.pop_back(); 
        }
    }

//////////////////////////////////////////
Combination sum 

Given a set of candidate number (C) and a target number (T), find all unique combinations in C where 
the candidate numbers sums to T. The same repeated number may be chosen from C unlimited number of times.

class Solution
{
public: 
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        vector<vector<int>> ret;

        // corner case, 注意target 为负数
        if(candidates.size() == 0 || target < 0)
            return ret; 

        vector<int> curr; 
        sort(candidates.begin(), candidates.end());
        Backtracking(ret, curr, candidates, target, 0);
        return ret; 

    }

    void Backtracking(vector<vector<int>>& ret, vector<int> curr, vector<int> candidates, int target, int level)
    {
        if(target == 0)
        {
            ret.push_back(curr);     // 需要满足条件才能push back
            return; 
        }
        else if(target < 0)     // save time
            return;

        for(int i = level; i < candidates.size(); ++i)
        {

            target -= candidates[i];
            curr.push_back(candidates[i]);  // preorder search: DFS
            Backtracking(ret, curr, candidates, target, i)  // i没加1, different from last problem.
            curr.pop_back();   // backtracking
            target += candidates[i];    // add back

        }

    }

};

time complexity O(n!)

///////////////////////////////////////////

Given a set of candidate number (C) and a target number (T), find all unique combinations in C where 
the candidate numbers sums to T. The same repeated number can not be chosen from C unlimited number of times.


class Solution
{
public: 
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        vector<vector<int>> ret;

        // corner case, 注意target 为负数
        if(candidates.size() == 0 || target < 0)
            return ret; 

        vector<int> curr; 
        sort(candidates.begin(), candidates.end());
        Backtracking(ret, curr, candidates, target, 0);
        return ret; 

    }

    void Backtracking(vector<vector<int>>& ret, vector<int> curr, vector<int> candidates, int target, int level)
    {
        if(target == 0)
        {
            ret.push_back(curr);   // 需要满足条件才能push back
            return; 
        }
        else if(target < 0)     // save time
            return;

        for(int i = level; i < candidates.size(); ++i)  // i = level 为了让每一次的选择不重头选
        {

            target -= candidates[i];
            curr.push_back(candidates[i]);  // preorder search: DFS
            Backtracking(ret, curr, candidates, target, i+1)  // i加了1, different from last problem.
            curr.pop_back();   // backtracking
            target += candidates[i];    // add back

            while(i < num.size() - 1 && num[i] == num[i+1])   // skip the same number 
                ++i;

        }

    }

};


////////////////////////////////////////////////////
Letter combinations of a phone number 

Given a digital string, return all possible letter combinations that the number could represent. 
A mapping of digit to letter (like on the telephone buttons) is given. 

input: string "23". output: "ad", "ae", ... "cf"


class Solution
{
public: 
    vector<string> letterCombinations(string digits)
    {
        vector<string> ret; 
        vector<string> dictionary;

        string tmp;
        dictionary.push_back("");
        dictionary.push_back("");
        dictionary.push_back("abc");
        dictionary.push_back("def");
        dictionary.push_back("ghi");
        dictionary.push_back("jkl");
        dictionary.push_back("mno");
        dictionary.push_back("pqrs");
        dictionary.push_back("tuv");
        dictionary.push_back("wxyz");

        combinations(ret, tmp, digits, dictionary, 0);
        return ret; 

    }

    void combinations(vector<string>& ret, string tmp, string digits, vector<string> dictionary, int level)
    {
        if(level == digits.size())
        {
            ret.push_back(tmp);   // 需要满足条件才能push back
            return;
        }

        int index = dictionary[level] - '0';

        for(int i = 0; i < dictionary[index].size(); ++i)  // here i is initialized to 0
        {
            tmp.push_back(dictionary[index][i]);
            // combinations(ret, tmp, digits, dictionary, i+1);   // wrong
            combinations(ret, tmp, digits, dictionary, level+1);   // wrong
            tmp.pop_back();
        }

    }

};


///////////////////////////////////////////////////

subsets

Given a set of distinct integers, S, return all possible subsets. Note: elements in a subsets must be
in non-descending order.  input: S= [1, 2]  output: [1], [2], [1,2]
solution: DFS + backtracking; 和combination 区别：输出不是fixed size


class Solution
{
    public:
        vector<vector<int>> res;

        vector<vector<int>> subsets(vector<int>& S) 
        {
            if(S.empty())
                return res;

            sort(S.begin(), S.end());

            res.push_back(vector<int>());   // 注意空集
            vector<int> v; 

            generate(vector<int>& v, vector<int>& S, int start)
            {
                if(start == S.size())
                    return; 

                for(int i = start; i < S.size(); i++)
                {
                    v.push_back(S[i]);
                    res.push_back(v);
                    generate(v, s, i+1);
                    v.pop_back();
                }
            }
        }

};

===============================

Given a collection of integers might contain duplicates, S, return all possible subsets. Note: elements in a subsets must be
in non-descending order.  input: S= [2, 2]  output: [2]
solution: DFS + backtracking; 和combination 区别：输出不是fixed size


class Solution
{
    public:
        vector<vector<int>> res;

        vector<vector<int>> subsets(vector<int>& S) 
        {
            if(S.empty())
                return res;

            sort(S.begin(), S.end());

            res.push_back(vector<int>());   // 注意空集
            vector<int> v; 

            generate(vector<int>& v, vector<int>& S, int start)
            {
                if(start == S.size())  // 注意与combinations 区别 
                    // res.push_back(v);
                    return; 

                for(int i = start; i < S.size(); i++)
                {
                    v.push_back(S[i]);
                    res.push_back(v);   // 在这push back
                    generate(v, S, i+1);
                    v.pop_back();

                    // skip duplicate number 
                    while(i < S.size()-1 && S[i] == S[i+1])
                        i++;
                }

            }
        }

};


///////////////////////////////////////////
combinations/subsets: 在 m 个元素里选 0-m个，顺序固定
permutation: 在 m 个元素里选 m个, 不同顺序


Permutations
Given a collection of numbers, return all possible permutations. 
input: [1,2,3]. output:[1,2,3],[1,3,2] ... [3,2,1]


class Solution
{
public:
    vector<vector<int>> permute(vector<int>& num)
    {
        vector<vector<int>> permutations;
        if(num.size == 0)
            return permutations;

        vector<int> curr;
        vector<bool> isVisited(num.size(), false);

        backTracking(permutation, curr, isVisited, num);

        return permutations; 
    }

    void backTracking(vector<vector<int>>& ret, vector<int> curr, vector<bool> isVisited, vector<int> num)
    {
        if(curr.size() == num.size())
        {
            ret.push_back(curr);
            return;
        }

        for(int i = 0; i < num.size(); ++i)
        {
            if(isVisited[i] == false)   // difference 
            {
                isVisited[i] = true;    // difference
                curr.push_back(num[i]);
                backTracking(ret, curr, isVisited, num);  // difference: 注意没有+1操作
                curr.pop_back();
                isVisited[i] = false;  
            }
        }

    }

};


=========================================
Permutations
Given a collection of numbers with duplicate number, return all possible permutations without duplicate. 
input: [1,2,2]. output:[1,2,2],[1,3,2] ... [3,2,1]

solution: 先排序

class Solution
{
public:
    vector<vector<int>> permute(vector<int>& num)
    {
        vector<vector<int>> permutations;
        if(num.size == 0)
            return permutations;

        vector<int> curr;
        vector<bool> isVisited(num.size(), false);

        sort(num.begin(), num.end());
        backTracking(permutation, curr, isVisited, num);

        return permutations; 
    }

    void backTracking(vector<vector<int>>& ret, vector<int> curr, vector<bool> isVisited, vector<int> num)
    {
        if(curr.size() == num.size())
        {
            ret.push_back(curr);
            return;
        }

        for(int i = 0; i < num.size(); ++i)
        {
            if(isVisited[i] == false)   // difference 
            {
                isVisited[i] = true;    // difference
                curr.push_back(num[i]);
                backTracking(ret, curr, isVisited, num);  // difference: 注意没有+1操作
                curr.pop_back();
                isVisited[i] = false;  

                while(i < num.size() - 1 && num[i] == num[i+1])  // remove duplicates, 常用技巧
                    ++i; 
            }
        }

    }

    
///////////////////////////////////////
Single Number III
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.
    

    vector<int> singleNumber(vector<int>& A)
    {
        int x = 0;
        size_t len = A.size();
        int pos = 0;
        for (int i = 0; i < len; ++i)
            x ^= A[i];
        
        // get the first bit position of these two elements that number is different
        for (int i = 0; i < 32; ++i)
        {
            if (x & (1 << i))    // 1<<0 == 0; 1 << 1 == 1; 
            {  
                pos = i;
                break;
            }
        }
        
        // 把所有数分成两拨， 和那first bit position相&为0的和不为0的；
        vector<int> results(2);
        for (int i = 0; i < len; ++i)
        {
            if (A[i] & (1 << pos))   // 不为0的
                results[0] ^= A[i];
            else                      // 为0的
                results[1] ^= A[i];
        }
        
        return results;
        
    }
    
    
Single Number II   
Given an array of integers, every element appears three times except for one, 
which appears exactly once. Find that single one.

1. 对每一位进行求和
2. 对每一位的和做%3运算，来消去所有重复3次的数


  int singleNumber(vector<int>& A) 
    {
        int n = A.size(); 
        int res = 0;
        for(int i=31; i>=0; i--) {
            int sum = 0;
            int mask = 1<<i;
            for(int j=0; j<n; j++) {
                if(A[j] & mask) 
                    sum++;
            }
            res = (res<<1) + (sum%3);
        }
        return res;
        
    }

////////////////////////////////////
 K-diff Pairs in an Array  

 Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array. 
 Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k.
The pairs (i, j) and (j, i) count as the same pair, but return only one. 

int findPairs(vector<int>& nums, int k) 
{
    int count = 0; 
    
    sort(nums.begin(), nums.end());
    
    for(int i = 0; i < nums.size(); )
    {
        for(int j = i+1; j < nums.size(); )
        {
            if(abs(nums[i] - nums[j]) == k)
            {
                count++;
            }
            
            while(nums[j] == nums[j+1])
            {
                ++j; 
            }
            ++j;
        }
        
        while(nums[i] == nums[i+1])
        {
            ++i; 
        }
        ++i;
        
    }
    return count; 
}

//////////////////////////////   
Lonely Pixel I 

Given a picture consisting of black and white pixels, find the number of black lonely pixels.
The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.
A black lonely pixel is character 'B' that located at a specific position where the same row and same column don not have any other black pixels.

[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']] 

int findLonelyPixel(vector<vector<char>>& picture) 
    {
        vector<int> row(picture.size(), 0); 
        vector<int> col(picture[0].size(), 0);
        
        for(int i = 0; i < picture.size(); ++i)
        {
            int count = 0; 
            for(int j = 0; j < picture[i].size(); ++j)
            {
                if(picture[i][j] == 'B')
                    count++; 
                
            }
            row[i] = count; 
        }
        
        for(int i = 0; i < picture[0].size(); ++i)
        {
            int count = 0; 
            for(int j = 0; j < picture.size(); ++j)
            {
                if(picture[j][i] == 'B')
                    count++;
            }
            col[i] = count; 
            
        }
        
        int count = 0; 
        for(int i = 0; i < picture.size(); ++i)
        {
            for(int j = 0; j < picture[i].size(); ++j)
            {
                if(picture[i][j] == 'B')  //这一行很重要 
                {
                    if(row[i] == 1)
                    {
                        if(col[j] == 1)
                            count++;                                         
                    }               
                }               
            }
 
        }        
        return count;              
    }

//////////////////////////////////////////   
First bad version. 

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

solution 1: 
 int firstBadVersion(int n) {
        int low = 1, high = n; 
        // int mid = low + (high-low)/2; 
        
        while(low + 1 < high)
        // while(low < high)   // this is wrong 
        {
            int mid = low + (high-low)/2; 

            if(isBadVersion(mid))
            {
               high = mid; 
            }
            else
            {
                low = mid; 
            }
            // mid = low + (high-low)/2;
        
        }
        
        // 不能确定只return low, or 只return high. 有可能都是bad version
        if(isBadVersion(low))
            return low;
        else 
            return high; 
        
    }


solution 2: 
int firstBadVersion(int n) 
{
        int low = 1, high = n; 
        
        // while(low + 1 < high)
        while(low < high)   // this is wrong 
        {
            int mid = low + (high-low)/2; 

            if(isBadVersion(mid))
            {
               high = mid; 
            }
            else
            {
            	// low = mid;  // 否则会出现死循环，low一直比high小. 原因是除法是向下取整 
                low = mid + 1;  // 注意区别
            }
        }
        
        // 不能确定只return low, or 只return high. 有可能都是bad version
        // if(isBadVersion(low))
        //     return low;
        // else 
            return high; 
        
    }


solution 3: 
int firstBadVersion(int n) {
        int low = 1, high = n; 
        
        // while(low + 1 < high)
        // while(low < high)   // this is wrong 
        while(low <= high)    
        {
            int mid = low + (high-low)/2; 

            if(isBadVersion(mid))
            {
               high = mid - 1; 
            }
            else
            {
            	// low = mid;  // 否则会出现死循环，low一直比high小. 原因是除法是向下取整 
                low = mid + 1;  // 注意区别
            }
        }
        
        // 不能确定只return low, or 只return high. 有可能都是bad version
        // if(isBadVersion(low))
        //     return low;
        // else 
            return low;  // 或者  return high + 1; 
            return high + 1; 
        
    }

//////////////////////////////////////////
Search Insert Position

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0


int searchInsert(vector<int>& nums, int target) {
        int low = 0; 
        int high = nums.size(); 
        
        while(low < high)
        {
            int mid = low + (high-low)/2; 
            if(nums[mid] == target) 
                return mid; 
            else if(nums[mid] > target)
                high = mid;
            else
                low = mid + 1; 
            
        }
        
        // return high; 
        return low;   // 注意是return low ， 这里return 的只是inserted index. target index上面返回
        
        
    }



=============================================
Search for a Range
Given an array of integers sorted in ascending order, find the starting and ending position of a given target value.

Your algorithms runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4]. 

solution: 关键target在数组中的左右边界， 要分别往左搜和往右搜，need two binary search 
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
     
        
              vector<int> ret; 
         // vector has 0 element
        if(nums.size() == 0)
        {
             ret.push_back(-1);
            ret.push_back(-1);
            return ret; 
        }
        
        // vector has only one element
        if(nums.size() == 1 && nums[0] == target)
        {
            ret.push_back(0);
            ret.push_back(0);
            return ret; 
            
        }
        else if(nums.size() == 1 && nums[0] != target)
        {
            ret.push_back(-1);
            ret.push_back(-1);
            return ret; 
            
        }
        
        
           int low = 0; 
        int high = nums.size(); 
        
        // 往左搜
        while(low < high)
        {
            int mid = low + (high - low)/2; 
            
            if(nums[mid] == target)
                high = mid; 
            else if(nums[mid] > target)
                high = mid; 
            else if(nums[mid] < target)
                low = mid + 1; 
            
        }
        
       // 注意这几行代码 
        if(high == nums.size())
            ret.push_back(-1);
        else if(nums[high] == target)
            ret.push_back(high);
        else
            ret.push_back(-1);
            
        
        low = 0; 
        high = nums.size(); 
        
        // 往右搜
         while(low + 1 < high)
        {
            int mid = low + (high - low)/2; 
            
            if(nums[mid] == target)
                low = mid; 
            else if(nums[mid] > target)
                high = mid; 
            else if(nums[mid] < target)
                low = mid + 1; 
        }
        
        
        if(nums[low] == target)
            ret.push_back(low);
        else
            ret.push_back(-1);
        
        
        return ret; 
        
    }
};


========================================



 bool isPerfectSquare(int num) {
        long low = 1; 
        long high = num; 
        
        // while(low < high)  // wrong: 因为low和high可能会需要相等， 当num=1时。  
        while(low <= high)
        {
            long mid = low + (high - low)/2; // 注意是long型, 用int会超时 
            if(mid * mid == num)
                return true;
            else if(mid * mid < num)
                low = mid +1;
            else 
                high = mid-1; 
    
        }
        
        return false;     
        
    }


====================================

每个houses对应所以的heaters, 在此前提下对所有heaters进行binary search, 找出离那个house左边和右边最近的两个heaters, 然后这两个heaters取距离最小的那个.  

对所有houses重复上面算法，取上面所得距离最大的那个  

    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int res = 0, n = heaters.size();
        sort(heaters.begin(), heaters.end());
        for (int house : houses) 
        {	

        	int left = 0, right = n;
            
            while (left < right) 
            {
                int mid = left + (right - left) / 2;

                if (heaters[mid] < house) // 找到那个heater刚比house大的
                	left = mid + 1;
                else 
                	right = mid;
            }

            // int dist1 = (right == n) ? INT_MAX : heaters[right] - house;
            // int dist2 = (right == 0) ? INT_MAX : house - heaters[right - 1];

            int dist1, dist2; // need to be visible to the line : max(res, min(dist1, dist2)) 

            if(right == n)   // right == n 时, 超出index范围. house有可能只有左边或只有右边有heater (只有一个heater时), 所以要用INT_MAX.  
            	dist1 = INT_MAX;   // 有比house大的heater, 但没有比house小的heater, 所以用INT_MAX
            else 
            	dist1 = heaters[right] - house; 

            if(right == 0)  // 有比house小的heater, 但没有比house大的heater, 所以用INT_MAX
            	dist2 = INT_MAX; 
            else 
            	dist2 = house - heaters[right-1]; 

            res = max(res, min(dist1, dist2));
        }

        return res;
    }

===============================================  
Intersection of Two Arrays 
Given two arrays, write a function to compute their intersection. 


 vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ret; 
        
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        for(int i = 0; i < nums1.size(); ++i)
        {
       
       	// nlogn solution:  using binary search 

            int low = 0; 
            int high = nums2.size();
            while(low < high)
            {
                int mid = low + (high-low)/2;
                
                if(nums2[mid] == nums1[i])
                {
                    ret.push_back(nums2[mid]);
                    break; 
                    
                }
                else if(nums2[mid] > nums1[i])
                    high = mid; 
                else 
                    low = mid +1;                     
            }
            
            
        // n^2 solution: 

            // for(int j = 0; j < nums2.size(); ++j)
            // {
            //     //  while(nums2[j] == nums2[j+1])
            //     //     ++j;
                    
            //     if(nums2[j] == nums1[i])
            //     {
            //         ret.push_back(nums2[j]);
                
            //         break;
            //     }
            // }

            while(nums1[i] == nums1[i+1])
                ++i; 
        }
        
        return ret;         
    }

=====================================
Intersection of Two Arrays II 

Given two arrays, write a function to compute their intersection. 

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].  // 最小重复值 

Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.



vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        vector<int> ret;
        
        int i= 0, j = 0; 
         while(i < nums1.size() && j < nums2.size())  // two index/pointer 
        {
                if(nums1[i] == nums2[j])
                {
                    ret.push_back(nums1[i]);
                    i++, j++; 
                }
                else if(nums1[i] > nums2[j])
                    j++;
                else 
                    i++; 
         
        }
        return ret; 
        
    }

=======================================
Two Sum II - Input array is sorted
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2


 vector<int> twoSum(vector<int>& numbers, int target) {
        
        vector<int> ret; 
        
        int i = 0; 
        int j = numbers.size()-1; 
        
        while(i < numbers.size() && j > 0)
        {
            if(numbers[i] + numbers[j] == target)
            {
                ret.push_back(i+1);
                ret.push_back(j+1);
                break;  
            }
            else if(numbers[i] + numbers[j] > target)
                --j;
            else 
                ++i; 
        }
        return ret; 
    }

==========================================
Implement int sqrt(int x).

input: 5
output: 2

这道题准确来说是找 a*a <= x; sqrt root可以比x小	
Corner case: 
(1) x<0，return -1表示出错（需要和面试官讨论）。
(2) x=0或1，此时mid=0，会形成x/y = 0/0。需要特殊处理。

int mySqrt(int x) 
{
        int low = 0; 
        int high = x;
        
        if(x <= 1)  // 0/1 corner cases; 
            return x; 
            
        while(low <= high)  // 因为low有可能等于high
        {
            int mid = low + (high-low)/2;   
            // if(mid*mid == x)  // wrong: mid太大时，mid*mid会超出范围. 若long mid; 则可以通过  
            if(x/mid == mid)
                return mid; 
            // else if(mid*mid < x)  // wrong
            else if(x/mid > mid)
                low = mid+1; 
            else
                high = mid-1;
        }
        
        // return low; // wrong: low的值比high大，low 确保 mid*mid > x, 因为 low = mid+1
        return high;  // 要往下取, high 确保 mid*mid < x, 因为 high = mid-1
        
    }

=========================================   
You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.

Given n, find the total number of full staircase rows that can be formed.



O(n) 解法
int arrangeCoins(int n) {
        // 1+2+3+...x <= n 
        // return x 
        
        int count = 0;
        while(n >= 0)
        {
            count++; 
            n = n - count;
            
        }
        return count-1; 
    }


logn 解法
 int arrangeCoins(int n) {
        // 1+2+3+...x <= n 
        // return x 
        
        if (n <= 1) return n;
        long low = 1, high = n;
        
        while (low < high) 
        {
            long mid = low + (high - low) / 2; // 注意是long型，计算前i行之和有可能会整型溢出
            if (mid * (mid + 1) / 2 <= n) 
                low = mid + 1;
            else 
                high = mid;
        }
        return low - 1;  // 注意不是low, 因为返回的x*(x+1)/2要>=n. 类似上面题目 
    }

==============================  
Divide Two Integers 

Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.

solution: 这个解法会超时， 
int divide(int dividend, int divisor) {

        if(divisor == 1)
            return dividend;
        if(dividend == INT_MIN && abs(divisor) == 1)
            return INT_MAX;  // abs(INT_MIN) 等于 INT_MIN
        
        // long long a = dividend >= 0 ? dividend : -(long long) dividend;
        // long long b = divisor >= 0 ? divisor : -(long long) divisor;
        long long a = abs((long long) dividend);
        long long b = abs((long long) divisor);
        // long long b = abs(divisor); // wrong: int 不够大，会溢出
        
        
        long long count = 0; 

        while(a >= 0)
        {
                a = a - b;
                count++;
        }
        
        if((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0) )
            return -(count-1); 
        else 
            return count-1; 
}


=======================================  
Search in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

solution: 
A[mid] =  target, 返回mid，否则

(1) A[mid] < A[end]: A[mid+1 : end] sorted
A[mid] < target <= A[end]  右半，否则左半。

(2) A[mid] > A[end] : A[start : mid-1] sorted
A[start] <= target < A[mid] 左半，否则右半。



int search(vector<int>& A, int target) {
   int n = A.size();
        int start = 0, end = n-1;

        while(start <= end) {   // 有可能出现一个元素, 所以用<=
            int mid = start + (end-start)/2;
            if(A[mid]==target) return mid;  
            
            if(A[mid]<A[end]) 
            { // right half sorted
                if(target>A[mid] && target<=A[end])
                    start = mid+1;
                else
                    end = mid-1;
            }
            else {  // left half sorted
                if(target>=A[start] && target<A[mid]) 
                    end = mid-1;
                else
                    start = mid+1;
            }
        }
        return -1;
    }


==========================================  
Pow(x, n)

solution1 : 注意n有可能为负数， n可以为奇数或偶数
这个解法用到recursion. 


double power(double x, int n) 
{
    if (n == 0) 
    	return 1.0;

    double ret = power(x, n / 2);

    if (n % 2 == 0) 
    	return ret * ret;
    else 
    	return x * ret * ret;
}


double myPow(double x, int n) 
{
  if(n == 0)
        return 1.0; 

    if(n < 0) 
    	return 1 / power(x, -n);
    
    if(n > 0)return power(x, n);
}


solution2: 

   double myPow(double x, int n) {
        double ret = 1.0; 
        
        if(n == 0)
            return ret; 
        
        ret = myPow(x, n/2);
        if(n%2 == 0)
            return ret*ret; 
        else if(n > 0)
            return ret*ret*x; 
        else if(n < 0)
            return ret*ret/x;  // 为什么要这样处理, 不理解 
            
    }

===========================================   

Search a 2D Matrix  
solution: two index/pointer method 
bool searchMatrix(vector<vector<int>>& matrix, int target) 
{
    
    if(matrix.size() == 0 || matrix[0].size() == 0)
        return false; 
    
    int i = 0;
    int j = matrix[0].size()-1;
    
    while(i < matrix.size() && j >= 0)
    {
            if(matrix[i][j] == target)
                return true; 
            // else if(matrix[i][j] > target)   // 错误，因为else if和else的内容位置
            //     --j; 						// 注意和下面区别 
            // else
            //     ++i; 
            else if(target > matrix[i][j])
                ++i; 
            else
                --j; 
     
    }       
    return false; 
}

============================================      
Search in Rotated Sorted Array II  

当有重复数字，会存在A[mid] = A[end]的情况。此时右半序列A[mid-1 : end]可能是sorted，也可能并没有sorted，如下例子。

3 1 2 3 3 3 3 
3 3 3 3 1 2 3

所以当A[mid] = A[end] != target时，无法排除一半的序列，而只能排除掉A[end]：

A[mid] = A[end] != target时：搜寻A[start : end-1]

正因为这个变化，在最坏情况下，算法的复杂度退化成了O(n)：
序列 2 2 2 2 2 2 2 中寻找target = 1。


bool search(vector<int>& A, int target) 
{

	    int n = A.size();
        int start = 0, end = n-1;
        while(start<=end) {
            int mid = start + (end-start)/2;
            if(A[mid]==target) return true;  
            
            if(A[mid]<A[end]) { // right half sorted
                if(target>A[mid] && target<=A[end])
                    start = mid+1;
                else
                    end = mid-1;
            }
            else if(A[mid] > A[end]) {  // left half sorted
                if(target>=A[start] && target<A[mid]) 
                    end = mid-1;
                else
                    start = mid+1;
            }
            else
                end--; 
        }
        // return -1;
        
        return false; 
        
    }

==========================================  
Minimum Size Subarray Sum 

我们用两个指针维护一个窗口，保证这个窗口的内的和是小于目标数的。如果新来的数加上后，和大于目标，则比较下当前窗口长度和最短窗口长度，窗口左边界右移。如果和仍小于目标数，则将窗口右边界右移。注意这里退出的条件，右边界是小于等于长度，因为我们窗口到了最右侧时，还需要继续左移左边界来看有没有更优的解法。另外，如果左边界大于右边界时，说明最短子串的长度已经小于等于1，我们就不用再查找了。

solution 1: O(n)
int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.size() == 0)
            return 0; 
        
        int left = 0, right = 0, sum = 0, minLen = nums.size()+1;
        while(right <= nums.size() && left <= right)
        {
            if(sum < s)
            {
                // 当右边界等于长度时，我们要多等一轮，等待左边界左移，这时候不能加
                if(right < nums.size())
                    sum += nums[right];
                
                right++; 
            }
            else
            {
                // 当和大于等于目标时，检查长度并左移边界
                minLen = min(minLen, right-left);
                sum -= nums[left];
                left++; 
            }
        }
        
        return minLen <= nums.size() ? minLen : 0;
        
    }

solution 2: binary search O(nlong)


==============================================  

Longest Palindromic Substring
Given a string s, find the longest palindromic substring in s.   

solution 1: Manacher Algorithm 
www.youtube.com/watch?v=nbTSfrEfo6M   // 讲解 

string longestPalindrome(string s) 
{
    
    string t = "$#";
    for(int i = 0; i < s.size(); ++i)
    {
        t += s[i];
        t += "#"; 
    }
    // t += "@";   // 这行可要可不要
    
    vector<int> p(t.size(), 0); 
    
    int C = 0, R = 0; 
    
    for(int i = 1; i < t.size() -1; ++i)
    {
        int mirr = 2*C - i; 
        
        if(i < R)
            p[i] = min(R - i, p[mirr]);
            
        while(t[i + (1 + p[i])] == t[i - (1 + p[i])])
            p[i]++; 
            
        if(i + p[i] > R)
        {
            C = i; 
            R = i + p[i];
        }
     }
     
     int length = 0; 
     C = 0;
     for(int i = 1; i < p.size()-1; ++i)
     {
         if(p[i] > length)
         {
             length = p[i]; 
             C = i;
         }
     }
     
    //  return s.substr((C - 1 - length)/2, (C - 1 + length)/2 );   // wrong: substr(begin_index, length);  
    return s.substr((C - 1 - length)/2, length );
    
}

time O(n); 


solution 2: brutal force (O(n^3)); 
solution 3: O(n^2) 


================================================
median of two sorted arrays 

leilater.gitbooks.io/codingpractice/content/binary_search/median_of_two_sorted_arrays.html  


  /*
    对于一个长度为n的已排序数列a，若n为奇数，中位数为a[n / 2 + 1] , 
    若n为偶数，则中位数(a[n / 2] + a[n / 2 + 1]) / 2
    如果我们可以在两个数列中求出第K小的元素，便可以解决该问题
    不妨设数列A元素个数为n，数列B元素个数为m，各自升序排序，求第k小元素
    取A[k / 2] B[k / 2] 比较，
    如果 A[k / 2] > B[k / 2] 那么，所求的元素必然不在B的前k / 2个元素中(证明反证法)
    反之，必然不在A的前k / 2个元素中，于是我们可以将A或B数列的前k / 2元素删去，求剩下两个数列的
    k - k / 2小元素，于是得到了数据规模变小的同类问题，递归解决
    如果 k / 2 大于某数列个数，所求元素必然不在另一数列的前k / 2个元素中，同上操作就好。
    */

// A_st(数组A的最左端), B_st(数组B的最右端) 类似于low, high; 随时移动
    double findKth(vector<int>& A, vector<int>& B, int A_st, int B_st, int k) 
    {
        // 边界情况，任一数列为空
        if (A_st >= A.size()) 
        {
            return B[B_st + k - 1];
        }

        if (B_st >= B.size()) 
        {
            return A[A_st + k - 1];  // 数组里的k-1和函数里的k是一个意思：第k个元素
        }

        // k等于1时表示取最小值，直接返回min
        if (k == 1) return min(A[A_st], B[B_st]);

        int A_key = A_st + k / 2 - 1 >= A.size() ? INT_MAX : A[A_st + k / 2 - 1];
        int B_key = B_st + k / 2 - 1 >= B.size() ? INT_MAX : B[B_st + k / 2 - 1];

        if (A_key < B_key)
        {
            return findKth(A, B, A_st + k / 2, B_st, k - k / 2);  // recusion 
        } 
        else 
        {
            return findKth(A, B, A_st, B_st + k / 2, k - k / 2);   // recursion 
        }
        
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        int sum = nums1.size() + nums2.size();
        double ret;
        
        if (sum & 1)   //判断奇偶数
        {
            ret = findKth(nums1, nums2, 0, 0, sum / 2 + 1);
        } else {
            ret = ((findKth(nums1, nums2, 0, 0, sum / 2)) +
                    findKth(nums1, nums2, 0, 0, sum / 2 + 1)) / 2.0;
        }
        return ret;
    }


===========================================================
Search a 2D Matrix II 

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.  

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]



bool searchMatrix(vector<vector<int>>& matrix, int target) 
{
    if(matrix.size() == 0)
        return false; 
    
    // for(int i = 0; i < matrix.size(); )   // there is error 
    // {
    //     for(int j = matrix[0].size() -1; j >= 0; )   // there is error , 因为i的值不会在for内循环检查; matrix[i][j] 会越界.  
    //     {  
    
    int i = 0; 
    int j = matrix[0].size()-1;
    
    while(i < matrix.size() && j >= 0)   // while 循环
    {
    
        if(matrix[i][j] == target)
            return true; 
        else if(matrix[i][j] > target)
            --j;
        else 
            ++i; 
    }
    
    return false; 

}


====================================
Longest Increasing Subsequence  

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS 


int lengthOfLIS(vector<int>& nums) 
{
    
    vector<int> counts(nums.size(), 0);  // counts count the LIS for every number
    
    int max = 0;
    for (int i = 0; i < nums.size(); i++) {
        counts[i] = 1;
        for (int j = 0; j < i; j++) 
        {
            if (nums[j] < nums[i]) 
            {
            	if(counts[i] > counts[j] + 1)
            		counts[i] = counts[i];
            	else 
            		counts[i] = counts[j] + 1; 

                // counts[i] = counts[i] > counts[j] + 1 ? counts[i] : counts[j] + 1;
            }
        }
        if (counts[i] > max) {
            max = counts[i];
        }
    }
    return max;
}

======================================
Kth Smallest Element in a Sorted Matrix  

Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.
k is always valid, 1 ≤ k ≤ n2.  

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,
return 13.


solution 1: maximum heap (c++ priority queue)

int kthSmallest(vector<vector<int>>& matrix, int k) 
{
    // priority_queue<int, vector<int>> q;
    priority_queue<int> q;
    for (int i = 0; i < matrix.size(); ++i) 
    {
        for (int j = 0; j < matrix[i].size(); ++j) 
        {
            q.push(matrix[i][j]);
            if (q.size() > k) 
            	q.pop();
        }
    }
    return q.top();
}


solution 2: 

=========================================
Find Right Interval 找右区间  

e.g. Input: [ [1,2] ]  Output: [-1]
Explanation: There is only one interval in the collection, so it outputs -1.

e.g. Input: [ [3,4], [2,3], [1,2] ] Output: [-1, 0, 1]
Explanation: There is no satisfied "right" interval for [3,4].
For [2,3], the interval [3,4] has minimum-"right" start point;
For [1,2], the interval [2,3] has minimum-"right" start point.



output: 每个interval 的第一个右区间的index 

 vector<int> findRightInterval(vector<Interval>& intervals) 
 {
    vector<int> res;
    map<int, int> m;

    for (int i = 0; i < intervals.size(); ++i) 
    {
        m[intervals[i].start] = i;
    }

    for (auto a : intervals) 
    {
        auto it = m.lower_bound(a.end);

        if (it == m.end()) 
        	res.push_back(-1);
        else 
        	res.push_back(it->second);
    }

    return res;
}

============================================   
Is Subsequence 是子序列  

Given a string s and a string t, check if s is subsequence of t.

"ace" is a subsequence of "abcde" while "aec" is not 

solution: two indexs 
bool isSubsequence(string s, string t) 
{
    if (s.empty()) return true;
    int i = 0, j = 0;
    while (i < s.size() && j < t.size()) 
    {
        if (s[i] == t[j]) 
        	++i;

        ++j;
    }
    return i == s.size();
}


==============================================
4Sum II 
Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.  

我们如果把A和B的两两之和都求出来，在哈希表中建立两数之和跟其出现次数之间的映射，那么我们再遍历C和D中任意两个数之和，我们只要看哈希表存不存在这两数之和的相反数就行了 O(n^2)

int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    int res = 0;
    unordered_map<int, int> m;
    for (int i = 0; i < A.size(); ++i) 
    {
        for (int j = 0; j < B.size(); ++j) 
        {
            ++m[A[i] + B[j]];
        }
    }

    for (int i = 0; i < C.size(); ++i) 
    {
        for (int j = 0; j < D.size(); ++j) 
        {
            int target = -1 * (C[i] + D[j]);
            res += m[target];
        }
    }
    return res;
}

brutal force (O(n^4))  
=========================================     
Number of Islands 岛屿的数量 
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

11000
11000
00100
00011
Answer: 3

这道求岛屿数量的题的本质是求矩阵中连续区域的个数，很容易想到需要用深度优先搜索DFS来解，我们需要建立一个visited数组用来记录某个位置是否被访问过，对于一个为‘1’且未被访问过的位置，我们递归进入其上下左右位置上为‘1’的数，将其visited对应值赋为true，继续进入其所有相连的邻位置，这样可以将这个连通区域所有的数找出来，并将其对应的visited中的值赋true，找完次区域后，我们将结果res自增1，然后我们在继续找下一个为‘1’且未被访问过的位置，以此类推直至遍历完整个原数组即可得到最终结果



void numIslandsDFS(vector<vector<char> > &grid, vector<vector<bool> > &visited, int x, int y) 
{
    if (x < 0 || x >= grid.size()) 
    	return;
    if (y < 0 || y >= grid[0].size()) 
    	return;

    if (grid[x][y] != '1' || visited[x][y]) 
    	return;
    
    visited[x][y] = true;
    numIslandsDFS(grid, visited, x - 1, y);
    numIslandsDFS(grid, visited, x + 1, y);
    numIslandsDFS(grid, visited, x, y - 1);
    numIslandsDFS(grid, visited, x, y + 1);
}


int numIslands(vector<vector<char> > &grid) 
{
    if (grid.empty() || grid[0].empty()) 
    	return 0;

    int m = grid.size(), n = grid[0].size(), res = 0;

    vector<vector<bool> > visited(m, vector<bool>(n, false));

    for (int i = 0; i < m; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            if (grid[i][j] == '1' && !visited[i][j]) 
            {
                numIslandsDFS(grid, visited, i, j);
                ++res;
            }
        }
    }
    return res;
}


=========================================   
Remove Invalid Parentheses 

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
Note: The input string may contain letters other than the parentheses ( and ).

e.g. 
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""]

 vector<string> removeInvalidParentheses(string s) 
 {
    vector<string> res;
    unordered_map<string, int> visited;

    queue<string> q;
    q.push(s);
    ++visited[s];
    bool found = false;

    while (!q.empty()) 
    {
        s = q.front(); 
        q.pop();
        if (isValid(s)) 
        {
            res.push_back(s);
            found = true;
        }

        if (found) continue;
        for (int i = 0; i < s.size(); ++i) 
        {
            if (s[i] != '(' && s[i] != ')') 
            	continue;

            string t = s.substr(0, i) + s.substr(i + 1);  // remove char at i 

            if (visited.find(t) == visited.end()) 
            {
                q.push(t);
                ++visited[t];
            }
        }
    }
    return res;
}


bool isValid(string t) 
{
    int cnt = 0;
    for (int i = 0; i < t.size(); ++i) 
    {
        if (t[i] == '(') 
        	++cnt;

        if (t[i] == ')' && cnt-- == 0) 
        	return false;
    }
    return cnt == 0;
}


======================================== 
Course Schedule 

There are a total of n courses you have to take, labeled from 0 to n - 1.
Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?


第一条就告诉我们了这道题的本质就是在有向图中检测环。 LeetCode中关于图的题很少，有向图的仅此一道，还有一道关于无向图的题是 Clone Graph 无向图的复制。个人认为图这种数据结构相比于树啊，链表啊什么的要更为复杂一些，尤其是有向图，很麻烦。第二条提示是在讲如何来表示一个有向图，可以用边来表示，边是由两个端点组成的，用两个点来表示边。第三第四条提示揭示了此题有两种解法，DFS和BFS都可以解此题。我们先来看BFS的解法，我们定义二维数组graph来表示这个有向图，一位数组in来表示每个顶点的入度。我们开始先根据输入来建立这个有向图，并将入度数组也初始化好。然后我们定义一个queue变量，将所有入度为0的点放入队列中，然后开始遍历队列，从graph里遍历其连接的点，每到达一个新节点，将其入度减一，如果此时该点入度为0，则放入队列末尾。直到遍历完队列中所有的值，若此时还有节点的入度不为0，则说明环存在，返回false，反之则返回true。


solution 1 : BFS 
bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) 
{
        
    vector<vector<int> > graph(numCourses, vector<int>(0));  // graph(vertexs 数目, 每个vertex所指向的所有vertexs)
    vector<int> in(numCourses, 0);   // 入度

    for (auto a : prerequisites) 
    {
        graph[a.second].push_back(a.first);  // 有向图， a.second 指向 a.first. a.second是prerequisites, a.first 是需要prerequisites的courses.  
        ++in[a.first];
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) 
    {
        if (in[i] == 0) 
        	q.push(i);
    }

    while (!q.empty()) 
    {
        int t = q.front();
        q.pop();

        for (auto a : graph[t])  
        {
            --in[a];   // 所有prerequisites是a的vertexs的度数减一   
            if (in[a] == 0) 
            	q.push(a);
        }
    }

    for (int i = 0; i < numCourses; ++i) 
    {
        if (in[i] != 0) 
        	return false;
    }

    return true;
}

---------------------------------

下面我们来看DFS的解法，也需要建立有向图，还是用二维数组来建立，和BFS不同的是，我们像现在需要一个一维数组visit来记录访问状态，大体思路是，先建立好有向图，然后从第一个门课开始，找其可构成哪门课，暂时将当前课程标记为已访问，然后对新得到的课程调用DFS递归，直到出现新的课程已经访问过了，则返回false，没有冲突的话返回true，然后把标记为已访问的课程改为未访问。

solution 2: DFS .  判断有无cycle, 若之前visit过了则有cycle. 
bool canFinishDFS(vector<vector<int> > &graph, vector<int> &visit, int i) 
{
    if (visit[i] == -1) return false;
    if (visit[i] == 1) return true;
    visit[i] = -1;

    for (auto a : graph[i]) 
    {
        if (!canFinishDFS(graph, visit, a)) 
        	return false;
    }
    visit[i] = 1;
    return true;
}  


bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) 
{

        
    vector<vector<int> > graph(numCourses, vector<int>(0));
    vector<int> visit(numCourses, 0);

    for (auto a : prerequisites) 
    {
        graph[a.second].push_back(a.first);
    }

    for (int i = 0; i < numCourses; ++i) 
    {
        if (!canFinishDFS(graph, visit, i)) 
        	return false;
    }
    return true;
}

==========================================================
Course Schedule II 

这题是之前那道 Course Schedule 课程清单的扩展，那道题只让我们判断是否能完成所有课程，即检测有向图中是否有环，而这道题我们得找出要上的课程的顺序，即有向图的拓扑排序，这样一来，难度就增加了，但是由于我们有之前那道的基础，而此题正是基于之前解法的基础上稍加修改，我们从queue中每取出一个数组就将其存在结果中，最终若有向图中有环，则结果中元素的个数不等于总课程数，那我们将结果清空即可。

vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) 
{
    vector<int> res;
    vector<vector<int> > graph(numCourses, vector<int>(0));
    vector<int> in(numCourses, 0);

    for (auto &a : prerequisites) 
    {
        graph[a.second].push_back(a.first);
        ++in[a.first];
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) 
    {
        if (in[i] == 0) q.push(i);
    }

    while (!q.empty()) 
    {
        int t = q.front();
        res.push_back(t);  // different line 
        q.pop();

        for (auto &a : graph[t]) 
        {
            --in[a];
            if (in[a] == 0) 
            	q.push(a);
        }
    }

    if (res.size() != numCourses) 
    	res.clear();
    return res;
}




=============================================================    
Nested List Weight Sum 

Given a nested list of integers, return the sum of all integers in the list weighted by their depth.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.
Example 1:
Given the list [[1,1],2,[1,1]], return 10. (four 1 at depth 2, one 2 at depth 1)

Example 2:
Given the list [1,[4,[6]]], return 27. (one 1 at depth 1, one 4 at depth 2, and one 6 at depth 3; 1 + 4*2 + 6*3 = 27)



int depthSum(vector<NestedInteger>& nestedList) 
{
    int res = 0;
    for (auto a : nestedList) 
    {
        res += getSum(a, 1);
    }
    return res;
}

int getSum(NestedInteger ni, int level) 
{
    int res = 0;
    if (ni.isInteger()) 
        return level * ni.getInteger();
    
    for (auto a : ni.getList()) 
    {
        res += getSum(a, level + 1);
    }
    return res;
}


solution 2:  much slower than solution 1 

int depthSum(vector<NestedInteger>& nestedList) 
{
  return depth(nestedList, 1); 
}


int depth(vector<NestedInteger>& nestedList, int count)
{
    int sum = 0; 

    for(int i = 0; i < nestedList.size(); ++i)
    {
        if(nestedList[i].isInteger())
            sum += count*nestedList[i].getInteger(); 
        else 
        {
            // count = count+1;   		// 不知道为什么这两句是错的 
            // sum += depth(nestedList[i].getList(), count); 

            sum += depth(nestedList[i].getList(), count+1);
        }
            
    }
    
    return sum; 
}

=============================================
Nested List Weight Sum II  

Different from the previous question where weight is increasing from root to leaf, now the weight is defined from bottom up. i.e., the leaf level integers have weight 1, and the root level integers have the largest weight. 
e.g. Given the list [[1,1],2,[1,1]], return 8. (four 1 at depth 1, one 2 at depth 2)





==============================================    

Longest Increasing Path in a Matrix 矩阵中的最长递增路径  


Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]

return 4 


这道题给我们一个二维数组，让我们求矩阵中最长的递增路径，规定我们只能上下左右行走，不能走斜线或者是超过了边界。那么这道题的解法要用递归和DP来解，用DP的原因是为了提高效率，避免重复运算。我们需要维护一个二维动态数组dp，其中dp[i][j]表示数组中以(i,j)为起点的最长递增路径的长度，初始将dp数组都赋为0，当我们用递归调用时，遇到某个位置(x, y), 如果dp[x][y]不为0的话，我们直接返回dp[x][y]即可，不需要重复计算。我们需要以数组中每个位置都为起点调用递归来做，比较找出最大值。在以一个位置为起点用DFS搜索时，对其四个相邻位置进行判断，如果相邻位置的值大于上一个位置，则对相邻位置继续调用递归，并更新一个最大值，搜素完成后返回即可，


int longestIncreasingPath(vector<vector<int>>& matrix) 
{
    if (matrix.empty() || matrix[0].empty()) 
    	return 0;

    int res = 1, m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));   // initialize 2D matrix 
 
    for (int i = 0; i < m; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            res = max(res, dfs(matrix, dp, i, j));
        }
    }
    return res;
}


int dfs(vector<vector<int> > &matrix, vector<vector<int> > &dp, int i, int j) 
{
    if (dp[i][j]) 
    	return dp[i][j];

    vector<vector<int> > dirs = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    int mx = 1, m = matrix.size(), n = matrix[0].size();

    for (auto a : dirs) 
    {
        int x = i + a[0], y = j + a[1];
        if (x < 0 || x >= m || y < 0 || y >= n || matrix[x][y] <= matrix[i][j]) 
        	continue;

        int len = 1 + dfs(matrix, dp, x, y);
        mx = max(mx, len);
    }
    dp[i][j] = mx;
    return mx;
}

===========================================  
Reconstruct Itinerary 重建行程单  
Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:

If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
All airports are represented by three capital letters (IATA code).
You may assume all tickets may form at least one valid itinerary.
 

Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].

Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.

这道题给我们一堆飞机票，让我们建立一个行程单，如果有多种方法，取其中字母顺序小的那种方法。这道题的本质是有向图的遍历问题，那么LeetCode关于有向图的题只有两道Course Schedule和Course Schedule II，而那两道是关于有向图的顶点的遍历的，而本题是关于有向图的边的遍历。每张机票都是有向图的一条边，我们需要找出一条经过所有边的路径，那么DFS不是我们的不二选择。先来看递归的结果，我们首先把图建立起来，通过邻接链表来建立。由于题目要求解法按字母顺序小的，那么我们考虑用multiset，可以自动排序。等我们图建立好了以后，从节点JFK开始遍历，只要当前节点映射的multiset里有节点，我们取出这个节点，将其在multiset里删掉，然后继续递归遍历这个节点，由于题目中限定了一定会有解，那么等图中所有的multiset中都没有节点的时候，我们把当前节点存入结果中，然后再一层层回溯回去，将当前节点都存入结果，那么最后我们结果中存的顺序和我们需要的相反的，我们最后再翻转一下即可，


vector<string> findItinerary(vector<pair<string, string> > tickets) 
{
    vector<string> res;
    unordered_map<string, multiset<string> > m;

    for (auto a : tickets) 
    {
        m[a.first].insert(a.second);  // graph initialization
    }

    dfs(m, "JFK", res);
    return vector<string> (res.rbegin(), res.rend());
}

void dfs(unordered_map<string, multiset<string> > &m, string s, vector<string> &res) 
{
    while (m[s].size()) 
    {
        string t = *m[s].begin();
        m[s].erase(m[s].begin());
        dfs(m, t, res);
    }

    res.push_back(s);
}


===================================================
Decode String 
Given an encoded string, return its decoded string. 
e.g. 
s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".


string decodeString(string s) 
{
    int i = 0;
    return decode(s, i);
}

string decode(string s, int& i) 
{
    string res = "";
    int n = s.size();
    while (i < n && s[i] != ']') 
    {
        if (s[i] < '0' || s[i] > '9') 
        {
            res += s[i++];
        } 
        else 
        {
            int cnt = 0;  // cnt counts the number of letters to appear 
            while (i < n && s[i] >= '0' && s[i] <= '9') 
            {
                cnt = cnt * 10 + s[i++] - '0';
            }
            ++i;  // 在这跳过[ 
            string t = decode(s, i);  // dfs here 
            ++i;  // 跳过]

            while (cnt-- > 0)   // output cnt times of letters 
            {
                res += t;
            }
        }
    }
    return res;
}

================================================   
Pacific Atlantic Water Flow 

Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.
Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.
Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean

 Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic


这道题给了我们一个二维数组，说是数组的左边和上边是太平洋，右边和下边是大西洋，假设水能从高处向低处流，问我们所有能流向两大洋的点的集合。刚开始我们没有理解题意，以为加括号的点是一条路径，连通两大洋的，但是看来看去感觉也不太对，后来终于明白了，是每一个点单独都路径来通向两大洋。那么就是典型的搜索问题，那么我最开始想的是对于每个点来搜索是否能到达边缘，只不过搜索的目标点不在是一个单点，而是所有的边缘点，找这种思路写出的代码无法通过OJ大数据集，那么我们就要想办法来优化我们的代码，优化的方法跟之前那道Surrounded Regions很类似，都是换一个方向考虑问题，既然从每个点像中间扩散会TLE，那么我们从边缘当作起点开始遍历搜索，然后标记能到达的点位true，分别标记出pacific和atlantic能到达的点，那么最终能返回的点就是二者均为true的点。我们可以先用DFS来遍历二维数组



vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) 
{
    if (matrix.empty() || matrix[0].empty()) 
    	return {};

    vector<pair<int, int>> res;
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));

    for (int i = 0; i < m; ++i) 
    {
        dfs(matrix, pacific, INT_MIN, i, 0);
        dfs(matrix, atlantic, INT_MIN, i, n - 1);
    }

    for (int i = 0; i < n; ++i) 
    {
        dfs(matrix, pacific, INT_MIN, 0, i);
        dfs(matrix, atlantic, INT_MIN, m - 1, i);
    }

    for (int i = 0; i < m; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            if (pacific[i][j] && atlantic[i][j]) 
            {
                res.push_back({i, j});
            }
        }
    }
    return res;
}


void dfs(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int pre, int i, int j) 
{
    int m = matrix.size(), n = matrix[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || matrix[i][j] < pre) 
    	return;

    visited[i][j] = true;
    dfs(matrix, visited, matrix[i][j], i + 1, j);
    dfs(matrix, visited, matrix[i][j], i - 1, j);
    dfs(matrix, visited, matrix[i][j], i, j + 1);
    dfs(matrix, visited, matrix[i][j], i, j - 1);
}


============================================================= 
Ternary Expression Parser 三元表达式解析器  

Given a string representing arbitrarily nested ternary expressions, calculate the result of the expression. You can always assume that the given expression is valid and only consists of digits 0-9, ?, :, T and F (T and Frepresent True and False respectively). 

Example 1:
Input: "T?2:3"
Output: "2"
Explanation: If true, then result is 2; otherwise result is 3.
 

Example 2:
Input: "F?1:T?4:5"
Output: "4"

如果有多个三元表达式嵌套的情况出现，那么我们的做法是从右边开始找到第一个问号，然后先处理这个三元表达式，然后再一步一步向左推，这也符合程序是从右向左执行的特点。那么我最先想到的方法是用用一个stack来记录所有问号的位置，然后根据此问号的位置，取出当前的三元表达式，调用一个eval函数来分析得到结果，能这样做的原因是题目中限定了三元表达式每一部分只有一个字符，而且需要分析的三元表达式是合法的，然后我们把分析后的结果和前后两段拼接成一个新的字符串，继续处理之前一个问号，这样当所有问号处理完成后，所剩的一个字符就是答案 


string parseTernary(string expression) 
{
    string res = expression;
    stack<int> s;
    for (int i = 0; i < expression.size(); ++i) 
    {
        if (expression[i] == '?') s.push(i);
    }
    while (!s.empty()) 
    {
        int t = s.top(); 
        s.pop();
        res = res.substr(0, t - 1) + eval(res.substr(t - 1, 5)) + res.substr(t + 4);
    }
    return res;
}

string eval(string str) 
{
    if (str.size() != 5) 
    	return "";

    return str[0] == 'T' ? str.substr(2, 1) : str.substr(4);
}

==========================================   
Target Sum 目标和

You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S. 

Input: nums is [1, 1, 1, 1, 1], S is 3. 
Output: 5
Explanation: 

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3


solution 1: 

int findTargetSumWays(vector<int>& nums, int S) 
{
    int res = 0;
    helper(nums, S, 0, res);
    return res;
}

void helper(vector<int>& nums, int S, int start, int& res) 
{
    if (start >= nums.size()) 
    {
        if (S == 0) 
        	++res;
        return;
    }

    helper(nums, S - nums[start], start + 1, res);
    helper(nums, S + nums[start], start + 1, res);
}

------------------------------------------------- 
solution 2: 递归方法进行优化，使用dp数组来记录中间值，这样可以避免重复运算 

int findTargetSumWays(vector<int>& nums, int S) 
{
    vector<unordered_map<int, int>> dp(nums.size());
    return helper(nums, S, 0, dp);
}

int helper(vector<int>& nums, int sum, int start, vector<unordered_map<int, int>>& dp) 
{
    if (start == nums.size()) 
    	return sum == 0;

    if (dp[start].count(sum)) 
    	return dp[start][sum];

    int cnt1 = helper(nums, sum - nums[start], start + 1, dp);
    int cnt2 = helper(nums, sum + nums[start], start + 1, dp);

    return dp[start][sum] = cnt1 + cnt2;
}

====================================================  
Matchsticks to Square 火柴棍组成正方形 

Input: [1,1,2,2,2]
Output: true

Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.

Input: [3,3,3,3,4]
Output: false

Explanation: You cannot find a way to form a square with all the matchsticks.

这道题让我们用数组中的数字来摆出一个正方形。跟之前有道题Partition Equal Subset Sum有点像，那道题问我们能不能将一个数组分成和相等的两个子数组，而这道题实际上是让我们将一个数组分成四个和相等的子数组。我一开始尝试着用那题的解法来做，首先来判断数组之和是否是4的倍数，然后还是找能否分成和相等的两个子数组，但是在遍历的时候加上判断如果数组中某一个数字大于一条边的长度时返回false。最后我们同时检查dp数组中一条边长度位置上的值跟两倍多一条边长度位置上的值是否为true，这种方法不幸TLE了。所以只能上论坛求助各路大神了，发现了可以用优化过的递归来解，递归的方法基本上等于brute force，但是C++版本的直接递归没法通过OJ，而是要先给数组从大到小的顺序排序，这样大的数字先加，如果超过target了，就直接跳过了后面的再次调用递归的操作，效率会提高不少，所以会通过OJ。下面来看代码，我们建立一个长度为4的数组sums来保存每个边的长度和，我们希望每条边都等于target，数组总和的四分之一。然后我们遍历sums中的每条边，我们判断如果加上数组中的当前数字大于target，那么我们跳过，如果没有，我们就加上这个数字，然后对数组中下一个位置调用递归，如果返回为真，我们返回true，否则我们再从sums中对应位置将这个数字减去继续循环

bool makesquare(vector<int>& nums) 
{
    if (nums.empty() || nums.size() < 4) 
    	return false;

    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 4 != 0) return false;
    vector<int> sums(4, 0);
    sort(nums.rbegin(), nums.rend());
    return helper(nums, sums, 0, sum / 4);
}

bool helper(vector<int>& nums, vector<int>& sums, int pos, int target) 
{
    if (pos >= nums.size()) 
    {
        return sums[0] == target && sums[1] == target && sums[2] == target;
    }

    for (int i = 0; i < 4; ++i) 
    {
        if (sums[i] + nums[pos] > target) 
        	continue;

        sums[i] += nums[pos];
        if (helper(nums, sums, pos + 1, target)) 
        	return true;

        sums[i] -= nums[pos];
    }
    return false;
}


===========================================  
Regular Expression Matching 正则表达式匹配  


Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true



这道求正则表达式匹配的题和那道 Wildcard Matching 通配符匹配的题很类似，不同点在于*的意义不同，在之前那道题中，*表示可以代替任意个数的字符，而这道题中的*表示之前那个字符可以有0个，1个或是多个，就是说，字符串a*b，可以表示b或是aaab，即a的个数任意，这道题的难度要相对之前那一道大一些，分的情况的要复杂一些，需要用递归Recursion来解，大概思路如下：

- 若p为空，若s也为空，返回true，反之返回false
- 若p的长度为1，若s长度也为1，且相同或是p为'.'则返回true，反之返回false
- 若p的第二个字符不为*，若此时s为空返回false，否则判断首字符是否匹配，且从各自的第二个字符开始调用递归函数匹配
- 若p的第二个字符为*，若s不为空且字符匹配，调用递归函数匹配s和去掉前两个字符的p，若匹配返回true，否则s去掉首字母
- 返回调用递归函数匹配s和去掉前两个字符的p的结果


bool isMatch(string s, string p) 
{
    if (p.empty()) 
    	return s.empty();

    if (p.size() == 1) 
    {
        return (s.size() == 1 && (s[0] == p[0] || p[0] == '.'));
    }

    if (p[1] != '*') 
    {
        if (s.empty()) 
        	return false;

        return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
    }

    while (!s.empty() && (s[0] == p[0] || p[0] == '.')) 
    {
        if (isMatch(s, p.substr(2))) 
        	return true;

        s = s.substr(1);
    }
    return isMatch(s, p.substr(2));
}


=========================================   
Generate Parentheses 生成括号

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses. For example, given n = 3, a solution set is:

"((()))", "(()())", "(())()", "()(())", "()()()"

在LeetCode中有关括号的题共有三道，除了这一道的另外两道是 Valid Parentheses 验证括号和 Longest Valid Parentheses 最长有效括号，这道题给定一个数字n，让生成共有n个括号的所有正确的形式，对于这种列出所有结果的题首先还是考虑用递归Recursion来解，由于字符串只有左括号和右括号两种字符，而且最终结果必定是左括号3个，右括号3个，所以我们定义两个变量left和right分别表示剩余左右括号的个数，如果在某次递归时，左括号的个数大于右括号的个数，说明此时生成的字符串中右括号的个数大于左括号的个数，即会出现')('这样的非法串，所以这种情况直接返回，不继续处理。如果left和right都为0，则说明此时生成的字符串已有3个左括号和3个右括号，且字符串合法，则存入结果中后返回。如果以上两种情况都不满足，若此时left大于0，则调用递归函数，注意参数的更新，若right大于0，则调用递归函数，同样要更新参数。

solution 1: 

vector<string> generateParenthesis(int n) 
{
    vector<string> res;
    generateParenthesisDFS(n, n, "", res);
    return res;
}

void generateParenthesisDFS(int left, int right, string out, vector<string> &res) 
{
    if (left > right) 
    	return;

    if (left == 0 && right == 0) 
    	res.push_back(out);
    else 
    {
        if (left > 0) 
        	generateParenthesisDFS(left - 1, right, out + '(', res);

        if (right > 0) 
        	generateParenthesisDFS(left, right - 1, out + ')', res);
    }
}


solution 2: 

vector<string> generateParenthesis(int n) 
{
    // Write your code here
    vector<string> res;
    string out;
    dfs(n, 0, 0, out, res);
    return res;
}


void dfs(int n, int left, int right, string &out, vector<string> &res) 
{
    if (left < n) 
    { //Keep 塞左括号
        out.push_back('(');
        dfs(n, left + 1, right, out, res);
        out.pop_back();
    }

    if (right < left) 
    { //避免出现右括号多余左括号的情况
        out.push_back(')');
        dfs(n, left, right + 1, out, res);
        out.pop_back();
    }

    if (out.size() == n * 2)
        res.push_back(out);
}

===========================================  
Gray Code 格雷码 

The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2


比如下面这种方法用到了一个set来保存已经产生的结果，我们从0开始，遍历其二进制每一位，对其取反，然后看其是否在set中出现过，如果没有，我们将其加入set和结果res中，然后再对这个数的每一位进行遍历，以此类推就可以找出所有的格雷码了


vector<int> grayCode(int n) 
{
    vector<int> res;
    unordered_set<int> s;
    helper(n, s, 0, res);
    return res;
}

void helper(int n, unordered_set<int>& s, int out, vector<int>& res) 
{
    if (!s.count(out)) 
    {
        s.insert(out);
        res.push_back(out);
    }

    for (int i = 0; i < n; ++i) 
    {
        int t = out;

        if ((t & (1 << i)) == 0)  // 1 << 0 == 1; 1 << 1 == 2; 1 << 2 == 4; ... 
        	t |= (1 << i);  // t = t | (1 << i) 
        else 
        	t &= ~(1 << i);  // 若t全为1则到这行

        if (s.count(t)) 
        	continue;

        helper(n, s, t, res);
        break;
    }
}

=======================================  





bool exist(vector<vector<char> > &board, string word) 
{
    if (word.empty()) 
        return true;

    if (board.empty() || board[0].empty()) 
        return false;

    vector<vector<bool> > visited(board.size(), vector<bool>(board[0].size(), false));

    for (int i = 0; i < board.size(); ++i) 
    {
        for (int j = 0; j < board[i].size(); ++j) 
        {
            if (search(board, word, 0, i, j, visited)) 
                return true;
        }
    }
    return false;
}


bool search(vector<vector<char> > &board, string word, int idx, int i, int j, vector<vector<bool> > &visited) 
{
    if (idx == word.size()) 
        return true;
    if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || visited[i][j] || board[i][j] != word[idx]) 
        return false;

    visited[i][j] = true;

    bool res = search(board, word, idx + 1, i - 1, j, visited) 
             || search(board, word, idx + 1, i + 1, j, visited)
             || search(board, word, idx + 1, i, j - 1, visited)
             || search(board, word, idx + 1, i, j + 1, visited);

    visited[i][j] = false;  // 为什么要这一行  

    return res;
}


=================================================    
Word Search II 

Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].



struct TrieNode 
{
    TrieNode *child[26];
    string str;

    TrieNode() : str("") 
    {
        for (auto &a : child) 
            a = NULL;
    }
};

struct Trie 
{
    TrieNode *root;
    Trie() : root(new TrieNode()) {}

    void insert(string s) 
    {
        TrieNode *p = root;
        for (auto &a : s) 
        {
            int i = a - 'a';
            if (!p->child[i]) 
                p->child[i] = new TrieNode();

            p = p->child[i];
        }
        p->str = s;
    }
};


vector<string> findWords(vector<vector<char> >& board, vector<string>& words) 
{
    vector<string> res;
    if (words.empty() || board.empty() || board[0].empty()) 
        return res;

    vector<vector<bool> > visit(board.size(), vector<bool>(board[0].size(), false));
    Trie T;

    for (auto &a : words) 
        T.insert(a);

    for (int i = 0; i < board.size(); ++i) 
    {
        for (int j = 0; j < board[i].size(); ++j) 
        {
            if (T.root->child[board[i][j] - 'a']) 
            {
                search(board, T.root->child[board[i][j] - 'a'], i, j, visit, res);
            }
        }
    }
    return res;
}
void search(vector<vector<char> > &board, TrieNode *p, int i, int j, vector<vector<bool> > &visit, vector<string> &res) 
{ 
    if (!p->str.empty()) 
    {
        res.push_back(p->str);
        p->str.clear();
    }

    int d[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    visit[i][j] = true;

    for (auto &a : d) 
    {
        int nx = a[0] + i, ny = a[1] + j;
        if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && !visit[nx][ny] && p->child[board[nx][ny] - 'a']) 
        {
            search(board, p->child[board[nx][ny] - 'a'], nx, ny, visit, res);
        }
    }
    visit[i][j] = false;
}



=============================================        
N-Queens

print all solutions of N queens (another problem: print 1 solution of N queens)

Given an integer n, return all distinct solutions to the n-queens puzzle.
Each solution contains a distinct board configuration of the n-queens placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

1) Start in the leftmost column
2) If all queens are placed
    return true
3) Try all rows in the current column.  Do following
   for every tried row.
    a) If the queen can be placed safely in this row
       then mark this [row, column] as part of the 
       solution and recursively check if placing  
       queen here leads to a solution.
    b) If placing queen in [row, column] leads to a
       solution then return true.
    c) If placing queen doesnot lead to a solution 
       then unmark this [row, column] (Backtrack) 
       and go to step (a) to try other rows.
3) If all rows have been tried and nothing worked, 
   return false to trigger backtracking.


时间复杂度高了, 需要优化 
bool isSafe(vector<string> board, int row, int col)
{
    int i, j;
    int N = board.size();
    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if (board[row][i] == 'Q')
            return false;

    for (i=row, j=col; i>=0 && j>=0; i--, j--)
        if (board[i][j] == 'Q')
            return false;

    for (i=row, j=col; j>=0 && i<N; i++, j--)
        if (board[i][j] == 'Q')
            return false;

    return true;
}


void solveNQUtil(vector<string> board, int col, vector<vector<string>>& ret)
{
    int N = board.size();

    if (col == N )
    {
        ret.push_back(board); 
    }

    for (int i = 0; i < N; i++)
    {

        if ( isSafe(board, i, col) )
        {
            board[i][col] = 'Q';

            solveNQUtil(board, col + 1, ret) ;

            board[i][col] = '.'; // BACKTRACK
        }
    }

}


vector<vector<string>> solveNQueens(int n) 
{

    vector<string> board(n, string(n, '.'));  // initialize
    vector<vector<string>> ret;  // initialize 

    solveNQUtil(board, 0, ret); 

    return ret; 
}


==============================================  
         
N-Queens II 

Follow up for N-Queens problem.
Now, instead outputting board configurations, return the total number of distinct solutions.

----- print one solution 

bool isSafe(vector<string> board, int row, int col)
{
    int i, j;
    int N = board.size();
    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if (board[row][i] == 'Q')
            return false;

    for (i=row, j=col; i>=0 && j>=0; i--, j--)
        if (board[i][j] == 'Q')
            return false;

    for (i=row, j=col; j>=0 && i<N; i++, j--)
        if (board[i][j] == 'Q')
            return false;

    return true;
}


void solveNQUtil(vector<string> board, int col, int& total)
{
int N = board.size();

if (col == N )
{
    // ret.push_back(board);
    total++; 
}

for (int i = 0; i < N; i++)
{

    if ( isSafe(board, i, col) )
    {
        board[i][col] = 'Q';

        solveNQUtil(board, col + 1, total) ;

        board[i][col] = '.'; // BACKTRACK
    }
}

}


int totalNQueens(int n) 
{

vector<string> board(n, string(n, '.'));  // initialize
// vector<vector<string>> ret;  // initialize 
int total = 0;  // 不初始化则total为随机值
solveNQUtil(board, 0, total); 

return total; 
}


=====================================================    
Combination Sum II 组合之和之二

Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:

All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
 

For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
A solution set is: 
[1, 7] 
[1, 2, 5] 
[2, 6] 
[1, 1, 6] 

 

这道题跟之前那道 Combination Sum 组合之和 本质没有区别，只需要改动一点点即可，之前那道题给定数组中的数字可以重复使用，而这道题不能重复使用，只需要在之前的基础上修改两个地方即可，首先在递归的for循环里加上if (i > start && num[i] == num[i - 1]) continue; 这样可以防止res中出现重复项，然后就在递归调用combinationSum2DFS里面的参数换成i+1，这样就不会重复使用数组中的数字了


vector<vector<int> > combinationSum2(vector<int> &num, int target) 
{
    vector<vector<int> > res;
    vector<int> out;
    sort(num.begin(), num.end());

    combinationSum2DFS(num, target, 0, out, res);

    return res;
}

void combinationSum2DFS(vector<int> &num, int target, int start, vector<int> &out, vector<vector<int> > &res) 
{
    if (target < 0) 
        return;

    else if (target == 0) 
        res.push_back(out);
    else 
    {
        for (int i = start; i < num.size(); ++i) 
        {
            if (i > start && num[i] == num[i - 1]) 
                continue;   // 这一行是防答案有重复 !!!!!!!!!!!!! 理解

            out.push_back(num[i]);

            combinationSum2DFS(num, target - num[i], i + 1, out, res);
            out.pop_back();
        }
    }
}

=========================================  









