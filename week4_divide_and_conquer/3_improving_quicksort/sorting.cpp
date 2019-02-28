#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <chrono>

size_t partition2(std::vector<int> &a, size_t left, size_t right)
{
  int pivot = a[left];
  size_t greater_pos = left + 1;
  for (size_t i = left + 1; i <= right; ++i)
  {
    if (a[i] <= pivot)
    {
      std::swap(a[i], a[greater_pos++]);
    }
  }
  std::swap(a[left], a[--greater_pos]);

  return greater_pos;
}

void partition3(std::vector<int> &a, size_t left, size_t right, size_t &ml, size_t &mr)
{
  int pivot = a[left];
  // std::cout << "Partitioning:\n   left: " << left << " | right: " << right << " | pivot: " << pivot << "\n";
  size_t eq_pos = left;
  size_t gt_pos = left + 1;
  for (size_t i = left + 1; i <= right; ++i)
  {
    if (a[i] < pivot)
    {
      std::swap(a[i], a[eq_pos++]);
      std::swap(a[i], a[gt_pos++]);
    }
    else if (a[i] == pivot)
    {
      std::swap(a[i], a[gt_pos++]);
    }
  }
  // std::swap(a[left], a[--eq_pos]);

  // for (auto val : a)
  //   std::cout << val << ' ';
  // std::cout << "\n";

  ml = eq_pos;
  mr = gt_pos;
}

void randomized_quick_sort(std::vector<int> &a, int left, int right)
{
  if (left > right)
    return;
  
  std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> distribution(left, right);
  size_t pivot = distribution(generator);
  // std::cout << "Left: " << left << " Right: " << right << "\n";
  // std::cout << "random pivot: " << pivot << ' ' << a[pivot] << "\n";

  std::swap(a[left], a[pivot]);

  size_t ml, mr;

  // size_t mid = partition2(a, left, right);
  partition3(a, left, right, ml, mr);
  // std::cout << "sorting left\n";
  randomized_quick_sort(a, left, ml -1);
  // std::cout << "sorting right\n";
  randomized_quick_sort(a, mr, right);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
  std::cout << "\n";
}