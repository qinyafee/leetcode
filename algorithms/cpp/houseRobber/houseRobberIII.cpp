
/** my impl
用f(o) 表示选择 o 节点的情况下，o 节点的子树上被选择的节点的最大权值和；
g(o) 表示不选择 o 节点的情况下，o 节点的子树上被选择的节点的最大权值和；l 和 r 代表 o 的左右孩子。

当 o 被选中时，o 的左右孩子都不能被选中，故 o 被选中情况下子树上被选中点的最大权值和为 l 和 r
不被选中的最大权值和相加， 即 f(o) = g(l)+g(r) + o->val。

当 o 不被选中时，o 的左右孩子可以被选中，也可以不被选中。对于 o 的某个具体的孩子 x(左或右)，它对 o
的贡献是 x 被选中和不被选中情况下权值和的较大值。 故 g(o) = max{f(l), g(l)} + max{f(r), g(r)}。

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/house-robber-iii/solution/da-jia-jie-she-iii-by-leetcode-solution/
*/

class Solution {
 public:
  unordered_map<TreeNode*, int> f;
  unordered_map<TreeNode*, int> g;

  void dfs(TreeNode* o) {//必须后根遍历，因为root节点值依赖left/right 的函数值。
    if (!o) {
      return;
    }
    dfs(o->left);
    dfs(o->right);
    f[o] = o->val + g[o->left] + g[o->right];
    g[o] = max(f[o->left], g[o->left]) + max(f[o->right], g[o->right]);
  }

  int rob(TreeNode* o) {
    dfs(o);
    return max(f[o], g[o]);
  }

  /*超时
  int rob(TreeNode* root) {
      return f(root);
  }
  int f(TreeNode* root){
      if(!root) return 0;
      return max(f(root->left)+f(root->right), //不抢root
                  g(root->left)+g(root->right)+root->val);//抢root
  }
  int g(TreeNode* root){
      if(!root) return 0;
      //if(!root->left && !root->right) return 0;
      return f(root->left) + f(root->right);
  }
  */
};

// clang-format off
// Source : https://leetcode.com/problems/house-robber-iii/
// Author : Calinescu Valentin, Hao Chen
// Date   : 2016-04-29

/*************************************************************************************** 
 *
 * The thief has found himself a new place for his thievery again. There is only one
 * entrance to this area, called the "root." Besides the root, each house has one and
 * only one parent house. After a tour, the smart thief realized that "all houses in
 * this place forms a binary tree". It will automatically contact the police if two 
 * directly-linked houses were broken into on the same night.
 * 
 * Determine the maximum amount of money the thief can rob tonight without alerting the
 * police.
 * 
 * Example 1:
 *     3
 *    / \
 *   2   3
 *    \   \ 
 *     3   1
 * Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
 * Example 2:
 *     3
 *    / \
 *   4   5
 *  / \   \ 
 * 1   3   1
 * Maximum amount of money the thief can rob = 4 + 5 = 9.
 * Credits:
 * Special thanks to @dietpepsi for adding this problem and creating all test cases.
 * 
 ***************************************************************************************/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
  /* 
 * Solution 1 - O(N log N)
 * =========
 *
 * We can use a recursive function that computes the solution for every node of the tree 
 * using the previous solutions calculated for the left and right subtrees. At every step
 * we have 2 options:
 *
 * 1) Take the value of the current node + the solution of the left and right subtrees of
 * each of the left and right children of the current node.
 * 2) Take the solution of the left and right subtrees of the current node, skipping over
 * its value.
 *
 * This way we can make sure that we do not pick 2 adjacent nodes.
 *
 * If we implemented this right away we would get TLE. Thus, we need to optimize the
 * algorithm. One key observation would be that we only need to compute the solution for
 * a certain node once. We can use memoization to calculate every value once and then
 * retrieve it when we get subsequent calls. As the header of the recursive function
 * doesn't allow additional parameters we can use a map to link every node(a pointer) to
 * its solution(an int). For every call the map lookup of an element and its insertion
 * take logarithmic time and there are a constant number of calls for each node. Thus, the
 * algorithm takes O(N log N) time to finish.
 * 
 */
class Solution {
public:
    map<TreeNode*, int> dict;
    int rob(TreeNode* root) {
        if(root == NULL)
            return 0;
        else if(dict.find(root) == dict.end())
        {
            int lwith = rob(root->left);
            int rwith = rob(root->right);
            int lwithout = 0, rwithout = 0;
            if(root->left != NULL)
                lwithout = rob(root->left->left) + rob(root->left->right);
            if(root->right != NULL)
                rwithout = rob(root->right->left) + rob(root->right->right);
            //cout << lwith << " " << rwith << " " << lwithout << " " << rwithout << '\n';
            dict[root] = max(root->val + lwithout + rwithout, lwith + rwith);
        }
        return dict[root];
    }
};


// Another implementation - Hao Chen

class Solution {
public:
    int max(int a, int b) {
        return a > b ? a: b;
    }
    int max(int a, int b, int c) {
        return max(a, max(b,c));
    }
    int max(int a, int b, int c, int d) {
        return max(a, max(b, max(c,d)));
    }

    void rob_or_not(TreeNode* root, int& max_robbed, int& max_not_robbed) {
        // NULL room return 0;
        if (root == NULL) {
            max_robbed = max_not_robbed = 0;
            return ;
        }

        // we have two options, rob current room or not.
        int max_left_robbed, max_left_not_robbed;
        int max_right_robbed, max_right_not_robbed;
        rob_or_not(root->left, max_left_robbed, max_left_not_robbed);
        rob_or_not(root->right, max_right_robbed, max_right_not_robbed);

        // If root is robbed, then both left and right must not be robbed.
        max_robbed = root->val + max_left_not_robbed + max_right_not_robbed;

        // If root is not robbed, then 4 combinations are possible:
		//     left is robbed or not and right is either robbed or not robbed,
        max_not_robbed = max(max_left_robbed + max_right_robbed,
                             max_left_robbed + max_right_not_robbed,
                             max_left_not_robbed + max_right_robbed,
                             max_left_not_robbed + max_right_not_robbed);

    }
    int rob(TreeNode* root) {
        int robbed, not_robbed;
        rob_or_not(root, robbed, not_robbed);
        return max(robbed, not_robbed);
    }
};
