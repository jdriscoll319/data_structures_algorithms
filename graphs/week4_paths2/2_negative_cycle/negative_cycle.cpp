#include <iostream>
#include <vector>
#include <limits>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here
  vector<int> dists(adj.size(), std::numeric_limits<int>::max() - 10000);
  dists[0] = 0;
  for (size_t i = 0; i < adj.size(); ++i)
  {
    for (size_t v = 0; v < adj.size(); ++v)
    {
      for (size_t edge = 0; edge < adj[v].size(); ++edge)
      {
        int new_dist = dists[v] + cost[v][edge];
        // std::cout << "On node: " << v << " checking node: " << adj[v][edge] << " cur dist is: " << dists[adj[v][edge]] << " new dist is: " << new_dist << "\n";
        if (new_dist < dists[adj[v][edge]])
        {
          if (i == adj.size() - 1) return 1;
          dists[adj[v][edge]] = new_dist;
        }
      }
    }
  }
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost) << "\n";
}
