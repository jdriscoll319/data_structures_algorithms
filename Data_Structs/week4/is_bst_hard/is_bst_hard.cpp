#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>

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

bool in_order_traversal(const vector<Node>& tree, size_t node, std::vector<int> &vals, bool &valid, std::deque<int> &path)
{
  //path 0 = left
  //path 1 = right
  if (!valid)
    return false;

  if (tree[node].left != -1)
  {
    path.push_back(0);
    in_order_traversal(tree, tree[node].left, vals, valid, path);
  }
  
  if (!valid)
    return false;

  vals.push_back(tree[node].key);

  if (vals.size() > 1)
  {
    if (path.front() == 0)
      valid = (*(vals.rbegin()+1) < vals.back());
    else
      valid = (*(vals.rbegin()+1) <= vals.back());
    path.pop_front();
  }

  if (tree[node].right != -1)
  {
    path.push_front(1);
    in_order_traversal(tree, tree[node].right, vals, valid, path);
  }

  return valid;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // Implement correct algorithm here
  if (tree.empty())
    return true;
  
  std::vector<int> vals;
  std::deque<int> path;
  bool valid = true;

  return in_order_traversal(tree, 0, vals, valid, path);
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
