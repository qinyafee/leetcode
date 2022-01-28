// Source : https://leetcode.com/problems/kth-largest-element-in-an-array/
// Author : Hao Chen
// Date   : 2015-06-11

/********************************************************************************** 
 * 
 * Find the kth largest element in an unsorted array. 
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * 
 * For example,
 * Given [3,2,1,5,6,4] and k = 2, return 5.
 * 
 * Note: 
 * You may assume k is always valid, 1 ≤ k ≤ array's length.
 * 
 * Credits:Special thanks to @mithmatt for adding this problem and creating all test cases.
 *               
 **********************************************************************************/

// my implm 1
// 堆排序，维护一个k大小的小根堆，将数组中的每个元素与堆顶元素进行比较
// 如果比堆顶元素大，则删除堆顶元素并添加该元素; 如果比堆顶元素小，则什么也不做。继续下一个元素。 
// 时间复杂度 O(nlogk)，空间复杂度 O(k) 。
class Solution2 {
public:
    //时间复杂度 O(nlogk) ， 空间复杂度 O(k) 。
    int findKthLargest(vector<int>& nums, int k) { 
        //默认是大根堆
        priority_queue<int,vector<int>,greater<int> >que;//这样就可以实现小根堆了
        for(int i = 0; i < k; ++i){
            que.push(nums[i]);
        }
        for(int i = k; i < nums.size(); ++i){
            if(nums[i] > que.top()){
                que.pop();
                que.push(nums[i]);
            }
        }
        return que.top();
    }
};
// my implm 2
// 利用快速排序中的partition思想，从数组中随机选择一个元素x，把数组划分为前后两部
// 分 sa 和 sb， sa 中的元素小于x， sb 中的元素大于或等于x。 这时有两种情况：
// i. sa 的元素个数小于 k ， 则递归求解 sb 中的第 k-|sa| 大的元素
// ii. sa 的元素个数大于或等于 k ， 则递归求解 sa 中的第 k 大的元素
// 时间复杂度 O(n) ， 空间复杂度 O(1)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        const int n = nums.size();
        int left = 0, right = n - 1;
        while (true) {
            int pos = partition(nums, left, right);
            if (pos == n - k){ 
                return nums[pos];
            }
            if (pos > n - k) {
                right = pos - 1;
            }else{
                left = pos + 1;  
            }  
        }
    }

    //qsort partition
    int partition (vector<int>& arr, int low, int high) 
    { 
        int pivot = arr[high]; // pivot 
        
        //所有小于pivot的index
        int i = (low - 1); // Index of smaller element 

        for (int j = low; j <= high - 1; ++j) 
        { 
            // If current element is smaller than the pivot 
            if (arr[j] < pivot) 
            { 
                ++i; // increment index of smaller element 
                swap(arr[i], arr[j]); 
            } 
        } 
        swap(arr[++i], arr[high]); 
        return i;
    } 
};


class Solution {
public:
    //STL using qsort to solve this problem
    int findKthLargest_buildin(vector<int>& nums, int k) {
        int n=nums.size();
        std::nth_element(nums.begin(),nums.end()-k,nums.end());
        return nums[n-k];
    }
    
    //qsort partition
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[left];
        int l = left + 1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot){
                swap(nums[l++], nums[r--]);
            }
            if (nums[l] >= pivot) l++;
            if (nums[r] <= pivot) r--;
        }
        swap(nums[left], nums[r]);
        return r;
    }
    
    int findKthLargest_qsort(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int pos = partition(nums, left, right);
            if (pos == k - 1){ 
                return nums[pos];
            }
            if (pos > k - 1) {
                right = pos - 1;
            }else{
                left = pos + 1;  
            }  
        }
    }
    
    
    int findKthLargest(vector<int>& nums, int k) {
        return findKthLargest_qsort(nums, k);
    }
};
