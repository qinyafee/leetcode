// method1 递归/深搜
// 时间复杂度：O(N^2),空间复杂度：O(N^2)
class Solution {
 public:
  vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res;
    string path;
    dfs(root, path, res);
    return res;
  }
  void dfs(TreeNode* root, string path, vector<string>& paths) {  // path不能引用
    if (root == nullptr) return;
    path += to_string(root->val);
    if (root->left == nullptr && root->right == nullptr) {  // 当前节点是叶子节点
      paths.push_back(path);
      return;
    } else {
      path.append("->");  // 当前节点不是叶子节点，继续递归遍历
      dfs(root->left, path, paths);
      dfs(root->right, path, paths);
    }
  }
};

// method2 宽搜
// https://leetcode.cn/problems/binary-tree-paths/solution/er-cha-shu-de-suo-you-lu-jing-by-leetcode-solution/
class Solution {
 public:
  vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> paths;
    if (root == nullptr) {
      return paths;
    }
    queue<TreeNode*> node_queue;
    queue<string> path_queue;

    node_queue.push(root);
    path_queue.push(to_string(root->val));

    while (!node_queue.empty()) {
      TreeNode* node = node_queue.front();
      string path = path_queue.front();
      node_queue.pop();
      path_queue.pop();

      if (node->left == nullptr && node->right == nullptr) {
        paths.push_back(path);
      } else {
        if (node->left != nullptr) {
          node_queue.push(node->left);
          path_queue.push(path + "->" + to_string(node->left->val));
        }

        if (node->right != nullptr) {
          node_queue.push(node->right);
          path_queue.push(path + "->" + to_string(node->right->val));
        }
      }
    }
    return paths;
  }
};

// Source : https://leetcode.com/problems/binary-tree-paths/
// Author : Calinescu Valentin, Hao Chen
// Date   : 2015-10-23

/***************************************************************************************
 *
 * Given a binary tree, return all root-to-leaf paths.
 *
 * For example, given the following binary tree:
 *
 *    1
 *  /   \
 * 2     3
 *  \
 *   5
 *
 * All root-to-leaf paths are:
 * ["1->2->5", "1->3"]
 *
 * Credits:
 * Special thanks to @jianchao.li.fighter for adding this problem and creating all test
 * cases.
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
class Solution {
 public:
  vector<string> TreePaths;
  void DFS(TreeNode* node, string answer) {
    answer += "->" + to_string(node->val);
    if (node->left == NULL && node->right == NULL)
      TreePaths.push_back(answer);
    else {
      if (node->left != NULL) DFS(node->left, answer);
      if (node->right != NULL) DFS(node->right, answer);
    }
  }
  vector<string> binaryTreePaths(TreeNode* root) {
    if (root != NULL) {
      DFS(root, "");
      for (int i = 0; i < TreePaths.size(); i++)
        TreePaths[i].erase(TreePaths[i].begin(), TreePaths[i].begin() + 2);
    }
    return TreePaths;
  }
};

// Another more clear DFS implementation

class Solution {
 public:
  void binaryTreePathsHelper(TreeNode* root, vector<int> solution, vector<string>& result) {
    if (!root) return;

    solution.push_back(root->val);

    // meet the leaf node, shape a path into the result
    if (root->left == NULL && root->right == NULL) {
      if (solution.size() > 0) {
        stringstream ss;
        for (int i = 0; i < solution.size(); i++) {
          ss << solution[i] << (i < solution.size() - 1 ? "->" : "");
        }
        result.push_back(ss.str());
      }
      return;
    }

    binaryTreePathsHelper(root->left, solution, result);
    binaryTreePathsHelper(root->right, solution, result);
  }
  vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> result;
    vector<int> solution;
    binaryTreePathsHelper(root, solution, result);
    return result;
  }
};
