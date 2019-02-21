#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  //write your code here
  int init = 1;
  while(n > 0)
  {
    if(init > n)
    {
      summands.back() += n;
      n = 0;
    }
    else
    {
      summands.push_back(init);
      n -= init;
      ++init;
    }
  }
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
  std::cout << "\n";
}
