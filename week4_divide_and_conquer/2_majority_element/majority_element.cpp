#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right)
    return -1; //size 0

  if (left + 1 == right) 
    return a[left]; //size 1.

  //write your code here
  int mid = left + (right - left) / 2;

  int left_val = get_majority_element(a, left, mid );
  if ( left_val != -1 ) 
  {
    int l_count = 0;
    for(size_t i = left; i < right; ++i)
    {
      if (a[i] == left_val)
      {
        ++l_count;
        if (l_count > (right - left)/2)
          return left_val;
      }
    }
  }

  int right_val =  get_majority_element(a, mid, right);
  if ( right_val != -1 ) 
  {
    int r_count = 0;
    for(size_t i = left; i < right; ++i)
    {
      if (a[i] == right_val)
      {
        ++r_count;
        if( r_count > (right - left)/2)
          return right_val;
      }
    }
  }

  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';

  return 0;
}
