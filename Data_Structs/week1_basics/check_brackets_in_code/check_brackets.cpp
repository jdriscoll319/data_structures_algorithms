#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket bracket(next, position+1);
            opening_brackets_stack.push(bracket);
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.empty())
            {
                // std::cout << position+1 << "\n";
                opening_brackets_stack.push(Bracket(next, position+1));
                break;
            }
            Bracket open = opening_brackets_stack.top();
            if (!open.Matchc(next))
            {
                // std::cout << open.position << "\n";
                opening_brackets_stack.push(Bracket(next, position+1));
                break;
            }
            opening_brackets_stack.pop();
        }
    }
    // Printing answer, write your code here
    if (opening_brackets_stack.empty())
        std::cout << "Success\n";
    else
        std::cout << opening_brackets_stack.top().position << "\n";

    return 0;
}
