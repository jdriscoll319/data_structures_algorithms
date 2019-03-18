#include <iostream>
#include <string>
#include <vector>

using std::string;

int edit_distance(const string &str1, const string &str2) {
  //write your code here
  std::vector<std::vector<int>> edit_table(str1.size()+1, std::vector<int>(str2.size()+1));
  edit_table[0][0] = 0;
  //prefill first row and first column
  for(size_t i = 1; i <= str1.size(); ++i)
    edit_table[i][0] = i;
  for(size_t i = 1; i <= str2.size(); ++i)
    edit_table[0][i] = i;

  for(size_t i = 1; i <= str1.size(); ++i)
  {
    for (size_t j = 1; j <= str2.size(); ++j)
    {
      int up = edit_table[i-1][j] + 1;
      int left = edit_table[i][j-1] + 1;
      int diag = edit_table[i-1][j-1] + (str1[i-1] != str2[j-1]);

      edit_table[i][j] = std::min(up, std::min(left, diag));
    }
  }
  
  return edit_table.back().back();
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
