#include <iostream>
#include <algorithm>
#include <vector>

bool comp(int i, int j)
{
  return (i < j && j > 0);
}

int main()
{
  std::vector<int> vec = {0,1,2,3,4,5};
  std::cout << "Min element: " << *std::min_element(vec.begin(), vec.end()) << "\n";
  std::cout << "Min element > 0: " << *std::min_element(vec.begin(), vec.end(), comp) << "\n";
  return 0;
}
