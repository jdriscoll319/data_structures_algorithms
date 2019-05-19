#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t(1);
  // write your code here
  int count = 0;
  for (auto & pattern : patterns)
  {
    int level = 0;
    for (auto & c : pattern)
    {
      // std::cout << c << '\n';
      if (t[level].find(c) != t[level].end())
        level = t[level].find(c)->second;
      else
      {
        t[level].insert(std::make_pair(c, ++count));
        level = count;
        t.resize(t.size() + 1);
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}