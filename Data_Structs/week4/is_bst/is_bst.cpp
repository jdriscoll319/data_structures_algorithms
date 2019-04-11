#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool in_order_traversal(const vector<Node>& tree, size_t node, std::vector<int> &vals, bool &valid)
{
  //left
  //print
  //right
  if (!valid)
    return false;

  if (tree[node].left != -1)
    in_order_traversal(tree, tree[node].left, vals, valid);
  
  vals.push_back(tree[node].key);
  if (vals.size() > 1 && vals.back() < *(vals.rbegin()+1))
    valid = false;

  if (tree[node].right != -1)
    in_order_traversal(tree, tree[node].right, vals, valid);
  // if (tree[node].key > prev_key)
  //   return false;

  return valid;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  if (tree.empty())
    return true;
  
  std::vector<int> vals;
  bool valid = true;

  return in_order_traversal(tree, 0, vals, valid);
  return true;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
