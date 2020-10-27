/*
 * Во всех задачах из следующего списка следует написать
 * структуру данных, обрабатывающую команды push* и pop*.
 *
 * Формат входных данных.
 *
 * В первой строке количество команд n. n ≤ 1000000.
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 *
 * Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
 * Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
 * Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
 *
 * Формат выходных данных.
 *
 * Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 *
 * Реализовать очередь с помощью двух стеков.
 * Использовать стек, реализованный с помощью динамического буфера.
 *
 * Требования:
 *
 * Очередь должна быть реализована в виде класса.
 * Стек тоже должен быть реализован в виде класса.
*/

#include <string.h>
#include <iostream>
#include <cassert>

/* <--------- VECTOR CLASS --------->*/

template <class T>
class vector
{
public:
    vector();
    ~vector();
    void push_back(const T &data);
    void pop_back(void);

    T back(void);

    bool empty(void) { return 0 == len; };

private:
    size_t cap, len;
    T *buf;
};

template <class T>
vector<T>::vector() : len(0), cap(1)
{
    buf = new T[cap];
}

template <class T>
vector<T>::~vector()
{
    delete[] buf;
}

template <class T>
void vector<T>::push_back(const T &data)
{
    if (len == cap)
    {
        T *temp = new T[(cap *= 2)];

        for (size_t i = 0; i < len; i++)
            temp[i] = buf[i];

        delete[] buf;
        buf = temp;
    }

    buf[len++] = data;
}

template <class T>
void vector<T>::pop_back(void)
{
    len--;

    if (len == cap / 2 && cap > 1)
    {
        T *temp = new T[(cap /= 2)];

        for (size_t i = 0; i < len; i++)
            temp[i] = buf[i];

        delete[] buf;
        buf = temp;
    }
}

template <class T>
T vector<T>::back(void)
{
    return buf[len - 1];
}

/* <--------- STACK CLASS --------->*/
template <class T>
class stack
{
private:
    int buffSize;
    vector<T> buff;

public:
    stack(int size = 1) {}

    ~stack(void) {}

    void push(T elem)
    {
        buff.push_back(elem);
    }

    T top()
    {
        return buff.back();
    }

    void pop()
    {
        buff.pop_back();
    }

    bool empty()
    {
        return buff.empty();
    }
};

/* <--------- QUEUE CLASS --------->*/
template <class T>
class queue
{

private:
    stack<T> first;
    stack<T> second;

public:
    void push(int elem)
    {
        first.push(elem);
    }

    T pop(void)
    {
        if (second.empty())
            while (!first.empty())
            {
                second.push(first.top());
                first.pop();
            }

        int res = second.top();
        second.pop();

        return res;
    }

    bool isEmpty(void)
    {
        return (first.empty() && second.empty());
    }
};

/* <--------- MAIN FUNCTIONAL --------->*/

bool expectedValue(int n)
{
    queue<int> a;

    int command = 0, value = 0;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> command >> value;

        if (command == 3)
        {
            a.push(value);
            continue;
        }

        if ((a.isEmpty() ? -1 : a.pop()) != value)
            return false;
    }

    return true;
}

int main(void)
{
    int n = 0;

    std::cin >> n;

    std::cout << (expectedValue(n) ? "YES" : "NO") << std::endl;
}
