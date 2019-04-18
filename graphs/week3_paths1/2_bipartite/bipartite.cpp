#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
  //write your code here
  //Idea: If we're exploring and find a visited node with the same depth, the graph is not bipartite
  queue<int> explore;

  //-1 unvisited
  vector<int> dist(adj.size(), -1);

  for (size_t src = 0; src < adj.size(); ++src)
  {
    if (dist[src] == -1)
    {
      explore.push(src);
      dist[src] = 0;
      while (!explore.empty())
      {
        int cur_node = explore.front();
        explore.pop();
        for (auto next : adj[cur_node])
        {
          if (dist[next] == -1)
          {
            explore.push(next);
            dist[next] = dist[cur_node] + 1;
          }
          else if (dist[next] == dist[cur_node])
            return 0;
        }
      }
    }
  }

  //0 if not, 1 if is
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj) << "\n";
}
