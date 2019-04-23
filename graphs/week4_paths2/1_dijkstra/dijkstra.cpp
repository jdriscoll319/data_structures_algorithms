#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::greater;

void remove_element(vector<pair<int, int>> &pq, int elem)
{
  for (auto it = pq.begin(); it != pq.end(); ++it)
  {
    if (it->second == elem)
    {
      pq.erase(it);
      std::make_heap(pq.begin(), pq.end(), greater<pair<int, int>>());
      return;
    }
  }
}
int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  //pair = dist, node 
  //comparison is lexicographical (compare first element first, only compare next element if necessary)
  //heap default compare is less<T> which is NOT what we want
  //priority queues in cpp don't let you search easily so just using a vector and heapifying it
  vector< pair<int, int>> pq;
  vector<int> dists(adj.size(), -1);
  dists[s] = 0;
  pq.push_back(std::make_pair(0, s));

  std::make_heap(pq.begin(), pq.end(), std::greater<pair<int, int>>());

  while (!pq.empty())
  {
    pair<int, int> node = pq.front();
    std::pop_heap(pq.begin(), pq.end(), greater<pair<int,int>>()); pq.pop_back();
    int dist = node.first;
    int vert = node.second;

    for (int i = 0; i <  adj[vert].size(); i++)
    {
      int v = adj[vert][i];
      int new_dist = dist + cost[vert][i];
      if (dists[v] == -1 || new_dist < dists[v])
      {
        dists[v] = new_dist;
        remove_element(pq, v);
        pq.push_back(std::make_pair(dists[v], v));
        std::push_heap(pq.begin(), pq.end(), greater<pair<int,int>>());
      } 
    }
  }
  return dists[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t) << "\n";
}
