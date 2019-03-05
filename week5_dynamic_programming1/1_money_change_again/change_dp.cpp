#include <iostream>
#include <vector>
#include <limits>   

int get_change(int m) {
  //write your code here
  std::vector<int> coins = {1, 3, 4};
  std::vector<int> min_num_coins(m+1, std::numeric_limits<int>::max());
  min_num_coins[0] = 0;
  //Start from the bottom and calculate the minimum number of coins needed. Then increment and use previous results to help calculate
  for(size_t i = 1; i <= m; ++i)
  {
    //Check each possible denomiation
    for (auto coin : coins)
    {
      //Skip denominations that are greater than the current amt we're looking at
      if (i >= coin)
      {
        //check number of coins needed for money amount equivalent to current denominations ago
        //i.e. checking denomination 6, check i-6;
        int num_coins = min_num_coins[i - coin] + 1;
        //if the new denomiation is better than previous, replace the count
        if (num_coins < min_num_coins[i])
          min_num_coins[i] = num_coins;
      }
    }
  }
  return min_num_coins[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
