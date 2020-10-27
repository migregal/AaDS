/*
 * Решение всех задач данного раздела предполагает использование кучи,
 * реализованной в виде класса.
 *
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * Куча должна быть динамической.
 *
 * Тупики.
 *
 * На вокзале есть некоторое количество тупиков, куда прибывают электрички.
 * Этот вокзал является их конечной станцией.
 *
 * Дано расписание движения электричек,
 * в котором для каждой электрички указано время ее прибытия,
 * а также время отправления в следующий рейс.
 *
 * Электрички в расписании упорядочены по времени прибытия.
 * Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
 * При этом если электричка из какого-то тупика отправилась в момент времени X,
 * то электричку, которая прибывает в момент времени X,
 * в этот тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
 *
 * В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
 * Напишите программу, которая по данному расписанию определяет,
 * какое минимальное количество тупиков требуется для работы вокзала.
 *
 * Формат входных данных. Вначале вводится n - количество электричек в расписании.
 * Затем вводится n строк для каждой электрички,
 * в строке - время прибытия и время отправления.
 *
 * Время - натуральное число от 0 до 10^9.
 * Строки в расписании упорядочены по времени прибытия.
 *
 * Формат выходных данных. Натуральное число - минимальное количеством тупиков.
 *
 * Максимальное время: 50мс, память: 5Мб.
*/

#include <iostream>
#include <cassert>

typedef std::pair<int, int> stop;

/* <--------- DEQUE CLASS --------->*/

template <class T>
class deque
{
public:
    deque();
    ~deque();
    size_t size(void) { return len; };
    T pop_front(void);
    void push_back(const T &);
    T &operator[](std::size_t idx) { return buf[(begin + idx) % buf_cap]; }
    const T &operator[](std::size_t idx) const { return buf[(begin + idx) % buf_cap]; }

private:
    size_t begin, len, buf_cap;
    T *buf;
};

/* <--------- HEAP CLASS --------->*/

template <class T>
class Heap
{
public:
    Heap(){};
    ~Heap(){};
    size_t size(void);
    T pop_front(void);
    T top(void);

    void add(const T &);

private:
    deque<T> dec;
    void swap(size_t, size_t);

    void SiftUp(size_t);
    void SiftDown(size_t);
};

/* <--------- MAIN FUNCS --------->*/

inline bool is_after(int stop_end, stop &b)
{
    return stop_end < b.first;
}

template <class T, class comp>
size_t dead_ends_count(Heap<T> &heap, comp comparator)
{

    Heap<int> dead_ends;

    while (heap.size() > 0)
    {
        stop temp = heap.pop_front();

        if (dead_ends.size() > 0 && comparator(dead_ends.top(), temp))
            dead_ends.pop_front();

        dead_ends.add(temp.second);
    }

    return dead_ends.size();
}

int main(void)
{
    int n;

    std::cin >> n;

    assert(n > 0);

    Heap<stop> heap;

    for (int i = 0, b, e; i < n; ++i)
    {
        std::cin >> b >> e;

        heap.add(stop(b, e));
    }

    std::cout << dead_ends_count(heap, is_after) << std::endl;
}

/* <--------- HEAP FUNCS --------->*/

template <class T>
size_t Heap<T>::size(void)
{
    return dec.size();
}

template <class T>
T Heap<T>::pop_front(void)
{
    T res = dec.pop_front();

    SiftDown(0);

    return res;
}

template <class T>
T Heap<T>::top(void)
{
    return dec[0];
}

template <class T>
void Heap<T>::SiftDown(size_t idx)
{
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    int smallest = idx;
    if (left < dec.size() && dec[left] < dec[idx])
        smallest = left;
    if (right < dec.size() && dec[right] < dec[smallest])
        smallest = right;

    if (smallest != idx)
    {
        swap(idx, smallest);
        SiftDown(smallest);
    }
}

template <class T>
void Heap<T>::SiftUp(size_t idx)
{
    for (int parent = 0; idx > 0; idx = parent)
    {
        parent = (idx - 1) / 2;

        if (dec[idx] < dec[parent])
            swap(idx, parent);
    }
}

template <class T>
void Heap<T>::add(const T &Data)
{
    dec.push_back(Data);

    SiftUp(dec.size() - 1);
}

template <class T>
void Heap<T>::swap(size_t i, size_t j)
{
    T temp = dec[i];
    dec[i] = dec[j];
    dec[j] = temp;
}

/* <--------- DEQUE FUNCS --------->*/

template <class T>
deque<T>::deque() : len(0), begin(0), buf_cap(1)
{
    buf = new T[buf_cap];
}

template <class T>
deque<T>::~deque()
{
    delete[] buf;
}

template <class T>
T deque<T>::pop_front(void)
{
    T res = buf[begin % buf_cap];

    if ((len - 1) < buf_cap / 2 && buf_cap > 1)
    {
        T *temp = new T[(buf_cap / 2)];

        for (size_t i = 1; i < len; ++i)
            temp[i - 1] = buf[(i + begin) % buf_cap];

        delete[] buf;
        buf = temp;

        buf_cap /= 2;
        begin = 0;
    }
    else
        begin++;

    len--;
    return res;
}

template <class T>
void deque<T>::push_back(const T &data)
{
    if (len == buf_cap)
    {
        T *temp = new T[buf_cap * 2];

        for (size_t i = 0; i < len; ++i)
            temp[i] = buf[(i + begin) % buf_cap];

        delete[] buf;
        buf = temp;

        buf_cap *= 2;
        begin = 0;
    }

    size_t back_idx = (begin + len) % buf_cap;
    buf[back_idx] = data;
    len++;
}
