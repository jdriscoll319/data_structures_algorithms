#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

std::vector<int> unwind(const std::vector<int> &a, const std::vector<int> a_len, int pos)
{
  // std::cout << "Unwinding\n";
  // std::cout << "pos: " << pos << "\n";
  std::vector<int> sequence;
  sequence.push_back(a[pos]);
  size_t current = pos;
  for(int i = pos-1; i >= 0; --i)
  {
    // std::cout << "Looping...\n";
    if (a_len[i] < a_len[current])
    {
      sequence.push_back(a[i]);
      current = i;
    }
  }

  std::reverse(sequence.begin(), sequence.end());
  // for (auto i : sequence)
  //   std::cout << i << ' ';
  // std::cout << "\n";
  return sequence;
}

int lcs2(const vector<int> &a, const vector<int> &b) {
  //write your code here

  //I think I can't search each array separately
  //Need to search them simultaneously
  //Inputs can be -,0,+ so can't pad them out to be the same size.
  //Triple nested forloop? Maybe markers tracking position?
  std::vector<int> a_len(a.size()), b_len(b.size());

  for(size_t i = 0; i < a.size(); ++i)
  {
    a_len[i] = 1;
    for(size_t j = 0; j < i; ++j)
    {
      if(a[j] < a[i] && a_len[i] < a_len[j]+1)
        a_len[i] = a_len[j]+1;
    }
  }
  // for (auto i : a_len)
  //   std::cout << i << ' ';
  // std::cout << "\n";

  for(size_t i = 0; i < b.size(); ++i)
  {
    b_len[i] = 1;
    for(size_t j = 0; j < i; ++j)
    {
      if(b[j] < b[i] && b_len[i] < b_len[j]+1)
        b_len[i] = b_len[j]+1;
    }
  }
  // for (auto i : b_len)
  //   std::cout << i << ' ';
  // std::cout << "\n";

  // std::cout << "Finished checking a and b separately\n";

  int max = 0;
  for(size_t i = 0; i < a.size(); ++i)
  {
    for(size_t j = 0; j < b.size(); ++j)
    {
      if(a_len[i] == b_len[j])
      {
        //check for match
        // std::cout << "found a length match: " << a_len[i] << "\n";
        std::vector<int> a_seq = unwind(a, a_len, i);
        std::vector<int> b_seq = unwind(b, b_len, j);
        if (a_seq == b_seq && a_len[i] > max)
          max = a_len[i];
      }
    }
  }

  return max;
  // return *std::max_element(len.begin(), len.end());
  // return std::min(a.size(), b.size());
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
