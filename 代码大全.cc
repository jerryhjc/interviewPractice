http://www.geeksforgeeks.org/program-for-nth-fibonacci-number/  



linked list 等号左边的->next 表示指向的意思;  等号右边的->next 表示下一个node的意思;

0跟任何数异或都还是那个数
=======================
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
                if(ar[i] + arr[j] + arr[k] + arr[l] == target)
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
基于上题, matrix的每一行都计算maxHistRectangle,  http://www.geeksforgeeks.org/maximum-size-rectangle-binary-sub-matrix-1s/


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
    if(num.size() == 1)
        return 0; 

    int lowerBound = 0; 
    int upperBound = arr.size() - 1;
    int mid = 0; 

    while(lowerBound <= upperBound)
    {
        mid = lowerBound + (upperBound - lowerBound)/2;   //往下取整 

        if(mid == 0 || arr[mid] >= num[mid-1]) && (mid == n -1 || arr[mid] >= arr[mid+1])
            return mid;
        else if(arr[mid - 1] > arr[mid])  // 注
            upperBound = mid - 1;  // 注, 因为arr[-1] = INT_MIN
            // upperBound = mid;
        else if(arr[mid + 1] > arr[mid])
            lowerBound = mid + 1;  // 因为arr[n] = INT_MIN
    }
    return mid; 

}


===========================================
Missing number 
Array containing n distinct numbers from 0 ,1, 2..n. find the missing number 

int missingNum(vector<int>& num)
{
    int x = 0; 
    for(int i = 0; i <= num.size(); ++i)
        x = x^i; 
    for(int i = 0; i < num.size(); ++i)
        x = x^num[i];

    return x;  
}


n sorted number: 0..n, but 1 number is missing. Find out that number 
binary search 

int solution(vector<int>& arr)
{

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
bool hasPathSum(TreeNode* root, int sum) {
    if(root == NULL)
    {
        // if(sum == 0)
        //     return true;
        // else return false; 
        return false;
    }
    
    bool ans = 0; 
    
    int remain = sum - root->val;
    if( remain == 0 && node->left == NULL && node->right == NULL )
      return 1;
    
    return hasPathSum(root->left, remain) || hasPathSum(root->right, remain);


    /////// be low solution is false, I don't know why 
    // if(root->left)
    //     return hasPathSum(root->left, remain);
    
    // if(root->right)
    //     return hasPathSum(root->right, remain);

    // return false;

}

solution 2: 
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
combination 

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
                ret.push_back(curr);
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
            ret.push_back(curr);
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
            ret.push_back(curr);
            return; 
        }
        else if(target < 0)     // save time
            return;

        for(int i = level; i < candidates.size(); ++i)
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

















































