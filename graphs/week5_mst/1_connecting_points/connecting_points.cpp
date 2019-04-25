#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <numeric>

using std::vector;
using std::pair; using std::make_pair;
using std::make_heap; using std::pop_heap; using std::push_heap;
using std::greater;

// Because we're only given nodes an no connections we need to do Prim's
// Kruskals means we need to assume every node is connected to every other node
//    which means worst case provided by problem is dealing with 39800 edges...oof
//    This is wrong, forgot to divide by two... there are 39800/2 = 19900 edges, still a lot

bool find(size_t target, vector<pair<double, int>> &pri_q)
{
  for (auto node : pri_q)
    if (node.second == target) return true;

  return false;
}

void change_priority(vector<pair<double, int>> &pri_q, int node, double cost)
{
  auto it = pri_q.begin();
  while (it->second != node) ++it;
  it->first = cost;
  make_heap(pri_q.begin(), pri_q.end(), greater<pair<double, int>>());
}

vector<double> get_edges(vector<int> &x, vector<int> &y, int root)
{
  vector<double> edges;
  for (size_t i = 0; i < x.size(); ++i)
  {
    double dist = sqrt( pow(x[i] - x[root], 2) + pow(y[i] - y[root], 2) );
    edges.push_back(dist);
  }
  
  return edges;
}

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;

  vector<double> cost(x.size(), std::numeric_limits<int>::max());
  cost[0] = 0;
  //pair is (cost, node_idx)
  vector<pair<double, int>> pri_q;
  for (int i = 0; i < x.size(); ++i)
    pri_q.push_back(make_pair(cost[i], i));
  make_heap(pri_q.begin(), pri_q.end(), greater<pair<double,int>>());

  while (!pri_q.empty())
  {
    pair<int, int> v = pri_q.front();
    pop_heap(pri_q.begin(), pri_q.end(), greater<pair<double, int>>()); pri_q.pop_back(); 
    vector<double> edges = get_edges(x, y, v.second);
    for (size_t z = 0; z < edges.size(); ++z)
    {
      if (find(z, pri_q) && cost[z] > edges[z])
      {
        cost[z] = edges[z];
        change_priority(pri_q, z, cost[z]);
      }
    }
  }

  result = std::accumulate(cost.begin(), cost.end(), 0.);
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
