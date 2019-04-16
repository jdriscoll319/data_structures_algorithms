#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  //write your code here
  if (used[x])
    return;
  
  used[x] = 1;
  for (auto vert : adj[x])
  {
    if (!used[vert])
    {
      dfs(adj, used, order, vert);
      order.push_back(vert);
    }
  }
}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  //write your code here
  for (int vert = 0; vert < adj.size(); ++vert)
  {
    if (!used[vert])
    {
      dfs(adj, used, order, vert);
      order.push_back(vert);
    }
  }

  std::reverse(order.begin(), order.end());

  return order;
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
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
  std::cout << std::endl;
}
