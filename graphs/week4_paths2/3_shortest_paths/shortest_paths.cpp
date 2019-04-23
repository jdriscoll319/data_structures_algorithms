#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

void bfs_ifinite(vector<vector<int> > &adj, queue<int> &explore, vector<int> &shortest) {
  while (!explore.empty())
  {
    int source = explore.front();
    explore.pop();

    for (auto vert : adj[source])
    {
      if (shortest[vert] == 1)
      {
        explore.push(vert);
        shortest[vert] = 0;
      }
    }
  }
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  //write your code here
  queue<int> inf_q;
  queue<int> explore;
  reachable[s] = 1;
  distance[s] = 0;

  for (size_t i = 0; i < adj.size(); ++i)
  {
    vector<int> explored(adj.size(), 0);
    explore.push(s);

    while (!explore.empty())
    {
      int v = explore.front();
      explore.pop();

      for (size_t edge = 0; edge < adj[v].size(); ++edge)
      {
        if (!explored[adj[v][edge]])
        {
          explored[adj[v][edge]] = 1;
          explore.push(adj[v][edge]);
        }

        reachable[adj[v][edge]] = 1;
        long long new_dist = distance[v] + cost[v][edge];

        if (new_dist < distance[adj[v][edge]])
        {
          if (i == adj.size() - 1)
            inf_q.push(adj[v][edge]);

          distance[adj[v][edge]] = new_dist;
        }
      }
    }
  }

  bfs_ifinite(adj, inf_q, shortest);
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
