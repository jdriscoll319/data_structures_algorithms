#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

typedef map<string, int> edges;
typedef vector<edges> tree;

const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ$";

void build_suffix_trie(tree &t, const string &text) {
  // write your code here
  int idx = 0;
  size_t n = text.size();
  for (size_t i = 0; i < n; ++i)
  {
    string sfx = text.substr(i, n);
    int node = 0;
    for (auto & c : sfx)
    {
      // std::cout << c << '\n';
      if (t[node].find(string(1,c)) != t[node].end())
        node = t[node].find(string(1,c))->second;
      else
      {
        t[node].insert(std::make_pair(string(1,c), ++idx));
        node = idx;
        t.resize(t.size() + 1);
      }
    }
    // t[node].insert(std::make_pair(std::to_string(i), ++idx));
    t[node].insert(std::make_pair("", i));
  }
}

//I believe I'm correctly traversign the tree
//Now just need to add the actual compression
void compress_suffix_trie(tree &t, int node, string new_edge, int prev_node)
{
  size_t num_branches = t[node].size();
  edges branch = t[node];
  int start = node;
  vector<int> delete_nodes;

  // while (num_branches == 1 && alphabet.find(branch.begin()->first) != string::npos)
  while (num_branches == 1 && !branch.begin()->first.empty())
  {
    new_edge += branch.begin()->first;
    node = branch.begin()->second;
    branch = t[node];
    num_branches= branch.size();
    delete_nodes.push_back(node);
  }
  
  if (!delete_nodes.empty())
    delete_nodes.pop_back();
  for (auto  delete_node : delete_nodes)
    t[delete_node].clear();

  if (new_edge.size() > 1)
  {
    // std::cout << prev_node << "->" << start << ": " << new_edge << '\n';
    t[prev_node].erase( t[prev_node].find( new_edge.substr(0,1) ) ) ;
    t[prev_node].insert(std::make_pair(new_edge, start));
    t[start] = t[node];
    t[node].clear();
  }

  // if (alphabet.find(branch.begin()->first) == string::npos)
  if (branch.begin()->first.empty())
    return;

  for (auto edge : t[start])
    compress_suffix_trie(t, edge.second, edge.first, node);
}

void fake_compress(tree &t, int node, string new_edge, vector<string> &result)
{
  size_t num_branches = t[node].size();
  edges branch = t[node];
  // int start = node;

  // while (num_branches == 1 && alphabet.find(branch.begin()->first) != string::npos)
  while (num_branches == 1 && !branch.begin()->first.empty())
  {
    new_edge += branch.begin()->first;
    node = branch.begin()->second;
    branch = t[node];
    num_branches= branch.size();
  }
  
  if (new_edge.size() > 0)
    result.push_back(new_edge);

  // if (alphabet.find(branch.begin()->first) == string::npos)
  if (branch.begin()->first.empty())
    return;

  for (auto edge : t[node])
    fake_compress(t, edge.second, edge.first, result);
}
// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  // Implement this function yourself
  tree suffix_trie(1);
  build_suffix_trie(suffix_trie, text);
  // compress_suffix_trie(suffix_trie, 0, "", 0);
  fake_compress(suffix_trie, 0, "", result);

  // std::cout << "\n\n";
  // for (size_t i = 0; i < suffix_trie.size(); ++i) {
  //   for (const auto & j : suffix_trie[i]) {
  //     if (!j.first.empty())
  //       result.push_back(j.first);
  //   }
  // }

  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
