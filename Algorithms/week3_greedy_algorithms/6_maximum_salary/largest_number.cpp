#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <random>

using std::vector;
using std::string;

bool compare(string a, string b)
{
  // if(a.size() == b.size())
  //   return a >= b;

  string a_b = a + b;
  string b_a = b + a;

  return a_b >= b_a;

  // while(a.size() < b.size())
  //   a += a[0];
  // while(a.size() > b.size())
  //   b += b[0];
  
  // for(size_t i = 0; i < a.size(); ++i)
  // {
  //   std::cout << "comparing digits: " << a[i] << " " << b[i] << "\n";
  //   if( a[i] > b[i] )
  //     return true;
  //   else if( a[i] < b[i] )
  //     return false;
  // }

  // return true;
}

string largest_number(vector<string> a) {
  //write your code here
  std::stringstream ret;

  while (!a.empty())
  {
    string max = "0";
    for(auto digit : a)
    {
      // std::cout << "comparing " << digit << " " << max << "\n";
      if( compare(digit, max) )
      // if ( digit >= max )
        max = digit;
      // std::cout << "Max is " << max << "\n";
    }
    ret << max;
    a.erase( std::find(a.begin(), a.end(), max) );
  }
  // for (size_t i = 0; i < a.size(); i++) {
  //   ret << a[i];
  // }
  string result;
  ret >> result;
  return result;
}

void gen_vector(int n, vector<string> &a)
{
  std::default_random_engine gen;
  std::uniform_int_distribution<int> number(1, 1000);
  for (size_t i = 0; i < n; ++i) {
    a[i] = std::to_string(number(gen));
  }
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  // gen_vector(n, a);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
    // std::cout << a[i] << " ";
  }
  std::cout << "\n";
  std::cout << largest_number(a) << "\n";
}
