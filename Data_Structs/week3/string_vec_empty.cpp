#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::vector<std::string> strings(5);

  for(auto s : strings)
    std::cout << s << "\n";

  return 0;
}
