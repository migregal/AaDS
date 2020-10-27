/*
 * Binary MSD для long long.
 *
 * Дан массив неотрицательных целых 64-разрядных чисел.
 * Количество чисел не больше 10^6.
 * Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/

#include <iostream>
#include <stdio.h>
#include <stdint.h>

#include <cassert>
#include <cstring>

#define BITSWORD 63

typedef unsigned long long ull;

inline bool digit(ull numbers, int idx)
{
    return numbers & ((ull)1 << idx);
}

void msd_qsort(ull *a, int first, int last, int word)
{
    int i = first;
    int j = last;

    if (last <= first || word < 0)
        return;

    while (j != i)
    {
        while (!digit(a[i], word) && (i < j))
            ++i;

        while (digit(a[j], word) && (j > i))
            --j;

        std::swap(a[i], a[j]);
    }

    if (!digit(a[last], word))
        ++j;

    msd_qsort(a, first, j - 1, word - 1);
    msd_qsort(a, j, last, word - 1);
}

int main(void)
{
    int size = 0;

    std::cin >> size;

    assert(size > 0);

    ull *numbers = new ull[size];

    for (int i = 0; i < size; ++i)
        std::cin >> numbers[i];

    msd_qsort(numbers, 0, size - 1, BITSWORD);

    for (int i = 0; i < size; ++i)
        std::cout << numbers[i] << " ";

    std::cout << std::endl;

    delete[] numbers;
}
