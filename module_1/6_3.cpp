/*
 * Даны:
 *  неотрицательные целые числа n,k
 *  массив целых чисел из [0..10^9] размера n.
 *
 * Требуется найти k-ю порядковую статистику,
 * т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1)
 * в отсортированном массиве.
 *
 * Требования:
 *  к дополнительной памяти: O(n).
 *  Среднее время работы: O(n).
 *  Должна быть отдельно выделенная функция partition.
 *  Рекурсия запрещена.
 *  Решение должно поддерживать передачу функции сравнения снаружи.
 *
 * Функцию Partition следует реализовывать
 * методом прохода двумя итераторами в одном направлении.
 *
 * Описание для случая прохода от начала массива к концу:
 *
 * Выбирается опорный элемент.
 * Опорный элемент меняется с последним элементом массива.
 * Во время работы Partition в начале массива содержатся элементы,
 * не бОльшие опорного.
 * Затем располагаются элементы, строго бОльшие опорного.
 * В конце массива лежат нерассмотренные элементы.
 * Последним элементом лежит опорный.
 *
 * Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 * Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 *
 * Шаг алгоритма.
 *
 * Рассматривается элемент, на который указывает j.
 * Если он больше опорного, то сдвигаем j.
 * Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 * В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 *
 * Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 * Функцию Partition реализуйте методом прохода
 * двумя итераторами от начала массива к концу.
*/

#include <iostream>

template <class T>
bool greater_then(T first, T second)
{
    return first > second;
}

template <class T, class comparator>
size_t partition(T *array, size_t left, size_t right, comparator compare)
{
    srand((unsigned int)time(0));

    size_t pivot = left + (size_t)rand() % (right - left);

    std::swap(array[pivot], array[right]);

    pivot = right;
    size_t i = left, j = left;

    while (j < pivot)
    {
        if (compare(array[j], array[pivot]))
        {
            j++;
            continue;
        }

        std::swap(array[j], array[i]);
        j++;
        i++;
    }

    std::swap(array[i], array[pivot]);

    return i;
}

template <class T, class comparator>
T k_statistics(T *array, size_t size, size_t index, comparator comp)
{
    size_t left = 0, right = size - 1, pivot = 0;

    while (left < right)
    {
        pivot = partition(array, left, right, comp);
        if (index > pivot)
            left = pivot + 1;

        if (index < pivot)
            right = pivot;

        if (index == pivot)
            break;
    }

    if ((left >= right) && (pivot + 1 == index))
        pivot++;

    return array[pivot];
}

int main(void)
{
    size_t size = 0, index = 0;

    std::cin >> size >> index;

    int *array = new int[size];

    for (size_t i = 0; i < size; i++)
        std::cin >> array[i];

    std::cout << k_statistics(array, size, index, greater_then<int>) << std::endl;

    delete[] array;
}
