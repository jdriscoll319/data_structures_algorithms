#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(const vector<vector<int> > &adj, const int x, vector<bool> &visited)
{
  visited[x] = 1;
  for(const auto v : adj[x])
  {
    if (!visited[v])
      explore(adj, v, visited);
  }
}

int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  vector<bool> visited(adj.size(), 0);
  explore(adj, x, visited);

  return visited[y];
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1) << "\n";
}
