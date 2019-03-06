#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>

using std::vector;

bool compare(std::vector<int> a, std::vector<int> b)
{
  size_t a_size = a.size();
  size_t b_size = b.size();
  if(a_size != 0 && b_size !=0)
    return a_size < b_size;
  else
    return a_size > b_size;
}

// bool compare(const std::set<int> a, const std::set<int> b)
// {
//   size_t a_size = a.size();
//   size_t b_size = b.size();
//   if(a_size != 0 && b_size !=0)
//     return a_size < b_size;
//   else
//     return a_size > b_size;
// }

// std::vector<int> optimal_sequence_recursive(int n)
// {
//   // std::cout << "checking: " << n <<"\n";
//   std::vector<int> sequence;
//   if (n - 3 <= 0)
//   {
//     sequence = {1, n};
//     return sequence;
//   }

//   std::vector<int>div3, div2, sub1;

//   if (n % 3 == 0)
//   {
//     div3 = optimal_sequence_recursive(n/3);
//     // div3.push_back(n/3);
//   }
//   if (n % 2 == 0)
//   {
//     div2 = optimal_sequence_recursive(n/2);
//     // div2.push_back(n/2);
//   }
//   sub1 = optimal_sequence_recursive(n-1);
//   // sub1.push_back(n-1);

//   sequence = std::min(div3, std::min(div2, sub1, compare), compare);

//   sequence.push_back(n);

//   return sequence;
// }

std::vector<int> optimal_sequence_dp(int n)
{
  std::vector<int> sequence, seq_len(n+1), prev_val(n+1);
  // sequence[0] = 1;
  seq_len[0] = 0;
  seq_len[1] = 0;
  prev_val[0] = 0;
  prev_val[1] = 0;
  
  for (size_t i = 1; i <= n; ++i)
  {
    seq_len[i] = 10e6;
    // int val = i+1;

    for(int j = 3; j >= 1; --j)
    {
      if(j > 1)
      {
        if (i % j == 0)
        {
          // std::cout << "Checking " << i << " / " << j << "\n";
          if(seq_len[i / j] + 1 < seq_len[i])
          {
            seq_len[i] = seq_len[i / j] + 1;
            prev_val[i] = i / j;
          }
        }
      }
      else
      {
        if(seq_len[i - 1] + 1 < seq_len[i])
        {
          seq_len[i] = seq_len[i - 1] + 1;
          prev_val[i] = i - 1;
        }
      }
    }
    // std::cout << "New shortest seq: " << seq_len[i] << "\n";
    // std::cout << "Prev val: " << prev_val[i] << "\n";
  }

  // std::cout << "shortest seq vec: \n";
  // for (auto i : seq_len)
  //   std::cout << i << ' ';
  // std::cout << "\n";
  // std::cout << "prev val vec: \n";
  // for (auto i : prev_val)
  //   std::cout << i << ' ';
  // std::cout << "\n";

  // return sequence;

  while (n >= 1)
  {
    // std::cout << "adding: " << n << "\n";
    sequence.push_back(n);
    n = prev_val[n];
  }
  
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

// std::vector<int> optimal_sequence_dp(int n, std::set<int> &checked)
// {
//   //need to keep track of not only what we've checked but the best sequence so far
//   //if that is the case, then doesn't that mean we can do iterative starting from 1????
//   std::vector<int> sequence;
//   if (checked.find(n) == checked.end() && n >= 1)
//   {
//     checked.insert(n);
//     std::cout << "checking: " << n <<"\n";
//     std::vector<int> div3, div2, sub1;
//     if(n % 3 == 0)
//     {
//       div3 = optimal_sequence_dp(n/3, checked);
//       std::cout << "div3: ";
//       for (auto i : div3)
//         std::cout << i << ' ';
//       std::cout << "\n";
//     }
//     if(n % 2 == 0)
//     {
//       div2 = optimal_sequence_dp(n/2, checked);
//       std::cout << "div2: ";
//       for (auto i : div2)
//         std::cout << i << ' ';
//       std::cout << "\n";
//     }
//     sub1 = optimal_sequence_dp(n-1, checked);
//     std::cout << "sub1: ";
//     for (auto i : sub1)
//       std::cout << i << ' ';
//     std::cout << "\n";

//     std::vector<int> shortest = std::min(div3, std::min(div2, sub1, compare), compare);
//     shortest.push_back(n);
//     sequence.insert(sequence.end(), shortest.begin(), shortest.end());
//     std::cout << "Shortest: ";
//     for (auto i : shortest)
//       std::cout << i << ' ';
//     std::cout << "\n";
//     std::cout << "Sequence: ";
//     for (auto i : sequence)
//       std::cout << i << ' ';
//     std::cout << "\n";
//   }
//   return sequence;
// }

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());

  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  // vector<int> sequence = optimal_sequence_recursive(n);
  std::set<int> checked ={1};
  vector<int> sequence = optimal_sequence_dp(n);
  std::cout << sequence.size() - 1 << std::endl;
  // for (size_t i = 0; i < sequence.size(); ++i) {
  //   std::cout << sequence[i] << " ";
  // }
  for (auto i : sequence)
    std::cout << i << ' ';
  std::cout << "\n";
}
