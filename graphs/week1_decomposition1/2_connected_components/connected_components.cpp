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

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  //write your code here
  vector<bool> visited(adj.size(), 0);
  for(size_t v = 0; v < adj.size(); ++v)
  {
    if (!visited[v])
    {
      ++res;
      explore(adj, v, visited);
    }
  }
  return res;
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
  std::cout << number_of_components(adj) << "\n";
}
