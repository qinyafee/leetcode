// 133. clone graph

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
// my impl
// 1. dfs。时间复杂度：O(N)，空间复杂度：O(N)+ O(H)栈的高度。
class Solution {
 public:
  unordered_map<Node*, Node*> visited;  //<原始节点，copy的节点>, 记录已经clone的节点
  Node* cloneGraph(Node* node) {
    if (node == nullptr) return node;
    // 如果该节点已经被访问过了，则直接从哈希表中取出对应的克隆节点返回
    if (visited.find(node) != visited.end()) {
      return visited[node];
    }
    // 深copy
    Node* cloned_node = new Node(node->val);
    // 注意标记visited，否则死循环
    visited[node] = cloned_node;
    // 遍历该节点的邻居并更新cloned_node的邻居列表
    for (const auto& neighbor : node->neighbors) {
      cloned_node->neighbors.emplace_back(cloneGraph(neighbor));
    }
    return cloned_node;
  }
};

// 2. bfs。时间复杂度：O(N)，空间复杂度：O(N)。
class Solution {
 public:
  Node* cloneGraph(Node* node) {
    if (node == nullptr) return node;

    unordered_map<Node*, Node*> copied;  //<原始节点，copy的节点>, 记录已经clone的节点
    queue<Node*> que;
    // 根节点先入队
    que.push(node);
    Node* cloned_node = new Node(node->val);
    copied[node] = cloned_node;

    while (!que.empty()) {
      Node* curr = que.front();
      que.pop();
      // 遍历该节点的邻居并更新cloned_node的邻居列表
      for (const auto& neighbor : curr->neighbors) {
        if (copied.find(neighbor) == copied.end()) {
          Node* new_node = new Node(neighbor->val);
          copied[neighbor] = new_node;
          // 将邻居节点加入队列中
          que.push(neighbor);
        }
        // 将邻居节点加入队列中
        copied[curr]->neighbors.emplace_back(copied[neighbor]);
      }
    }
    return cloned_node;
  }
};

// Source : https://oj.leetcode.com/problems/clone-graph/
// Author : Hao Chen
// Date   : 2014-10-12

/**********************************************************************************
 *
 * Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.
 *
 * OJ's undirected graph serialization:
 *
 * Nodes are labeled uniquely.
 *
 * We use # as a separator for each node, and , as a separator for node label and each neighbor of
 *the node.
 *
 * As an example, consider the serialized graph {0,1,2#1,2#2,2}.
 *
 * The graph has a total of three nodes, and therefore contains three parts as separated by #.
 *
 * First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
 * Second node is labeled as 1. Connect node 1 to node 2.
 * Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
 *
 * Visually, the graph looks like the following:
 *
 *        1
 *       / \
 *      /   \
 *     0 --- 2
 *          / \
 *          \_/
 *
 *
 **********************************************************************************/

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
 public:
  UndirectedGraphNode* cloneGraph(UndirectedGraphNode* node) {
    if (node == NULL) return NULL;

    // create a map, key is source node, value is clone node.
    map<UndirectedGraphNode*, UndirectedGraphNode*> cloneMap;

    // using queue for breadth first search
    queue<UndirectedGraphNode*> q;
    q.push(node);

    // clone the root
    UndirectedGraphNode* cloneNode = new UndirectedGraphNode(node->label);
    cloneMap[node] = cloneNode;

    // breadth first search
    while (!q.empty()) {
      UndirectedGraphNode* n = q.front();
      q.pop();
      // for each neighbors
      for (int i = 0; i < n->neighbors.size(); i++) {
        UndirectedGraphNode* neighbor = n->neighbors[i];
        // not existed in cloneMap
        if (cloneMap.find(neighbor) == cloneMap.end()) {
          // clone a node
          UndirectedGraphNode* newNode = new UndirectedGraphNode(neighbor->label);
          cloneMap[n]->neighbors.push_back(newNode);
          cloneMap[neighbor] = newNode;

          // put the neighbors into the queue
          q.push(neighbor);
        } else {
          cloneMap[n]->neighbors.push_back(cloneMap[neighbor]);
        }
      }
    }

    return cloneNode;
  }
};
