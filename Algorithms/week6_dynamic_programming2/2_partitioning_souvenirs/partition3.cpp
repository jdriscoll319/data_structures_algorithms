#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;

void unwind_and_remove(std::vector<int> &A, std::vector< std::vector<int> > &value_table, int cur_val)
{
  //figure out which numbers where used in the solution
  int col = value_table[value_table.size()-1].size()-1;
  for(size_t i = A.size(); i > 0; --i)
  {
    //column is not updating correctly
    int test_val = A[i-1];
    int test_col = col - test_val;
    if (test_col >= 0 && value_table[i-1][test_col] == cur_val - test_val)
    {
      // solution[i-1] = 1;
      cur_val -= test_val;
      col = test_col;
      //remove those numbers from A so we don't use them again
      A.erase(A.begin() + i - 1);
    }
  }
}

int partition3(vector<int> &A) {
  //write your code here
  //sum array and mod 3, divide by 3.
  //if mod 3 != 0, don't bother checking
  //sum / 3 is goal for each partition
  //Now this is just the knapsack problem with a twist
  //we have to keep track of what we've taken
  //Also we want to hit exactly our goal, not just the closest possible option
  int total = std::accumulate(A.begin(), A.end(), 0);
  if (total % 3 != 0)
    return 0;
  
  int goal = total / 3;

  //Not sure the logic behind it, but this doesn't work unless you sort
  std::sort(A.begin(), A.end());

  //Knapsack twice
  for(size_t part = 0; part < 2; ++  part)
  {
    std::vector< std::vector<int> > value(A.size() + 1, std::vector<int>(goal + 1));
    for (size_t i = 0; i <= goal; ++i)
      value[0][i] = 0;
    for (size_t i = 0; i <= A.size(); ++i)
      value[i][0] = 0;

    for (size_t i = 1; i <= A.size(); ++i)
    {
      for (size_t j = 1; j <= goal; ++j)
      {
        value[i][j] = value[i-1][j];
        if(A[i-1] <= j)
        {
          int val = value[i-1][j - A[i-1]] + A[i-1];
          if (value[i][j] < val)
            value[i][j] = val;
        }
      }
    }
    if (value.back().back() != goal)
      return 0;
    
    unwind_and_remove(A, value, goal);
  }
  //If we've successfully knapsacked twice and there is a solution, everything left should sum up to 1/3 total
  if (std::accumulate(A.begin(), A.end(), 0) == goal)
    return 1;

  return 0;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
