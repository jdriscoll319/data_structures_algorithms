#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> pq = {10,20,30,40};
  std::make_heap(pq.begin(), pq.end(), std::greater<int>());

  for (int i : pq)
    std::cout << i << ' ';
  std::cout << "\n";

  std::pop_heap(pq.begin(), pq.end(), std::greater<int>());
  for (int i : pq)
    std::cout << i << ' ';
  std::cout << "\n";

  return 0;
}
