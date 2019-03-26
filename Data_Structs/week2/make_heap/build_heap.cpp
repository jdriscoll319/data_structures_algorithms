#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int parent(const int idx)
  {
    return (idx - 1)/2;
  }

  int l_child(const int idx)
  {
    return idx * 2 + 1;
  }

  int r_child(const int idx)
  {
    return idx * 2 + 2;
  }

  bool valid_node(const int idx)
  {
    return idx >= 0 && idx < data_.size();
  }

  int min_child(const int left, const int right)
  {
    bool has_left = valid_node(left);
    bool has_right = valid_node(right);
    
    if(has_left && has_right)
    {
      int min_val = std::min(data_[left], data_[right]);
      return (min_val == data_[left]) ? left : right;
    }
    else if (has_left)
      return left;
    else if (has_right)
      return right;
    else
      return -1;
    
  }

  void sift_down(int idx)
  {
    int parent, left_child, right_child;
    parent = idx;

    while (parent <= data_.size()/2 - 1)
    {
      int parent_val = data_[parent];

      int left_child = l_child(parent);

      int right_child = r_child(parent);

      int min = min_child(left_child, right_child);
      // std::cout << "Current index, value: " << parent << ' ' << data_[parent] << "\n";
      // std::cout << "left_child index, value: " << left_child << ' ' << data_[left_child] << "\n";
      // std::cout << "right_child index, value: " << right_child << ' ' << data_[right_child] << "\n";

      if (min == -1)
        return;
      else if (data_[parent] > data_[min])
      {
        swap(data_[parent], data_[min]);
        swaps_.push_back( make_pair(parent, min) );
        parent = min;
      }
      else
        return;
      

      // if (has_left && parent_val > left_val && 
      //     (!valid_node(right_child) || left_val <= right_val))
      // {
      //   // std::cout << "Swapping left\n";
      //   swap(data_[parent], data_[left_child]);
      //   swaps_.push_back( make_pair(parent, left_child) );
      //   parent = left_child;
      // }
      // else if (valid_node(right_child) && parent_val > right_val && 
      //           (valid_node(left_child) || right_val <= left_val))
      // {
      //   // std::cout << "Swapping right\n";
      //   swap(data_[parent], data_[right_child]);
      //   swaps_.push_back( make_pair(parent, right_child) );
      //   parent = right_child;
      // }
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    // for (int i = 0; i < data_.size(); ++i)
    //   for (int j = i + 1; j < data_.size(); ++j) {
    //     if (data_[i] > data_[j]) {
    //       swap(data_[i], data_[j]);
    //       swaps_.push_back(make_pair(i, j));
    //     }
    //   }
    for (int i = data_.size()/2 - 1; i >= 0; --i)
    {
      sift_down(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
