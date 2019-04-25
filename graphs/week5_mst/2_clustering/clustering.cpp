#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <map>
#include <set>

using std::vector;
using std::pair;
using std::multimap;
using std::set;

class disjoint_set {
  public:
  disjoint_set(size_t size)
  {
    for (size_t i = 0; i < size; ++i)
      parent.push_back(i);
    
    roots.insert(parent.begin(), parent.end());
    rank.resize(size, 0);
  }

  int find(int x)
  {
    vector<int> path = {x};

    while (parent[path.back()] != path.back())
      path.push_back(parent[path.back()]);
    
    for (auto node : path)
    {
      parent[node] = path.back();
      rank[node] = 0;
    }
    rank[path.back()] = 1;
    return path.back();
  }

  void merge(int x, int y)
  {
    int i = find(x);
    int j = find(y);
    if (i == j) return;
    
    int sub;
    if (rank[i] > rank[j])
    {
      parent[j] = i;
      roots.erase(j);
    }
    else
    {
      parent[i] = j;
      roots.erase(i);
      if (rank[i] == rank[j])
        ++rank[j];
    }
  }
  
  unsigned int num_clusters()
  {
    return roots.size();
  }

  private:
  vector<int> parent;
  vector<int> rank;
  set<int> roots;
};

double distance(int x1, int y1, int x2, int y2)
{
  return sqrt( pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void get_edges(vector<int> &x, vector<int> &y, multimap<double, pair<int, int>> &edges)
{
  for (int i = 0; i < x.size(); ++i)
  {
    for (int j = i+1; j < x.size(); ++j)
    {
      double dist = distance(x[i], y[i], x[j], y[j]);
      edges.insert(std::make_pair(dist, std::make_pair(i,j)));
    }
  }
}

double clustering(vector<int> x, vector<int> y, int k) {
  disjoint_set ds(x.size());
  multimap<double, pair<int, int>> edges;
  get_edges(x, y, edges);

  auto edge_it = edges.begin();
  while (ds.num_clusters() > k)
  {
    pair<double, pair<int,int>> e = *edge_it; *edges.begin();
    edges.erase(edges.begin());
    ds.merge(e.second.first, e.second.second);
    ++edge_it;
  }

  double min = std::numeric_limits<double>::max();
  for (auto edge : edges)
  {
    if (ds.find(edge.second.first) != ds.find(edge.second.second) && edge.first < min)
      min = edge.first;
  }
  // for (size_t i = 0; i < x.size(); ++i)
  // {
  //   for (size_t j = 0; j < x.size(); ++j)
  //   {
  //     if (ds.find(i) != ds.find(j))
  //     {
  //       double dist = distance(x[i], y[i], x[j], y[j]);
  //       if (dist < min) min = dist;
  //     }
  //   }
  // }
  return min;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
