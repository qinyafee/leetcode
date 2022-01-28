// Source : https://leetcode.com/problems/range-sum-query-mutable/
// Author : Hao Chen
// Date   : 2015-11-24

/*************************************************************************************** 
 *
 * Given an integer array nums, find the sum of the elements between indices i and j (i 
 * ≤ j), inclusive.
 * 
 * The update(i, val) function modifies nums by updating the element at index i to val.
 * 
 * Example:
 * 
 * Given nums = [1, 3, 5]
 * 
 * sumRange(0, 2) -> 9
 * update(1, 2)
 * sumRange(0, 2) -> 8
 * 
 * Note:
 * 
 * The array is only modifiable by the update function.
 * You may assume the number of calls to update and sumRange function is distributed 
 * evenly.
 *
 ***************************************************************************************/

//线段树
// https://leetcode-cn.com/problems/range-sum-query-mutable/solution/xian-duan-shu-zu-shou-hui-tu-xiang-yi-qing-er-chu-/
// 链接：https://leetcode-cn.com/problems/range-sum-query-mutable/solution/qu-yu-he-jian-suo-shu-zu-ke-xiu-gai-by-leetcode/

class NumArray {
private:
    vector<int> tree;
    int n;
public:
    //构建线段树
    //时间 O(n), 空间 O(n)
    NumArray(vector<int>& nums) {
        n = nums.size();
        tree.resize(2*n);
        //自下而上的方法来构建线段树
        for (int i = n, j = 0;  i < 2 * n; ++i,  ++j)
            tree[i] = nums[j];
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }

    //自下而上，更新线段树
    //时间 O(logn), 空间 O(1)
    void update(int pos, int val) {
        pos += n; //找到对应的叶子节点
        tree[pos] = val;
        while (pos > 0) {
            int left = pos;
            int right = pos;
            if (pos % 2 == 0) { //pos 是左节点
                right = pos + 1;
            } else { //pos 是右节点
                left = pos - 1;
            }
            // parent is updated after child is updated
            tree[pos / 2] = tree[left] + tree[right];
            pos /= 2;
        }
    }

    int sumRange(int l, int r) {
        // get leaf with value 'l'
        l += n;
        // get leaf with value 'r'
        r += n;
        int sum = 0;
        while (l <= r) {
            if ((l % 2) == 1) {//l是右节点，要加上这个节点，再向右移动
                sum += tree[l];
                ++l;
            }
            if ((r % 2) == 0) {//r是左节点，要加上这个节点，再向左移动
                sum += tree[r];
                --r;
            }
            l /= 2;
            r /= 2;
        }
        return sum;
    }

};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */

// The following idea is using `Binary Index Tree`
// There are two articles explaine this technique quite well:
// 1) http://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
// 2) http://cs.stackexchange.com/questions/10538/bit-what-is-the-intuition-behind-a-binary-indexed-tree-and-how-was-it-thought-a

class NumArray {
private:
    int _sz;
    vector<int> _nums;
    vector<int> _sums;    
public:
    NumArray(vector<int> &nums)  {
        _sz = nums.size();
        _nums.resize(_sz+1, 0);
        _sums.resize(_sz+1, 0);
        for(int i=0; i< _sz; i++) {
            update(i, nums[i]);          
        }
    }

    void update(int i, int val) {
        int oldv = _nums[i+1];
        for(int idx = i+1; idx <= _sz; idx += (idx & (-idx))  ) {
            _sums[idx] = _sums[idx] - oldv + val;
        }
        _nums[i+1] = val;
    }

    int sumRange(int i, int j) {
        return sumRange(j+1) - sumRange(i);
    }
    
    int sumRange(int i) {
        int ret = 0;
        for(int idx=i; idx>0; idx -= (idx & (-idx)) ) {
            ret += _sums[idx];
        }
        return ret;
    }
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);
