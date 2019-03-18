#include <iostream>
#include <vector>

int main()
{
  std::vector< std::vector<int> > vec(10, std::vector<int>(5));

  std::cout << vec[vec.size()-1].size() << "\n";

  return 0;
}
