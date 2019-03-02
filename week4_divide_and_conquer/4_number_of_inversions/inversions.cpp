#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;


//This algorithm uses a recursive merge sort implementation. Every time a sort takes place
//we count that as an inversion
//Technically only need to return #inversions, but also returns the sorted array
long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;

  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);
  //write your code here
  size_t i = left;
  size_t j = ave;
  size_t k = left;
  for (; k < right && i < ave && j < right; ++k)
  {
    if (a[i] <= a[j])
    {
      b[k] = a[i++];
    }
    else
    {
      //add one for each element still in the "left" side.
      //We know if we're inverting the first element, everything after it is also an inversion so count those
      number_of_inversions += (ave - i);
      b[k] = a[j++];
    }
  }
  //Maybe there's a more elegant way to do this?
  if(i == ave)
  {
    //move rest of j;
    for(; j < right; ++j, ++k)
      b[k] = a[j];
  }
  else
  {
    //move rest of i
    for(; i < ave; ++i, ++k)
    {
      b[k] = a[i];
    }
  }

  //Using B to sort so after sorting swap the sorted sequence back into A
  std::swap_ranges(a.begin()+left, a.begin()+right, b.begin()+left);
  
  return number_of_inversions;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
