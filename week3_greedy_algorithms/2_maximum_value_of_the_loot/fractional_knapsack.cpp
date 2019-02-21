#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::vector;

bool sort_func(std::pair<int, int> i, std::pair<int, int> j)
{
  return (i.first / double(i.second)) > (j.first / double(j.second));
}

std::vector<std::pair<int,int>> sort_items(vector<int> &weights, vector<int> &values)
{
  std::vector<std::pair<int, int>> combined;

  for (size_t i = 0; i < weights.size(); ++i)
    combined.push_back(std::pair<int, int>(values[i],weights[i]));
  
  std::sort(combined.begin(), combined.end(), sort_func);

  // for (auto item : combined)
  //   std::cout << item.first << " " << item.second <<  "\n";

  return combined;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;

  // write your code here
  std::vector<std::pair<int, int>> combined = sort_items(weights, values);

  size_t item = 0;
  double available = (double)capacity;

  while (available > 0 && item < combined.size())
  {
    // std::cout << "Current item: " << item << "\n";
    // std::cout << "Item value: " << combined[item].first << "\n";
    // std::cout << "Available space: " << available << "\n";
    if(combined[item].second < available)
    {
      value += (double)combined[item].first;
      available -= (double)combined[item].second;
      // std::cout << "adding " << (double)combined[item].first << "\n";
      // std::cout << "fit whole item, value is now: " << value << "\n";
      // std::cout << "available is now: " << available << "\n";
    }
    else
    {
      value += (available * ((double)combined[item].first / (double)combined[item].second));
      available = 0;
      // std::cout << "adding " << available * ((double)combined[item].first / (double)combined[item].second) << "\n";
      // std::cout << "fit partial item, value is now: " << value << "\n";
      // std::cout << "available is now: " << available << "\n";
    }
    ++item;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
