#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <random>

using std::vector;

struct Segment {
  int start, end;
};

bool comparison(Segment seg1, Segment seg2)
{
  if (seg1.end == seg2.end)
    return seg1.start < seg2.start;

  return seg1.end < seg2.end;
}

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here
  std::sort(segments.begin(), segments.end(), comparison);

  // std::cout << "Sorted: \n";
  // for (auto item : segments)
  //   std::cout << "   " << item.start << " " << item.end <<  "\n";
  // std::cout << "\n\n";

  vector<int> marked(segments.size(), 0);

  for (size_t i = 0; i < segments.size(); ++i) {
    if(marked[i] == 0)
    {
      int cur_time = segments[i].end;
      points.push_back(cur_time);
      marked[i] = 1;
      for(int check_seg = i+1; check_seg < segments.size() && segments[check_seg].start <= cur_time; ++check_seg)
        marked[check_seg] = 1;
    }
  }
  return points;
}

void rand_inputs(int n, vector<Segment> &segs)
{
  std::default_random_engine gen;
  std::uniform_int_distribution<int> start(1, 10);
  std::uniform_int_distribution<int> seg_len(1, 5);
  for (size_t i = 0; i < segs.size(); ++i) {
    int start_time = start(gen);
    segs[i].start = start_time;
    segs[i].end = start_time + seg_len(gen);
  }
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }

  // rand_inputs(n, segments);

  // std::cout << "Input: \n";
  // for (auto item : segments)
  //   std::cout << "   " << item.start << " " << item.end <<  "\n";
  // std::cout << "\n\n";

  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
  std::cout << "\n";
}
