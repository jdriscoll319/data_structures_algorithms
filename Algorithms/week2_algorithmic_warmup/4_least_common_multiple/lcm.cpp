#include <iostream>
#include <algorithm>
#include <map>
#include <array>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd_fast(int a, int b)
{
  if (b == 0)
    return a;

  gcd_fast(b, a%b);
}

long long lcm_fast(int a, int b) {

  int gcd = gcd_fast(a, b);

  return (long long) a * b / gcd;

  // int max = std::max(a, b);
  // int min = std::min(a, b);
  // for (long long l = max; l <= (long long) a * b; l += max)
  //   if (l % min == 0)
  //     return l;

  // return (long long) a * b;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
