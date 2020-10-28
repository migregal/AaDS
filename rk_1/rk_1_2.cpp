#include <iostream>
#include <cassert>
#include <vector>

const int initialSize = 256;

class stack_t
{
public:
    void push(char element);

    char pop();

    bool empty();

private:
    std::vector<char> vec;
};

void stack_t::push(char element)
{
    vec.push_back(element);
}

char stack_t::pop()
{
    assert(vec.size() > 0);

    char res = vec[vec.size() - 1];
    vec.pop_back();

    return res;
}

bool stack_t::empty()
{
    return (0 == vec.size());
}

int main()
{
    char *string = new char[20000];
    char c = 0;
    int length = 0;

    while (std::cin >> c)
    {
        string[length++] = c;
    }

    length /= 2;

    int j = 0;
    stack_t stack;

    for (int i = 0; i < length; ++i)
    {
        if (string[i] == string[length + j])
        {
            ++j;
            continue;
        }

        if (stack.empty())
        {
            stack.push(string[i]);
            continue;
        }

        c = stack.pop();
        if (string[length + j] == c)
        {
            ++j;
            --i;
            continue;
        }

        stack.push(c);
        stack.push(string[i]);
    }

    while (!stack.empty())
    {
        if (string[length + j] == stack.pop())
        {
            ++j;
            continue;
        }

        std::cout << "NO\n";

        delete[] string;
        return 0;
    }

    std::cout << "YES\n";
    delete[] string;

    return 0;
}
