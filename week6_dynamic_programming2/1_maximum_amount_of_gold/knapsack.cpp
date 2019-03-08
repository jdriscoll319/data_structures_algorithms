#include <iostream>
#include <vector>
#include <limits>

using std::vector;

int optimal_weight_dp(int W, const vector<int> &w)
{
  std::vector< std::vector<int> > value(w.size() + 1, std::vector<int>(W + 1));
  for (size_t i = 0; i <= W; ++i)
    value[0][i] = 0;
  for (size_t i = 0; i <= w.size(); ++i)
    value[i][0] = 0;

  for (size_t i = 1; i <= w.size(); ++i)
  {
    for (size_t j = 1; j <= W; ++j)
    {
      value[i][j] = value[i-1][j];
      if(w[i-1] <= j)
      {
        int val = value[i-1][j - w[i-1]] + w[i-1];
        if (value[i][j] < val)
          value[i][j] = val;
      }
    }
  }

  // for (auto i : value)
  // {
  //   for (auto j : i)
  //     std::cout << j << ' ';
  //   std::cout << "\n";
  // }

  return value.back().back();

}

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  int current_weight = 0;
  for (size_t i = 0; i < w.size(); ++i) {
    if (current_weight + w[i] <= W) {
      current_weight += w[i];
    }
  }
  return current_weight;
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight_dp(W, w) << '\n';
  // std::cout << optimal_weight(W, w) << '\n';
}
