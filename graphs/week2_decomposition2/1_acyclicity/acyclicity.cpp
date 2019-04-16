#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;
using std::pair;

void explore(vector<vector<int> > &adj,  unordered_set<int> &path, const int node, bool &acyclic)
{
  //need to also keep track of visited so we don't get stuck in a loop;
  //alternatively use "stack" to keep track of current path, if new node is on "stack" we have a cycle
  if (!acyclic)
    return;
  for (auto vertex : adj[node])
  {
    if(path.find(vertex) != path.end())
    {
      acyclic = false;
      return;
    }
    else
    {
      path.insert(vertex);
      explore(adj, path, vertex, acyclic);
      path.erase(vertex);
    }
  }
}

int acyclic(vector<vector<int> > &adj) {
  //write your code here
  bool acyclic = true;
  unordered_set<int> path;

  for (int i = 0; i < adj.size(); ++i)
  {
    path.insert(i);
    explore(adj, path, i, acyclic);
    if (!acyclic)
      return !acyclic;
    path.clear();
  }

  return !acyclic;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj) << "\n";
}
