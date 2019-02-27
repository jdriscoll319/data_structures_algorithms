#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) {
    std::cout << "returning -1\n";
    return -1; //size 0
  }
  if (left + 1 == right) 
  {
    std::cout << "returning: " << a[left] << "\n";
    return a[left]; //size 1.
  }
  //write your code here
  int mid = left + (right - left) / 2;
  std::cout << "Mid: " << mid << "\n";//Mid val: " << a[mid] << "\n";

  std::cout << "Calling left branch with: " << left << mid << "\n";
  int left_val = get_majority_element(a, left, mid );
  std::cout << "Left branch val: " << left_val << "\n";
  std::cout << "Calling right branch with: " << mid << right << "\n";
  int right_val =  get_majority_element(a, mid, right);
  std::cout << "Right branch val: " << right_val << "\n";
  std::cout << "comparing: " << left_val << " and " << right_val << "\n";
  if ( left_val != -1  &&
       right_val != -1 && 
       left_val == right_val)
  {
    // if (val == a[left+1])
    return left_val;
    // else
    //   return -1;
  }

  // if ( val != -1 )
  // {
  //   if (val == a[left+1])
  //     return val;
  //   // else
  //   //   return -1;
  // }

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
}
