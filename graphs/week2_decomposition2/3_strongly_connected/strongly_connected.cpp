#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(const vector<vector<int> > &adj, vector<bool> &visited, const int x)
{
  visited[x] = 1;
  for(const auto v : adj[x])
  {
    if (!visited[v])
      explore(adj, visited, v);
  }
}

void explore(const vector<vector<int> > &adj, vector<bool> &visited, vector<int> &order, const int x)
{
  visited[x] = 1;
  for(const auto v : adj[x])
  {
    if (!visited[v])
    {
      explore(adj, visited, order, v);
      order.push_back(v);
    }
  }
}

vector<int> dfs(vector<vector<int>> &adj)
{
  vector<bool> visited(adj.size(), 0);
  vector<int> order;
  for (int vert = 0; vert < adj.size(); ++vert)
  {
    if (!visited[vert])
    {
      explore(adj, visited, order, vert);
      order.push_back(vert);
    }
  }

  std::reverse(order.begin(), order.end());

  return order;
}
void reverse_graph(const vector<vector<int>> &adj, vector<vector<int>> &reverse)
{
  for (size_t i = 0; i < adj.size(); ++i)
  {
    for (const auto node : adj[i])
      reverse[node].push_back(i);
  }
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int result = 0;
  vector<vector<int>> r_graph(adj.size(), vector<int>());
  reverse_graph(adj, r_graph);

  vector<int> reverse_post = dfs(r_graph);

  vector<bool> visited(adj.size(), 0);
  for (const auto node : reverse_post)
  {
    if (!visited[node])
    {
      explore(adj, visited, node);
      ++result;
    }
  }

  return result;
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
  std::cout << number_of_strongly_connected_components(adj) << "\n";
}
