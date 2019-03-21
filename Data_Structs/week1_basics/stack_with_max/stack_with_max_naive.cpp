#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
    vector<int> max_stack;
    int max = -1;

  public:

    void Push(int value) {
        stack.push_back(value);
        //if we have a new max value update our current max
        //we only need to track new max values. If lower values are added later, the max will still be the max
        if(value >= max)
        {
            max = value;
            max_stack.push_back(value);
        }
    }

    void Pop() {
        assert(stack.size());
        assert(max_stack.size());
        if(max_stack.back() == stack.back())
            max_stack.pop_back();
        max = max_stack.back();
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        //this is faster than always accessing the back of max_stack
        //also lower memory
        return max;
        // return max_stack.back();
        // return *max_element(stack.begin(), stack.end());
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}