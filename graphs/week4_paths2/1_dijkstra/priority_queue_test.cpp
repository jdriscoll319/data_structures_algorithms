#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

int main()
{
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>> pq;

  pq.push(std::make_pair(1,10));


  return 0;
}
