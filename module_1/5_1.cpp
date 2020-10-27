/*
 * Во всех задачах данного раздела необходимо реализовать
 * и использовать сортировку слиянием.
 * Общее время работы алгоритма O(n log n).
 *
 * Реклама
 *
 * В супермаркете решили оптимизировать показ рекламы.
 * Известно расписание прихода и ухода покупателей (два целых числа).
 * Каждому покупателю необходимо показать минимум 2 рекламы.
 * Рекламу можно транслировать только в целочисленные моменты времени.
 * Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
 * В каждый момент времени может показываться только одна реклама.
 * Считается, что реклама показывается мгновенно.
 * Если реклама показывается в момент ухода или прихода, то считается,
 * что посетитель успел её посмотреть.
 *
 * Требуется определить минимальное число показов рекламы.
 */

#include <iostream>
#include <cstring>
#include <cassert>

/* <--------- VISITOR CLASS --------->*/

struct visitor
{
    int32_t in;
    int32_t out;
    int32_t adv_count;

    visitor(int32_t time_in, int32_t time_out) : in(time_in), out(time_out), adv_count(0) {}

    visitor() : in(0), out(0), adv_count(0) {}

    bool operator<(const visitor &) const;
};

bool visitor::operator<(const visitor &other) const
{
    if (out < other.out)
        return true;

    if (out == other.out)
        return in > other.in;

    return false;
}

bool compare_visitors(const visitor &v1, const visitor &v2)
{
    return v1 < v2;
}

/* <--------- QUEUE CLASS --------->*/

template <class T>
class queue
{
public:
    explicit queue(int32_t n) : arr(new T[n]), m_size(0) {}

    ~queue()
    {
        delete[] arr;
    }

    queue &operator=(const queue &);

    void add(T);
    void merge_sort(int32_t, int32_t, bool (*)(const T &, const T &));
    int32_t adv_counter();

    size_t size() const
    {
        return m_size;
    }

private:
    T *arr;
    size_t m_size;
    void merge(int32_t, int32_t, int32_t, bool (*)(const T &, const T &));
    void adv_count_inc(int32_t, int32_t);
};

template <class T>
queue<T> &queue<T>::operator=(const queue &other)
{
    queue buf(other);
    *this = std::move(buf);
    return *this;
}

template <class T>
void queue<T>::add(T visitor)
{
    arr[m_size++] = visitor;
}

/* <--------- QUEUE MERGE SORT --------->*/

template <class T>
void queue<T>::merge_sort(int32_t b, int32_t e, bool (*isLess)(const T &, const T &))
{
    if (e - b == 1)
        return;

    int32_t mid = b + (e - b) / 2;

    merge_sort(b, mid, isLess);
    merge_sort(mid, e, isLess);

    merge(b, mid, e, isLess);
}

template <class T>
void queue<T>::merge(int32_t l, int32_t mid, int32_t r, bool (*isLess)(const T &, const T &))
{
    int32_t it_l = 0, it_r = 0;

    T *buf = new T[mid - l];
    memcpy(buf, arr + l, sizeof(T) * (mid - l));

    while (l + it_l < mid && mid + it_r < r)
    {
        // if (buf[it_l] < arr[mid + it_r])
        if (isLess(buf[it_l], arr[mid + it_r]))
        {
            arr[l + it_l + it_r] = buf[it_l];
            it_l++;
            continue;
        }

        arr[l + it_l + it_r] = arr[mid + it_r];
        it_r++;
    }

    for (; l + it_l < mid; ++it_l)
        arr[l + it_l + it_r] = buf[it_l];

    delete[] buf;
}

/* <--------- MAIN FUNCS --------->*/

template <class T>
void queue<T>::adv_count_inc(int32_t visitor, int32_t m)
{
    for (size_t i = visitor; i < size() && arr[i].in <= m; ++i)
        ++arr[i].adv_count;
}

template <class T>
int32_t queue<T>::adv_counter()
{
    int32_t ads = 0;
    for (size_t i = 0; i < size(); i++)
    {
        if (arr[i].adv_count == 0)
        {
            adv_count_inc(i, arr[i].out - 1);
            ads++;
        }
        if (arr[i].adv_count == 1)
        {
            adv_count_inc(i, arr[i].out);
            ads++;
        }
    }
    return ads;
}

int32_t main()
{
    size_t n = 0;
    std::cin >> n;

    assert(n > 0);

    queue<visitor> queue(n);

    for (size_t i = 0; i < n; ++i)
    {
        int32_t in = 0, out = 0;
        std::cin >> in >> out;

        visitor new_one(in, out);
        queue.add(new_one);
    }

    queue.merge_sort(0, n, compare_visitors);

    std::cout << queue.adv_counter() << std::endl;

    return 0;
}
