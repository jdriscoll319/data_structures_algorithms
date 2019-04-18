#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  //write your code here
  queue<int> explore;
  vector<int> dists(adj.size(), -1);
  explore.push(s);
  dists[s]=0;
  while (!explore.empty())
  {
    int source = explore.front();
    if (source == t)
      break;
    explore.pop();
    for (auto vert : adj[source])
    {
      if (dists[vert] == -1)
      {
        explore.push(vert);
        dists[vert] = dists[source]+1;
      }
    }
  }
  return dists[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t) << "\n";
}
